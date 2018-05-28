#pragma once
#include "UIElement.h"
class UIRectangle;
class UISlider : public UIElement
{
public:
	UISlider(	unsigned int a_shader,
				glm::vec2 a_position,
				glm::vec2 a_dimensions,
				unsigned int a_barTexture,
				unsigned int a_sliderTexture,
				float * a_cbFloat,
				float a_min = 0.f,
				float a_max = 1.f,
				glm::vec4 a_barColour = glm::vec4(1),
				glm::vec4 a_sliderColour = glm::vec4(1));
	~UISlider(void);

	virtual void update(float a_deltaTime);

protected:
	float * m_CBValue;

	float m_slider_MinValue;
	float m_slider_MaxValue;

	bool m_pressed;

	UIRectangle * m_bar;
	UIRectangle * m_slider;
};

