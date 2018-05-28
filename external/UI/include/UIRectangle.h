#pragma once

#include "UIElement.h"

class UIRectangle : public UIElement
{
public:
	UIRectangle(void){}
	UIRectangle(unsigned int a_shader,
				const glm::vec2 & a_dimensions = glm::vec2(1,1),
				const glm::vec4 & a_colour = glm::vec4(1,1,1,1));
	virtual ~UIRectangle(void);
	
	virtual void draw(const glm::mat4 & a_projection);
	
	void setTexture(unsigned int a_texture) {m_texture = a_texture;}
	void setTextureCoords(glm::vec2 a_bottomLeft, glm::vec2 a_topRight);
	void setColour(glm::vec4 a_colour) {m_colour = a_colour;}

	const glm::vec2 & getDimensions() const {return m_dimensions;}

protected:
	unsigned int	m_shader;
	unsigned int	m_vao, m_vbo;

	glm::vec2		m_dimensions;
	unsigned int	m_texture;
	glm::vec2		m_textureCoords[4];

};