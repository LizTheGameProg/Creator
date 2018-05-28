#pragma once

#include "UIRectangle.h"
#include <functional>

class UIButton : public UIRectangle
{
public:
	UIButton(	unsigned int a_shader,
				const glm::vec2 & a_dimensions		= glm::vec2(1,1),
				std::function<void()> a_lambaFunction = nullptr,
				const glm::vec4 & a_normalColour	= glm::vec4(1),
				const glm::vec4 & a_hoverColour		= glm::vec4(1),
				const glm::vec4 & a_pressedColour	= glm::vec4(1),
				wchar_t * a_text = nullptr);
	virtual ~UIButton(void);
	
	virtual void update(float a_deltaTime);
	virtual void draw(glm::mat4 a_projection);

	bool shouldPlaySound(){ return m_playSound; }

	void setNormalTexture(unsigned int a_texture) {m_normalTexture = a_texture;}
	void setHoverTexture(unsigned int a_texture) {m_hoverTexture = a_texture;}
	void setPressedTexture(unsigned int a_texture) {m_pressedTexture = a_texture;}
	void setText(wchar_t * Text);

protected:
	std::function<void()> m_buttonCallBack;
	
	glm::vec4 m_normalColour;
	glm::vec4 m_pressedColour;
	glm::vec4 m_hoverColour;
	
	bool m_pressed;
	
	wchar_t * m_text;
	glm::vec2 m_textPos;

	unsigned int m_normalTexture;
	unsigned int m_hoverTexture;
	unsigned int m_pressedTexture;

	bool m_playSound;
};