#include "PhysicsObject.h"

#include <Utilities.h>
#include "Gizmos.h"
#include <glm\ext.hpp>

#define MIN_LINEAR_THRESHOLD 0.01f
#define MIN_ROTATION_THRESHOLD 0.01f

using namespace AIE_2ND_YEAR;

PlaneClass::PlaneClass(glm::vec3 a_normal, float a_distance)
{
	normal = glm::normalize(a_normal);
	distance = a_distance;
	shapeID = ShapeType::PLANE;
	calculateVerts();
}

PlaneClass::PlaneClass(glm::vec3 a_normal,glm::vec3 a_origin)
{
	normal = glm::normalize(a_normal);
	distance = -glm::dot(a_normal, a_origin);
	shapeID = ShapeType::PLANE;
	calculateVerts();
}


void PlaneClass::makeGizmo()
{
	glm::vec4 colour(1,1,1,1);
	Gizmos::addLine(start,end,colour);

	
}

std::vector<glm::vec3> PlaneClass::prepareVector()
{
	std::vector<glm::vec3> vecs_box(0);
	
	vecs_box.push_back(normal * -distance);
	vecs_box.push_back(start);
	vecs_box.push_back(end);
	
	return vecs_box;
}

std::vector<glm::vec3> PlaneClass::getNorm()
{
	std::vector<glm::vec3> normals;
	
	normals.push_back(normal);

	return normals;
}

void PlaneClass::calculateVerts()
{
	float lineSegmentLength = 100;

	glm::vec3 centrePoint = normal * -distance;
	glm::vec3 parallel = glm::vec3(normal.y,-normal.x,0); //easy to rotate normal through 90degrees around z
	
	start = centrePoint + (parallel * (lineSegmentLength));
	end = centrePoint - (parallel * (lineSegmentLength));
}

BallClass::BallClass(glm::vec3 a_Position, 
					 glm::vec3 a_Velocity, 
					 float a_Rotation, 
					 float a_Mass, 
					 float a_Radius, 
					 glm::vec4 a_Colour)
					 : DIYRigidBody(a_Position, a_Velocity, a_Rotation, a_Mass)
{
	radius = a_Radius;
	colour = a_Colour;
	shapeID = ShapeType::SPHERE;
	rotationalInertia *= radius;
}

BallClass::BallClass(glm::vec3 a_Position, 
					 float a_Angle, 
					 float a_Speed, 
					 float a_Rotation, 
					 float a_Mass, 
					 float a_Radius, 
					 glm::vec4 a_Colour)
					 : DIYRigidBody(a_Position, glm::vec3( a_Speed * cos(a_Angle), a_Speed * sin(a_Angle), 0), a_Rotation, a_Mass)
{
	radius = a_Radius;
	colour = a_Colour;
	shapeID = ShapeType::SPHERE;
	rotationalInertia *= radius;
}

void BallClass::makeGizmo()
{
	rotationMatrix = glm::rotate(glm::mat4(1), rotation2D, glm::vec3(0,0,1));
	Gizmos::addSphere(position, 15, 15, radius, colour, &rotationMatrix);
}

DIYRigidBody::DIYRigidBody(glm::vec3 a_Position, 
						   glm::vec3 a_Velocity, 
						   float a_Rotation, 
						   float a_Mass)
{
	position = a_Position;
	velocity = a_Velocity;
	rotation2D = a_Rotation;
	mass = a_Mass;
	inverseMass = 1.0f / mass;
	rotationalInertia = 2.0f / 5.0f * mass;
	rotationalDrag = .95f;
	dynamicObject = true;
	sleeping = false;
	colour = glm::vec4(1,1,1,1);
	rotationMatrix = glm::rotate(glm::mat4(1), rotation2D, glm::vec3(0,0,1));
	angularVelocity = 0.0f;
	drag = .99f;
	elasticity = .5f;
}

void DIYRigidBody::update(glm::vec3 a_Gravity, float a_TimeStep)
{
	if(dynamicObject)
	{
		if(!sleeping)
		{
			applyForce(a_Gravity * mass * a_TimeStep);

			position += velocity * a_TimeStep;
			
			velocity *= drag;
			angularVelocity *= rotationalDrag;
			
			rotation2D += angularVelocity * a_TimeStep;

			if(glm::length(velocity) < MIN_LINEAR_THRESHOLD)
			{
				velocity = glm::vec3(0);
			}

			if(abs(angularVelocity) < MIN_ROTATION_THRESHOLD)
			{
				angularVelocity = 0;
			}
		}
		sleeping = (velocity == glm::vec3(0) && angularVelocity == 0) ? true : false;
	}
}

void DIYRigidBody::collisionResponse(glm::vec3 a_CollisionResponse, glm::vec3 a_ForceVector)
{

}

void DIYRigidBody::applyDrag(float a_Drag)
{
	velocity *= drag;
	angularVelocity *= rotationalDrag;
}

void DIYRigidBody::applyForce(glm::vec3 a_Force)
{
	if(dynamicObject)
	{
		velocity += a_Force / mass;
		sleeping = false;
	}
}

