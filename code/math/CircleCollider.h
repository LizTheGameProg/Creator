#pragma once
#include "BaseCollider.h"

class CircleCollider : public BaseCollider
{
private:
	CircleCollider() = delete;
public:
	CircleCollider(LML::transform2D & transform, float radius);
	~CircleCollider() {}

	virtual void Render();

	float radius;
};