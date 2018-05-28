#include "BaseApplication.h"
#include "FlyCamera3D.h"

#include "Gizmos.h"

#include <glm\glm.hpp>
#include <glm\ext.hpp>

// needed for printf
#include <iostream>

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

using namespace INTRO_OPENGL;
using namespace ANGINE;

BaseApplication::BaseApplication()
{
#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
}

BaseApplication::~BaseApplication()
{

}

bool BaseApplication::startUp()
{
	// Initalise the glfw framework
	if(glfwInit() == false)
		return false;
	
	// Create a window to render things to
	window = glfwCreateWindow(1280, 720, "Introduction To OpenGL", nullptr, nullptr);

	// Check if window creation was successful
	if(window == nullptr)
	{
		// if not: Terminate the glfw framework
		glfwTerminate();
		return false;
	}
	
	// Make the newly created window the window that has focus
	glfwMakeContextCurrent(window);

	// Load openGL functions and check if the load was successful
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// if not: destroy our window and terminate the glfw framwork
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	// Initialise aies' gizmos class
	Gizmos::Create();
	
	view = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();
	
	printf("OpenGL Version: %i.%i\n", major, minor);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glEnable(GL_DEPTH_TEST);
	
	camera = new INTRO_OPENGL::FlyCamera3D();

	lastFrameTime = 0.f;
	thisFrameTime = 0.f;

	return true;
}

void BaseApplication::shutDown()
{
	delete camera;
	Gizmos::Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool BaseApplication::update()
{
	// Exit if the user has pressed the close button or pressed ESC
	if (!(glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
		return false;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::Clear();

	// do stuff here
	lastFrameTime = thisFrameTime;
	thisFrameTime = glfwGetTime();
	deltaTime = float(thisFrameTime - lastFrameTime);

	camera->update(window, deltaTime);

	return true;
}

void BaseApplication::render()
{
	Gizmos::AddTransform(glm::mat4(1));
	
	Gizmos::Draw(camera->getProjectionView());

	glfwSwapBuffers(window);
	glfwPollEvents();
}