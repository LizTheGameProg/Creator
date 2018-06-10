#include "RenderTargets.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

RenderTargets::RenderTargets()
{

}

RenderTargets::~RenderTargets()
{

}

bool RenderTargets::onCreate(int a_argc, char* a_argv[]) 
{
	// load the shader
	const char* aszInputs[] =  { "Position", "Color", "TexCoord1" };
	const char* aszOutputs[] = { "outColour" };

	// load shader internally calls glCreateShader...
	GLuint vshader = Utility::loadShader("../../Build/shaders/SimpleFBX_Tutorial.vert", GL_VERTEX_SHADER);
	GLuint pshader = Utility::loadShader("../../Build/shaders/SimpleFBX_Tutorial.frag", GL_FRAGMENT_SHADER);

	m_shader = Utility::createProgram( vshader, 0, 0, 0, pshader, 3, aszInputs, 1, aszOutputs);

	// free our shader once we built our program
	glDeleteShader( vshader );
	glDeleteShader( pshader );

	// load the shader
	const char* raszInputs[] =  { "Position", "Color", "TexCoord1" };
	const char* raszOutputs[] = { "outColour" };

	// load shader internally calls glCreateShader...
	GLuint rvshader = Utility::loadShader("../../Build/shaders/RenderTargets.vert", GL_VERTEX_SHADER);
	GLuint rpshader = Utility::loadShader("../../Build/shaders/RenderTargets.frag", GL_FRAGMENT_SHADER);

	m_shader_renderTargets = Utility::createProgram( rvshader, 0, 0, 0, rpshader, 3, raszInputs, 1, raszOutputs);

	// free our shader once we built our program
	glDeleteShader( rvshader );
	glDeleteShader( rpshader );


	m_fbx = new FBXFile();
	m_fbx->load( "../../Build/models/soulspear/soulspear.fbx", FBXFile::UNITS_CENTIMETER );
	InitFBXSceneResource( m_fbx );

	// this would be within your onCreate() function
	glGenFramebuffers(1, &m_FBO);

	int maxAttachments = 0;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);
	printf("The number of FBO color attachments my graphics card supports is: %i\n", maxAttachments);

	// bind the framebuffer for editing
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	
	// create a texture to be attached to the framebuffer, stored in the derived app class as a member
	glGenTextures(1, &m_FBO_texture);
	
	// bind the texture for editing
	glBindTexture(GL_TEXTURE_2D, m_FBO_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// create the texture. Note, the width and height are the dimensions of the screen and the final
	// data pointer is 0 as we aren't including any initial data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
	
	// attach the texture to the 0th color attachment of the framebuffer
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_FBO_texture, 0);
	
	// Here we tell the framebuffer which color attachments we will be drawing to and how many
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	
	// if Status doesn't equal GL_FRAMEBUFFER_COMPLETE there has been an error when creating it
	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	    printf("Framebuffer Error!\n");
	
	// binding 0 to the framebuffer slot unbinds the framebuffer and means future render calls will be sent to 
	// the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glGenTextures(1, &m_FBO_depth);

	// m_FBO_depth would be a member for the derived application class
	glBindTexture(GL_TEXTURE_2D, m_FBO_depth);
	
	// note the use of GL_DEPTH_COMPONENT32F and GL_DEPTH_COMPONENT
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	// attach it as a GL_DEPTH_ATTACHMENT
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_FBO_depth, 0);

	Utility::build3DPlane(10, m_vao, m_vbo, m_ibo);

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

	return true;
}

void RenderTargets::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
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

	UpdateFBXSceneResource(m_fbx);
}

void RenderTargets::onDraw() 
{
	// bind the framebuffer for rendering
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);

	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	RenderFBXSceneResource(m_fbx, viewMatrix, m_projectionMatrix);

	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	RenderFBXSceneResource(m_fbx, viewMatrix, m_projectionMatrix);

	glUseProgram(m_shader_renderTargets);

	GLint uDiffuseTexture = glGetUniformLocation(m_shader, "DiffuseTexture");
	GLint uModel      = glGetUniformLocation(m_shader, "Model");
	GLint uView       = glGetUniformLocation(m_shader, "View");
	GLint uProjection = glGetUniformLocation(m_shader, "Projection");

	glUniformMatrix4fv( uModel,	     1, false, glm::value_ptr(glm::mat4()) );
	glUniformMatrix4fv( uView,       1, false, glm::value_ptr(viewMatrix) );
	glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(m_projectionMatrix) );

	// Bind the texture to one of the ActiveTextures
	// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, m_FBO_texture );

	// tell the shader which texture to use
	glUniform1i( uDiffuseTexture, 2);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	glUseProgram(0);
}

void RenderTargets::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	glDeleteShader(m_shader);
	glDeleteShader(m_shader_renderTargets);
	DestroyFBXSceneResource(m_fbx);
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new RenderTargets();
//	
//	if (app->create("AIE - RenderTargets",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}

