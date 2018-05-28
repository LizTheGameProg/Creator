#pragma once
#include "Transform3D.h"

#include "glm\mat4x4.hpp"
#include "glm\gtx\quaternion.hpp"

namespace ANGINE
{
	class BaseCamera
	{
	public:
		BaseCamera();
		~BaseCamera();

		virtual void update(const float deltaTime);
		//void lookAt(const glm::vec3 & from, const glm::vec3 & to, const glm::vec3 & up);
		//void setPosition(const glm::vec3 & position);

		glm::mat4 getWorldTransform();
		glm::mat4 getView();
		glm::mat4 getProjection();
		glm::mat4 getProjectionView();

	protected:
		Transform3D m_worldTransform;
		glm::mat4	m_projection;		// FOV and aspect ration information
		glm::mat4	m_view;				// Inverse of the worldTransform

		float		m_near;
		float		m_far;
	};


}