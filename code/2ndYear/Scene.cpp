#include "Scene.h"

#include <glm\glm.hpp>
#include <glm/ext.hpp>

#include <Utilities.h>
#include "Gizmos.h"
#include <float.h>

#include "PhysicsObject.h"

using namespace AIE_2ND_YEAR;

Scene::fn Scene::collisionfunctionArray[] = 
{
	Scene::plane2Plane,		Scene::plane2Sphere,	Scene::plane2Box,
	Scene::sphere2Plane,	Scene::sphere2Sphere,	Scene::sphere2Box,
	Scene::box2Plane,		Scene::box2Sphere,		Scene::box2Box
};

Scene::Scene(glm::vec3 a_Gravity, float a_TimeStep) : m_gravity(a_Gravity), m_timeStep(a_TimeStep)
{
	m_defaultScreenWidth	= 1280;
	m_defaultScreenHeight	= 720;

	// 3d camera
	//m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 1280/(float)720, 0.1f, 1000.0f);

	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(0,0,100), glm::vec3(0,0,0), glm::vec3(0,1,0)));
	float aspectRatio = (float)m_defaultScreenWidth/(float)m_defaultScreenHeight;
		
	float fSize = 25;
	float farPlane = 200;
	m_projectionMatrix = glm::ortho<float>(-fSize * aspectRatio, fSize * aspectRatio, -fSize, fSize, 0, farPlane);
	
	m_actors.push_back(new PlaneClass(glm::vec3( 0,1,0), glm::vec3(0,-20,0)));
	m_actors.push_back(new PlaneClass(glm::vec3( 1,1,0), glm::vec3(0,-16,0)));
	m_actors.push_back(new PlaneClass(glm::vec3( -1,1,0), glm::vec3(0,-16,0)));
	//m_actors.push_back(new PlaneClass(glm::vec3( 1,0,0), 20));
	//m_actors.push_back(new PlaneClass(glm::vec3(-1,0,0), 20));
	//m_actors.push_back(new PlaneClass(glm::vec3(0, 1,0), 20));
	//m_actors.push_back(new PlaneClass(glm::vec3(0,-1,0), 20));
	//
	//m_actors.push_back(new PlaneClass(glm::vec3(-1, 1,0), 15));
	//m_actors.push_back(new PlaneClass(glm::vec3( 1, 1,0), 15));
	//m_actors.push_back(new PlaneClass(glm::vec3(-1,-1,0), 15));
	//m_actors.push_back(new PlaneClass(glm::vec3( 1,-1,0), 15));

	BoxClass * box1 = new BoxClass(glm::vec3(10,-10,0), glm::vec3(0,-0,0), -0, 1, 1, 1, glm::vec4(1,1,1,1));
	m_actors.push_back(box1);
	
	BoxClass * box2 = new BoxClass(glm::vec3(-10,-10,0), glm::vec3(0,-0,0), -0, 1, 1, 1, glm::vec4(0,0,0,1));
	m_actors.push_back(box2);
	
	for(int i = 0; i < 3; i++)
	{
		BoxClass * box1 = new BoxClass(glm::vec3(i * 3.f - 10.f, 5.f + rand() % 5,0.f), glm::vec3( rand() % 20 - 10.f, rand() % 20 - 10.f,0.f), rand() % 360, 1.f, 1.f, 1.f, glm::vec4(1.f,1.f,1.f,1.f));
		m_actors.push_back(box1);
	}

	//for(int i = 0; i < 15; i++)
	//{
	//	BallClass * ball = new BallClass(glm::vec3(i * 3 - 10, rand() % 5, 0), glm::vec3(0,0,0), 0, 1, 1, glm::vec4(1,0,0,1));
	//	m_actors.push_back(ball);
	//}

	//BallClass * ball1 = new BallClass(glm::vec3(3,0,0), glm::vec3(0), 1.0f, 1.0f, 1.0f, glm::vec4(1,1,0,1));
	//m_actors.push_back(ball1);
	
	//std::vector<std::vector<BallClass *>> clothVector;
	//
	//int x = 6;
	//int y = 6;
	//
	//for(int i = 0; i < x; i++)
	//{
	//	std::vector<BallClass *> foo;
	//	clothVector.push_back(foo);
	//	for(int j = 0; j < y; j++)
	//	{
	//		int offset = 3;
	//		BallClass * ball = new BallClass(glm::vec3(i * offset + 35, j * offset - 5, 0), glm::vec3(0,-1,0), 0.0f, 10.0f, 1.0f, glm::vec4(1,0,0,1));
	//		ball->drag = .99f;
	//		ball->elasticity = .9f;
	//		if(j == y - 1 && i == 0 || j == y - 1 && i == x - 1)
	//		{
	//			ball->dynamicObject = false;
	//		}
	//		m_actors.push_back(ball);
	//		clothVector[i].push_back(ball);
	//	}
	//}
	//for(int i = 0; i < x; i++)
	//{
	//	for(int j = 0; j < y; j++)
	//	{
	//		if(i != 0)
	//		{
	//			SpringJoint * sj = new SpringJoint(clothVector[i][j], clothVector[i-1][j], 50, 0.1f);
	//			m_jointActors.push_back(sj);
	//		}
	//		if(j != 0)
	//		{
	//			SpringJoint * sj = new SpringJoint(clothVector[i][j], clothVector[i][j-1], 50, 0.1f);
	//			m_jointActors.push_back(sj);
	//		}
	//		if(!(i == 0 || j == 0))
	//		{
	//			SpringJoint * sj = new SpringJoint(clothVector[i][j], clothVector[i-1][j-1], 50, 0.1f);
	//			m_jointActors.push_back(sj);
	//		}
	//		if(!(i == y - 1 || j == 0))
	//		{
	//			SpringJoint * sj = new SpringJoint(clothVector[i][j], clothVector[i+1][j-1], 50, 0.1f);
	//			m_jointActors.push_back(sj);
	//		}
	//	}
	//}

	m_timeSinceLastUpdate = 0.0f;
	frames = 0;
	time = 0.f;
}

