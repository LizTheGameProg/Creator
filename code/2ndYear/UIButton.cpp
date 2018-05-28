#include "UIButton.h"
#include <GLFW/glfw3.h>

UIButton::UIButton(void){}
UIButton::UIButton(	unsigned int a_shader,
					const vec2 & a_dimensions,
					const vec4 & a_normalColour,
					const vec4 & a_pressedColour,
					const vec4 & a_hoverColour) :
					UIRectangle(a_shader, a_dimensions),
					m_normalColour(a_normalColour),
					m_pressedColour(a_pressedColour),
					m_hoverColour(a_hoverColour),
					m_pressed(false), m_pressedCB(nullptr), m_pressedUD(nullptr){}


UIButton::~UIButton(void){}

void UIButton::update(float a_deltaTime)
{
	// get window
	GLFWwindow * window = glfwGetCurrentContext();
	int w = 0, h = 0;
	glfwGetWindowSize(window, &w, &h);

	// get cursor
	double x = 0, y = 0;
	glfwGetCursorPos(window, &x, &y);

	// flip cursor's Y
	glm::vec3 cursor = glm::vec3(x, h-y, 1);

	// transform by inverse
	cursor = glm::inverse(getTransform()) * cursor;

	// compare if inside
	vec2 scaledHalfDimensions = m_dimensions * m_size * 0.5f;
	if(	cursor.x >= -scaledHalfDimensions.x &&
		cursor.x <=  scaledHalfDimensions.x &&
		cursor.y >= -scaledHalfDimensions.y &&
		cursor.y <=  scaledHalfDimensions.y)
	{
		// test for pressed/unpressed 
		if(glfwGetMouseButton(window, 0) == GLFW_PRESS)
		{
			m_colour = m_pressedColour;
			m_pressed = true;
		}
		else
		{
			// if released?
			if(m_pressed == true)
			{
				m_pressed = false;
				if(m_pressedCB != nullptr)
					m_pressedCB(this, m_pressedUD);
			}
			m_colour = m_hoverColour;
		}
	}
	else
	{
		m_pressed = false;
		m_colour = m_normalColour;
	}
	

	UIRectangle::update(a_deltaTime);
}