//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	19/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	19/08/2015
//--------------------------------

#include "Transform2D.h"

#include "glm\ext.hpp"

using namespace INTRO_OPENGL;

Transform2D::Transform2D(	glm::vec2 a_translation	/* = glm::vec2(0)*/, 
							glm::float32 a_rotation	/* = glm::float32(0.f)*/, 
							glm::vec2 a_scale		/* = glm::vec2(1)*/)
{
	m_translation		= glm::translate(glm::vec3(a_translation, 0.f));
	m_rotation			= glm::rotate(a_rotation, glm::vec3(0.f, 0.f, 1.f));
	m_scale				= glm::scale(glm::vec3(a_scale, 1.f));

	m_finalTransform	= m_translation * m_rotation * m_scale;
	m_isDirty			= false;
}

Transform2D::~Transform2D()
{

}

void Transform2D::TranslateBy(glm::vec2 a_translation)
{
	m_translation	= glm::translate(m_translation, glm::vec3(a_translation, 0.f));
	m_isDirty		= true;
}

void Transform2D::RotateBy(glm::float32 a_rotation)
{
	m_rotation		= glm::rotate(m_rotation, a_rotation, glm::vec3(0.f, 0.f, 1.f));
	m_isDirty		= true;
}

void Transform2D::ScaleBy(glm::vec2 a_scale)
{
	m_scale			= glm::scale(m_scale, glm::vec3(a_scale, 1.f));
	m_isDirty		= true;
}
				
glm::vec2 Transform2D::GetTranslation()
{
	return glm::vec2(m_translation[3][0], m_translation[3][1]);
}

glm::float32 Transform2D::GetRotation()
{
	return glm::float32(atan2(m_rotation[1][0], m_rotation[0][0]));
}

glm::vec2 Transform2D::GetScale()
{
	return glm::vec2(m_scale[0][0], m_scale[1][1]);
}
				
void Transform2D::SetTranslation(glm::vec2 a_translation)
{
	m_translation	= glm::translate(glm::vec3(a_translation, 0.f));
	m_isDirty		= true;
}

void Transform2D::SetRotation(glm::float32 a_rotation)
{
	m_rotation		= glm::rotate(a_rotation, glm::vec3(0.f, 0.f, 1.f));
	m_isDirty		= true;
}

void Transform2D::SetScale(glm::vec2 a_scale)
{
	m_scale			= glm::scale(glm::vec3(a_scale, 1.f));
	m_isDirty		= true;
}

glm::mat4 Transform2D::GetTransform()
{
	if(m_isDirty)
	{
		m_finalTransform = m_translation * m_rotation * m_scale;
		m_isDirty = false;
	}
	return m_finalTransform;
}