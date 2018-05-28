#include <vector>
#include <glm/glm.hpp>
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>

struct Projection
{
public:
	float min;
	float max;
	Projection(float min,float max)
	{
		this->min = min;
		this->max = max;
	}
};

enum ShapeType
{
	PLANE = 0,
	SPHERE =1,
	BOX = 2,
	NUMBERSHAPE = 3,
};

class PhysicsObject
{
public:
	void virtual update(glm::vec3 gravity,float timeStep) = 0;
	void virtual debug() =0;
	void virtual makeGizmo() =0;
	void virtual resetPosition(){};
	ShapeType shapeID;
};

class PlaneClass: public PhysicsObject
{
public:
	glm::vec3 normal;
	float distance;
	void virtual update(glm::vec3 gravity,float timeStep){};
	void virtual debug(){};
	void virtual makeGizmo();
	PlaneClass(glm::vec3 normal,float distance);
	PlaneClass();
};

class DIYRigidBody: public PhysicsObject
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	glm::vec3 oldPosition;
	glm::vec3 contactPoint; //if a collision occurs then this is the point of contact
	float mass;
	float rotation2D; //2D so we only need a single float to represent our rotation about Z
	glm::mat4 rotationMatrix;
	DIYRigidBody(glm::vec3 position,glm::vec3 velocity,float rotation,float mass);
	virtual void update(glm::vec3 gravity,float timeStep);
	virtual void debug();
	virtual void collisionResponse(glm::vec3 collisionPoint);
	virtual void resetPosition(){position = oldPosition;};
	void applyForce(glm::vec3 force);
	void DIYRigidBody::applyForceToActor(DIYRigidBody* actor2, glm::vec3 force);

};

class BallClass: public DIYRigidBody
{
public:
	float radius;
	BallClass(	glm::vec3 position,glm::vec3 velocity,float rotation,float mass,float radius, glm::vec4 colour);
	BallClass(	glm::vec3 position, float angle, float speed, float rotation, float radius, float mass, glm::vec4 colour);
	virtual void makeGizmo();
};

class BoxClass: public DIYRigidBody
{
public:
	float width,height;
	BoxClass(	glm::vec3 position,glm::vec3 velocity,float rotation,float mass,float width, float height,glm::vec4 colour);
	BoxClass(	glm::vec3 position, float angle, float speed, float rotation, float width, float height, float mass, glm::vec4 colour);
	virtual void makeGizmo();
};


class DIYPhysicScene
{
	public:
	glm::vec3 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
	void addActor(PhysicsObject*);
	void removeActor(PhysicsObject*);
	void upDate();
	void solveIntersections();
	void debugScene();
	void upDateGizmos();
	bool checkForCollision();
	static bool sphere2Sphere(PhysicsObject* ball1,PhysicsObject* ball2);
	static bool sphere2Plane(PhysicsObject* ball,PhysicsObject* plane);
	static bool plane2Sphere(PhysicsObject* plane,PhysicsObject* ball);
	static bool plane2Plane(PhysicsObject* plane,PhysicsObject* plane2); //never used but we'll add it for completeness
	static bool box2Box(PhysicsObject* ball1,PhysicsObject* ball2);
	static bool box2Plane(PhysicsObject* ball,PhysicsObject* plane);
	static bool box2Sphere(PhysicsObject* ball,PhysicsObject* plane);
	static bool plane2Box(PhysicsObject* ball,PhysicsObject* plane);
	static bool sphere2Box(PhysicsObject* plane,PhysicsObject* ball);
	static int box2PlaneHelper(glm::vec3* verts,glm::vec3 normal,float distance);
};