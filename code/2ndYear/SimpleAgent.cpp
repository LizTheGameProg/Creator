#include "SimpleAgent.h"
#include "FuzzyLogicEngine.h"
#include <iostream>

extern Fuzzy fuzzyEngine;

using namespace AIE_2ND_YEAR;

void WorldObject::draw()
{
	Gizmos::addSphere(position,15,15,radius,colour);
}

BaseAI::BaseAI(glm::vec3 position,glm::vec4 colour,float radius)
{
	this->position = position;
	this->colour = colour;
	this->radius = radius;
}


BaseResource::BaseResource(glm::vec3 position,glm::vec4 colour,float radius)
{
	this->position = position;
	this->colour = colour;
	this->radius = radius;
}

Water::Water(glm::vec3 position):BaseResource(position,glm::vec4(0,0,1,1),6)
{
	type = WATER;
}

Food::Food(glm::vec3 position):BaseResource(position,glm::vec4(0,1,0,1),6)
{
	type = FOOD;
}

Cave::Cave(glm::vec3 position):BaseResource(position,glm::vec4(0,0,0,1),6)
{
	type = CAVE;
}

SimpleAI::SimpleAI(glm::vec3 position,glm::vec4 colour,float radius):BaseAI(position,colour,radius)
{
	stamina = 1;
	solids = 1;
	fluids = 1;
	type = SIMPLE_AI;
	maxSpeed = 20;
};

void SimpleAI::drawBar(float value,int index)
{
	glm::vec4 colours[] = {glm::vec4(1,0,0,1),glm::vec4(0,1,0,1),glm::vec4(0,0,1,1)};
	glm::vec3 leftPos(-70,45,0);
	float barLength = 15;
	float barHeight = 1;
	glm::vec4 white(1,1,1,1);
	glm::vec4 colour(.3,.3,.3,1);
	glm::vec3 extents(barLength,barHeight,1);
	glm::vec3 leftPos1 = leftPos;
	leftPos1.y -= barHeight*3 * index;
	leftPos1.x += barLength;
	Gizmos::addAABB(leftPos1,extents,white);
	barLength*=value;
	extents = glm::vec3(barLength,barHeight,1);
	leftPos1 = leftPos;
	leftPos1.y -= barHeight*3 * index;
	leftPos1.x += barLength;
	colour = colours[index];
	Gizmos::addAABBFilled(leftPos1,extents,colour);
}

float BaseAI::findNearestResource(WorldObjectType type)
{
	float minDistance = 1000000;
	for(auto object:*worldObjects)
	{
		if(object->type == type)
		{
			float distance = glm::length(object->position - position);
			if(distance < minDistance)
			{
				minDistance = distance;
			}
		}
	}
	return minDistance;
}

glm::vec3 BaseAI::findResourceVector(WorldObjectType type)
{
	float minDistance = 1000000;
	glm::vec3 target;
	for(auto object:*worldObjects)
	{
		if(object->type == type)
		{
			float distance = glm::length(object->position - position);
			if(distance < minDistance)
			{
				minDistance = distance;
				target = object->position;
			}
		}
	}
	glm::vec3 vector;
	if(minDistance<1)
	{
		vector = glm::vec3(0,0,0);
	}
	else
	{
		vector = (target - position)/minDistance;
	}
	return vector;
}

void SimpleAI::draw()
{
	BaseAI::draw();
	drawBar(stamina,0);
	drawBar(solids,1);
	drawBar(fluids,2);
}



float SimpleAI::checkEatingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float foodRange = findNearestResource(FOOD);
	//how far is the nearest food source
	//how hungry are we...
	float hungry = fuzzyEngine.hungry->getMembership(solids);	
	//how full are we...
	float full = fuzzyEngine.full->getMembership(solids);
	//are we very hungry?
	float veryHungry  = fuzzyEngine.veryHungry->getMembership(solids);
	//how close are we to food...
	float foodRangeClose = fuzzyEngine.veryNear->getMembership(foodRange);
	float foodRangeMedium = fuzzyEngine.mediumRange->getMembership(foodRange);
	float foodRangeFar = fuzzyEngine.farAway->getMembership(foodRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(foodRangeClose,hungry),veryHungry);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(foodRangeFar),hungry);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = full;
	//set up our maximum values ready to defuzzify
	float maxVeryDesirable = fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1 + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	//cout << desire << endl;
	return desire;
}