void DIYRigidBody::applyForceToActor(DIYRigidBody * a_Other, glm::vec3 a_Force)
{
	a_Other->applyForce(a_Force);
	applyForce(-a_Force);
}

void DIYRigidBody::applyTorque(float a_Torque)
{
	if(dynamicObject)
	{
		angularVelocity += a_Torque / rotationalInertia;
		sleeping = false;
	}
}

void DIYRigidBody::applyImpulse(glm::vec3 Impulse, glm::vec3 ContactVector)
{
	if(dynamicObject)
	{
		velocity += Impulse * inverseMass;
		glm::vec3 cross = glm::cross(ContactVector, Impulse);
		angularVelocity += 1.0f / rotationalInertia * cross.z;
		sleeping = false;
	}
}

SpringJoint::SpringJoint(DIYRigidBody* connection1,DIYRigidBody* connection2,float springCoefficient,float damping) : PhysicsObject()
{
	this->connections[0] = connection1;
	this->connections[1] = connection2;
	this->springCoefficient = springCoefficient;
	this->damping = damping;
	this->restLength = glm::length(connections[0]->position - connections[1]->position);
	shapeID = ShapeType::JOINT;
}

SpringJoint::~SpringJoint()
{

}

void SpringJoint::update(glm::vec3 Gravity, float TimeSpan)
{
	float k = springCoefficient;
	float X = glm::length(connections[0]->position - connections[1]->position) - restLength;
	float b = damping;
	glm::vec3 v = connections[0]->velocity - connections[1]->velocity;

	glm::vec3 f1 = k * X - b * v;
	glm::vec3 f2 = k * X - b * -v;
	
	glm::vec3 direction0to1 = glm::normalize(connections[1]->position - connections[0]->position);
	glm::vec3 direction1to0 = glm::normalize(connections[0]->position - connections[1]->position);

	connections[0]->applyForce(f2 * direction0to1);
	connections[1]->applyForce(f1 * direction1to0);
}

void SpringJoint::makeGizmo()
{
	Gizmos::addLine(connections[0]->position, connections[1]->position, glm::vec4(1,1,1,1), glm::vec4(1,1,1,1));
}

BoxClass::BoxClass(glm::vec3 a_Position, glm::vec3 a_Velocity, float a_Rotation, float a_Width, float a_Height, float a_Mass, glm::vec4 a_Colour)
	: DIYRigidBody(a_Position, a_Velocity, a_Rotation, a_Mass)
{
	colour = a_Colour;

	shapeID = ShapeType::BOX;
	
	width = a_Width;
	height = a_Height;

	calculateVerts();
}

void BoxClass::update(glm::vec3 Gravity, float TimeStep)
{
	DIYRigidBody::update(Gravity, TimeStep);

	calculateVerts();	
}

void BoxClass::makeGizmo()
{
	//rotationMatrix = glm::rotate(glm::mat4(1), rotation2D, glm::vec3(0,0,1));
	//Gizmos::addAABBFilled(position, glm::vec3(width, height, 1), colour, &rotationMatrix);

	Gizmos::addLine(vert[1], vert[2], colour, colour);// Top Line
	Gizmos::addLine(vert[2], vert[3], colour, colour);// Right Line
	Gizmos::addLine(vert[3], vert[4], colour, colour);// Bottom Line
	Gizmos::addLine(vert[4], vert[1], colour, colour);// Left Line
}

void BoxClass::calculateVerts()
{
	rotationMatrix = glm::rotate(glm::mat4(1), rotation2D, glm::vec3(0,0,1));

	glm::vec3 box1vX(width, 0, 0);
	glm::vec3 box1vY(0, height, 0);

	box1vX = (rotationMatrix * glm::vec4(box1vX, 0)).xyz;
	box1vY = (rotationMatrix * glm::vec4(box1vY, 0)).xyz;

	vert[0] = position;
	vert[1] = position - box1vX + box1vY;// Top Left
	vert[2] = position + box1vX + box1vY;// Top Right
	vert[3] = position + box1vX - box1vY;// Bottom Right
	vert[4] = position - box1vX - box1vY;// Bottom Left
}

std::vector<glm::vec3> BoxClass::prepareVector()
{
	std::vector<glm::vec3> vecs_box(0);
	
	for (int i = 1; i < 5; i++) 
	{
		vecs_box.push_back(vert[i]);
	}
	
	return vecs_box;
}

std::vector<glm::vec3> BoxClass::getNorm()
{
	std::vector<glm::vec3> normals;
	for (int i = 1; i < 4; i++) 
	{
		glm::vec3 currentNormal( glm::normalize(glm::vec3( vert[i + 1].x - vert[i].x, vert[i + 1].y - vert[i].y, 0)));
		normals.push_back(currentNormal);
	}
	normals.push_back( glm::normalize( glm::vec3(vert[1].x - vert[4].x, vert[1].y - vert[4].y, 0)));
	return normals;
}