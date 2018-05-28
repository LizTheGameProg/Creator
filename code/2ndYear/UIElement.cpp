#include "UIElement.h"

UIElement::UIElement(const glm::vec2& a_position /* = glm::vec2 */,
					 const glm::vec2& a_size /* = glm::vec2(1,1) */, 
					 float a_rotation /* = 0 */)
					 : m_parent(nullptr),
					 m_position(a_position),
					 m_size(a_size),
					 m_rotation(a_rotation)
{

}

UIElement::~UIElement()
{
	for (auto child : m_children)
		delete child;
}

void UIElement::addElement(UIElement* a_element)
{
	if (a_element->m_parent == nullptr)
	{
		a_element->m_parent = this;
		m_children.push_back(a_element);
	}
}

void UIElement::draw(const glm::mat4& a_projection)
{
	for (auto child : m_children)
		child->draw(a_projection);
}

void UIElement::update(float a_deltaTime)
{
	for (auto child : m_children)
		child->update(a_deltaTime);
}

mat3 UIElement::getTransform() const
{
	// build local transforms
	mat3 trans, rot, scale;
	trans[2] = glm::vec3(m_position,1);
	scale[0][0] = m_size.x;
	scale[1][1] = m_size.y;
	rot[0][0] = cos(m_rotation);
	rot[0][1] = -sin(m_rotation);
	rot[1][0] = sin(m_rotation);
	rot[1][1] = cos(m_rotation);

	if (m_parent == nullptr)
	{
		return trans * rot * scale;
	}
	else
	{
		// combine with parent's transform
		return m_parent->getTransform() * (trans * rot * scale);
	}
}