Scene::~Scene(void)
{
	for(auto actor : m_actors)
	{
		delete actor;
	}
	for(auto actor : m_jointActors)
	{
		delete actor;
	}
}

void Scene::update(void)
{
	time += Utility::getDeltaTime();
	frames++;
	if( time >= 1.0f)
	{
		time = 0.f;
		printf("FPS: %i\n", frames);
		frames = 0;
	}

	m_timeSinceLastUpdate += Utility::getDeltaTime();
	
	if(m_timeSinceLastUpdate < m_timeStep)
		return;
	m_timeSinceLastUpdate -= m_timeStep;
	for(int i = 0; i < m_actors.size(); i++)
	{
		checkForCollisionActor(m_actors[i], i);
	}
	for(int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->update(m_gravity, m_timeStep);
	}
	for( auto actor : m_jointActors)
	{
		actor->update(m_gravity, m_timeStep);
	}
}

void Scene::render(void)
{
	for( auto actor : m_actors)
	{
		actor->makeGizmo();
	}
	
	for( auto actor : m_jointActors)
	{
		actor->makeGizmo();
	}

	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );

	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void Scene::checkForCollisionActor(PhysicsObject* object1, int iterator)
{
	//need to check for collisions against all objects except this one.
	//for(PhysicsObject * object2 : m_actors)
	for(int i = iterator+1; i < m_actors.size(); i++)
	{
		PhysicsObject * object2 = m_actors[i];
		if(object1 != object2)
		{
			int shapeID1 = (int)object1->shapeID;
			int shapeID2 = (int)object2->shapeID;
			//ignore collision if either actor is a spring
			if(shapeID1 < (int)ShapeType::NUMBERSHAPE && shapeID2 < (int)ShapeType::NUMBERSHAPE)
			{
				int functionIndex = (shapeID1 * (int)ShapeType::NUMBERSHAPE) + shapeID2;
				fn collisionFunctionPtr = collisionfunctionArray[functionIndex];
				if(collisionFunctionPtr != nullptr)
				{
					collisionFunctionPtr(object1,object2);
				}
			}
		}
	}
}

