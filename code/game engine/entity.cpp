#include "entity.h"

static unsigned int _currentID = 0;

Entity::Entity()
{
	_currentID++;
	id = _currentID;
}

Entity::~Entity()
{
	id = 0;
}

unsigned int Entity::GetID()
{
	return id;
}