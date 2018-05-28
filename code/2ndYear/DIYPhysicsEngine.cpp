#include "DIYPhysicsEngine.h"
#include "Gizmos.h"
#include <iostream>

//rigid body functions
using namespace std;

using namespace AIE_2ND_YEAR;

//plane class functions

PlaneClass::PlaneClass(glm::vec3 normal,float distance)
{
	this->normal = glm::normalize(normal);
	this->distance = distance;
	shapeID = PLANE;
}

void PlaneClass::makeGizmo()
{
	float lineSegmentLength = 100;
	glm::vec3 centrePoint = normal * distance;
	glm::vec3 parallel = glm::vec3(normal.y,-normal.x,0); //easy to rotate normal through 90degrees around z
	glm::vec4 colour(1,1,1,1);
	glm::vec3 start = centrePoint + (parallel * lineSegmentLength);
	glm::vec3 end = centrePoint - (parallel * lineSegmentLength);
	Gizmos::addLine(start,end,colour);
}

//ball class functions

BallClass::BallClass(	glm::vec3 position,glm::vec3 velocity,float rotation,float radius,float mass,glm::vec4 colour)
	: DIYRigidBody(position,velocity,rotation,mass)  //call the base class constructor
{
	this->radius = radius;
	this->colour = colour;
	std::cout<<"adding ball "<<this->position.x<<','<<this->position.y<<','<<this->position.z<<std::endl;
	shapeID = SPHERE;
}

BallClass::BallClass(	glm::vec3 position,float angle,float speed,float rotation,float radius,float mass,glm::vec4 colour)
		: DIYRigidBody(position,glm::vec3(speed * cos(angle),speed * sin(angle),0),rotation,mass)  //call the base class constructor
{
	this->radius = radius;
	this->colour = colour;
	std::cout<<"adding ball "<<this->position.x<<','<<this->position.y<<','<<this->position.z<<std::endl;
	shapeID = SPHERE;
}

void BallClass::makeGizmo()
{
	Gizmos::addSphere(position,15,15,radius,colour);
}

//box class functions

BoxClass::BoxClass(	glm::vec3 position,glm::vec3 velocity,float rotation,float mass,float width, float height,glm::vec4 colour)
	: DIYRigidBody(position,velocity,rotation,mass)  //call the base class constructor
{
	this->width = width;
	this->height = height;
	this->colour = colour;
	shapeID = BOX;
}

BoxClass::BoxClass(	glm::vec3 position, float angle, float speed, float rotation, float width, float height, float mass, glm::vec4 colour)
	: DIYRigidBody(position,glm::vec3(speed * cos(angle),speed * sin(angle),0),rotation,mass)  //call the base class constructor
{
	this->width = width;
	this->height = height;
	this->colour = colour;
	shapeID = BOX;
}

void BoxClass::makeGizmo()
{
	//Get a rotation matrix from our 2D rotation so we can draw our gizmo
	Gizmos::addAABBFilled(position,glm::vec3(width,height,0),colour,&rotationMatrix);
}

DIYRigidBody::DIYRigidBody(	glm::vec3 position,glm::vec3 velocity,float rotation,float mass)
{
	std::cout<<"adding rigid body "<<position.x<<','<<position.y<<','<<position.z<<std::endl;
	this->position = position;
	this->velocity = velocity;
	this->rotation2D = rotation;
	this->mass = mass;
	colour = glm::vec4(1,1,1,1); //white by default
}

void DIYRigidBody::applyForce(glm::vec3 force)
{
		velocity += force/mass;
}

void DIYRigidBody::applyForceToActor(DIYRigidBody* actor2, glm::vec3 force)
{
	actor2->applyForce(force);
	applyForce(-force);
}

void DIYRigidBody::collisionResponse(glm::vec3 collisionPoint)
{
	// for now we'll just set the velocity to zero
	velocity = glm::vec3(0,0,0);
	collisionPoint = collisionPoint;
}

void DIYRigidBody::update(glm::vec3 gravity,float timeStep)
{

	applyForce(gravity * mass * timeStep);
	oldPosition = position; //keep our old position for collision response
	position += velocity * timeStep;
	//rotationMatrix = glm::rotate(rotation2D,0.0f,0.0f,1.0f); 
}

void DIYRigidBody::debug()
{
	cout<<"position "<<position.x<<','<<position.y<<','<<position.z<<endl;
}

//scene functions

void DIYPhysicScene::addActor(PhysicsObject* object)
{
	actors.push_back(object);
}
	
void DIYPhysicScene::removeActor(PhysicsObject* object)
{
	auto item = std::find(actors.begin(), actors.end(), object);
	if(item < actors.end())
	{
		actors.erase(item);
	}
}

//function pointer array for doing our collisions
typedef bool (*fn)( PhysicsObject*, PhysicsObject* );
//function pointer array for doing our collisions
static fn collisionfunctionArray[] = 
{ 
	DIYPhysicScene::plane2Plane,	DIYPhysicScene::plane2Sphere,	DIYPhysicScene::plane2Box, 
	DIYPhysicScene::sphere2Plane,	DIYPhysicScene::sphere2Sphere,	DIYPhysicScene::sphere2Box, 
	DIYPhysicScene::box2Plane,		DIYPhysicScene::box2Sphere,		DIYPhysicScene::box2Box
};

