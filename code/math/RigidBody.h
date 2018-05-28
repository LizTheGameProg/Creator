#pragma once
#include "vec2.h"

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void Update(float deltaTime);

	// Linear Dynamics ///////////////
	void AddForce(LML::vec2 force);	//
									//
	LML::vec2 velocity;				//
	LML::vec2 acceleration;			//
	float mass;						//
	float friction;					//
	//////////////////////////////////

	// Rotational Dynamics ///////////
	void AddTorque(float torque);	//
									//
	float angularVelocity;			//
	float angularAcceleration;		//
	float drag;						//
	//////////////////////////////////
};