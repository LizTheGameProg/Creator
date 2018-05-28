#include "InputHandler.h"
#include <iostream>
namespace ANGINE
{
	InputHandler * InputHandler::instance = nullptr;

	std::map<int, std::vector<std::string>> InputHandler::keyCodeToName =
	{
		{-1, {"UNKNOWN"}},
		{32, {"SPACE", " "}},
		{39, {"APOSTROPHE", "'"}},
		{44, {"COMMA", ","}},
		{45, {"MINUS", "-"}},
		{46, {"PERIOD", "."}},
		{47, {"SLASH", "/"}},
		{48, {"0"}},
		{49, {"1"}},
		{50, {"2"}},
		{51, {"3"}},
		{52, {"4"}},
		{53, {"5"}},
		{54, {"6"}},
		{55, {"7"}},
		{56, {"8"}},
		{57, {"9"}},
		{59, {"SEMICOLON", ";"}},
		{61, {"EQUAL", "="}},
		{65, {"A"}},
		{66, {"B"}},
		{67, {"C"}},
		{68, {"D"}},
		{69, {"E"}},
		{70, {"F"}},
		{71, {"G"}},
		{72, {"H"}},
		{73, {"I"}},
		{74, {"J"}},
		{75, {"K"}},
		{76, {"L"}},
		{77, {"M"}},
		{78, {"N"}},
		{79, {"O"}},
		{80, {"P"}},
		{81, {"Q"}},
		{82, {"R"}},
		{83, {"S"}},
		{84, {"T"}},
		{85, {"U"}},
		{86, {"V"}},
		{87, {"W"}},
		{88, {"X"}},
		{89, {"Y"}},
		{90, {"Z"}},
		{91, {"LEFT_BRACKET", "["}},
		{92, {"BACKSLASH", "\\"}},
		{93, {"RIGHT_BRACKET", "]"}},
		{96, {"GRAVE_ACCENT", "`"}},
		{161, {"WORLD_1"}},
		{162, {"WORLD_2"}},
		{256, {"ESCAPE"}},
		{257, {"ENTER", "\n"}},
		{258, {"TAB", "	", "\t"}},
		{259, {"BACKSPACE"}},
		{260, {"INSERT"}},
		{261, {"DELETE"}},
		{262, {"RIGHT"}},
		{263, {"LEFT"}},
		{264, {"DOWN"}},
		{265, {"UP"}},
		{266, {"PAGE_UP"}},
		{267, {"PAGE_DOWN"}},
		{268, {"HOME"}},
		{269, {"END"}},
		{280, {"CAPS_LOCK"}},
		{281, {"SCROLL_LOCK"}},
		{282, {"NUM_LOCK"}},
		{283, {"PRINT_SCREEN"}},
		{284, {"PAUSE"}},
		{290, {"F1"}},
		{291, {"F2"}},
		{292, {"F3"}},
		{293, {"F4"}},
		{294, {"F5"}},
		{295, {"F6"}},
		{296, {"F7"}},
		{297, {"F8"}},
		{298, {"F9"}},
		{299, {"F10"}},
		{300, {"F11"}},
		{301, {"F12"}},
		{302, {"F13"}},
		{303, {"F14"}},
		{304, {"F15"}},
		{305, {"F16"}},
		{306, {"F17"}},
		{307, {"F18"}},
		{308, {"F19"}},
		{309, {"F20"}},
		{310, {"F21"}},
		{311, {"F22"}},
		{312, {"F23"}},
		{313, {"F24"}},
		{314, {"F25"}},
		{320, {"KP_0"}},
		{321, {"KP_1"}},
		{322, {"KP_2"}},
		{323, {"KP_3"}},
		{324, {"KP_4"}},
		{325, {"KP_5"}},
		{326, {"KP_6"}},
		{327, {"KP_7"}},
		{328, {"KP_8"}},
		{329, {"KP_9"}},
		{330, {"KP_DECIMAL"}},
		{331, {"KP_DIVIDE"}},
		{332, {"KP_MULTIPLY"}},
		{333, {"KP_SUBTRACT"}},
		{334, {"KP_ADD"}},
		{335, {"KP_ENTER"}},
		{336, {"KP_EQUAL"}},
		{340, {"LEFT_SHIFT", "SHIFT"}},
		{341, {"LEFT_CONTROL", "CONTROL"}},
		{342, {"LEFT_ALT", "ALT"}},
		{343, {"LEFT_SUPER"}},
		{344, {"RIGHT_SHIFT", "SHIFT"}},
		{345, {"RIGHT_CONTROL", "CONTROL"}},
		{346, {"RIGHT_ALT", "ALT"}},
		{347, {"RIGHT_SUPER"}},
		{348, {"MENU"}}
	};

	void InputHandler::Create()
	{
		if(instance != nullptr)
			return;
		instance = new InputHandler();
	}

