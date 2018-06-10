#include "MultipleTextures_Tutorial.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

MultipleTextures_Tutorial::MultipleTextures_Tutorial()
{

}

MultipleTextures_Tutorial::~MultipleTextures_Tutorial()
{

}

bool MultipleTextures_Tutorial::onCreate(int a_argc, char* a_argv[]) 
{
	m_time = 0.0f;

	// load the shader
	const char* aszInputs[] =  {"Position", "Normal", "Tangent", "BiNormal", "TexCoord1",};
	const char* aszOutputs[] = { "outColour" };

	// load shader internally calls glCreateShader...
	GLuint vshader = Utility::loadShader("../../Build/shaders/MultipleTexture_Exercise.vert", GL_VERTEX_SHADER);
	GLuint pshader = Utility::loadShader("../../Build/shaders/MultipleTexture_Exercise.frag", GL_FRAGMENT_SHADER);

	m_shader = Utility::createProgram( vshader, 0, 0, 0, pshader, 3, aszInputs, 1, aszOutputs);

	// free our shader once we built our program
	glDeleteShader( vshader );
	glDeleteShader( pshader );

	m_fbx = new FBXFile();
	m_fbx->load( "../../Build/models/soulspear/soulspear.fbx", FBXFile::UNITS_CENTIMETER );
	InitFBXSceneResource( m_fbx );

	m_decayTexture = SOIL_load_OGL_texture("../../Build/textures/decay.png", 4, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);
	m_decayValue = 1;


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

void MultipleTextures_Tutorial::onUpdate(float a_deltaTime) 
{
	m_time += a_deltaTime;

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

	if (glfwGetKey(m_window,GLFW_KEY_LEFT) == GLFW_PRESS) m_decayValue -= a_deltaTime;
	if (glfwGetKey(m_window,GLFW_KEY_RIGHT) == GLFW_PRESS) m_decayValue += a_deltaTime;
	
	if( m_decayValue < 0.0f) m_decayValue = 0.0f;
	if( m_decayValue > 1.0f) m_decayValue = 1.0f;

	UpdateFBXSceneResource(m_fbx);

}

void MultipleTextures_Tutorial::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );

	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	RenderFBXSceneResource( m_fbx, viewMatrix, m_projectionMatrix );
}

void MultipleTextures_Tutorial::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	glDeleteShader(m_shader);
	glDeleteTextures(1, &m_decayTexture);

	DestroyFBXSceneResource( m_fbx );
	m_fbx->unload();
	delete m_fbx;
	m_fbx = NULL;

}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new MultipleTextures_Tutorial();
//
//	if (app->create("AIE - FBX Tutorial",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}

void MultipleTextures_Tutorial::InitFBXSceneResource(FBXFile *a_pScene)
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

void MultipleTextures_Tutorial::DestroyFBXSceneResource(FBXFile *a_pScene)
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

void MultipleTextures_Tutorial::UpdateFBXSceneResource(FBXFile *a_pScene)
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

void MultipleTextures_Tutorial::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	// enable transparent blending
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// activate a shader
	glUseProgram( m_shader );

	GLint uMVP					= glGetUniformLocation(m_shader, "MVP");
	GLint uMV					= glGetUniformLocation(m_shader, "MV");
	GLint uNormalMatrix			= glGetUniformLocation(m_shader, "NormalMatrix");
	GLint uLightPosition		= glGetUniformLocation(m_shader, "LightPosition");
	
	GLint uDiffuseTexture		= glGetUniformLocation(m_shader, "DiffuseTexture");
	GLint uNormalTexture		= glGetUniformLocation(m_shader, "NormalTexture");
	GLint uSpecularTexture		= glGetUniformLocation(m_shader, "SpecularTexture");
	GLint uAmbientLightColor	= glGetUniformLocation(m_shader, "AmbientLightColor");
	GLint uLightColor			= glGetUniformLocation(m_shader, "LightColor");
	GLint uToggle				= glGetUniformLocation(m_shader, "toggle");


	// get the location of uniforms on the shader
	
	GLint uDiffuseColor			= glGetUniformLocation(m_shader, "DiffuseColor");	

	GLint uModel				= glGetUniformLocation(m_shader, "Model");
	GLint uView					= glGetUniformLocation(m_shader, "View");
	GLint uProjection			= glGetUniformLocation(m_shader, "Projection");

	GLint uDecayTexture			= glGetUniformLocation(m_shader, "DecayTexture");
	GLint uDecayValue			= glGetUniformLocation(m_shader, "DecayValue");
	
	// for each mesh in the model...
	for(unsigned int i=0; i<a_pScene->getMeshCount(); ++i)
	{
		// get the current mesh
		FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

		// get the render data attached to the m_userData pointer for this mesh
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

		// Bind the texture to one of the ActiveTextures
		// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture] );

		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_2D, m_decayTexture );

		// tell the shader which texture to use
		glUniform1i( uDiffuseTexture, 1 );
		glUniform1i( uDecayTexture, 2 );

		// tell the shader the decay value
		glUniform1f( uDecayValue, m_decayValue );
	 
		// send the Model, View and Projection Matrices to the shader
		glUniformMatrix4fv( uModel,			1, false, glm::value_ptr(mesh->m_globalTransform) );
		glUniformMatrix4fv( uView,			1, false, glm::value_ptr(a_view) );
		glUniformMatrix4fv( uProjection,	1, false, glm::value_ptr(a_projection) );

		// bind our vertex array object
		// remember in the initialise function, we bound the VAO and IBO to the VAO
		// so when we bind the VAO, openGL knows what what vertices,
		// indices and vertex attributes to send to the shader
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);

	}

	// reset back to the default active texture
	glActiveTexture( GL_TEXTURE0 );

	// finally, we have finished rendering the meshes
	// disable this shader
	glUseProgram(0);
}