void RenderTargets::InitFBXSceneResource(FBXFile * a_pScene)
{
	// how manu meshes and materials are stored within the fbx file
	unsigned int meshCount = a_pScene->getMeshCount();
	unsigned int matCount = a_pScene->getMaterialCount();

	// loop through each mesh
	for(unsigned int i=0; i<meshCount; ++i)
	{
		// get the current mesh
		FBXMeshNode *pMesh = a_pScene->getMeshByIndex(i);

		// genorate our OGL_FBXRenderData for storing the meshes VBO, IBO and VAO
		// and assign it to the meshes m_userData pointer so that we can retrive 
		// it again within the render function
		OGL_FBXRenderData *ro = new OGL_FBXRenderData();
		pMesh->m_userData = ro;

		// OPENGL: genorate the VBO, IBO and VAO
		glGenBuffers(1, &ro->VBO);
		glGenBuffers(1, &ro->IBO);
		glGenVertexArrays(1, &ro->VAO);

		// OPENGL: Bind  VAO, and then bind the VBO and IBO to the VAO
		glBindVertexArray(ro->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, ro->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro->IBO);

		// Send the vertex data to the VBO
		glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(FBXVertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);

		// send the index data to the IBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);

		// enable the attribute locations that will be used on our shaders
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// tell our shaders where the information within our buffers lie
		// eg: attrubute 0 is expected to be the verticy's position. it should be 4 floats, representing xyzw
		// eg: attrubute 1 is expected to be the verticy's color. it should be 4 floats, representing rgba
		// eg: attrubute 2 is expected to be the verticy's texture coordinate. it should be 2 floats, representing U and V
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::PositionOffset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::ColourOffset);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord1Offset);

		// finally, where done describing our mesh to the shader
		// we can describe the next mesh
		glBindVertexArray(0);
	}

	// Loop through each material and load the texture
	for(unsigned int i = 0; i<matCount; ++i)
	{
		// get the current material being loaded
		FBXMaterial *pMaterial = a_pScene->getMaterialByIndex(i);

		// each material can optionally have many different textures that can be used to describe how the object should be rendered.
		// Look at the FBXMaterial structure.
		// the following textures can be assigned to a material within the 3D modeling programs
		// we can optionally support loading these in...
		// - DiffuseTexture,
		// - AmbientTexture,
		// - GlowTexture,
		// - SpecularTexture,
		// - GlossTexture,
		// - NormalTexture,
		// - AlphaTexture,
		// - DisplacementTexture,

		for(unsigned int j = 0; j<FBXMaterial::TextureTypes_Count; ++j)
		{
			// find the path to the texture to be loaded
			std::string path = a_pScene->getPath();

			// append the filename of the texture
			path += pMaterial->textureFilenames[j];

			// load the texture using SOIL
			pMaterial->textureIDs[j] = SOIL_load_OGL_texture(path.c_str(), 4, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);

			// lets just print what is loaded to the console...
			printf("Loading texture %i: %s - ID: %i\n", j, path.c_str(), pMaterial->textureIDs[j]);
		}
	}
}

void RenderTargets::DestroyFBXSceneResource(FBXFile * a_pScene)
{
	// how manu meshes and materials are stored within the fbx file
	unsigned int meshCount = a_pScene->getMeshCount();
	unsigned int matCount = a_pScene->getMaterialCount();

	// remove meshes
	for(unsigned int i=0; i<meshCount; i++)
	{
		// Get the current mesh and retrive the render data we assigned to m_userData
		FBXMeshNode* pMesh = a_pScene->getMeshByIndex(i);
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *)pMesh->m_userData;

		// delete the buffers and free memory from the graphics card
		glDeleteBuffers(1, &ro->VBO);
		glDeleteBuffers(1, &ro->IBO);
		glDeleteVertexArrays(1, &ro->VAO);

		// this is memory we created earlier in the InitFBXSceneResources function
		// make sure to destroy it
		delete ro;

	}

	// loop through each of the materials
	for(unsigned int i=0; i<matCount; i++)
	{
		// get the current material
		FBXMaterial *pMaterial = a_pScene->getMaterialByIndex(i);
		for(int j=0; j<FBXMaterial::TextureTypes_Count; j++)
		{
			// delete the texture if it was loaded
			if( pMaterial->textureIDs[j] != 0 )
				glDeleteTextures(1, &pMaterial->textureIDs[j]);
		}
	}
}

void RenderTargets::UpdateFBXSceneResource(FBXFile *a_pScene)
{
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// get the current mesh
		FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

		// if you move an object around within your scene
		// children nodes are not updated until this function is called.
		mesh->updateGlobalTransform();
	}
}

void RenderTargets::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// activate a shader
		glUseProgram( m_shader );

		// get the location of uniforms on the shader
		GLint uDiffuseTexture = glGetUniformLocation(m_shader, "DiffuseTexture");
		//GLint uDiffuseColor   = glGetUniformLocation(m_shader, "DiffuseColor");	

		GLint uModel      = glGetUniformLocation(m_shader, "Model");
		GLint uView       = glGetUniformLocation(m_shader, "View");
		GLint uProjection = glGetUniformLocation(m_shader, "Projection");

		// get the current mesh
		FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

		// get the render data attached to the m_userData pointer for this mesh
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

		// Bind the texture to one of the ActiveTextures
		// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture] );

		// tell the shader which texture to use
		glUniform1i( uDiffuseTexture, 1);

		// reset back to the default active texture
		glActiveTexture( GL_TEXTURE0 );

		// send the Model, View and Projection Matrices to the shader
		glUniformMatrix4fv( uModel,	     1, false, glm::value_ptr(mesh->m_globalTransform) );
		glUniformMatrix4fv( uView,       1, false, glm::value_ptr(a_view) );
		glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(a_projection) );

		// bind our vertex array object
		// remember in the initialise function, we bound the VAO and IBO to the VAO
		// so when we bind the VAO, openGL knows what what vertices,
		// indices and vertex attributes to send to the shader
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	// finally, we have finished rendering the meshes
	// disable this shader
	glUseProgram(0);
}