#include "DIYPhysicScene.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Scene.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

DIYPhysicScene::DIYPhysicScene()
{

}

DIYPhysicScene::~DIYPhysicScene()
{

}

bool DIYPhysicScene::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create(100000, 100000);
	
	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_scene = new Scene(glm::vec3(0,-10,0), 1.0f/60.0f);
	glfwSwapInterval(0);
	return true;
}

void DIYPhysicScene::onUpdate(float a_deltaTime) 
{
	// clear all gizmos from last frame
	Gizmos::clear();

	// add a 20x20 grid on the XZ-plane
	//for ( int i = 0 ; i < 21 ; ++i )
	//{
	//	Gizmos::addLine( glm::vec3(-10 + i, 10, 0), glm::vec3(-10 + i, -10, 0), i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//	
	//	Gizmos::addLine( glm::vec3(10, -10 + i, 0), glm::vec3(-10, -10 + i, 0), i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	m_scene->update();
}

void DIYPhysicScene::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_scene->render();
}

void DIYPhysicScene::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	delete m_scene;
	m_scene = nullptr;
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new DIYPhysicScene();
	
	if (app->create("AIE - DIYPhysicScene",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	_CrtDumpMemoryLeaks();

	return 0;
}