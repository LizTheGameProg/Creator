//#include "Game.h"
////Game * Game::m_game = nullptr;
//
//#include "glm\ext.hpp"
//
//#include "Gizmos.h"
//#include "InputHandler.h"
//
//#include "openGLBindings.h"
//#include "Shader.h"
//
//#include <iostream>
//
//Game::Game(WindowInfo & a_windowInfo) : deltaTime(0.f), thisTotalTicks(0), lastTotalTicks(0), timeSinceLaunch(0.f), quitOnEscape(true), quit(false)
//{
//	m_window = new Window_GLFW(a_windowInfo);
//
//	openGLBindings::init();
//
//	// Initialise the inputHandler so that input can be detected
//	InputHandler::Create();
//	inputHandler = InputHandler::Get();
//
//	// Set the callback function to handle keyboard button input
//	glfwSetKeyCallback(((Window_GLFW*) m_window)->GetGLFWWindow(), &(inputHandler->glfwKeyboardButtonCallBack));
//
//	// Initialise gizmos so that primitives can be drawn
//	Gizmos::Create();
//}
//
//Game::~Game()
//{
//	InputHandler::Destroy();
//	Gizmos::Destroy();
//	glDeleteProgram(Shader::getBasicShaderID());
//	delete m_window;
//}
//
//void Game::Run()
//{
//	glClearColor(0.25f, 0.25f, 0.25f, 1);
//	glEnable(GL_DEPTH_TEST);
//
//	while(!quit)
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//		UpdateDeltaTime();
//
//		// Poll Events
//		PollEvents();
//		
//		// Remove the stuff that was drawn last frame
//		Gizmos::Clear();
//
//		Update();
//		Render();
//
//		m_window->SwapBuffers();
//	}
//}
//
//void Game::PollEvents()
//{
//	glfwPollEvents();
//	quit = (quitOnEscape ? InputHandler::Get()->isKeyDown("ESCAPE") : false) || glfwWindowShouldClose(((Window_GLFW *)GetWindow())->GetGLFWWindow());
//}
//
//void Game::UpdateDeltaTime()
//{
//	// Update the last frames total number of ticks to this frames total number of ticks : thisTotalTicks is now last frames information
//	lastTotalTicks = thisTotalTicks;
//
//	// Update the total number of ticks
//	thisTotalTicks = glfwGetTime();
//
//	// DeltaTime is the difference between the two
//	deltaTime = ((float)thisTotalTicks - (float)lastTotalTicks);
//
//	timeSinceLaunch = (float)thisTotalTicks;
//}
//
//float Game::TimeSinceLaunch()
//{
//	return timeSinceLaunch;
//}