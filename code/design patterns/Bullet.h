#pragma once
#include "IEntity.h"
#include "vec2.h"

class Bullet : public IEntity
{
public:
	Bullet();
	virtual ~Bullet();

	void Update(float deltaTime);

	//Vector2 m_velocity;
};