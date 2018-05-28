//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	19/08/2015
//--------------------------------

#include "Transform3D.h"

#include "glm\ext.hpp"

Transform3D::Transform3D(	glm::vec3 a_translation	/* = glm::vec3(0.f, 0.f, 0.f)*/, 
							glm::vec3 a_rotation	/* = glm::vec3(0.f, 0.f, 0.f)*/, 
							glm::vec3 a_scale		/* = glm::vec3(1.f, 1.f, 1.f)*/)
{
	SetTranslation(a_translation);
	SetRotation(a_rotation);
	SetScale(a_scale);
	m_finalTransform	= m_translation * glm::toMat4(m_rotation) * m_scale;
	m_isDirty			= false;
}

Transform3D::~Transform3D()
{

}

void Transform3D::TranslateBy(glm::vec3 a_translation)
{
	m_translation	= glm::translate(m_translation, a_translation);
	m_isDirty		= true;
}

void Transform3D::RotateBy(glm::vec3 a_rotation)
{
	m_rotation	   *= glm::angleAxis(a_rotation.x, glm::vec3(0.f, 1.f, 0.f));
	m_rotation	   *= glm::angleAxis(a_rotation.y, glm::vec3(1.f, 0.f, 0.f));
	m_rotation		= glm::normalize(m_rotation);
	m_isDirty		= true;
}

void Transform3D::ScaleBy(glm::vec3 a_scale)
{
	m_scale			= glm::scale(m_scale, a_scale);
	m_isDirty		= true;
}
				
glm::vec3 Transform3D::GetTranslation()
{
	return glm::vec3(m_translation[3].x, m_translation[3].y, m_translation[3].z);
}

glm::vec3 Transform3D::GetRotation()
{
	glm::vec3 rotation = glm::vec3();
	rotation = glm::eulerAngles(m_rotation); // pitch, yaw, roll

	// heading, bank, attitude
	float heading, bank, attitude;

	glm::quat q1 = m_rotation;
	
	double test = q1.x*q1.y + q1.z*q1.w;
	if (test > 0.499) { // singularity at north pole
		heading = 2 * atan2(q1.x,q1.w);
		attitude = glm::half_pi<float>();
		bank = 0;
	}
	if (test < -0.499) { // singularity at south pole
		heading = -2 * atan2(q1.x,q1.w);
		attitude = -glm::half_pi<float>();
		bank = 0;
	}
	double sqx = q1.x*q1.x;
    double sqy = q1.y*q1.y;
    double sqz = q1.z*q1.z;
	heading = (float) atan2(2 * q1.y*q1.w - 2 * q1.x*q1.z, 1 - 2 * sqy - 2 * sqz);
	attitude = (float) asin(2 * test);
	bank = (float) atan2(2 * q1.x*q1.w - 2 * q1.y*q1.z, 1 - 2 * sqx - 2 * sqz);

	rotation = glm::vec3(bank, heading, attitude);

	return rotation;
}

glm::vec3 Transform3D::GetScale()
{
	return glm::vec3(m_scale[0][0], m_scale[1][1], m_scale[2][2]);
}
				
void Transform3D::SetTranslation(glm::vec3 a_translation)
{
	m_translation	= glm::translate(a_translation);
	m_isDirty		= true;
}

void Transform3D::SetRotation(glm::vec3 a_rotation)
{
	m_rotation	    = glm::angleAxis(a_rotation.x, glm::vec3(0.f, 1.f, 0.f));
	m_rotation	   *= glm::angleAxis(a_rotation.y, glm::vec3(1.f, 0.f, 0.f));
	m_rotation		= glm::normalize(m_rotation);
	m_isDirty		= true;
}

void Transform3D::SetScale(glm::vec3 a_scale)
{
	m_scale			= glm::scale(a_scale);
	m_isDirty		= true;
}

glm::mat4 Transform3D::GetTransform()
{
	if(m_isDirty)
	{
		m_finalTransform	= m_translation * glm::toMat4(m_rotation) * m_scale;
		m_isDirty			= false;
	}
	return m_finalTransform;
}

Transform3D Transform3D::operator=(glm::mat4 a_rhs)
{
	m_finalTransform = a_rhs;

	m_translation[3] = m_finalTransform[3];
	m_rotation = glm::toQuat(m_finalTransform);

	// scale = final transform / translation / rotation
	m_scale = (m_finalTransform * glm::inverse(m_translation)) * glm::inverse(glm::toMat4(m_rotation));

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i != j)
				m_scale[i][j] = 0;
		}
	}
	
	m_finalTransform = m_translation * glm::toMat4(m_rotation) * m_scale;

	return *this;
}

glm::vec3 Transform3D::GetForward()
{
	glm::vec4 forward = GetTransform()[2];
	return glm::vec3(forward.x, forward.y, forward.z);
}

glm::vec3 Transform3D::GetRight()
{
	glm::vec4 right = GetTransform()[0];
	return glm::vec3(right.x, right.y, right.z);
}

glm::vec3 Transform3D::GetUp()
{
	glm::vec4 up = GetTransform()[1];
	return glm::vec3(up.x, up.y, up.z);
}