float SimpleAI::checkSleepDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float caveRange = findNearestResource(CAVE);
	//how far is the nearest food source
	//how hungry are we...
	float tired = fuzzyEngine.tired->getMembership(stamina);	
	//how full are we...
	float active = fuzzyEngine.superActive->getMembership(stamina);
	//are we very hungry?
	float awake  = fuzzyEngine.awake->getMembership(stamina);
	//how close are we to food...
	float caveClose = fuzzyEngine.veryNear->getMembership(caveRange);
	float caveMedium = fuzzyEngine.mediumRange->getMembership(caveRange);
	float caveFar = fuzzyEngine.farAway->getMembership(caveRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(caveClose,awake),tired);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(caveFar),tired);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = active;
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1 + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	//cout << desire << endl;
	return desire;
}

float SimpleAI::checkDrinkingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float waterRange = findNearestResource(WATER);
	//how far is the nearest food source
	//how hungry are we...
	float thirsty = fuzzyEngine.thirsty->getMembership(fluids);	
	//how full are we...
	float notThirsty = fuzzyEngine.notThirsty->getMembership(fluids);
	//are we very hungry?
	float veryThirsty = fuzzyEngine.veryThirsty->getMembership(fluids);
	float weekFromThirst = fuzzyEngine.WeekFromThirsty->getMembership(fluids);
	//how close are we to food...
	float waterRangeClose = fuzzyEngine.veryNear->getMembership(waterRange);
	float waterRangeMedium = fuzzyEngine.mediumRange->getMembership(waterRange);
	float waterRangeFar = fuzzyEngine.farAway->getMembership(waterRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(waterRangeClose,thirsty),veryThirsty);
	veryDesirableValue= Fuzzy::OR(veryDesirableValue,weekFromThirst);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(waterRangeClose),thirsty);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = notThirsty;
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1 + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
//	cout << desire << endl;
	return desire;

}

glm::vec3 SimpleAI::gotoFood(float desirability,float delta)
{
	glm::vec3 velocity = findResourceVector(FOOD) * delta * (1+desirability)*maxSpeed;
	return velocity;
}

glm::vec3 SimpleAI::gotoCave(float desirability,float delta)
{
	glm::vec3 velocity = findResourceVector(CAVE) * delta * (1+desirability)*maxSpeed;
	return velocity;
}

glm::vec3 SimpleAI::gotoWater(float desirability,float delta)
{
	glm::vec3 velocity = findResourceVector(WATER) * delta * (1+desirability) * maxSpeed;
	return velocity;
}

void SimpleAI::update(float delta)
{
	float eatDesirability = checkEatingDesirable();
	float sleepDesirability = checkSleepDesirable();
	float drinkDesirability = checkDrinkingDesirable();
	glm::vec3 velocity;
	if(eatDesirability>sleepDesirability && eatDesirability>drinkDesirability)
	{
		velocity= gotoFood(eatDesirability,delta);
	}
	else if(sleepDesirability>drinkDesirability)
	{
		velocity = gotoCave(sleepDesirability,delta);
	}
	else
	{
		velocity = gotoWater(drinkDesirability,delta);
	}
	position += velocity;
	//if we are near water then drink
	if(findNearestResource(WATER) <2)
	{
		fluids  = 1;
	}
	//else we are using water
	else
	{
		fluids -= delta *.05f;
	}
	//clamp fluids
	if(fluids <0)
	{
		fluids = 0;
	}
	if(fluids >1)
	{
		fluids = 1;
	}
	//if we are near food then eat
	if(findNearestResource(FOOD) <2)
	{
		solids += delta * .2;
	}
	//else we get hungrier
	else
	{
		solids -= delta * .03f;
	}
	//clamp food
	if(solids <0)
	{
		solids = 0;
	}
	if(solids > 1)
	{
		solids = 1;
	}
	//if we are near cave then sleep
	if(findNearestResource(CAVE) <2)
	{
		stamina += delta * .3f;
	}
	//else we get sleepier
	else
	{
		stamina -= delta * .02f;
	}
	//clamp stamina
	if(stamina <0)
	{
		stamina = 0;
	}
	if(stamina >1)
	{
		stamina = 1;
	}
}

void WorldController::update(float delta)
{
	for(auto worldObject:worldObjects)
	{
		worldObject->update(delta);
	}
}

void WorldController::draw()
{
	for(auto worldObject:worldObjects)
	{
		worldObject->draw();
	}
}

void WorldController::addObject(WorldObject* newObject)
{
	newObject->worldObjects = &worldObjects;
	worldObjects.push_back(newObject);
}