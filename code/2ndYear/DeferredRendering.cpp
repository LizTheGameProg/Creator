#include "DeferredRendering.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

DeferredRendering::DeferredRendering(){}

DeferredRendering::~DeferredRendering(){}

bool DeferredRendering::onCreate(int a_argc, char* a_argv[]) 
{
	m_lightDir = glm::mat4();
	m_screenSize = glm::vec2(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);

	m_fbx = new FBXFile();
	m_fbx->load( "../../Build/models/ruinedtank/tank.fbx", FBXFile::UNITS_CENTIMETER);
	InitFBXSceneResource( m_fbx );

	createGPassBuffer();
	createLightingBuffer();
	createShadowBuffer();
	setUpLightAndShadowMatrix(1);
	createShaderPrograms();
	createQuads();

	//------------------------------------------------------------
	//	Standard onCreate stuff
	//------------------------------------------------------------
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

void DeferredRendering::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	freeMovement(m_lightDir, a_deltaTime, 10);

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	UpdateFBXSceneResource(m_fbx);
}

void DeferredRendering::onDraw() 
{
	RenderGPass();
	RenderLighting();
	RenderShadows();
	RenderToQuad();
}

void DeferredRendering::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	glDeleteProgram(m_geomPassShader);
	glDeleteProgram(m_quadShader);
	glDeleteProgram(m_LPPShader);
	glDeleteProgram(m_RenderShadowMap);

	DestroyFBXSceneResource(m_fbx);
	m_fbx->unload();
	delete m_fbx;
	m_fbx = nullptr;
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new DeferredRendering();
	
	if (app->create("AIE - DeferredRendering",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}

void DeferredRendering::InitFBXSceneResource(FBXFile * a_pScene)
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
		glEnableVertexAttribArray(3);

		// tell our shaders where the information within our buffers lie
		// eg: attrubute 0 is expected to be the verticy's position. it should be 4 floats, representing xyzw
		// eg: attrubute 1 is expected to be the verticy's color. it should be 4 floats, representing rgba
		// eg: attrubute 2 is expected to be the verticy's texture coordinate. it should be 2 floats, representing U and V
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::PositionOffset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::ColourOffset);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord1Offset);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::NormalOffset);

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

void DeferredRendering::DestroyFBXSceneResource(FBXFile * a_pScene)
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

void DeferredRendering::UpdateFBXSceneResource(FBXFile *a_pScene)
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

void DeferredRendering::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// activate a shader
		glUseProgram( m_geomPassShader );

		// get the location of uniforms on the shader
		GLint uDiffuseTexture	= glGetUniformLocation(m_geomPassShader, "DiffuseTexture");
		GLint uModel			= glGetUniformLocation(m_geomPassShader, "Model");
		GLint uProjection		= glGetUniformLocation(m_geomPassShader, "perspectiveView");

		// get the current mesh
		FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

		// get the render data attached to the m_userData pointer for this mesh
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

		// send the Model and ProjectionView Matrices to the shader
		glUniformMatrix4fv( uModel,	     1, false, glm::value_ptr(mesh->m_globalTransform) );
		glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(a_projection * a_view) );

		// Bind the texture to one of the ActiveTextures
		// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture] );

		// tell the shader which texture to use
		glUniform1i( uDiffuseTexture, 1);

		// reset back to the default active texture
		glActiveTexture( GL_TEXTURE0 );

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

