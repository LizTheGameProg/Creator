#include "Camera2D.h"
#include "glm\ext.hpp"
#include "InputHandler.h"
#include "BaseWindow.h"
#include <iostream>
Camera2D::Camera2D()
{
	glm::vec2 halfWindowDimensions = BaseWindow::Get()->GetWindowSize() / 2.f;

	left = -halfWindowDimensions.x;
	right = halfWindowDimensions.x;
	top = halfWindowDimensions.y;
	bottom = -halfWindowDimensions.y;
	m_near = -1.f;
	m_far = 100.f;
	movementSpeed = glm::vec2(10);

	//view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0), glm::vec3(0, 1, 0));
	//projection = glm::ortho(left, right, bottom, top, m_near, m_far);
}

Camera2D::Camera2D(const float a_left, const float a_right,
	const float a_top, const float a_bottom,
	const float a_near, const float a_far)
{
	left = a_left;
	right = a_right;
	top = a_top;
	bottom = a_bottom;
	m_near = a_near;
	m_far = a_far;
	movementSpeed = glm::vec2(10);

	//view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0), glm::vec3(0, 1, 0));
	//projection = glm::ortho(left, right, bottom, top, m_near, m_far);
}

Camera2D::~Camera2D() {}

void Camera2D::update(float a_deltaTime)
{
	glm::vec3 cameraMovement = glm::vec3();

	if(InputHandler::Get()->isKeyDown("A"))
	{
		cameraMovement += glm::vec3(-movementSpeed.x, 0, 0);
	}
	if(InputHandler::Get()->isKeyDown("D"))
	{
		cameraMovement += glm::vec3(movementSpeed.x, 0, 0);
	}
	if(InputHandler::Get()->isKeyDown("W"))
	{
		cameraMovement += glm::vec3(0, movementSpeed.y, 0);
	}
	if(InputHandler::Get()->isKeyDown("S"))
	{
		cameraMovement += glm::vec3(0, -movementSpeed.y, 0);
	}
	cameraMovement *= a_deltaTime;
	//transform = glm::translate(transform, cameraMovement);
}