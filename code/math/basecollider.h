#pragma once

class SpriteBatch;
class CollisionHandler;

#include "transform2D.h"
#include "SpriteBatch.h"

class BaseCollider
{
public:
	BaseCollider();
	BaseCollider(bool dynamic);
	BaseCollider(LML::transform2D transform);
	BaseCollider(LML::transform2D transform, bool dynamic);
	virtual ~BaseCollider();

	virtual void Render() = 0;

	static SpriteBatch * spriteBatch;
	static CollisionHandler * collisionHandler;

	LML::transform2D & transform;

	bool dynamic;
};