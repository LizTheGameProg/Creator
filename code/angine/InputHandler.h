#pragma once

#include "GLFW\glfw3.h"
#include <string>
#include <vector>
#include <map>

#include "glm\vec2.hpp"

namespace ANGINE
{
	typedef void(*buttonDown)();
	typedef void(*buttonUp)  ();
	typedef void(*buttonHeld)();

	typedef void(*mouseScroll)();
	typedef void(*mouseMove)	();

	enum ButtonState
	{
		PRESSED = 1,
		DOWN = 2,
		RELEASED = 3
	};

	struct Button
	{
		ButtonState state;

		std::vector<buttonDown> buttonDownFunctions;
		std::vector<buttonUp>	buttonUpFunctions;
		std::vector<buttonHeld> buttonHeldFunctions;
	};

	class InputHandler
	{
	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Singleton Related Functions
		static void Create();
		static void Destroy();
		static InputHandler * Get();

	private:
		InputHandler();

	public:
		~InputHandler();
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	private:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Singleton Related Variables
		static InputHandler * instance;
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Instance Related Functions

		bool isButtonUp(std::string buttonName);
		bool isButtonDown(std::string buttonName);
		bool wasButtonPressed(std::string buttonName);

		void bindButtonDownCallback(std::string buttonName, buttonDown callbackFunction);
		void bindButtonUpCallback(std::string buttonName, buttonUp   callbackFunction);
		void bindButtonHeldCallback(std::string buttonName, buttonHeld callbackFunction);

		void unbindButtonDownCallback(std::string buttonName, buttonDown callbackFunction);
		void unbindButtonUpCallback(std::string buttonName, buttonUp   callbackFunction);
		void unbindButtonHeldCallback(std::string buttonName, buttonHeld callbackFunction);

		void updateKey(std::string key, ButtonState buttonState);

		void updateMouseButton(std::string key, ButtonState buttonState);
		void updateMouseCursor(double xPos, double yPos);
		void updateMouseScroll(double xOffset, double yOffset);

		glm::vec2 cursorPosition;
		glm::vec2 scrollPosition;

		std::map<std::string, Button> buttonMap;

		std::vector<mouseMove>	 mouseCursorMoveFunctions;
		std::vector<mouseScroll> mouseScrollFunctions;

		// KEYBOARD RELATED
		bool isKeyDown(std::string key);
		bool isKeyUp(std::string key);

		bool wasKeyPressed(std::string key);

		//void addOnKeyDownFunction(std::string key, onKeyDown functionToBeCalled);
		//void addOnKeyUpFunction	 (std::string key, onKeyUp	 functionToBeCalled);
		//void addOnKeyHeldFunction(std::string key, onKeyHeld functionToBeCalled);



		// MOUSE RELATED
		bool isMouseButtonDown(std::string key);
		bool isMouseButtonUp(std::string key);

		bool wasMouseButtonPressed(std::string key);

		//void addOnMouseButtonDownFunction(std::string key, onMouseButtonDown functionToBeCalled);
		//void addOnMouseButtonUpFunction(std::string key, onMouseButtonUp functionToBeCalled);
		//void addOnMouseButtonHeldFunction(std::string key, onMouseButtonHeld functionToBeCalled);
		//void addOnMouseCursorMoveFunction(onMouseCursorMove functionToBeCalled);
		//void addOnMouseScrollFunction(onMouseScroll functionToBeCalled);





	private:
		void callOnKeyDownFunctions(std::string key);
		void callOnKeyUpFunction(std::string key);
		void callOnKeyHeldFunction(std::string key);

		void callOnMouseButtonDownFunction(std::string mouseButton);
		void callOnMouseButtonUpFunction(std::string mouseButton);
		void callOnMouseButtonHeldFunction(std::string mouseButton);
		void callOnMouseCursorMoveFunction();
		void callOnMouseScrollFunction();
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// GLFW callback functions
		static void glfwKeyboardButtonCallBack(GLFWwindow * window, int key, int scancode, int action, int mods);

		static void glfwMouseCursorCallBack(GLFWwindow * window, double xPos, double yPos);
		static void glfwMouseButtonCallBack(GLFWwindow * window, int button, int action, int mods);
		static void glfwMouseScrollCallBack(GLFWwindow * window, double xOffset, double yOffset);
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// my GLFW Utilities
		static std::string	getGLFWKeyName(int keyCode);
		static std::map<int, std::vector<std::string>> keyCodeToName;
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	private:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Instance Related Variables
		std::map<std::string, ButtonState> buttonStateMap; // Map that contains a key value pair of a string that represents a keyboard button or a mouse button and it's state

		// KEYBOARD RELATED
		//std::map<std::string, std::vector<onKeyDown>> keyDownFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyDown functions
		//std::map<std::string, std::vector<onKeyUp>>	  keyUpFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyUp functions
		//std::map<std::string, std::vector<onKeyHeld>> keyHeldFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyHeld functions

		// MOUSE RELATED
		//std::map<std::string, std::vector<onMouseButtonDown>> mouseButtonDownFunctionsMap;
		//std::map<std::string, std::vector<onMouseButtonUp>>	  mouseButtonUpFunctionsMap;
		//std::map<std::string, std::vector<onMouseButtonHeld>> mouseButtonHeldFunctionsMap;

		//std::vector<onMouseCursorMove> mouseCursorMoveFunctions;
		//std::vector<onMouseScroll>	   mouseScrollFunctions;

		double cursorXPosition;
		double cursorYPosition;
		double scrollXPosition;
		double scrollYPosition;
		//// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//// Instace Related Variables
		//std::map<std::string, ButtonState> buttonStateMap; // Map that contains a key value pair of a string that represents a keyboard button or a mouse button and it's state
		//
		//// KEYBOARD RELATED
		//std::map<std::string, std::vector<onKeyDown>> keyDownFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyDown functions
		//std::map<std::string, std::vector<onKeyUp>>	  keyUpFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyUp functions
		//std::map<std::string, std::vector<onKeyHeld>> keyHeldFunctionsMap; // Map that contains a key value pair of a string and a list of onKeyHeld functions
		//
		//// MOUSE RELATED
		//std::map<std::string, std::vector<onMouseButtonDown>> mouseButtonDownFunctionsMap;
		//std::map<std::string, std::vector<onMouseButtonUp>>	  mouseButtonUpFunctionsMap;
		//std::map<std::string, std::vector<onMouseButtonHeld>> mouseButtonHeldFunctionsMap;
		//
		//
		//

		//double cursorXPosition;
		//double cursorYPosition;
		//double scrollXPosition;
		//double scrollYPosition;
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	};
}