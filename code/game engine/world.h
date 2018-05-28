#pragma once

#include "entity.h"

class World
{
public:
	World();
	~World();
	
	void AddEntity(Entity * entity);
};