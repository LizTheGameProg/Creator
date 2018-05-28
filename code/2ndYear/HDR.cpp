#include "HDR.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

HDR::HDR()
{

}

HDR::~HDR()
{

}

bool HDR::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// load model
	m_spear = new FBXFile();
	m_spear->load("../../Build/models/soulspear/soulspear.fbx", FBXFile::UNITS_CENTIMETER);
	createOpenGLBuffers(m_spear);
	
	{
		// load shader for spear
		unsigned int vs = Utility::loadShader("../../Build/shaders/normalMapped.vert", GL_VERTEX_SHADER);
		unsigned int fs = Utility::loadShader("../../Build/shaders/normalMapped.frag", GL_FRAGMENT_SHADER);
		m_shader = Utility::createProgram(vs,0,0,0,fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
	
		// bind never changing uniforms	
		glUseProgram(m_shader);
		int location = glGetUniformLocation(m_shader, "diffuseMap");
		glUniform1i(location, 0);
		location = glGetUniformLocation(m_shader, "specularMap");
		glUniform1i(location, 1);
		location = glGetUniformLocation(m_shader, "normalMap");
		glUniform1i(location, 2);
		glUseProgram(0);
	}

	// quad
	createFullScreenQuad();

	createFrameBuffer(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, &m_fbo, &m_fboTexture, &m_fboDepth);

	m_downsampledSize = glm::ivec2( DEFAULT_SCREENWIDTH / 4, DEFAULT_SCREENHEIGHT / 4 );
	
	createFrameBuffer(m_downsampledSize.x, m_downsampledSize.y, &m_downsampledFBO[0], &m_downsampledTexture[0],nullptr);
	createFrameBuffer(m_downsampledSize.x, m_downsampledSize.y, &m_downsampledFBO[1], &m_downsampledTexture[1],nullptr);

	// bright pass shader with a vertex shader for a quad
	unsigned int vs = Utility::loadShader("../../Build/shaders/fullscreen.vert", GL_VERTEX_SHADER);
	unsigned int bp = Utility::loadShader("../../Build/shaders/brightPass.frag", GL_FRAGMENT_SHADER);
	m_brightPassShader = Utility::createProgram(vs, 0, 0, 0, bp);
	glDeleteShader(bp);
	
	glUseProgram(m_brightPassShader);
	int location = glGetUniformLocation(m_brightPassShader, "originalMap");
	glUniform1i(location, 0);
	glUseProgram(0);

	// gaussian pass shader, shares vertex shader for quad
	unsigned int gb = Utility::loadShader("../../Build/shaders/gaussianBlur.frag", GL_FRAGMENT_SHADER);
	m_gaussianShader = Utility::createProgram(vs, 0, 0, 0, gb);
	glDeleteShader(gb);

	glUseProgram(m_gaussianShader);
	location = glGetUniformLocation(m_gaussianShader, "originalMap");
	glUniform1i(location, 0);
	glUseProgram(0);

	// bloom pass shader, shares vertex shader for quad
	unsigned int bl = Utility::loadShader("../../Build/shaders/bloom.frag", GL_FRAGMENT_SHADER);
	m_bloomShader = Utility::createProgram(vs, 0, 0, 0, bl);
	glDeleteShader(bl);
	glDeleteShader(vs);

	glUseProgram(m_bloomShader);
	location = glGetUniformLocation(m_bloomShader, "originalMap");
	glUniform1i(location, 0);
	location = glGetUniformLocation(m_bloomShader, "blurredMap");
	glUniform1i(location, 1);
	glUseProgram(0);	

	m_brightnessThreshold = 0.5f;

	return true;
}