glm::vec4 Scene::getMinMax(std::vector<glm::vec3> vecs_box, glm::vec3 axis)
{
	float min_proj_box = glm::dot(vecs_box[0], axis); int min_dot_box = 1;
	float max_proj_box = glm::dot(vecs_box[0], axis); int max_dot_box = 1;
	
	for (int j = 1; j < vecs_box.size(); j++) 
	{
		float curr_proj = glm::dot(vecs_box[j], axis);
		//select the maximum projection on axis to corresponding box corners
		if (min_proj_box > curr_proj) 
		{
			min_proj_box = curr_proj;
			min_dot_box = j;
		}
		//select the minimum projection on axis to corresponding box corners
		if (curr_proj > max_proj_box) 
		{
			max_proj_box = curr_proj;
			max_dot_box = j;
		}
	}
	return glm::vec4(min_proj_box, max_proj_box, min_dot_box, max_dot_box);
}

bool Scene::plane2Plane(PhysicsObject* obj1,PhysicsObject* obj2)
{
	return false;
}

bool Scene::plane2Sphere(PhysicsObject* obj1,PhysicsObject* obj2)
{
	PlaneClass * plane	= dynamic_cast<PlaneClass *>(obj1);
	BallClass * ball	= dynamic_cast<BallClass *>(obj2);
	if(ball != nullptr && plane != nullptr)
	{
		float sphereToPlane = glm::dot(ball->position,plane->normal) - plane->distance;
		if(abs(sphereToPlane) < ball->radius)//use abs because collision on both sides
		{
			float overlap = abs(sphereToPlane) - ball->radius;
			//calculate collision response:
			glm::vec3 planeNormal = plane->normal;
			glm::vec3 planeForceVector = ball->mass * planeNormal * (glm::dot(planeNormal,ball->velocity));
			ball->position += planeNormal * overlap;
			glm::vec3 torqueLevel = glm::vec3(planeNormal.y, -planeNormal.x, 0);
			float torque = glm::dot(torqueLevel, ball->velocity) * 1.0f/(1/ball->mass);
			ball->applyTorque(torque);
			
			ball->applyForce(-2.0f * planeForceVector);
			
			return true;
		}
	}
	return false;
}

bool Scene::sphere2Sphere(PhysicsObject* obj1,PhysicsObject* obj2)
{
	//try to cast objects to ball and ball
	BallClass * ball1 = dynamic_cast<BallClass *>(obj1);
	BallClass * ball2 = dynamic_cast<BallClass *>(obj2);
	//if we are successful then test for collision
	if(ball1 != nullptr && ball2 != nullptr)
	{
		glm::vec3 delta = ball2->position - ball1->position;
		float distance = glm::length(delta);
		float intersection = ball1->radius + ball2->radius - distance;
		if(intersection > 0)
		{
			glm::vec3 collisionNormal = glm::normalize(delta);
			glm::vec3 relativeVelocity =  ball1->velocity - ball2->velocity;
			glm::vec3 collisionVector = collisionNormal * (glm::dot(relativeVelocity,collisionNormal));
			glm::vec3 forceVector = collisionVector * 2.0f/(1/ball1->mass + 1/ball2->mass);

			float combinedElasticity = (ball1->elasticity * ball2->elasticity) * 0.5f;
			
			glm::vec3 seperationVector = collisionNormal * intersection * .505f;
			glm::vec3 torqueLevel = glm::normalize(glm::vec3(delta.y, -delta.x, 0) * ball1->radius);
			float torque = glm::dot(torqueLevel, relativeVelocity) * 1.0f/(1/ball1->mass + 1/ball2->mass);

			if(ball1->dynamicObject && ball2->dynamicObject)
			{
				ball1->applyForceToActor(ball2, /*-0.5f * */forceVector /** combinedElasticity*/);
				ball1->position -= seperationVector;
				ball2->position += seperationVector;
				ball1->applyTorque(-torque);
				ball2->applyTorque( torque);
			}
			else if (ball1->dynamicObject)
			{
				ball1->applyForce(forceVector/* * forceVector * combinedElasticity*/);
				ball1->position -= seperationVector;
				ball1->applyTorque(-torque);
			}
			else if (ball2->dynamicObject)
			{
				ball2->applyForce(-(forceVector/* * forceVector * combinedElasticity*/));
				ball2->position += seperationVector;
				ball2->applyTorque(torque);
			}						
			return true;
		}
	}
	return false;
}

