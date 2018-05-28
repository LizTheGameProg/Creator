#include "SpaceTrain.h"
#include "Gizmos.h"
#include "Utilities.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#include "FBXManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;
SpaceTrain::SpaceTrain()
{

}

SpaceTrain::~SpaceTrain()
{

}

bool SpaceTrain::onCreate(int a_argc, char* a_argv[]) 
{
	//--------------------------------
	// Standard onCreate stuff
	//--------------------------------
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

	//--------------------------------
	// My initialization
	//--------------------------------
	FBXManager::Create();
	time = 0.0f;
	m_spherePos = glm::vec3(0, 2.925f, -9.925f);
	m_LightPos[0] = m_spherePos;
	
	{
		//--------------------------------
		// Creating a basic shader program
		//--------------------------------
	
		m_basicShader = new ShaderProgram();
		
		std::map<ShaderType, const char *> shaderMap;
		shaderMap[ShaderType::VERT] = "./Build/shaders/ForwardRendering.vert";
		shaderMap[ShaderType::FRAG] = "./Build/shaders/ForwardRendering.frag";
		
		const char* Inputs[] =  { "POSITION", "COLOUR", "NORMAL", "TANGENT", "BINORMAL", "INDICES", "WEIGHTS", "TEXCOORD1", "TEXCOORD2" };
		const char* Outputs[] = { "OUTCOLOUR" };
		
		m_basicShader->MakeProgram(shaderMap, Inputs, 9, Outputs, 1);
		
		//m_basicShader->m_uInfo["View"]				= (UniformInfo(UniformType::MAT4, &m_viewMatrix));
		//m_basicShader->m_uInfo["Projection"]		= (UniformInfo(UniformType::MAT4, &m_projectionMatrix));
		//m_basicShader->m_uInfo["LightPosition_W"]	= (UniformInfo(UniformType::VEC3, &m_LightPos, 1));
	}

	//{
	//	m_fbx = new FBXFile();
	//	m_fbx->load("./Build/models/Final/L1_spacetrain.fbx", FBXFile::UNITS_METER);
	//	fbxSR = new FBXSceneResource(m_fbx, m_basicShader);
	//	FBXManager::Get().AddNewFBXSceneResource(fbxSR);
	//}

	char * fileNames[16] = {"./Build/models/Final/L1_S0_carriage.fbx",
							"./Build/models/Final/L1_S0_skybox.fbx",
							"./Build/models/Final/L1_S1_archwaychair.fbx",
							"./Build/models/Final/L1_S1_eggchair.fbx",
							"./Build/models/Final/L1_S1_lounge.fbx",
							"./Build/models/Final/L1_S2_ashtray.fbx",
							"./Build/models/Final/L1_S2_bar.fbx",
							"./Build/models/Final/L1_S2_barstool.fbx",
							"./Build/models/Final/L1_S2_chair.fbx",
							"./Build/models/Final/L1_S2_hanginglight.fbx",
							"./Build/models/Final/L1_S2_menu.fbx",
							"./Build/models/Final/L1_S2_pepper.fbx",
							"./Build/models/Final/L1_S2_salt.fbx",
							"./Build/models/Final/L1_S2_table.fbx",
							"./Build/models/Final/L1_S2_walllight.fbx",
							"./Build/models/Final/L1_S2_windows.fbx"};
	
	for(int i = 0; i < 16; i++)
	{
		m_fbx = new FBXFile();
		m_fbx->load(fileNames[i], FBXFile::UNITS_METER);
		fbxSR = new FBXSceneResource(m_fbx, m_basicShader, false);
		FBXManager::Get().AddNewFBXSceneResource(fbxSR);
	}

	{
		m_fbx = new FBXFile();
		m_fbx->load("./Build/models/Pyro/Pyro.fbx", FBXFile::UNITS_METER);
		fbxSR = new FBXSceneResource(m_fbx, m_basicShader, true);
		FBXManager::Get().AddNewFBXSceneResource(fbxSR);
	}

	//--------------------------------
	// Create a particle emitter for the stars that will be going past the space train
	//--------------------------------
	m_particleEmitter_Positive = new ParticleEmitter();
	m_particleEmitter_Positive->initalise(1000, 
			     50.0f, 100.0f, 25, 100, 0.1f, 0.5f,
			     glm::vec4(1,1,0,1.0f), glm::vec4(1,0,0,0.0f), 1.0);
	m_particleEmitter_Negative = new ParticleEmitter();
	m_particleEmitter_Negative->initalise(1000, 
			     50.0f, 100.0f, 25, 100, 0.1f, 0.5f,
			     glm::vec4(1,1,0,1.0f), glm::vec4(1,0,0,0.0f), -1.0);

	return true;
}

void SpaceTrain::onUpdate(float a_deltaTime) 
{
	time += a_deltaTime;

	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	FBXManager::Get().Update();

	freeMovement(m_spherePos, a_deltaTime, 4);
	m_LightPos[0] = m_spherePos;
}

void SpaceTrain::onDraw() 
{
	// switch back to rendering to the back buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get the view matrix from the world-space camera matrix
	m_viewMatrix = glm::inverse( m_cameraMatrix );
	
	Gizmos::addSphere(m_spherePos, 8, 8, 0.1f, glm::vec4(0,1,1,1));

	// draw the gizmos from this frame
	Gizmos::draw(m_viewMatrix, m_projectionMatrix);

	// Render all FBXFiles
	FBXManager::Get().Render(m_cameraMatrix, m_projectionMatrix, time);

	m_particleEmitter_Positive->draw(m_cameraMatrix, m_projectionMatrix);
	m_particleEmitter_Negative->draw(m_cameraMatrix, m_projectionMatrix);
}

void SpaceTrain::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	delete m_basicShader;
	m_basicShader = nullptr;

	FBXManager::Destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new SpaceTrain();
	
	if (app->create("AIE - SpaceTrain",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;
	
	_CrtDumpMemoryLeaks();

	return 0;
}

void SpaceTrain::freeMovement(glm::vec3& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up /* = glm::vec3(0,1,0) */)
{
	GLFWwindow* window = glfwGetCurrentContext();

	// Get the camera's forward, right, up, and location vectors
	glm::vec3 vForward		= glm::vec3(0,0,1);
	glm::vec3 vRight		= glm::vec3(1,0,0);
	glm::vec3 vUp			= glm::vec3(0,1,0);
	glm::vec3 vTranslation	= a_transform;

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
	a_transform = vTranslation;
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		PrintSpherePosition();
	}
}

void SpaceTrain::PrintSpherePosition()
{
	//std::cout << "Sphere X: " << m_spherePos.x << ", Sphere Y: " << m_spherePos.y << ", Sphere Z: " << m_spherePos.z << std::endl;
}