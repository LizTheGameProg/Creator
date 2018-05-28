#ifndef __UIBUTTON_H_
#define  __UIBUTTON_H_

#include "UIRectangle.h"

class UIButton : public UIRectangle
{
public:
	UIButton(	unsigned int a_shader,
				const vec2 & a_dimensions = vec2(1,1),
				const vec4 & a_normalColour = vec4(1),
				const vec4 & a_pressedColour = vec4(1),
				const vec4 & a_hoverColour = vec4(1));
	virtual ~UIButton(void);

	typedef void (*OnPressCB)(	UIButton * a_caller, 
								void * a_userData);
	void setPressedCB(OnPressCB a_callback, void * a_userData){m_pressedCB = a_callback; m_pressedUD = a_userData;}
	virtual void update(float a_deltaTime);

protected:
	UIButton(void);

	vec4 m_normalColour;
	vec4 m_pressedColour;
	vec4 m_hoverColour;
	bool m_pressed;

	OnPressCB	m_pressedCB;
	void *		m_pressedUD;
};

#endif