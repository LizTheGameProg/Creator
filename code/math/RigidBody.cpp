#include "RigidBody.h"
#include "common.h"
#include <iostream>

RigidBody::RigidBody() : velocity(LML::vec2()), acceleration(LML::vec2()), mass(5.f), friction(1.1f), angularVelocity(0.f), angularAcceleration(0.f), drag(1.1f)
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::Update(float a_deltaTime)
{
	// Is this where I decrease velocity based on friction?
	velocity /= friction;
	velocity.magnitude() <= 0.0001f ? velocity = LML::vec2() : velocity = velocity;

	// Add current acceleration to velocity
	velocity += (acceleration * a_deltaTime);
	
	angularVelocity /= drag;
	
	if(LML::abs(angularVelocity) <= 0.0001f)
		angularVelocity = 0.f;
	
	angularVelocity += (angularAcceleration * a_deltaTime);

	// Do I set acceleration to 0? 'cause I am
	acceleration = LML::vec2();
	angularAcceleration = 0.f;
}

void RigidBody::AddForce(LML::vec2 force)
{
	force = force / mass;
	acceleration = acceleration + force;
}

void RigidBody::AddTorque(float torque)
{
	torque = torque / mass;
	angularAcceleration += torque;
}