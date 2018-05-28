#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	13/11/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	17/11/2015
//--------------------------------

#include "glm\mat4x4.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\vec3.hpp"

class Transform3D
{
public:
	Transform3D(glm::vec3 translation = glm::vec3(0.f, 0.f, 0.f), 
				glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), 
				glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
	~Transform3D();

	void		TranslateBy(glm::vec3 translation);
	void		RotateBy(glm::vec3 rotation);
	void		ScaleBy(glm::vec3 scale);

	glm::vec3	GetTranslation();
	glm::vec3	GetRotation();
	glm::vec3	GetScale();

	void		SetTranslation(glm::vec3 translation);
	void		SetRotation(glm::vec3 rotation);
	void		SetScale(glm::vec3 scale);

	glm::mat4	GetTransform();

	Transform3D operator=(glm::mat4 rhs);

	glm::vec3	GetForward();
	glm::vec3	GetRight();
	glm::vec3	GetUp();

private:
	glm::mat4	m_translation;
	glm::quat	m_rotation;
	glm::mat4	m_scale;

	glm::mat4	m_finalTransform;

	bool		m_isDirty;
};