bool Scene::plane2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
	PlaneClass * plane = dynamic_cast<PlaneClass *>(obj1);
	BoxClass * box = dynamic_cast<BoxClass *>(obj2);

	if(plane == nullptr && box == nullptr)
	{
		plane = dynamic_cast<PlaneClass *>(obj2);
		box = dynamic_cast<BoxClass *>(obj1);
	}
	
	{
		std::vector<glm::vec3> vecs_box = box->prepareVector();
		float fLargestInside = 0.0f;
		unsigned int uiLargestIndex = (unsigned int)vecs_box.size();
		unsigned int uiContactCount = 0;

		for(unsigned int i = 0; i < vecs_box.size();++i)
		{
			float fDist = glm::dot(vecs_box[i],-plane->normal);
			float fInsideDist = fDist - plane->distance;
		
			if(fInsideDist > 0)
			{
				if(fInsideDist > fLargestInside)
				{
					fLargestInside = fInsideDist;
					uiLargestIndex = i;
				}
				uiContactCount++;
			}
		
		}
		if(uiLargestIndex == vecs_box.size()) return false;
				
		float intersection = fLargestInside;
		glm::vec3 normal = plane->normal;
		glm::vec3 impact = vecs_box[uiLargestIndex] - box->position;

		
		float elasticity = box->elasticity;

		glm::vec3 relativeVelocity = box->velocity;
		glm::vec3 rA = vecs_box[uiLargestIndex]-box->position;

		float rAdotN2 = glm::dot(rA, normal);
		rAdotN2 *= rAdotN2;

		float jtop = -(1+elasticity) * glm::dot(box->velocity, normal);
		float jbot = glm::dot(normal, normal*(box->inverseMass)) + rAdotN2 / box->rotationalInertia;
		float j = jtop / jbot;

		box->velocity += normal * j;
		box->position += normal * intersection;
		box->angularVelocity += (glm::cross(rA, normal) * j).z * box->rotationalInertia;
		/*box->position -= -plane->normal * fLargestInside;
		
		//-----------------------------------------------------------------------
		// Collision Response

				
		glm::vec3 rA = vecs_box[uiLargestIndex] - box->position;//plane->normal * plane->distance;
		glm::vec3 relativeVelocity = -box->velocity - glm::cross(glm::vec3(0, 0, box->angularVelocity), rA);

		glm::vec3 normal = glm::normalize(plane->normal);
		float contactVal = glm::dot(relativeVelocity, normal);
		
		//if(contactVal > 0)
		//	return true;
			
		glm::vec3 rAcrossN = glm::cross(rA, normal);
		glm::vec3 inverseMassSum = box->inverseMass + glm::sqrt(rAcrossN) * box->rotationalInertia + glm::sqrt(rAcrossN) * (100000000.0f);
		//float inverseMassSum = glm::dot(normal, normal) * box->inverseMass + (glm::dot(rA, normal) * glm::dot(rA, normal)) / box->rotationalInertia;

		float j = -(1.0f + elasticity) * contactVal;
		j /= inverseMassSum.z;
		

		//float impulseScalar = glm::length(normal) * j;//-(1 + box->elasticity) * contactVal;
		//impulseScalar /= inverseMassSum.x;
		//impulseScalar /= uiContactCount;
		
		glm::vec3 impulse = normal * j;
		box->applyImpulse(-impulse, rA);			
		
		relativeVelocity = box->velocity - glm::cross(glm::vec3(0, 0, box->angularVelocity), rA);

		glm::vec3 tangent = relativeVelocity - (normal * glm::dot(relativeVelocity, normal));
		
		if(tangent.x > 0)
			tangent.x = glm::normalize(tangent.x);
		if(tangent.y > 0)
			tangent.y = glm::normalize(tangent.y);
		if(tangent.z > 0)
			tangent.z = glm::normalize(tangent.z);
		
		float tangentMag = -glm::dot(relativeVelocity, tangent);
		//tangentMag /= inverseMassSum.x;
		//tangentMag /= uiContactCount;

		if(tangentMag == 0.0f)
			return true;

		glm::vec3 tangentImpulse;
		
		if(abs(tangentMag) < j * 0.04f)
			tangentImpulse = tangent * tangentMag;
		else
			tangentImpulse = tangent * -j * 0.04f;
		
		box->applyImpulse(-tangentImpulse, rA);*/

	}
	return false;
}

