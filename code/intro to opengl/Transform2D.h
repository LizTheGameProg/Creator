#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	19/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	17/11/2015
//--------------------------------

#include "glm\mat4x4.hpp"
#include "glm\vec2.hpp"

class Transform2D
{
public:
	Transform2D(glm::vec2 translation = glm::vec2(0.f, 0.f), glm::float32 rotation = glm::float32(0.f), glm::vec2 scale = glm::vec2(1, 1));
	~Transform2D();

	void			TranslateBy(glm::vec2 translation);
	void			RotateBy(glm::float32 rotation);
	void			ScaleBy(glm::vec2 scale);

	glm::vec2		GetTranslation();
	glm::float32	GetRotation();
	glm::vec2		GetScale();

	void			SetTranslation(glm::vec2 translation);
	void			SetRotation(glm::float32 rotation);
	void			SetScale(glm::vec2 scale);

	glm::mat4		GetTransform();

private:
	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;

	glm::mat4 m_finalTransform;

	bool m_isDirty;
};