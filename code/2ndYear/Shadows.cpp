#include "Shadows.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

Shadows::Shadows()
{

}

Shadows::~Shadows()
{

}

bool Shadows::onCreate(int a_argc, char* a_argv[]) 
{
	unsigned int vs = Utility::loadShader("../../Build/shaders/RenderShadowMap.vert", GL_VERTEX_SHADER);
	unsigned int fs = Utility::loadShader("../../Build/shaders/RenderShadowMap.frag", GL_FRAGMENT_SHADER);

	const char * inputs [] = {"Position"};
	const char * outputs[] = {"depth"};

	m_RenderShadowMap = Utility::createProgram(vs, 0, 0, 0, fs, 1, inputs, 1, outputs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	unsigned int smvs = Utility::loadShader("../../Build/shaders/DisplayShadowMap.vert", GL_VERTEX_SHADER);
	unsigned int smfs = Utility::loadShader("../../Build/shaders/DisplayShadowMap.frag", GL_FRAGMENT_SHADER);

	const char * sminputs [] = {"Position", "TexCoord"};
	const char * smoutputs[] = {"FragColor"};

	m_DisplayShadowMap = Utility::createProgram(smvs, 0, 0, 0, smfs, 2, sminputs, 1, smoutputs);

	glDeleteShader(smvs);
	glDeleteShader(smfs);

	unsigned int ssvs = Utility::loadShader("../../Build/shaders/SimpleFBX_Tutorial.vert", GL_VERTEX_SHADER);
	unsigned int ssfs = Utility::loadShader("../../Build/shaders/SimpleFBX_Tutorial.frag", GL_FRAGMENT_SHADER);

	const char * ssinputs [] = {"Position", "Color", "TexCoord1", "Normals"};
	const char * ssoutputs[] = {"outColor"};

	m_simpleShader = Utility::createProgram(ssvs, 0, 0, 0, ssfs, 4, ssinputs, 1, ssoutputs);

	glDeleteShader(ssvs);
	glDeleteShader(ssfs);

	unsigned int spvs = Utility::loadShader("../../Build/shaders/Shadow.vert", GL_VERTEX_SHADER);
	unsigned int spfs = Utility::loadShader("../../Build/shaders/Shadow.frag", GL_FRAGMENT_SHADER);

	const char * spinputs [] = {"Position", "Color", "TexCoord", "Normals"};
	const char * spoutputs[] = {"FragColor"};

	m_shaderProgram = Utility::createProgram(spvs, 0, 0, 0, spfs, 4, spinputs, 1, spoutputs);

	glDeleteShader(spvs);
	glDeleteShader(spfs);

	createShadowBuffer();
	
	create2DQuad();

	m_fbx = new FBXFile();
	m_fbx->load("../../Build/models/ruinedtank/tank.fbx", FBXFile::UNITS_CENTIMETER);
	InitFBXSceneResource( m_fbx );

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

	m_lightPosition = glm::vec3(4,5,10);

	return true;
}

void Shadows::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	freeMovement(m_lightPosition, a_deltaTime, 10);
	 
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
	setUpLightAndShadowMatrix(1.0f);
}

void Shadows::onDraw() 
{
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_shadowFramebuffer);
	glViewport(0,0,m_shadowWidth, m_shadowHeight);
	glScissor(0,0,m_shadowWidth, m_shadowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
	
	RenderFBXSceneResourceFromLight(m_fbx, viewMatrix, m_projectionMatrix);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0,0,DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);
	glScissor(0,0,DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);

	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawScene();
	displayShadowMap();
}

void Shadows::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	glDeleteProgram(m_simpleShader);
	glDeleteProgram(m_shaderProgram);
	glDeleteProgram(m_RenderShadowMap);
	glDeleteProgram(m_DisplayShadowMap);

	DestroyFBXSceneResource(m_fbx);
	m_fbx->unload();
	delete m_fbx;
	m_fbx = nullptr;
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new Shadows();
//	
//	if (app->create("AIE - Shadows",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//	_CrtDumpMemoryLeaks();
//	return 0;
//}

void Shadows::createShadowBuffer()
{
	//resolution of the texture to put our shadow map in
	m_shadowWidth = 2048;
	m_shadowHeight = 2048;

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

void Shadows::setUpLightAndShadowMatrix(float count)
{
	// setup light direction and shadow matrix
	m_lightDirection = glm::normalize(glm::vec4( -m_lightPosition, 0 ));

	glm::mat4 depthViewMatrix = glm::lookAt(m_lightPosition, glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-25,25,-25,25,-20,50);
	m_shadowProjectionViewMatrix = depthProjectionMatrix * depthViewMatrix;
}

void Shadows::create2DQuad()
{
	glGenVertexArrays(1, &m_2dQuad.VAO);
	glBindVertexArray(m_2dQuad.VAO);

	// create a 200x200 2D GUI quad (resize it to screen-space!)
	glm::vec2 size(200,200);
	size.x /= DEFAULT_SCREENWIDTH;
	size.y /= DEFAULT_SCREENHEIGHT;
	size *= 2;
	
	// setup the quad in the top corner
	float quadVertices[] = {
		-1.0f,			1.0f - size.y,	 0.0f, 1.0f, 0, 0,
		-1.0f + size.x, 1.0f - size.y,	 0.0f, 1.0f, 1, 0,
		-1.0f,			1.0f,			 0.0f, 1.0f, 0, 1,

		-1.0f,			1.0f,			 0.0f, 1.0f, 0, 1,
		-1.0f + size.x, 1.0f - size.y,	 0.0f, 1.0f, 1, 0,
		-1.0f + size.x, 1.0f,			 0.0f, 1.0f, 1, 1,
	};

	glGenBuffers(1, &m_2dQuad.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_2dQuad.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 6, quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char*)0)+16);
	glBindVertexArray(0);
}