bool Scene::sphere2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
	BallClass * sphere = dynamic_cast< BallClass * >(obj1);
	BoxClass * box = dynamic_cast< BoxClass * >(obj2);

	if(sphere == nullptr && box == nullptr)
	{
		sphere = dynamic_cast< BallClass * >(obj2);
		box = dynamic_cast< BoxClass * >(obj1);
	}
	
	{
		//Left side collision check
		glm::vec3 Ldirection(box->rotationMatrix[0].xyz);
		glm::vec3 LplanePosition = box->position + Ldirection * box->width;
		float fLeftSideDist = glm::dot(sphere->position - LplanePosition, Ldirection) - sphere->radius;

		//Right side collision check
		glm::vec3 Rdirection(-1.0f * box->rotationMatrix[0].xyz);
		glm::vec3 RplanePosition = box->position + Rdirection * box->width;
		float fRightSideDist = glm::dot(sphere->position - RplanePosition, Rdirection)- sphere->radius;

		//Top side collision check
		glm::vec3 Tdirection(box->rotationMatrix[1].xyz);
		glm::vec3 TplanePosition = box->position + Tdirection * box->height;
		float fTopSideDist = glm::dot(sphere->position - TplanePosition, Tdirection) - sphere->radius;

		//Bottom side collision check
		glm::vec3 Bdirection(-1.0f*box->rotationMatrix[1].xyz);
		glm::vec3 BplanePosition = box->position + Bdirection * box->height;
		float fBottomSideDist = glm::dot(sphere->position - BplanePosition, Bdirection) - sphere->radius;
		
		if(fLeftSideDist > 0 || fRightSideDist > 0 || fTopSideDist > 0 || fBottomSideDist > 0 )
			return false;

		float smallest = fLeftSideDist;
		glm::vec3 normal = Ldirection;
		glm::vec3 planePos = LplanePosition;

		if(fabs(smallest) > fabs(fRightSideDist))
		{
			smallest = fRightSideDist;
			normal = Rdirection;
			planePos = RplanePosition;
		}
		if(fabs(smallest) > fabs(fTopSideDist))
		{
			smallest = fTopSideDist;
			normal = Tdirection;
			planePos = TplanePosition;
		}
		if(fabs(smallest)  > fabs(fBottomSideDist))
		{
			smallest = fBottomSideDist;
			normal = Bdirection;
			planePos = BplanePosition;
		}

		//float fDist = glm::dot((sphere->position - planePos), normal);
		glm::vec3 collisionNormal = glm::normalize((sphere->position - box->position));
		glm::vec3 delta = sphere->position - box->position;
		glm::vec3 relativeVelocity =  sphere->velocity - box->velocity;
		glm::vec3 collisionVector = collisionNormal * (sphere->elasticity * glm::dot(relativeVelocity,collisionNormal));
		glm::vec3 forceVector = collisionVector * 2.0f/(1/sphere->mass + 1/box->mass);

		float fPushAmount = -smallest;
		glm::vec3 SeperationVec = normal * abs(fPushAmount) * 0.1f;

		glm::vec3 torqueLevel = glm::normalize(glm::vec3(delta.y, -delta.x, 0) * sphere->radius);
		float torque = glm::dot(torqueLevel, relativeVelocity) * 1.0f/(1/sphere->mass + 1/box->mass);

		if (!(sphere->dynamicObject) || !(box->dynamicObject))
		{
			SeperationVec *= 2.0f;
		}

		if(sphere->dynamicObject)
		{
			sphere->position += SeperationVec;
			sphere->applyForce(-forceVector );
			//sphere->applyTorque(-torque);
		}

		if(box->dynamicObject)
		{
			box->position -= SeperationVec;
			box->applyForce(forceVector);	
			//box->applyTorque(torque);
		}	
		
		return true;
	} 
	return false;
}

