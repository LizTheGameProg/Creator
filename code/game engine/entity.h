#pragma once

class Entity
{
public:
	Entity();
	virtual ~Entity();

	unsigned int GetID();
private:
	unsigned int id;
};