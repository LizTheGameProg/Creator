#include "FlyCamera3D.h"
#include <GLFW\glfw3.h>

#include <iostream>

namespace ANGINE
{
	FlyCamera3D * FlyCamera3D::instance = nullptr;

	FlyCamera3D::FlyCamera3D()
	{
		m_movementSpeed = 0.075f;
		m_rotationSpeed = 0.3f;
		m_lookAtDistance = 10.f;
		instance = this;

		reset();
	}

	FlyCamera3D::FlyCamera3D(const float a_fieldOfView,
		const float a_aspectRatio,
		const float a_near,
		const float a_far) : FlyCamera3D()
	{
		setPerspective(a_fieldOfView, a_aspectRatio, a_near, a_far);
	}

	FlyCamera3D::~FlyCamera3D()
	{

	}

	void FlyCamera3D::update(GLFWwindow * window, const float a_deltaTime)
	{
		glfwSetScrollCallback(window, &mouseScrollCallback);

		float movementSpeed = m_movementSpeed;
		float rotationSpeed = m_rotationSpeed;

		if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			movementSpeed *= 3.f;
			rotationSpeed *= 3.f;
		}
		else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			movementSpeed *= 0.3f;
			rotationSpeed *= 0.3f;
		}

		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Left
		{
			m_worldTransform.TranslateBy(m_worldTransform.GetRight() * -movementSpeed);
		}
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Right
		{
			m_worldTransform.TranslateBy(m_worldTransform.GetRight() * movementSpeed);
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Back
		{
			m_worldTransform.TranslateBy(m_worldTransform.GetForward() * movementSpeed);
		}
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Forward
		{
			m_worldTransform.TranslateBy(m_worldTransform.GetForward() * -movementSpeed);
		}
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // Up
		{
			m_worldTransform.TranslateBy(glm::vec3(0, 1, 0) * movementSpeed);
		}
		if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // Down
		{
			m_worldTransform.TranslateBy(glm::vec3(0, 1, 0) * -movementSpeed);
		}

		// Get the mouse movement over the previous frame
		static glm::vec2 prevMousePosition;
		static glm::vec2 mousePosition;

		prevMousePosition = mousePosition;

		static double mouseX = 0.0;
		static double mouseY = 0.0;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		mousePosition = glm::vec2(mouseX, mouseY);

		// If right mouse is down
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			// Get current rotation
			glm::vec3 rotationXYZ = m_worldTransform.GetRotation();
			glm::vec2 rotationYX = glm::vec2(rotationXYZ.y, rotationXYZ.x);

			// Add mouse movement to that 
			rotationYX += (prevMousePosition - mousePosition) * a_deltaTime * rotationSpeed;

			// Set rotation based on new values
			m_worldTransform.SetRotation(glm::vec3(rotationYX.x, rotationYX.y, 0.f));

			m_view = glm::inverse(m_worldTransform.GetTransform());
		}
		else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			// Get the mouse movement and set up a rotation amounts based on that
			glm::vec2 rotationYX = (prevMousePosition - mousePosition) * a_deltaTime * rotationSpeed * 100.f;

			glm::vec3 up = glm::vec3(0, 1, 0);

			// Set the centre to be the current position then moved forward based on the look at distance
			glm::vec3 centre = m_worldTransform.GetTranslation();
			centre -= m_worldTransform.GetForward() * m_lookAtDistance;

			// Translate the camera based on the movement of the mouse
			m_worldTransform.TranslateBy(m_worldTransform.GetRight() * rotationYX.x);
			m_worldTransform.TranslateBy(m_worldTransform.GetUp() * -rotationYX.y);

			// Store the new position of the camera
			glm::vec3 position = m_worldTransform.GetTranslation();

			// Get the camera to look back at where it was already looking at
			m_view = glm::lookAt(position, centre, up);
			m_worldTransform = glm::inverse(m_view);

			// Set the position of the camera to the where it is looking at
			m_worldTransform.SetTranslation(centre);

			// Move the camera away from where it is looking at by the look at distance
			m_worldTransform.TranslateBy(m_worldTransform.GetForward() * m_lookAtDistance);
			m_view = glm::inverse(m_worldTransform.GetTransform());
		}
		else if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			reset();
		}
	}

	void FlyCamera3D::reset()
	{
		m_lookAtDistance = 10.f;

		glm::vec3 position = glm::vec3(1, 1, 1);
		glm::vec3 centre = glm::vec3(0);
		glm::vec3 up = glm::vec3(0, 1, 0);

		m_view = glm::lookAt(position, centre, up);

		m_worldTransform = glm::inverse(m_view);

		glm::vec3 forward = m_worldTransform.GetForward();
		m_worldTransform.SetTranslation(centre);
		m_worldTransform.TranslateBy(forward * m_lookAtDistance);

		m_view = glm::inverse(m_worldTransform.GetTransform());
	}

	void FlyCamera3D::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		glm::vec3 up = glm::vec3(0, 1, 0);

		// Set the centre to be the current position then moved forward based on the look at distance
		glm::vec3 centre = instance->m_worldTransform.GetTranslation();
		centre -= instance->m_worldTransform.GetForward() * instance->m_lookAtDistance;

		// Store the new position of the camera
		glm::vec3 position = instance->m_worldTransform.GetTranslation();

		// Get the camera to look back at where it was already looking at
		instance->m_view = glm::lookAt(position, centre, up);
		instance->m_worldTransform = glm::inverse(instance->m_view);

		// Set the position of the camera to the where it is looking at
		instance->m_worldTransform.SetTranslation(centre);

		instance->m_lookAtDistance -= yoffset;
		if(instance->m_lookAtDistance < 1.f)
		{
			instance->m_lookAtDistance = 1.f;
		}

		// Move the camera away from where it is looking at by the look at distance
		instance->m_worldTransform.TranslateBy(instance->m_worldTransform.GetForward() * instance->m_lookAtDistance);
		instance->m_view = glm::inverse(instance->m_worldTransform.GetTransform());
	}
}