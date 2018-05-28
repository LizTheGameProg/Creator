#pragma once
#include "BaseCamera.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"

namespace INTRO_OPENGL
{
	class Camera3D : public BaseCamera
	{
	public:
		Camera3D();
		Camera3D(const float fieldOfView,
			const float aspectRatio,
			const float near,
			const float far);
		~Camera3D();

		//void setPerspective(float fieldOfView, float aspectRatio, float near, float far)
		void setPerspective(const float fieldOfView /*= glm::pi<float>() * 0.25f*/,
			const float aspectRatio = (16.f / 9.f),
			const float near = 0.1f,
			const float far = 1000.f);

	private:
		float fieldOfView;
		float aspectRatio;
	};
}