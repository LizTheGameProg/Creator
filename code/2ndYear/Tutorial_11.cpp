#include "Tutorial_11.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

Tutorial_11::Tutorial_11()
{

}

Tutorial_11::~Tutorial_11()
{

}

bool Tutorial_11::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();
	m_fTime = 0.f;
	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 100.0f);
	glClearColor(0.25f,0.25f,0.25f,1);

	//Utility::build3DPlane( 100, m_plane.VAO, m_plane.VBO, m_plane.IBO );

	//Create a Fullscreen quad from the following values.
	// break down is 4 floats for position, 2 floats for UV coordinates
	float fullScreenVertexValues[] = {
		-1.f,  1.f, 0.f, 1.f, 0.f, 1.f,
		-1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 
		 1.f, -1.f, 0.f, 1.f, 1.f, 0.f, 
		 1.f,  1.f, 0.f, 1.f, 1.f, 1.f
	};

	unsigned int fullscreenQuadIndexes[] = {
		0, 1, 2, 0, 2, 3
	};

	//Generate and set the vertex attributes for our fullScreen quad
	glGenBuffers( 1, &m_FullScreenQuad.VBO );
	glGenBuffers( 1, &m_FullScreenQuad.IBO );

	glGenVertexArrays( 1, &m_FullScreenQuad.VAO );
	glBindVertexArray( m_FullScreenQuad.VAO );

	glBindBuffer( GL_ARRAY_BUFFER, m_FullScreenQuad.VBO );
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), fullScreenVertexValues, GL_STATIC_DRAW);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_FullScreenQuad.IBO );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), fullscreenQuadIndexes, GL_STATIC_DRAW);

	// enable the attribute locations that will be used on our shaders
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)16);

	// finally, where done describing our mesh to the shader
	// we can describe the next mesh
	glBindVertexArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,0 );

	// Geometry Pass Shader Loading 
	{
		const char* aszInputs[] =  { "Position", "Color", "Normal", "TexCoord1" };
		const char* aszOutputs[] = { "DiffuseTexture", "NormalTexture" };

		// load shader internally calls glCreateShader...
		GLuint vshader = Utility::loadShader("./shaders/GPass.vert", GL_VERTEX_SHADER);
		GLuint pshader = Utility::loadShader("./shaders/GPass.frag", GL_FRAGMENT_SHADER);

		m_gPassShader = Utility::createProgram( vshader, 0, 0, 0, pshader, 3, aszInputs, 2, aszOutputs);
		// free our shader once we built our program
		glDeleteShader( vshader );
		glDeleteShader( pshader );
	}
	// Light Pass Shader Loading 
	{
		const char* aszInputs[] =  { "Position", "Color", "Normal", "TexCoord1" };
		const char* aszOutputs[] = { "LightTexture" };

		// load shader internally calls glCreateShader...
		GLuint vshader = Utility::loadShader("./shaders/LPassShader.vert", GL_VERTEX_SHADER);
		GLuint pshader = Utility::loadShader("./shaders/LPassShader.frag", GL_FRAGMENT_SHADER);

		m_lPassShader = Utility::createProgram( vshader, 0, 0, 0, pshader, 3, aszInputs, 1, aszOutputs);
		// free our shader once we built our program
		glDeleteShader( vshader );
		glDeleteShader( pshader );
	}
	// Composite Pass Shader loading
	{
		const char* aszInputs[] =  { "Position", "TexCoord1" };
		const char* aszOutputs[] = { "outColor" };

		// load shader internally calls glCreateShader...
		GLuint vshader = Utility::loadShader("./shaders/CompositeShader.vert", GL_VERTEX_SHADER);
		GLuint pshader = Utility::loadShader("./shaders/CompositeShader.frag", GL_FRAGMENT_SHADER);

		m_cPassShader = Utility::createProgram( vshader, 0, 0, 0, pshader, 2, aszInputs, 1, aszOutputs);

		// free our shader once we built our program
		glDeleteShader( vshader );
		glDeleteShader( pshader );
	}

	{
		glGenFramebuffers(1, &m_gPassFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_gPassFBO);
		//Generate a Texture for our FBO to draw into 
		glGenTextures( 1, &m_DiffuseTexture );
		glBindTexture( GL_TEXTURE_2D, m_DiffuseTexture );
		//Create the textreu, width and Height are screen size, data pointer is 0 
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glGenTextures( 1, &m_NormalTexture );
		glBindTexture( GL_TEXTURE_2D, m_NormalTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		//Generate our FBO's Depth Texture
		glGenTextures( 1, &m_FBODepth );
		glBindTexture( GL_TEXTURE_2D, m_FBODepth );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL );
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		//Attach the diffuse and depth textures to our FBO
		glFramebufferTexture( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_DiffuseTexture, 0 );
		glFramebufferTexture( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, m_NormalTexture, 0 );
		glFramebufferTexture( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_FBODepth, 0 );
		//Now tell the Framebuffer which color attachements we will be drawring into and how many
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers( 2, drawBuffers );

		
		//Check to see if the framebuffer has been initialise correcly
		GLenum status = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );
		if( status != GL_FRAMEBUFFER_COMPLETE )
		{
			printf( "Framebuffer Error!");
		}

		glClearBufferfv( GL_COLOR, 0, glm::value_ptr( glm::vec4( 0.f, 0.f, 0.f, 0.f ) ));
		glClearBufferfv( GL_COLOR, 1, glm::value_ptr( glm::vec4( 0.f, 0.f, 0.f, 0.f ) ));
	}

	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

	{
		//Light PrePass FBO
		glGenFramebuffers(1, &m_lPrePassFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_lPrePassFBO);
		//Generate a Texture for our FBO to draw into 
		glGenTextures( 1, &m_LightTexture );
		glBindTexture( GL_TEXTURE_2D, m_LightTexture );
		//Create the textreu, width and Height are screen size, data pointer is 0 
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_LightTexture, 0 );

		//Generate our FBO's Depth Texture
		glGenTextures( 1, &m_LightDepthTexture );
		glBindTexture( GL_TEXTURE_2D, m_LightDepthTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL );
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		glFramebufferTexture( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_LightDepthTexture, 0 );
		
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers( 1, drawBuffers );
		
		GLenum status = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );
		if( status != GL_FRAMEBUFFER_COMPLETE )
		{
			printf( "Light Framebuffer Error!");
		}

		glClearBufferfv( GL_COLOR, 0, glm::value_ptr( glm::vec4( 0.f, 0.f, 0.f, 0.f ) ));
	}
	// set the clear colour and enable depth testing and backface culling
	//
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_fbx = new FBXFile();
	m_fbx->load( "../../Build/models/ruinedtank/tank.fbx", FBXFile::UNITS_CENTIMETER );
	InitFBXSceneResource( m_fbx );

	m_pPointLight = new CRenderSphere();
	//m_pPointLight->SetTextureID(g_TextureID);

	return true;
}