void Shadows::displayShadowMap()
{
	glUseProgram(m_DisplayShadowMap);
	unsigned int texLoc = glGetUniformLocation(m_DisplayShadowMap, "shadowMap");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,m_shadowTexture);
	glUniform1i(texLoc, 0);
	glBindVertexArray(m_2dQuad.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Shadows::InitFBXSceneResource(FBXFile * a_pScene)
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

void Shadows::DestroyFBXSceneResource(FBXFile * a_pScene)
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

void Shadows::UpdateFBXSceneResource(FBXFile *a_pScene)
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

void Shadows::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// activate a shader
		glUseProgram( m_simpleShader );

		// get the location of uniforms on the shader
		GLint uDiffuseTexture	= glGetUniformLocation(m_simpleShader, "DiffuseTexture");
		GLint uModel			= glGetUniformLocation(m_simpleShader, "Model");
		GLint uView				= glGetUniformLocation(m_simpleShader, "View");
		GLint uProjection		= glGetUniformLocation(m_simpleShader, "Projection");

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
		glUniformMatrix4fv( uView,		 1, false, glm::value_ptr(a_view) );
		glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(a_projection) );

		// bind our vertex array object
		// remember in the initialise function, we bound the VAO and IBO to the VAO
		// so when we bind the VAO, openGL knows what what vertices,
		// indices and vertex attributes to send to the shader
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	// finally, we have finished rendering the meshes
	// disable this shader
	glUseProgram(0);
}

void Shadows::drawScene()
{
	// set to render to the back-buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	glViewport(0, 0, DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );

	//use the selected shader program
	glUseProgram(m_shaderProgram);

	// bind the shadow map to texture slot 1
	unsigned int texLoc = glGetUniformLocation(m_shaderProgram, "shadowMap");
	glUniform1i(texLoc, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);

	// bind projection * view matrix
	unsigned int projectionView = glGetUniformLocation(m_shaderProgram,"projectionView");
	glUniformMatrix4fv(projectionView, 1, false, glm::value_ptr(m_projectionMatrix * viewMatrix));

	// bind light and shadow information
	unsigned int ambient = glGetUniformLocation(m_shaderProgram,"ambientLight");
	unsigned int lightPos = glGetUniformLocation(m_shaderProgram,"lightPos");
	glUniform3f(ambient, 0.5f, 0.5f,0.5f);
	glUniform3fv(lightPos, 1, glm::value_ptr(m_lightPosition));

	// set diffuse texture location for binding
	unsigned int diffuseMap = glGetUniformLocation(m_shaderProgram,"diffuseMap");
	glUniform1i(diffuseMap, 0);
	glActiveTexture(GL_TEXTURE0);

	// get the world transform location and shadow matrix location
	unsigned int world = glGetUniformLocation(m_shaderProgram,"world");
	unsigned int shadowMatrix = glGetUniformLocation(m_shaderProgram,"lightProjectionViewWorld");

	// render FBX scene
	for ( unsigned int i = 0 ; i < m_fbx->getMeshCount() ; ++i )
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);
		glUniformMatrix4fv(shadowMatrix, 1, false, glm::value_ptr(m_shadowProjectionViewMatrix * mesh->m_globalTransform));
		glUniformMatrix4fv(world, 1, false, glm::value_ptr(mesh->m_globalTransform));
		glBindTexture(GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture ]);

		glBindVertexArray( ((OGL_FBXRenderData*)mesh->m_userData)->VAO );
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void Shadows::RenderFBXSceneResourceFromLight(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		if(i != 1)
		{
			// activate a shader
			glUseProgram( m_RenderShadowMap );

			// get the current mesh
			FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

			// get the render data attached to the m_userData pointer for this mesh
			OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

			// get the location of uniforms on the shader
			GLint uLPVW = glGetUniformLocation(m_RenderShadowMap, "lightProjectionViewWorld");

			glUniformMatrix4fv(uLPVW, 1, false, glm::value_ptr(m_shadowProjectionViewMatrix * mesh->m_globalTransform));

			// bind our vertex array object
			// remember in the initialise function, we bound the VAO and IBO to the VAO
			// so when we bind the VAO, openGL knows what what vertices,
			// indices and vertex attributes to send to the shader
			glBindVertexArray(ro->VAO);
			glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	// finally, we have finished rendering the meshes
	// disable this shader
	glUseProgram(0);
}

void Shadows::freeMovement(glm::vec3& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up /* = glm::vec3(0,1,0) */)
{
	GLFWwindow* window = glfwGetCurrentContext();

	// Get the camera's forward, right, up, and location vectors
	glm::vec4 vForward		= glm::vec4(0,0,1,1);
	glm::vec4 vRight		= glm::vec4(1,0,0,1);
	glm::vec4 vUp			= glm::vec4(0,1,0,1);
	glm::vec4 vTranslation	= glm::vec4(a_transform, 1);

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
	//a_transform = vTranslation.xyz;
	if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		//std::cout << "Light Position X: " << a_transform.x << std::endl;
		//std::cout << "Light Position Y: " << a_transform.y << std::endl;
		//std::cout << "Light Position Z: " << a_transform.z << std::endl;
	}
}