bool DIYPhysicScene::checkForCollision()
{
	size_t actorCount = actors.size();
	//need to check for collisions against all objects except this one.
	for(size_t outer = 0;outer < actorCount-1;outer++)
	{
		for(size_t inner = outer+1;inner < actorCount;inner++)
		{
			PhysicsObject* object1 = actors[outer];
			PhysicsObject* object2 = actors[inner];
			int shapeID1 = object1->shapeID;
			int shapeID2 = actors[inner]->shapeID;
			//using function pointers
			int functionIndex = (shapeID1 * NUMBERSHAPE) + shapeID2;
			fn collisionFunctionPtr = collisionfunctionArray[functionIndex];
			if(collisionFunctionPtr!= NULL)
			{
				if(collisionFunctionPtr(object1,object2))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool DIYPhysicScene::sphere2Sphere(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and ball
	BallClass *ball1 = dynamic_cast<BallClass*>(obj1);
	BallClass *ball2 = dynamic_cast<BallClass*>(obj2);
	//if we are successful then test for collision
	if(ball1 != NULL && ball2 != NULL)
	{
		glm::vec3 delta = ball2->position - ball1->position;
		float distance = glm::length(delta);
		if(distance < ball1->radius + ball2->radius)
		{
			//find the point where the collision occured (we need this for collision response later)
			glm::vec3 collisionPoint = ball1->position + glm::normalize(delta)*ball1->radius;
			ball1->collisionResponse(collisionPoint);
			ball2->collisionResponse(collisionPoint);
			return true;
		}
	}
	return false;
}

bool DIYPhysicScene::plane2Sphere(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//we just need to reverse the order of arguments and pass them into our sphere to plane collision detectio
	//don't want to write the same code twice :)
	return sphere2Plane(obj2,obj1);
}

bool DIYPhysicScene::sphere2Plane(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and plane
	BallClass *ball = dynamic_cast<BallClass*>(obj1);
	PlaneClass *plane = dynamic_cast<PlaneClass*>(obj2);
	//if we are successful then check for collision
	if(ball != NULL && plane != NULL)
	{
		float sphereToPlane = glm::dot(ball->position,plane->normal) - plane->distance;
		if(abs(sphereToPlane) < ball->radius)//use abs because collision on both sides
		{
			//find the point where the collision occured (we need this for collision response later)
			glm::vec3 collisionPoint = ball->position - (plane->normal*sphereToPlane);
			ball->collisionResponse(collisionPoint);
			return true;
		}
	}
	return false;
}

bool DIYPhysicScene::plane2Plane(PhysicsObject* plane,PhysicsObject* plane2)
{
	//never used but we'll add it for completeness
	return false;
}

void getAxis(glm::vec3 *verts1,glm::vec3 *axis,int numberVerts)
{	
	for(int vertIndex = 0;vertIndex<numberVerts;vertIndex++)
	{
		//find axis from vertices
		//there are quicker ways of doing this for boxes but our code works for other 2D shapes
		int nextIndex = (vertIndex+1)%numberVerts;
		glm::vec3 perpendicular = glm::normalize(verts1[vertIndex] - verts1[nextIndex]);
		//for 3D we do a cross product between two edges here instead...
		axis[vertIndex] = glm::vec3(perpendicular.y,-perpendicular.x,0);
	}
}

Projection project(glm::vec3 *verts,glm::vec3 axis,int numberVerts)
{
	float min = glm::dot(axis,verts[0]);
	float max = min;
	for(int vertIndex = 0;vertIndex<numberVerts;vertIndex++)
	{
		float p = glm::dot(axis,verts[vertIndex]);
		if(p< min)
		{
			min = p;
		}
		if(p> max)
		{
			max = p;
		}
	}
	return Projection(min,max);
}

bool overlap(Projection p1,Projection p2)
{
	if(p1.max < p2.min)
	{
		return false;
	}
	if(p1.min > p2.max)
	{
		return false;
	}
	return true;
}

//box collision routines
bool DIYPhysicScene::box2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and plane
	BoxClass *box1 = dynamic_cast<BoxClass*>(obj1);
	BoxClass *box2 = dynamic_cast<BoxClass*>(obj2);
	const int numberAxis = 4;
	if(box1 != NULL && box2 != NULL)
	{
		glm::vec3 axis1[numberAxis];
		glm::vec3 axis2[numberAxis];
		float width1 = box1->width;
		float height1 = box1->height;
		float width2 = box2->width;
		float height2 = box2->height;
		//create our vertices, they must be in correct order
		glm::vec3 verts1[4] = {glm::vec3(-width1,height1,0),glm::vec3(width1,height1,0),glm::vec3(width1,-height1,0),glm::vec3(-width1,-height1,0)};
		glm::vec3 verts2[4] = {glm::vec3(-width2,height2,0),glm::vec3(width2,height2,0),glm::vec3(width2,-height2,0),glm::vec3(-width2,-height2,0)};

		//transform to world space
		for(int count=0;count < numberAxis;count++)
		{
			verts1[count] = (box1->rotationMatrix*glm::vec4(verts1[count],1) ).xyz + box1->position;
			verts2[count] = (box2->rotationMatrix*glm::vec4(verts2[count],1) ).xyz + box2->position;
		}
		//get the axis
		getAxis(verts1,axis1,numberAxis);
		getAxis(verts2,axis2,numberAxis);
		for(int i=0;i<numberAxis;i++)
		{
			Projection projection1 = project(verts1,axis1[i],numberAxis);
			Projection projection2 = project(verts2,axis1[i],numberAxis);
			if(!overlap(projection1,projection2))
			{
				return false;
			}
		}
		for(int i=0;i<numberAxis;i++)
		{
			Projection projection1 = project(verts1,axis2[i],numberAxis);
			Projection projection2 = project(verts2,axis2[i],numberAxis);
			if(!overlap(projection1,projection2))
			{
				return false;
			}
		}
	}
	glm::vec3 closestPoint; //how to find this...
	box1->collisionResponse(closestPoint);
	box2->collisionResponse(closestPoint);
	return true;
}

int DIYPhysicScene::box2PlaneHelper(glm::vec3* verts,glm::vec3 normal,float distance)
{
	float min = FLT_MAX;
	float max = FLT_MIN;
	float minDistance = FLT_MAX;
	int closestPointIndex;
	//float projectedPoints[4];
	for(int count=0;count < 4;count++)
	{
		//project the vertex onto the planes normal and work out the distance to the plane
		float projectedPoints = glm::dot(verts[count],normal) - distance;
		if(projectedPoints <min)
		{
			min = projectedPoints;
		}
		if(projectedPoints > max)
		{
			max = projectedPoints;
		}
		if(abs(projectedPoints)<minDistance)
		{
			minDistance = abs(projectedPoints);
			closestPointIndex= count;
		}
	}
	//if min and max have different signs then box is across plane
	if(min<0 && max > 0)
	{
		return closestPointIndex;
	}
	return -1;
}

bool DIYPhysicScene::box2Plane(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and plane
	BoxClass *box = dynamic_cast<BoxClass*>(obj1);
	PlaneClass *plane = dynamic_cast<PlaneClass*>(obj2);
	if(box != NULL && plane != NULL)
	{	
		float width = box->width;
		float height = box->height;
		glm::vec3 verts[4] = {glm::vec3(-width,height,0),glm::vec3(width,height,0),glm::vec3(width,-height,0),glm::vec3(-width,-height,0)};
		//find the coordinates for the four corners of our box
		for(int count=0;count < 4;count++)
		{
			verts[count] = (box->rotationMatrix*glm::vec4(verts[count],1) ).xyz + box->position;
		}
		//do the collision check.
		int closetsPointIndex = DIYPhysicScene::box2PlaneHelper(verts,plane->normal,plane->distance);
		//if closetsPointIndex is not negative then a collision has occured 
		if(closetsPointIndex!=-1)
		{
			//closetsPointIndex is the index of the closest point
			box->collisionResponse(verts[closetsPointIndex]);
			return true;
		}
	}
	return false;
}

bool DIYPhysicScene::box2Sphere(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and plane
	BoxClass *box = dynamic_cast<BoxClass*>(obj1);
	BallClass *ball = dynamic_cast<BallClass*>(obj2);
	if(box != NULL && ball != NULL)
	{
		return false;
	}
	return false;
}

bool DIYPhysicScene::plane2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
		return box2Plane(obj2,obj1);
}
bool DIYPhysicScene::sphere2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
	return box2Sphere(obj2,obj1);
}



void DIYPhysicScene::solveIntersections()
{
	for(auto actorPtr:actors)
	{
		actorPtr->resetPosition();
	}
}

void DIYPhysicScene::upDate()
{
	bool runPhysics = true;
	int maxIterations = 10; //emergency count to stop us repeating for ever in extreme situations
	while(runPhysics && maxIterations>0)
	{
		for(auto actorPtr:actors)
		{
			actorPtr->update(gravity,timeStep);
		}
		if(checkForCollision())
		{
		//	cout<<"collision found"<<endl;
			//if a collision has a occured we need to fix our simulation
		//	solveIntersections();
		}
		else
		{
			runPhysics = false;
		}
		maxIterations--;
	//	if(maxIterations == 0)
	//	{
	//		cout<<"solver maxed out";
	//	}
	}
}

void DIYPhysicScene::debugScene()
{
	int count = 0;
	for (auto actorPtr:actors)
	{
		cout<<count<<" : ";
		actorPtr->debug();
		count++;
	}
}

void DIYPhysicScene::upDateGizmos()
{

	for (auto actorPtr:actors)
	{
		actorPtr->makeGizmo();
	}
}