bool Scene::box2Box(PhysicsObject* obj1,PhysicsObject* obj2)
{
	BoxClass * box1 = dynamic_cast<BoxClass *>(obj1);
	BoxClass * box2 = dynamic_cast<BoxClass *>(obj2);

	if(box1 != nullptr && box2 != nullptr)
	{
		std::vector<glm::vec3> normals_box1 = box1->getNorm();
		std::vector<glm::vec3> normals_box2 = box2->getNorm();
		
		std::vector<glm::vec3> vecs_box1 = box1->prepareVector();
		std::vector<glm::vec3> vecs_box2 = box2->prepareVector();
		
		/*
		//results of P, Q
		glm::vec4 result_P1 = getMinMax(vecs_box1, normals_box1[1]);
		glm::vec4 result_P2 = getMinMax(vecs_box2, normals_box1[1]);
		bool separate_P = (result_P1.y < result_P2.x || result_P2.y < result_P1.x) ? true : false;
		
		glm::vec4 result_Q1 = getMinMax(vecs_box1, normals_box1[0]);
		glm::vec4 result_Q2 = getMinMax(vecs_box2, normals_box1[0]);
		bool separate_Q = (result_Q1.y < result_Q2.x || result_Q2.y < result_Q1.x) ? true : false;
		
		//results of R, S
		glm::vec4 result_R1 = getMinMax(vecs_box1, normals_box2[1]);
		glm::vec4 result_R2 = getMinMax(vecs_box2, normals_box2[1]);
		bool separate_R = (result_R1.y < result_R2.x || result_R2.y < result_R1.x) ? true : false;
		
		glm::vec4 result_S1 = getMinMax(vecs_box1, normals_box2[0]);
		glm::vec4 result_S2 = getMinMax(vecs_box2, normals_box2[0]);
		bool separate_S = (result_S1.y < result_S2.x || result_S2.y < result_S1.x) ? true : false;
		
		bool isSeparated = false;
		
		isSeparated = (separate_P || separate_Q || separate_R || separate_S);

		if (isSeparated)
			return false;
			*/

		//results of P, Q
		glm::vec4 result_P1 = getMinMax(vecs_box1, normals_box1[1]);
		glm::vec4 result_P2 = getMinMax(vecs_box2, normals_box1[1]);
		float intersection_P = glm::min(result_P1.y - result_P2.x, result_P2.y - result_P1.x);
		bool separate_P = (result_P1.y < result_P2.x || result_P2.y < result_P1.x) ? true : false;
		

		glm::vec4 result_Q1 = getMinMax(vecs_box1, normals_box1[0]);
		glm::vec4 result_Q2 = getMinMax(vecs_box2, normals_box1[0]);
		float intersection_Q = glm::min(result_Q1.y - result_Q2.x, result_Q2.y - result_Q1.x);
		bool separate_Q = (result_Q1.y < result_Q2.x || result_Q2.y < result_Q1.x) ? true : false;
		
		//results of R, S
		glm::vec4 result_R1 = getMinMax(vecs_box1, normals_box2[1]);
		glm::vec4 result_R2 = getMinMax(vecs_box2, normals_box2[1]);
		float intersection_R = glm::min(result_R1.y - result_R2.x, result_R2.y - result_R1.x);
		bool separate_R = (result_R1.y < result_R2.x || result_R2.y < result_R1.x) ? true : false;
		
		glm::vec4 result_S1 = getMinMax(vecs_box1, normals_box2[0]);
		glm::vec4 result_S2 = getMinMax(vecs_box2, normals_box2[0]);
		float intersection_S = glm::min(result_S1.y - result_S2.x, result_S2.y - result_S1.x);
		bool separate_S = (result_S1.y < result_S2.x || result_S2.y < result_S1.x) ? true : false;
		
		bool isSeparated = false;
		isSeparated = (separate_P || separate_Q || separate_R || separate_S);
		if (isSeparated)
			return false;

		glm::vec3 normal1 = normals_box1[1];
		float intersection1 = intersection_P;
		unsigned int index1 = (unsigned int) result_P1.z;

		glm::vec3 normal2 = normals_box2[1];
		float intersection2 = intersection_R;
		unsigned int index2 = (unsigned int) result_R2.z;

		if (intersection_Q < intersection1)
		{
			normal1 = normals_box1[0];
			intersection1 = intersection_Q;
			index1 = (unsigned int) result_Q1.z;
		}
				
		if (intersection_S < intersection2)
		{
			normal2 = normals_box2[0];
			intersection2 = intersection_S;
			index2 = (unsigned int) result_S2.z;
		}
		
		glm::vec3 normal = normal2;

		//if(intersection1 < intersection2)
		//	normal = normal1;

		normal = glm::normalize(box2->position - box1->position);

		//glm::vec3 perpNormal = glm::vec3( normal.y, -normal.x, 0 );

		glm::vec3 relativeVelocity = box2->velocity - box1->velocity;
		
		float jtop = -(1+0.5f) * glm::dot(relativeVelocity, normal);
		float jbot = glm::dot(normal, normal)*(box1->inverseMass + box2->inverseMass);
		float j = jtop / jbot;

		box1->velocity -= normal * j * box1->inverseMass;
		box2->velocity += normal * j * box2->inverseMass;

		box1->position -= normal * intersection1 * 0.505f;
		box2->position += normal * intersection2 * 0.505f;
		
		glm::vec3 impactPoint1 = box1->position + normal * intersection1 * 0.505f;
		glm::vec3 impactPoint2 = box2->position + normal * intersection2 * 0.505f;

		glm::vec3 rA = vecs_box1[index1] - box1->position;
		glm::vec3 rB = vecs_box2[index2] - box2->position;

		box1->angularVelocity += (glm::cross(rA, normal) * j).z * box1->rotationalInertia;
		box2->angularVelocity -= (glm::cross(rB, normal) * j).z * box2->rotationalInertia;


		
		/*
		float fBestDistance1 = -FLT_MAX;
		unsigned int uiBestIndex1 = vecs_box1.size();
		
		float fBestDistance2 = -FLT_MAX;
		unsigned int uiBestIndex2 = vecs_box2.size();
		
		glm::vec3 n1;
		glm::vec3 n2;
		
		// Box1 Best Distance
		if(result_P1.y > fBestDistance1)
		{
			fBestDistance1 = result_P1.y;
			uiBestIndex1 = result_P1.w;
			n1 = normals_box1[1];
		}
		if(result_Q1.y > fBestDistance1)
		{
			fBestDistance1 = result_Q1.y;
			uiBestIndex1 = result_Q1.w;
			n1 = normals_box1[0];
		}
		if(result_R1.y > fBestDistance1)
		{
			fBestDistance1 = result_R1.y;
			uiBestIndex1 = result_R1.w;
			n1 = normals_box2[1];
		}
		if(result_S1.y > fBestDistance1)
		{
			fBestDistance1 = result_S1.y;
			uiBestIndex1 = result_S1.w;
			n1 = normals_box2[0];
		}
		
		// Box2 Best Distance
		if(result_P2.y > fBestDistance2)
		{
			fBestDistance2 = result_P2.y;
			uiBestIndex2 = result_P2.w;
			n1 = normals_box1[1];
		}
		if(result_Q2.y > fBestDistance2)
		{
			fBestDistance2 = result_Q2.y;
			uiBestIndex2 = result_Q2.w;
			n1 = normals_box1[0];
		}
		if(result_R2.y > fBestDistance2)
		{
			fBestDistance2 = result_R2.y;
			uiBestIndex2 = result_R2.w;
			n1 = normals_box2[1];
		}
		if(result_S2.y > fBestDistance2)
		{
			fBestDistance2 = result_S2.y;
			uiBestIndex2 = result_S2.w;
			n1 = normals_box2[0];
		}
				
		uiBestIndex1--;
		uiBestIndex2--;

		glm::vec3 ra = box1->position - vecs_box1[uiBestIndex1];
		glm::vec3 rb = box2->position - vecs_box2[uiBestIndex2];  
				
		//-----------------------------------------------------------------------
		// Collision Response
		//		Seperation
		// Transform vertices to world space
		glm::vec3 v1 = vecs_box1[uiBestIndex1];
		glm::vec3 v2 = vecs_box2[uiBestIndex2];
		
		// Calculate reference face side normal in world space
		glm::vec3 v2Minusv1 = v2 - v1;
		
		glm::vec3 sidePlaneNormal = glm::normalize(v2Minusv1);
		
		// Orthogonalize
		glm::vec3 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x, 0 );
		
		// ax + by = c
		// c is distance from origin
		float refC		=  glm::dot( refFaceNormal, v1 );
		//float negSide	= -glm::dot( sidePlaneNormal, v1 );
		//float posSide	=  glm::dot( sidePlaneNormal, v2 );
		
		// Flip
		glm::vec3 n = refFaceNormal;
		glm::vec3 incidentVert[2] = {vecs_box1[uiBestIndex1], vecs_box2[uiBestIndex2]};
		
		if(fBestDistance1 >= fBestDistance2)
		{
			n = -refFaceNormal;
		}
		
		float separation = glm::dot( refFaceNormal, incidentVert[0]) - refC;
		
		box1->position += n * separation;
		
		separation = glm::dot( refFaceNormal, incidentVert[1]) - refC;
		
		box2->position -= n * separation;
		*/		
		//		Force and torque
		//						-(1 + e)vab.n
		//	j = ---------------------------------------------
		//		 n.n(ima + imb)+((ra.n)^2/ia)+((rb.n)^2/ib)
		// e = elesticity
		// vab = relative velocity
		// n = collision normal
		// ima = mass of a
		// imb = mass of b
		// ra = cm of a to ct
		// rb = cm of b to ct
		// ia = rotational inertia of a
		// ib = rotational inertia of b
		
		//float e = (box2->elasticity + box1->elasticity) * 0.5f;
		//glm::vec3 vab = box2->velocity - box1->velocity;
		//
		//float ima = box1->inverseMass;
		//float imb = box2->inverseMass;
		//float ia = box1->rotationalInertia;
		//float ib = box2->rotationalInertia;
		//
		////Top : -(1 + e)vab.n
		//float jTop = (-(1 + e) * glm::dot(vab, n));
		//// Bottom : n.n * mass + ra.n ^ 2 / ia + rb.n ^ 2 / ib
		//float jBottom = glm::dot(n, n * (ima + imb)) + (( glm::dot(ra, n) * glm::dot(ra, n)) / ia) + (( glm::dot(rb, n) * glm::dot(rb, n)) / ib);
		//					
		//float j = jTop / jBottom;
		//
		//box1->velocity -= n * j;
		//box2->velocity += n * j;
		
		//box1->angularVelocity += (glm::cross(ra, n) * j).z * box1->rotationalInertia;
		//box2->angularVelocity -= (glm::cross(rb, n) * j).z * box2->rotationalInertia;

		//box1->applyImpulse(n * j, ra);
		//box2->applyImpulse(-n * j, rb);
		
		//std::cout << "obb collision detected" << std::endl;
		//
		//float combinedElasticity = (box2->elasticity + box1->elasticity * 0.5f);
		//glm::vec3 relativeVelocity = box2->velocity - box1->velocity;
		//glm::vec3 collisionNormal = glm::normalize(box2->position - box1->position);
		//
		//float j = (-(1+combinedElasticity)* glm::dot(relativeVelocity, collisionNormal))/( glm::dot(collisionNormal, collisionNormal) * ( 1/box1->mass + 1/box2->mass ) );
		//
		//if(box1->dynamicObject)
		//{
		//	box1->position -= collisionNormal * 0.3f;
		//}
		//if(box2->dynamicObject)		
		//{
		//	box2->position += collisionNormal * 0.3f;
		//}
		//box1->applyForceToActor(box2, 1.0f * collisionNormal * j/box1->mass);

		return true;
	}
	return false;
}
