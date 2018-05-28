#pragma once
#include "Camera3D.h"

class GLFWwindow;
namespace ANGINE
{
	class FlyCamera3D : public Camera3D
	{
	public:
		FlyCamera3D();
		FlyCamera3D(const float fieldOfView,
			const float aspectRatio,
			const float nearDistance,
			const float farDistance);
		~FlyCamera3D();

		virtual void update(GLFWwindow * window, const float deltaTime);
		static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	protected:
		void reset();

	private:
		float m_movementSpeed;
		float m_rotationSpeed;
		float m_lookAtDistance;

		static FlyCamera3D * instance;
	};
}