void Tutorial_11::onUpdate(float a_deltaTime) 
{
	m_fTime += a_deltaTime;
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	UpdateFBXSceneResource(m_fbx);
	m_pPointLight->Update(a_deltaTime);

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
}

void Tutorial_11::onDraw() 
{
	// clear the backbuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_gPassFBO);
	
	glUseProgram( m_gPassShader );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	RenderFBXSceneResource( m_gPassShader, m_fbx, viewMatrix, m_projectionMatrix );
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glUseProgram(0);
	glDisable( GL_CULL_FACE );
	//Light Pre Pass
	//m_pPointLight->Draw(m_lPassShader);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_lPrePassFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv( GL_COLOR, 0, glm::value_ptr( glm::vec4( 0.2f, 0.2f, 0.2f, 0.f ) ));
	glUseProgram( m_lPassShader );

	GLint uView       = glGetUniformLocation(m_lPassShader, "View");
	GLint uProjection = glGetUniformLocation(m_lPassShader, "Projection");
	glUniformMatrix4fv( uView,       1, false, glm::value_ptr(viewMatrix) );
	glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(m_projectionMatrix) );

	{
		// get the view matrix from the world-space camera matrix
		GLint invProjectionViewLoc = glGetUniformLocation( m_lPassShader, "invProjection");
		glUniformMatrix4fv(invProjectionViewLoc, 1, GL_FALSE, glm::value_ptr(glm::inverse(m_projectionMatrix)));

		glm::vec2 screenSize = glm::vec2(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
		GLint uScreenSize = glGetUniformLocation( m_lPassShader, "screenSize");
		glUniform2fv( uScreenSize, 1, glm::value_ptr(screenSize) );
	}

	// get the location of uniforms on the shader
	GLint uNormalTexture =  glGetUniformLocation( m_lPassShader, "NormalTexture" );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_NormalTexture );
	// tell the shader which texture to use
	glUniform1i( uNormalTexture, 0 );
	
	//glCullFace( GL_CW );
	m_pPointLight->Draw(m_lPassShader);
	//glCullFace( GL_CCW );
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glUseProgram(0);
	glEnable( GL_CULL_FACE );
	//Now switch back and draw our Plane using the texture we just drew
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_cPassShader);

	// get the view matrix from the world-space camera matrix
	GLint invProjectionViewLoc = glGetUniformLocation( m_cPassShader, "invProjection");
	glUniformMatrix4fv(invProjectionViewLoc, 1, GL_FALSE, glm::value_ptr(glm::inverse(m_projectionMatrix)));

	

	glm::vec2 screenSize = glm::vec2(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
	GLint uScreenSize = glGetUniformLocation( m_cPassShader, "screenSize");
	glUniform2fv( uScreenSize, 1, glm::value_ptr(screenSize) );

	GLint location = glGetUniformLocation( m_cPassShader, "DiffuseTexture" );
	glUniform1i(location, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);

	location = glGetUniformLocation( m_cPassShader, "NormalTexture" );
	glUniform1i(location, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);

	location = glGetUniformLocation( m_cPassShader, "LightTexture" );
	glUniform1i(location, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_LightTexture);

	glBindVertexArray(m_FullScreenQuad.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Tutorial_11::onDestroy()
{
	// clean up anything we created
	glDeleteProgram(m_gPassShader);
	glDeleteProgram(m_cPassShader);

	DestroyFBXSceneResource( m_fbx );
	m_fbx->unload();
	delete m_fbx;
	m_fbx = nullptr;

	Gizmos::destroy();
}

void Tutorial_11::InitFBXSceneResource(FBXFile *a_pScene)
{
	// how manu meshes and materials are stored within the fbx file
	unsigned int meshCount = a_pScene->getMeshCount();
	unsigned int matCount = a_pScene->getMaterialCount();

	// loop through each mesh
	for(unsigned int i=0; i<meshCount; ++i)
	{
		// get the current mesh
		FBXMeshNode *pMesh = a_pScene->getMeshByIndex(i);
		//std::cout << pMesh->m_name << std::endl;

		// generate our OGL_FBXRenderData for storing the meshes VBO, IBO and VAO
		// and assign it to the meshes m_userData pointer so that we can retrive 
		// it again within the render function
		OGL_FBXRenderData *ro = new OGL_FBXRenderData();
		pMesh->m_userData = ro;

		// OPENGL: generate the VBO, IBO and VAO
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
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::NormalOffset);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord1Offset);

		// finally, where done describing our mesh to the shader
		// we can describe the next mesh
		glBindVertexArray(0);
	}

}

