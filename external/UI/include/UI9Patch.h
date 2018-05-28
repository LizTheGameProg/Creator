#pragma once
#include "UIElement.h"


class UI9Patch : public UIElement
{
public:
	UI9Patch(	unsigned int a_shader,
				glm::vec2 a_position,
				glm::vec2 a_dimensions,
				glm::vec2 a_imageDimensions,
				glm::vec2 a_cornerDimensions = glm::vec2(10,10),
				glm::vec4 a_colour = glm::vec4(1));
	virtual ~UI9Patch(void);

	virtual void draw(glm::mat4 Projection);

	virtual void setReference(float * Reference){m_reference = Reference;}
	virtual void setTexture(unsigned int Texture);
	virtual void setText(wchar_t * Text);
	virtual glm::vec2 getDimensions();	

protected:
	glm::vec2 m_dimensions;
	wchar_t * m_text;
	glm::vec2 m_textPos;
	void * m_reference;
};

