#pragma once
#include "BaseCamera.h"

#include "glm\mat3x3.hpp"
#include "glm\mat4x4.hpp"

class Camera2D : public ANGINE::BaseCamera
{
public:
	Camera2D();
	Camera2D(	const float left, const float right, 
				const float top,  const float bottom, 
				const float near, const float far);
	~Camera2D();
	void update(const float deltaTime);

private:
	float left;
	float right;
	float top;
	float bottom;

	glm::vec2 movementSpeed;
};

