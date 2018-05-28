#include "Camera3D.h"
#include <glm\ext.hpp>

namespace ANGINE
{
	Camera3D::Camera3D()
	{
		fieldOfView = glm::pi<float>() * 0.25f;
		aspectRatio = 16 / 9.f;
		setPerspective(fieldOfView, aspectRatio, m_near, m_far);
	}

	Camera3D::Camera3D(const float a_fieldOfView,
		const float a_aspectRatio,
		const float a_near,
		const float a_far) : BaseCamera()
	{
		fieldOfView = a_fieldOfView;
		aspectRatio = a_aspectRatio;
		m_near = a_near;
		m_far = a_far;
		setPerspective(fieldOfView, aspectRatio, m_near, m_far);
	}

	Camera3D::~Camera3D() {}

	void Camera3D::setPerspective(const float a_fieldOfView = glm::pi<float>() * 0.25f,
		const float a_aspectRatio,
		const float a_near,
		const float a_far)
	{
		fieldOfView = a_fieldOfView;
		aspectRatio = a_aspectRatio;
		m_near = a_near;
		m_far = a_far;

		m_projection = glm::perspective(fieldOfView, aspectRatio, m_near, m_far);
	}
}