void Tutorial_11::DestroyFBXSceneResource(FBXFile *a_pScene)
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

void Tutorial_11::UpdateFBXSceneResource(FBXFile *a_pScene)
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

void Tutorial_11::RenderFBXSceneResource(unsigned int a_iShader, FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	//Set up the view and projection matrices
	GLint uView       = glGetUniformLocation(a_iShader, "View");
	GLint uProjection = glGetUniformLocation(a_iShader, "Projection");
	glUniformMatrix4fv( uView,       1, false, glm::value_ptr(a_view) );
	glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(a_projection) );

	// get the location of uniforms on the shader
	GLint uDiffuseTexture = glGetUniformLocation(a_iShader, "Diffuse");
	GLint uModel      = glGetUniformLocation(a_iShader, "Model");
	
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// get the current mesh
		FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);
		// get the render data attached to the m_userData pointer for this mesh
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

		// Bind the texture to one of the ActiveTextures
		// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture] );
		// tell the shader which texture to use
		glUniform1i( uDiffuseTexture, 0 );
	 
		// send the Model, View and Projection Matrices to the shader
		glUniformMatrix4fv( uModel, 1, GL_FALSE, glm::value_ptr( mesh->m_globalTransform ) );
		
		// bind our vertex array object
		// remember in the initialise function, we bound the VAO and IBO to the VAO
		// so when we bind the VAO, openGL knows what what vertices,
		// indices and vertex attributes to send to the shader
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);

	}

	// finally, we have finished rendering the meshes
	// disable this shader
	//glUseProgram(0);
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new Tutorial_11();
//	
//	if (app->create("AIE - Tutorial_11 - Defferred Rendering",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}