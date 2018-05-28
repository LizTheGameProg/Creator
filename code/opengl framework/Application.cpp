//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	17/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	18/08/2015
//--------------------------------

#include "Application.h"
#include "Window.h"
#include <iostream>
#include "Sprite.h"
#include "Camera.h"
#include "InputHandler.h"
namespace openGL
{
	Application::Application() : m_lastError(ERROR::NONE),
		m_window(nullptr),
		m_camera(nullptr),
		m_lastFrameTime(0.0),
		m_deltaTime(0.0)
	{
		glewExperimental = GL_TRUE;

		// Sets the function to be called when there is an error
		glfwSetErrorCallback(&Application::ErrorCallBack);
	}

	Application::~Application()
	{

	}

	int Application::StartUp(GLuint a_windowWidth, GLuint a_windowHeight, GLboolean a_fullScreen, const GLchar * title)
	{
		// Initialise the glfw framework : this needs to be done before almost any glfw function can be used
		if(glfwInit() == GL_FALSE)
		{
			// If the glfw framework failed to initialised then set the last error and return
			m_lastError = ERROR::GLFW_INIT_FAILED;
			return GL_FALSE;
		}

		// Fill a struct with the information we want for when the window is created
		WindowInfo info = {a_windowWidth, a_windowHeight, title, a_fullScreen};

		// Make the window, passing through the information we just set
		m_window = new Window(this, info);

		// Check that the window was succsessfully created
		if(m_window->GetWindow() == nullptr)
		{
			// If it wasn't then terminate the glfw framework, set the last error and return
			glfwTerminate();
			m_lastError = ERROR::GLFW_WINDOW_CREATION_FAILED;
			return GL_FALSE;
		}

		// Initialise the glew framework
		if(glewInit() != GLEW_OK)
		{
			// If the glew framework failed to initialise then set the last error and return
			m_lastError = ERROR::GLEW_INIT_FAILED;
			return GL_FALSE;
		}

		// If the code runs to here then everything was successfully setup and we can return true
		return GL_TRUE;
	}

	void Application::Run()
	{
		// Create game related content
		Create();

		// From here the game will run in a loop untill the window should close (X is pressesed in the top right of the window, or ESC is pressed)
		while(!glfwWindowShouldClose(m_window->GetWindow()))
		{
			// Set the background colour
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT);

			// Update events (i.e.: keyboard and mouse input)
			glfwPollEvents();

			// Update deltaTime based on the difference of time between this frame and the last frame
			GLdouble l_time = glfwGetTime();
			m_deltaTime = l_time - m_lastFrameTime;
			m_lastFrameTime = l_time;

			// Call the update function where most of code will go
			Update((GLfloat) m_deltaTime);

			// Call the render function where we will render all our stuff
			Render();

			// Swap the front and back buffer
			glfwSwapBuffers(m_window->GetWindow());
		}

		// Delete game releted content
		Destroy();
	}

	void Application::ShutDown()
	{
		// Destroy the window
		delete m_window;

		// Shutdown the glfw framework
		glfwTerminate();
	}

	void Application::ErrorCallBack(GLint a_error, const GLchar * a_description)
	{
		// Output the error code and description to the console
		printf("Error %i:\t%s\n", a_error, a_description);
	}

	void Application::Create()
	{
		m_camera = new Camera2D();

		// Creation code that is releated to the game goes here
		m_testSprite = new Sprite();
	}

	void Application::Destroy()
	{
		// Deletion code that is releated to the game goes here
		delete m_testSprite;

		// Destroy the camera
		delete m_camera;
	}

	void Application::Update(GLfloat a_deltaTime)
	{
		// Update code for our game
		m_testSprite->Update(a_deltaTime);
	}

	void Application::Render()
	{
		// Render code for our game
		m_testSprite->Render(m_camera->GetProjectionView());
	}
}