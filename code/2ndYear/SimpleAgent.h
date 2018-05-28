#include <glm/glm.hpp>
#include "Gizmos.h"
#include <vector>

enum WorldObjectType
{
	SIMPLE_AI,
	WATER,
	FOOD,
	CAVE,
};

using namespace std;
class WorldObject
{
public:
	vector<WorldObject*>* worldObjects;
	virtual void update(float delta) =0;
	virtual void draw();
	float radius;
	glm::vec4 colour;
	glm::vec3 position;
	WorldObjectType type;
};

class BaseResource:public WorldObject
{
	public:
	float amount;

	BaseResource(glm::vec3 position,glm::vec4 colour,float radius);
	void virtual update(float delta){};
};


class Water:public BaseResource
{
	public:
	Water(glm::vec3 position);
};

class Food:public BaseResource
{
	public:
	Food(glm::vec3 position);
};

class Cave:public BaseResource
{
	public:
	Cave(glm::vec3 position);
};

class BaseAI:public WorldObject
{
public:
	BaseAI(glm::vec3 position,glm::vec4 colour,float radius);
	float findNearestResource(WorldObjectType type);
	glm::vec3 findResourceVector(WorldObjectType type);
	float stamina;
	float solids;
	float fluids;
};

class SimpleAI: public BaseAI
{
public:
	float maxSpeed;
	virtual void update(float delta);
	virtual void draw();
	void drawBar(float value,int index);
	SimpleAI(glm::vec3 position,glm::vec4 colour,float radius);
	float checkEatingDesirable();
	float checkSleepDesirable();
	float checkDrinkingDesirable();
	glm::vec3 gotoFood(float desirability,float delta);
	glm::vec3 gotoCave(float desirability,float delta);
	glm::vec3 gotoWater(float desirability,float delta);
};

class WorldController
{
public:
	vector<WorldObject*> worldObjects;
	void update(float delta);
	void draw();
	void addObject(WorldObject* newObject);
};