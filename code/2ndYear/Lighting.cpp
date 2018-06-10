#include "Lighting.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

Lighting::Lighting()
{

}

Lighting::~Lighting()
{

}

bool Lighting::onCreate(int a_argc, char* a_argv[]) 
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
	
	{
		// load shaders and link shader program
		unsigned int m_vertShader = Utility::loadShader("../../Build/shaders/lit.vert", GL_VERTEX_SHADER);
		unsigned int m_fragShader = Utility::loadShader("../../Build/shaders/lit.frag", GL_FRAGMENT_SHADER);
		const char* inputs[] = { "Position", "Normal"};
		m_shader = Utility::createProgram(m_vertShader, 0, 0, 0, m_fragShader, 2, inputs);

		glDeleteShader(m_vertShader);
		glDeleteShader(m_fragShader);
	}

	m_fbx = new FBXFile();
	m_fbx->load("../../Build/models/stanford/Bunny.fbx");
	InitFBXSceneResource(m_fbx);

	return true;
}

void Lighting::onUpdate(float a_deltaTime) 
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

void Lighting::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	RenderFBXSceneResource( m_fbx, viewMatrix, m_projectionMatrix );
}

void Lighting::onDestroy()
{
	DestroyFBXSceneResource( m_fbx );
	m_fbx->unload();
	delete m_fbx;
	m_fbx = nullptr;

	// clean up anything we created
	Gizmos::destroy();
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new Lighting();
//	
//	if (app->create("AIE - Lighting",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}

void Lighting::InitFBXSceneResource(FBXFile *a_pScene)
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
		//glEnableVertexAttribArray(2);
		
		// tell our shaders where the information within our buffers lie
		// eg: attrubute 0 is expected to be the verticy's position. it should be 4 floats, representing xyzw
		// eg: attrubute 1 is expected to be the verticy's color. it should be 4 floats, representing rgba
		// eg: attrubute 2 is expected to be the verticy's texture coordinate. it should be 2 floats, representing U and V
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::PositionOffset);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::ColourOffset);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord1Offset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::NormalOffset);

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

void Lighting::DestroyFBXSceneResource(FBXFile *a_pScene)
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

void Lighting::UpdateFBXSceneResource(FBXFile *a_pScene)
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

void Lighting::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection)
{
	//// activate a shader
	//glUseProgram( m_shader );

	//// get the location of uniforms on the shader
	//GLint uDiffuseTexture = glGetUniformLocation(m_shader, "DiffuseTexture");
	//GLint uDiffuseColor   = glGetUniformLocation(m_shader, "DiffuseColor");	

	//GLint uModel      = glGetUniformLocation(m_shader, "Model");
	//GLint uView       = glGetUniformLocation(m_shader, "View");
	//GLint uProjection = glGetUniformLocation(m_shader, "Projection");
	//
	//// for each mesh in the model...
	//for(int i=0; i<a_pScene->getMeshCount(); ++i)
	//{
	//	// get the current mesh
	//	FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

	//	// get the render data attached to the m_userData pointer for this mesh
	//	OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

	//	// Bind the texture to one of the ActiveTextures
	//	// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
	//	glActiveTexture( GL_TEXTURE1 );
	//	glBindTexture( GL_TEXTURE_2D, mesh->m_material->textureIDs[ FBXMaterial::DiffuseTexture] );

	//	
	//	// reset back to the default active texture
	//	glActiveTexture( GL_TEXTURE0 );

	//	// tell the shader which texture to use
	//	glUniform1i( uDiffuseTexture, 1 );
	// 
	//	// send the Model, View and Projection Matrices to the shader
	//	glUniformMatrix4fv( uModel,	     1, false, glm::value_ptr(mesh->m_globalTransform) );
	//	glUniformMatrix4fv( uView,       1, false, glm::value_ptr(a_view) );
	//	glUniformMatrix4fv( uProjection, 1, false, glm::value_ptr(a_projection) );

	//	// bind our vertex array object
	//	// remember in the initialise function, we bound the VAO and IBO to the VAO
	//	// so when we bind the VAO, openGL knows what what vertices,
	//	// indices and vertex attributes to send to the shader
	//	glBindVertexArray(ro->VAO);
	//	glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);

	//}

	//// finally, we have finished rendering the meshes
	//// disable this shader
	//glUseProgram(0);

	// bind shader to the GPU
	glUseProgram(m_shader);

	// fetch locations of the view and projection matrices and bind them
	unsigned int location = glGetUniformLocation(m_shader,"view");
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(a_view));

	location = glGetUniformLocation(m_shader,"projection");
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(m_projectionMatrix));

	// send camera position
	location = glGetUniformLocation(m_shader,"cameraPosition");
	glUniform3fv(location, 1, glm::value_ptr(m_cameraMatrix[3]));

	location = glGetUniformLocation(m_shader, "lightAmbient");
	glUniform3fv(location, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));

	location = glGetUniformLocation(m_shader, "lightDirection");
	glUniform3fv(location, 1, glm::value_ptr(glm::vec3(1,-1,1)));

	location = glGetUniformLocation(m_shader, "lightColour");
	glUniform3fv(location, 1, glm::value_ptr(glm::vec3(0,1,1)));

	location = glGetUniformLocation(m_shader, "lightSpecular");
	glUniform3fv(location, 1, glm::value_ptr(glm::vec3(0.5f,0.5f,0.5f)));

	// bind our vertex array object and draw the mesh
	for ( unsigned int i = 0 ; i < m_fbx->getMeshCount() ; ++i )
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);

		unsigned int* glData = (unsigned int*)mesh->m_userData;
		
		glBindVertexArray( glData[0] );
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