	void InputHandler::Destroy()
	{
		if(instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	InputHandler * InputHandler::Get()
	{
		return instance;
	}

	InputHandler::InputHandler()
	{
		cursorXPosition = 0.0;
		cursorYPosition = 0.0;
		scrollXPosition = 0.0;
		scrollYPosition = 0.0;
	}

	InputHandler::~InputHandler()
	{

	}

	bool InputHandler::isKeyDown(std::string key)
	{
		if(buttonStateMap[key] == ButtonState::DOWN ||
			buttonStateMap[key] == ButtonState::PRESSED)
		{
			return true;
		}
		return false;
	}

	bool InputHandler::isKeyUp(std::string key)
	{
		if(buttonStateMap[key] == ButtonState::RELEASED)
			return true;
		return false;
	}

	bool InputHandler::wasKeyPressed(std::string key)
	{
		if(buttonStateMap[key] == ButtonState::PRESSED)
			return true;
		return false;
	}

	//void InputHandler::addOnKeyDownFunction(std::string key, onKeyDown functionToBeCalled)
	//{
	//	keyDownFunctionsMap[key].push_back(functionToBeCalled);
	//}
	//
	//void InputHandler::addOnKeyUpFunction(std::string key, onKeyUp functionToBeCalled)
	//{
	//	keyUpFunctionsMap[key].push_back(functionToBeCalled);
	//}
	//
	//void InputHandler::addOnKeyHeldFunction(std::string key, onKeyHeld functionToBeCalled)
	//{
	//	keyHeldFunctionsMap[key].push_back(functionToBeCalled);
	//}

	void InputHandler::updateKey(std::string key, ButtonState buttonState)
	{
		//std::cout << key << std::endl;
		switch(buttonStateMap[key])
		{
		case PRESSED:
		{
			if(buttonState == DOWN)
			{
				buttonStateMap[key] = DOWN;
			}
			else if(buttonState == RELEASED)
			{
				buttonStateMap[key] = RELEASED;

				//for (int i = 0; i < keyUpFunctionsMap[key].size(); i++)
				//{
				//	keyUpFunctionsMap[key][i]();
				//}
			}
			else
			{
				buttonStateMap[key] = DOWN;
			}
		}
		break;
		case DOWN:
		{
			if(buttonState == RELEASED)
			{
				buttonStateMap[key] = RELEASED;

				//for(int i = 0; i < keyUpFunctionsMap[key].size(); i++)
				//{
				//	keyUpFunctionsMap[key][i]();
				//}
			}
			else if(buttonState == DOWN)
			{
				//for(int i = 0; i < keyHeldFunctionsMap[key].size(); i++)
				//{
				//	keyHeldFunctionsMap[key][i]();
				//}
			}
		}
		break;
		case RELEASED:
		{
			if(buttonState == DOWN)
			{
				buttonStateMap[key] = PRESSED;

				//for (int i = 0; i < keyDownFunctionsMap[key].size(); i++)
				//{
				//	keyDownFunctionsMap[key][i]();
				//}
			}
		}
		break;
		default:
		{
			buttonStateMap[key] = RELEASED;
		}
		break;
		}
	}

	bool InputHandler::isMouseButtonDown(std::string key)
	{
		return false;
	}

	bool InputHandler::isMouseButtonUp(std::string key)
	{
		return false;
	}

	bool InputHandler::wasMouseButtonPressed(std::string key)
	{
		return false;
	}

	//void InputHandler::addOnMouseButtonDownFunction(std::string key, onMouseButtonDown functionToBeCalled)
	//{
	//	
	//}
	//
	//void InputHandler::addOnMouseButtonUpFunction(std::string key, onMouseButtonUp functionToBeCalled)
	//{
	//
	//}
	//
	//void InputHandler::addOnMouseButtonHeldFunction(std::string key, onMouseButtonHeld functionToBeCalled)
	//{
	//
	//}
	//
	//void InputHandler::addOnMouseCursorMoveFunction(onMouseCursorMove functionToBeCalled)
	//{
	//
	//}
	//
	//void InputHandler::addOnMouseScrollFunction(onMouseScroll functionToBeCalled)
	//{
	//
	//}

	void InputHandler::updateMouseCursor(double xPos, double yPos)
	{
		cursorXPosition = xPos;
		cursorYPosition = yPos;
	}

	void InputHandler::updateMouseButton(std::string key, ButtonState buttonState)
	{

	}

	void InputHandler::updateMouseScroll(double xOffset, double yOffset)
	{
		scrollXPosition += xOffset;
		scrollYPosition += yOffset;
	}

	void InputHandler::callOnKeyDownFunctions(std::string key)
	{

	}

	void InputHandler::callOnKeyUpFunction(std::string key)
	{

	}

	void InputHandler::callOnKeyHeldFunction(std::string key)
	{

	}

	void InputHandler::callOnMouseButtonDownFunction(std::string mouseButton)
	{

	}

	void InputHandler::callOnMouseButtonUpFunction(std::string mouseButton)
	{

	}

	void InputHandler::callOnMouseButtonHeldFunction(std::string mouseButton)
	{

	}

	void InputHandler::callOnMouseCursorMoveFunction()
	{

	}

	void InputHandler::callOnMouseScrollFunction()
	{

	}

	void InputHandler::glfwKeyboardButtonCallBack(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		// use key and turn it into a string for buttonStateMap
		std::string keyName = getGLFWKeyName(key);
		//std::cout << key << " : " << l_key << " : " << static_cast<char>(key) << std::endl;
		switch(action)
		{
		case GLFW_PRESS:
		case GLFW_REPEAT:
		{
			Get()->updateKey(keyName, DOWN);
		}
		break;
		case GLFW_RELEASE:
		{
			Get()->updateKey(keyName, RELEASED);
		}
		break;
		default:
		{

		}
		break;
		}
	}

	void InputHandler::glfwMouseCursorCallBack(GLFWwindow * window, double xPos, double yPos)
	{
		Get()->updateMouseCursor(xPos, yPos);
	}

	void InputHandler::glfwMouseButtonCallBack(GLFWwindow * window, int button, int action, int mods)
	{

	}

	void InputHandler::glfwMouseScrollCallBack(GLFWwindow * window, double xOffset, double yOffset)
	{
		Get()->updateMouseScroll(xOffset, yOffset);
	}

	std::string InputHandler::getGLFWKeyName(int keyCode)
	{
		std::string keyName = "";

		keyName = keyCodeToName[keyCode][0];

		return keyName;
	}
}