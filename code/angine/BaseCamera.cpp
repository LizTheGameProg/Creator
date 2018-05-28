#include "BaseCamera.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"

namespace ANGINE
{
	BaseCamera::BaseCamera()
	{
		m_worldTransform = Transform3D();
		m_projection = glm::mat4(1);
		m_view = glm::mat4(1);

		m_near = 0.1f;
		m_far = 100000.f;
	}

	BaseCamera::~BaseCamera() {}

	void BaseCamera::update(const float a_deltaTime) {}

	//void BaseCamera::lookAt(const glm::vec3 & a_from, 
	//						const glm::vec3 & a_to, 
	//						const glm::vec3 & a_up)
	//{
	//	view = glm::lookAt(a_from, a_to, a_up);
	//	transform = glm::inverse(view);
	//}

	//void BaseCamera::setPosition(const glm::vec3 & a_position)
	//{
	//	transform[0][3] = a_position.x;
	//	transform[1][3] = a_position.y;
	//	transform[2][3] = a_position.z;
	//
	//	m_view = glm::inverse(m_worldTransform.GetTransform());
	//}

	glm::mat4 BaseCamera::getWorldTransform() { return m_worldTransform.GetTransform(); }
	glm::mat4 BaseCamera::getView() { return m_view; }
	glm::mat4 BaseCamera::getProjection() { return m_projection; }

	glm::mat4 BaseCamera::getProjectionView()
	{
		m_view = glm::inverse(m_worldTransform.GetTransform());
		return m_projection * m_view;
	}
}