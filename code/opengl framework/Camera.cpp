//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	20/08/2015
//--------------------------------

#include "Camera.h"
#include "glm\ext.hpp"

// GLEW
#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

#include "Window.h"
namespace openGL
{
	Camera2D::Camera2D()
	{
		m_transform = glm::mat4();
		m_projection = glm::mat4();

		// Set the view to look down positive Z and Positive Y is up
		m_view = glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0), glm::vec3(0.f, 1.f, 0.f));
		m_transform = glm::inverse(m_view);

		int width = 0;
		int height = 0;
		glfwGetWindowSize(Window::Get()->GetWindow(), &width, &height);
		m_projection = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 3.f);

	}

	Camera2D::~Camera2D()
	{

	}

	glm::mat4 Camera2D::GetProjectionView()
	{
		return m_projection * m_view;
	}
}