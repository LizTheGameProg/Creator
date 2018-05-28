#pragma once
#include <glm/glm.hpp>
#include <vector>

enum TransitionType
{
	None,
	FadeIn,
	FadeOut,
	FadeUpIn,
	FadeUpOut,
	FadeDownIn,
	FadeDownOut,
	FadeLeftIn,
	FadeLeftOut,
	FadeRightIn,
	FadeRightOut
};

class UIElement
{
public:
	UIElement(	const glm::vec2 & a_position = glm::vec2(0,0),
				const glm::vec2 & a_size = glm::vec2(1, 1), 
				float a_rotation = 0,
				const glm::vec4 & a_colour = glm::vec4(1,1,1,1));
	virtual ~UIElement(void);
	void			setPosition	(const glm::vec2& a_position)	{ m_position = a_position; }
	void			setSize		(const glm::vec2& a_size)		{ m_size = a_size; }
	void			setRotation	(float a_rotation)				{ m_rotation = a_rotation; }
	
	const glm::vec2&	getPosition() const	{ return m_position; }
	const glm::vec2&	getSize() const		{ return m_size; }
	float				getRotation() const	{ return m_rotation; }
	glm::mat3			getTransform() const;
	TransitionType getCurrentTransition() {return m_currentTransition;}

	void addElement(UIElement* a_element);
	void transition(TransitionType Type, float TotalTime, float DisplacementAmount = 0.f);

	virtual void	draw(const glm::mat4& a_projection);
	virtual void	update(float a_deltaTime);

protected:
	// Transition helper functions
	void IncreaseTransparency(float a_deltaTime);
	void DecreaseTransparency(float a_deltaTime);
	void IncreaseUsedTime(float a_deltaTime);
	void ResetTransitionVariables();

	float Lerp(float a_start, float a_end, float a_percentage);
	glm::vec2 Lerp(glm::vec2 a_start, glm::vec2 a_end, float a_percentage);

	bool m_isVisiable; // if true, update and draw the element
	
	// information about the current transition
	TransitionType m_currentTransition;
	glm::vec2 m_startPos;
	glm::vec2 m_endPos;
	float m_totalTime;
	float m_usedTime;

	UIElement * m_parent;
	std::vector<UIElement *> m_children;

	glm::vec2	m_position;
	glm::vec2	m_size;
	float		m_rotation;
	glm::vec4	m_colour;
};

