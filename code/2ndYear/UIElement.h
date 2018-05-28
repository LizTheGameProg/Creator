#ifndef __UIELEMENT_H_
#define __UIELEMENT_H_

#include <glm/glm.hpp>
#include <vector>

using glm::vec2;
using glm::mat3;

// An extremely basic UI element that allows for a hierarchy
// Setup for ease-of-use NOT performance
class UIElement
{
public:

	UIElement(const vec2& a_position = vec2(0,0),
			  const vec2& a_size = vec2(1,1), 
			  float a_rotation = 0);
	virtual ~UIElement();

	void	setPosition(const vec2& a_position)	{ m_position = a_position; }
	void	setSize(const vec2& a_size)			{ m_size = a_size; }
	void	setRotation(float a_rotation)		{ m_rotation = a_rotation; }

	const vec2&	getPosition() const	{ return m_position; }
	const vec2&	getSize() const		{ return m_size; }
	float		getRotation() const	{ return m_rotation; }

	// gives ownership of a_element to this instance
	void	addElement(UIElement* a_element);

	// get a transform combined with parents
	mat3			getTransform() const;

	// calls draw() on children
	virtual void	draw(const glm::mat4& a_projection);

	// calls update() on children
	virtual void	update(float a_deltaTime);

protected:

	UIElement*	m_parent;

	vec2		m_position;
	vec2		m_size;
	float		m_rotation;

	std::vector<UIElement*>	m_children;
};

#endif // __UIELEMENT_H_