void DeferredRendering::freeMovement(glm::mat4& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up /* = glm::vec3(0,1,0) */)
{
	GLFWwindow* window = glfwGetCurrentContext();

	// Get the camera's forward, right, up, and location vectors
	glm::vec4 vForward = a_transform[2];
	glm::vec4 vRight = a_transform[0];
	glm::vec4 vUp = a_transform[1];
	glm::vec4 vTranslation = a_transform[3];

	float frameSpeed = glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? a_deltaTime * a_speed * 2 : a_deltaTime * a_speed;	

	// Translate camera
	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
	{
		vTranslation -= vForward * frameSpeed;
	}
	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		vTranslation += vForward * frameSpeed;
	}
	if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		vTranslation += vRight * frameSpeed;
	}
	if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		vTranslation -= vRight * frameSpeed;
	}
	if (glfwGetKey(window,GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
	{
		vTranslation += vUp * frameSpeed;
	}
	if (glfwGetKey(window,GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
	{
		vTranslation -= vUp * frameSpeed;
	}

	a_transform[3] = vTranslation;
}

void DeferredRendering::createGPassBuffer()
{
	//------------------------------------------------------------
	//	Gen buffer and textures for buffers
	//------------------------------------------------------------
	//create and bind the framebuffer
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	
	//generate the textures we need, these should be member variables in the class for your app
	glGenTextures(1, &m_FBO_diffuse);
	glGenTextures(1, &m_FBO_normal);
	glGenTextures(1, &m_FBO_worldposition);
	
	//creating and binding the texture for the diffuse data to GL_COLOR_ATTACHMENT0
	glBindTexture(GL_TEXTURE_2D, m_FBO_diffuse);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_FBO_diffuse, 0);
	
	//creating and binding the texture for the normal data to GL_COLOR_ATTACHMENT1
	glBindTexture(GL_TEXTURE_2D, m_FBO_normal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, m_FBO_normal, 0);
	
	//creating and binding the texture for the world position data to GL_COLOR_ATTACHMENT2
	glBindTexture(GL_TEXTURE_2D, m_FBO_worldposition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, m_FBO_worldposition, 0);
	
	// build depth buffer
	//glGenTextures(1, &m_FBO_depth);
	//glBindTexture(GL_TEXTURE_2D, m_FBO_depth);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F,DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT, 0, GL_DEPTH_COMPONENT,GL_FLOAT,0);
	//glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_FBO_depth, 0);
	
	// Here we tell the framebuffer which color attachments we will be drawing to and how many
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, drawBuffers);
	
	// if Status doesn't equal GL_FRAMEBUFFER_COMPLETE there has been an error when creating it
	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	    printf("Framebuffer Error!\n");
	
	// binding 0 to the framebuffer slot unbinds the framebuffer and means future render calls will be sent to 
	// the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRendering::createLightingBuffer()
{
	//create and bind the framebuffer
	glGenFramebuffers(1, &m_FBO_lightPass);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO_lightPass);
	
	//generate the textures we need, these should be member variables in the class for your app
	glGenTextures(1, &m_FBO_lightTexture);
	
	//creating and binding the texture for the diffuse data to GL_COLOR_ATTACHMENT0
	glBindTexture(GL_TEXTURE_2D, m_FBO_lightTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_FBO_lightTexture, 0);

	GLenum LPdrawBuffers[] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, LPdrawBuffers);

	// if Status doesn't equal GL_FRAMEBUFFER_COMPLETE there has been an error when creating it
	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	    printf("Framebuffer Error!\n");

	// binding 0 to the framebuffer slot unbinds the framebuffer and means future render calls will be sent to 
	// the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRendering::createShadowBuffer()
{
	//resolution of the texture to put our shadow map in
	m_shadowWidth = 1024;
	m_shadowHeight = 1024;

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &m_shadowFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFramebuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &m_shadowTexture);
	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, m_shadowWidth, m_shadowHeight, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		printf("depth buffer not created");
	}
	else
	{
		printf("Success! created depth buffer\n"); 
	}

	// return to back-buffer rendering
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredRendering::RenderGPass()
{
	// bind the framebuffer for rendering
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	RenderFBXSceneResource(m_fbx, viewMatrix, m_projectionMatrix);

	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRendering::RenderLighting()
{
	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO_lightPass);
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glUseProgram(m_LPPShader);
	
	GLint uWorldTexture		= glGetUniformLocation(m_LPPShader, "world_tex");
	GLint uNormalTexture	= glGetUniformLocation(m_LPPShader, "normal_tex");
	GLint uCameraPos		= glGetUniformLocation(m_LPPShader, "camera_pos");
	GLint uScreenSize		= glGetUniformLocation(m_LPPShader, "screenSize");
	GLint uLightDir			= glGetUniformLocation(m_LPPShader, "light_dir");

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_FBO_worldposition);
	glUniform1i(uWorldTexture, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_FBO_normal);
	glUniform1i(uNormalTexture, 2);

	glUniform3fv(uCameraPos, 1, glm::value_ptr(m_cameraMatrix[3]));

	glUniform2fv(uScreenSize, 1, glm::value_ptr(m_screenSize));

	glUniform3fv(uLightDir, 1, glm::value_ptr(m_lightDir[3]));

	glBindVertexArray(m_lightQuad.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	
	glDisable(GL_BLEND);

	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRendering::RenderShadows()
{
	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_shadowFramebuffer);
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRendering::RenderToQuad()
{
	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( m_quadShader );
	
	// get the location of uniforms on the shader
	GLint quDiffuseTexture	= glGetUniformLocation(m_quadShader, "DiffuseTexture");
	GLint quScreenSize		= glGetUniformLocation(m_quadShader, "screenSize");
	GLint quLightingTexture = glGetUniformLocation(m_quadShader, "LightingTexture");

	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, m_FBO_diffuse );
	glUniform1i( quDiffuseTexture, 3);

	glUniform2fv(quScreenSize,	1, glm::value_ptr(m_screenSize));

	glActiveTexture( GL_TEXTURE4 );
	glBindTexture( GL_TEXTURE_2D, m_FBO_lightTexture );
	glUniform1i( quLightingTexture, 4);

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_quad.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DeferredRendering::setUpLightAndShadowMatrix(float count)
{
	// setup light direction and shadow matrix
	glm::vec3 lightPosition = glm::vec3(1.0f,1.0f,0);
	m_lightDir[3] = glm::normalize(glm::vec4( -lightPosition, 0 ));

	glm::mat4 depthViewMatrix = glm::lookAt(lightPosition, glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-3,3,-3,3,-50,50);
	m_shadowProjectionViewMatrix = depthProjectionMatrix * depthViewMatrix;
}

void DeferredRendering::createShaderPrograms()
{
	//------------------------------------------------------------
	//	Create the geometry pass shader program
	//------------------------------------------------------------
	{
		const char* inputs[] = {"Position", "Colour", "TexCoord", "Normal"};

		// Three outputs, one for each texture we will be rendering into
		const char* outputs[] = {"Diffuse", "Normal", "World"};
			
		unsigned int vs = Utility::loadShader("../../Build/shaders/geom_pass.vert", GL_VERTEX_SHADER);
		unsigned int fs = Utility::loadShader("../../Build/shaders/geom_pass.frag", GL_FRAGMENT_SHADER);
			
		m_geomPassShader = Utility::createProgram(vs, 0, 0, 0, fs, 4, inputs, 3, outputs);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	//------------------------------------------------------------
	//	Create the back buffer quad shader program
	//------------------------------------------------------------
	{
		const char * inputs[] = {"Position", "Colour", "TexCoord"};
		const char * outputs[] = {"OutColour"};
			
		unsigned int vs = Utility::loadShader("../../Build/shaders/quad.vert", GL_VERTEX_SHADER);
		unsigned int fs = Utility::loadShader("../../Build/shaders/quad.frag", GL_FRAGMENT_SHADER);
			
		m_quadShader = Utility::createProgram(vs, 0, 0, 0, fs, 3, inputs, 1, outputs);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	//------------------------------------------------------------
	//	Create the Light pre pass quad shader program
	//------------------------------------------------------------
	{
		const char* inputs[] = {"Position", "Colour", "TexCoord"};
		const char* output[] = {"Lighting"};
			
		unsigned int vs = Utility::loadShader("../../Build/shaders/LightPrePass.vert", GL_VERTEX_SHADER);
		unsigned int fs = Utility::loadShader("../../Build/shaders/LightPrePass.frag", GL_FRAGMENT_SHADER);
			
		m_LPPShader = Utility::createProgram(vs, 0, 0, 0, fs, 3, inputs, 1, output);
		
		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	//------------------------------------------------------------
	//	Create the rendering the shadow map shader program
	//------------------------------------------------------------
	//{
	//	const char* inputs[] = {"Position"};
	//	const char* output[] = {"depth"};
	//		
	//	unsigned int vs = Utility::loadShader("../../Build/shaders/RenderShadowMap.vert", GL_VERTEX_SHADER);
	//	unsigned int fs = Utility::loadShader("../../Build/shaders/RenderShadowMap.frag", GL_FRAGMENT_SHADER);
	//		
	//	m_RenderShadowMap = Utility::createProgram(vs, 0, 0, 0, fs, 1, inputs, 1, output);
	//	
	//	glDeleteShader(vs);
	//	glDeleteShader(fs);
	//}
}

void DeferredRendering::createQuads()
{
	//------------------------------------------------------------
	//	Create a quad to draw the FBO textures to
	//------------------------------------------------------------

	BasicVertex m_quadData[4];

	m_quadData[0].position = glm::vec4(-1.f,-1.f,0.f,0.f);
	m_quadData[1].position = glm::vec4(-1.f, 1.f,0.f,0.f);
	m_quadData[2].position = glm::vec4( 1.f, 1.f,0.f,0.f);
	m_quadData[3].position = glm::vec4( 1.f,-1.f,0.f,0.f);

	m_quadData[0].colour = glm::vec4(0,0,1,1);
	m_quadData[1].colour = glm::vec4(0,1,0,1);
	m_quadData[2].colour = glm::vec4(1,0,0,1);
	m_quadData[3].colour = glm::vec4(0,1,0,1);

	m_quadData[0].texCoord = glm::vec2(0,0);
	m_quadData[1].texCoord = glm::vec2(0,1);
	m_quadData[2].texCoord = glm::vec2(1,1);
	m_quadData[3].texCoord = glm::vec2(1,0);

	unsigned int indices[6] = {
		3,1,0,
		3,2,1 
	};

	// create and bind buffers to a vertex array object
	glGenBuffers(1, &m_quad.VBO);
	glGenBuffers(1, &m_quad.IBO);
	glGenVertexArrays(1, &m_quad.VAO);

	glBindVertexArray(m_quad.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_quad.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quad.IBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(BasicVertex), m_quadData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 16);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 32);

	//------------------------------------------------------------
	//	Create a quad to draw the FBO textures to
	//------------------------------------------------------------
	// create and bind buffers to a vertex array object
	glGenBuffers(1, &m_lightQuad.VBO);
	glGenBuffers(1, &m_lightQuad.IBO);
	glGenVertexArrays(1, &m_lightQuad.VAO);

	glBindVertexArray(m_lightQuad.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_lightQuad.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lightQuad.IBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(BasicVertex), m_quadData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 16);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 32);

	// unbind vertex array
	glBindVertexArray(0);
}