void HDR::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the Z-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void HDR::onDraw() 
{	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );

	//////////////////////////////////////////////////////////////////////////
	// Initial G-Pass
	renderToFrameBuffer(m_fbo, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);

	// bind shader for geometry
	glUseProgram(m_shader);

	int location = glGetUniformLocation(m_shader, "projectionView");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix * viewMatrix));

	location = glGetUniformLocation(m_shader, "cameraPosition");
	glUniform3fv(location, 1, glm::value_ptr(m_cameraMatrix[3]));

	// sending time to act as a fake rotating light
	location = glGetUniformLocation(m_shader, "time");
	glUniform1f(location, Utility::getTotalTime());

	int worldLocation = glGetUniformLocation(m_shader, "world");
	int invWorldLocation = glGetUniformLocation(m_shader, "transposeInvWorld");
	
	unsigned int count = m_spear->getMeshCount();
	for ( unsigned int i = 0 ; i < count ; ++i )
	{
		FBXMeshNode* mesh = m_spear->getMeshByIndex(i);

		// bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture ]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::SpecularTexture ]);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::NormalTexture ]);

		// bind transforms, including a transposed
		glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(mesh->m_globalTransform));
		glUniformMatrix4fv(invWorldLocation, 1, GL_TRUE, glm::value_ptr(glm::inverse(mesh->m_globalTransform)));

		// draw
		GLData* glData = (GLData*)mesh->m_userData;
		glBindVertexArray( glData->vao );
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}	
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	//////////////////////////////////////////////////////////////////////////
	// Down-sampled Bright Pass
	renderToFrameBuffer(m_downsampledFBO[0], m_downsampledSize.x, m_downsampledSize.y);

	glUseProgram(m_brightPassShader);

	location = glGetUniformLocation(m_brightPassShader, "brightnessThreshold");
	glUniform1f(location, m_brightnessThreshold);

	// bind normal and light buffers
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);

	renderFullScreenQuad();

	//////////////////////////////////////////////////////////////////////////
	// Vertical Gaussian Blur Pass
	renderToFrameBuffer(m_downsampledFBO[1], m_downsampledSize.x, m_downsampledSize.y);

	glUseProgram(m_gaussianShader);

	location = glGetUniformLocation(m_gaussianShader, "horizontal");
	glUniform1i(location, 0);

	// bind bright filtered down-sampled framebuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_downsampledTexture[0]);

	renderFullScreenQuad();

	//////////////////////////////////////////////////////////////////////////
	// Horizontal Gaussian Blur Pass
	renderToFrameBuffer(m_downsampledFBO[0], m_downsampledSize.x, m_downsampledSize.y);
	
	location = glGetUniformLocation(m_gaussianShader, "horizontal");
	glUniform1i(location, 1);
	
	// bind vertically blurred gaussian framebuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_downsampledTexture[1]);

	renderFullScreenQuad();

	//////////////////////////////////////////////////////////////////////////
	// Final Composite Bloom Pass
	renderToBackBuffer();

	glUseProgram(m_bloomShader);

	// bind original along with the fully gaussian blurred down-sampled version
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_downsampledTexture[0]);

	renderFullScreenQuad();

	// unbind framebuffer textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HDR::renderFullScreenQuad()
{
	glBindVertexArray(m_quad.vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void HDR::renderToBackBuffer()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glViewport(0, 0, DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HDR::renderToFrameBuffer(unsigned int a_fbo, unsigned int a_width, unsigned int a_height)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, a_fbo);

	glViewport(0, 0, a_width, a_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HDR::onDestroy()
{
	glDeleteProgram(m_shader);

	glDeleteVertexArrays(1, &m_quad.vao);
	glDeleteBuffers(1, &m_quad.vbo);

	cleanupOpenGLBuffers(m_spear);
	delete m_spear;

	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new HDR();
	
	if (app->create("AIE - HDR",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}

void HDR::createOpenGLBuffers(FBXFile* a_fbx)
{
	// create the GL VAO/VBO/IBO data for meshes
	for ( unsigned int i = 0 ; i < a_fbx->getMeshCount() ; ++i )
	{
		FBXMeshNode* mesh = a_fbx->getMeshByIndex(i);

		// storage for the opengl data in 3 unsigned int
		GLData* glData = new GLData();

		glGenVertexArrays(1, &glData->vao);
		glBindVertexArray(glData->vao);

		glGenBuffers(1, &glData->vbo);
		glGenBuffers(1, &glData->ibo);

		glBindBuffer(GL_ARRAY_BUFFER, glData->vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData->ibo);

		glBufferData(GL_ARRAY_BUFFER, mesh->m_vertices.size() * sizeof(FBXVertex), mesh->m_vertices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indices.size() * sizeof(unsigned int), mesh->m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // normal
		glEnableVertexAttribArray(2); // tangent
		glEnableVertexAttribArray(3); // binormal
		glEnableVertexAttribArray(4); // texture coord
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::PositionOffset );
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::NormalOffset );
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TangentOffset );
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::BiNormalOffset );
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TexCoord1Offset );

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		mesh->m_userData = glData;
	}
}

void HDR::cleanupOpenGLBuffers(FBXFile* a_fbx)
{
	// bind our vertex array object and draw the mesh
	for ( unsigned int i = 0 ; i < a_fbx->getMeshCount() ; ++i )
	{
		FBXMeshNode* mesh = a_fbx->getMeshByIndex(i);

		GLData* glData = (GLData*)mesh->m_userData;

		glDeleteVertexArrays(1, &glData->vao);
		glDeleteBuffers(1, &glData->vbo);
		glDeleteBuffers(1, &glData->ibo);

		delete[] glData;
	}
}

void HDR::createFullScreenQuad()
{
	// Fullscreen Quad
	glm::vec4 corners[] = {
		glm::vec4(-1,1,0,1),
		glm::vec4(-1,-1,0,1),
		glm::vec4(1,1,0,1),
		glm::vec4(1,-1,0,1)
	};

	glGenVertexArrays(1, &m_quad.vao);
	glBindVertexArray(m_quad.vao);

	glGenBuffers(1, &m_quad.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_quad.vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), corners, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);

	glBindVertexArray(0); 
}

void HDR::createFrameBuffer(unsigned int a_width, unsigned int a_height, 
							unsigned int* a_fbo, unsigned int* a_fboTexture, unsigned int* a_fboDepth)
{
	glGenTextures(1, a_fboTexture);

	glBindTexture(GL_TEXTURE_2D, *a_fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, a_width, a_height, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// optionally create a depth buffer
	if (a_fboDepth != nullptr)
	{
		glGenTextures(1, a_fboDepth);
		glBindTexture(GL_TEXTURE_2D, *a_fboDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 
			0, GL_DEPTH_COMPONENT, GL_FLOAT,0);
	}

	// create and bind the framebuffer
	glGenFramebuffers(1, a_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, *a_fbo);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *a_fboTexture, 0);

	if (a_fboDepth != nullptr)
		glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *a_fboDepth, 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers( 1, drawBuffers );

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}