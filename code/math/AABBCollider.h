#pragma once
#include "BaseCollider.h"
#include "vec2.h"

class AABBCollider : public BaseCollider
{
public:
	AABBCollider();
	~AABBCollider();

	virtual void Render();

	LML::vec2 minExtents;
	LML::vec2 maxExtents;
};