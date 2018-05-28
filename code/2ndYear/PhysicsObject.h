#pragma once

#include <glm\glm.hpp>
#include <vector>

enum class ShapeType
{
	PLANE = 0,
	SPHERE = 1,
	BOX = 2,
	NUMBERSHAPE = 3,
	JOINT
};

class PhysicsObject
{
public:
	virtual void update(glm::vec3 Gravity, float TimeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition(){};
	ShapeType shapeID;
};

class PlaneClass : public PhysicsObject
{
public:
	glm::vec3 normal;
	float distance;
	virtual void update(glm::vec3 Gravity, float TimeStep){};
	virtual void debug(){};
	virtual void makeGizmo();
	PlaneClass(glm::vec3 Normal,float Distance);
	PlaneClass(glm::vec3 Normal,glm::vec3 Origin);
	PlaneClass(){};

	std::vector<glm::vec3> prepareVector();
	std::vector<glm::vec3> getNorm();

private:
	glm::vec3 start;
	glm::vec3 end;

	void calculateVerts();
};

class DIYRigidBody : public PhysicsObject
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	float angularVelocity;
	glm::vec4 colour;
	glm::vec3 contacePosition;
	
	float mass;
	float inverseMass;
	
	float elasticity;
	float drag;

	float rotationalInertia;
	float rotationalDrag;
	
	bool dynamicObject;
	bool sleeping;
	float rotation2D;
	glm::mat4 rotationMatrix;

	DIYRigidBody(glm::vec3 Position, glm::vec3 Velocity, float Rotation, float Mass);
	virtual void update(glm::vec3 Gravity, float TimeStep);
	virtual void debug(){};
	virtual void collisionResponse(glm::vec3 CollisionPoint, glm::vec3 ForceVector);
	virtual void applyDrag(float Drag);
	virtual void makeGizmo(){};
	void applyForce(glm::vec3 Force);
	void applyForceToActor(DIYRigidBody * Other, glm::vec3 Force);
	void applyImpulse(glm::vec3 Impulse, glm::vec3 ContactVector);
	void applyTorque(float Torque);
};

class BallClass : public DIYRigidBody
{
public:
	float radius;
	BallClass(glm::vec3 Position, glm::vec3 Velocity, float Rotation, float Mass, float Radius, glm::vec4 Colour);
	BallClass(glm::vec3 Position, float Angle, float Speed, float Rotation, float Mass, float Radius, glm::vec4 Colour);
	virtual void makeGizmo();
};

class BoxClass : public DIYRigidBody
{
public:
	float width, height;
	glm::vec3 vert[5];
	BoxClass(glm::vec3 Position, glm::vec3 Velocity, float Rotation, float Width, float Height, float Mass, glm::vec4 Colour);
	
	virtual void update(glm::vec3 Gravity, float TimeStep);
	virtual void makeGizmo();
	
	void calculateVerts();
	std::vector<glm::vec3> prepareVector();
	std::vector<glm::vec3> getNorm();
};

class SpringJoint : public PhysicsObject
{
public:
	SpringJoint(DIYRigidBody* connection1,DIYRigidBody* connection2,float springCoefficient,float damping);
	~SpringJoint();

	DIYRigidBody * connections[2];
	float springCoefficient;
	float damping;
	float restLength;

	void update(glm::vec3 Gravity, float TimeStep);
	void debug(){}
	void makeGizmo();
};