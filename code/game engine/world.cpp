#include "world.h"

#include "vector"
std::vector<Entity*> entities;

World::World()
{
	entities = std::vector<Entity*>();
}

World::~World()
{
	
}

void World::AddEntity(Entity * entity)
{
	entities.push_back(entity);
}