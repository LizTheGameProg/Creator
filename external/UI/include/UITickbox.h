#pragma once

#include <glm\glm.hpp>
#include "UIElement.h"

class UITickbox : public UIElement
{
public:
	UITickbox(	unsigned int a_shader,
				bool * a_callBackBool,
				glm::vec2 a_position,	
				glm::vec2 a_dimensions,	
				unsigned int a_boxTexture,
				unsigned int a_TickTexture,
				unsigned int a_CrossTexture,
				glm::vec4 a_colour		= glm::vec4(1),
				glm::vec4 a_tickColour	= glm::vec4(0,1,0,1),
				glm::vec4 a_crossColour	= glm::vec4(1,0,0,1));
	virtual ~UITickbox(void);

	virtual void	update(float a_deltaTime);

protected:
	unsigned int m_shader;
	bool * m_CBvalue;
	glm::vec2 m_dimensions;
	unsigned int m_texture_tick;
	unsigned int m_texture_cross;
	glm::vec4 m_colour;
	glm::vec4 m_tickColour;
	glm::vec4 m_crossColour;

	bool m_pressed;
};

