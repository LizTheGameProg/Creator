#pragma once
#include "UIElement.h"
#include <glm\glm.hpp>

class UIRectangle;
class UI9Patch;

class UIDropDownBox : public UIElement
{
public:
	UIDropDownBox(UIRectangle * DisplayBox, UIRectangle * DropButton, UI9Patch * ListBox, std::vector<wchar_t *> ChoiceList, unsigned int * DefaultChoice);
	virtual ~UIDropDownBox(void);

	void update(float DeltaTime);
	void draw(glm::mat4 Projection);

protected:
	bool m_dropDown;
	bool m_pressedThisFrame;
	bool m_pressedLastFrame;

	UIRectangle * m_displayBox;
	UIRectangle * m_dropButton;
	UI9Patch * m_listBox;

	std::vector<wchar_t *> m_choiceList;
	unsigned int * m_choice;
	glm::vec2 m_choiceTextPos;
};

