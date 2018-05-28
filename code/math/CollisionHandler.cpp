#include "CollisionHandler.h"

// Collision Types
#include "CircleCollider.h"
#include "AABBCollider.h"

// Needed math classes
#include "vec2.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

bool CollisionHandler::DetectCollisions()
{
	bool collisionsDetected = false;
	for(std::map<BaseCollider *, std::string>::iterator iter = colliders.begin(); iter != colliders.end(); ++iter)
	{
		for(std::map<BaseCollider *, std::string>::iterator jiter = iter; jiter != colliders.end(); ++jiter)
		{
			if(jiter == iter)
				continue;
			if(iter->second == std::string("Circle"))
			{
				if(iter->second == std::string("Circle"))
				{
					if(CircleCircleDetection(*(CircleCollider *) iter->first, *(CircleCollider *) jiter->first))
					{
						collisionsDetected = true;

						//Manifold info;

						LML::vec2 relativeVelocity = (jiter->first->transform.getTransform()[2].xy() - iter->first->transform.getTransform()[2].xy());
						

						


						//info.collider1 = *iter;
						//info.collider2 = *jiter;
						//collisions.push_back(info);
					}
				}
			}
		}
	}
	return collisionsDetected;
}

void CollisionHandler::ResolveCollisions()
{
	//for(std::vector<CollisionInformation>::iterator iter = collisions.begin(); iter != collisions.end(); ++iter)
	//{
	//	if(iter->collider1.second == std::string("Circle"))
	//	{
	//		if(iter->collider2.second == std::string("Circle"))
	//		{
	//			CircleCircleResolution(*iter);
	//			iter = collisions.erase(iter);
	//			if(iter == collisions.end())
	//			{
	//				break;
	//			}
	//		}
	//	}
	//}
}

void CollisionHandler::AddCollider(BaseCollider * collider, std::string type)
{
	colliders[collider] = type;
}


bool CollisionHandler::CircleCircleDetection(const CircleCollider & circle1, const CircleCollider & circle2)
{
	//float distance = (circle1.transform.getTransform()[2].xy() - circle2.transform.getTransform()[2].xy()).magnitudeSquared();
	//float radii = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
	//if(distance < radii)
	//	return true;
	//return false;

	float distance = (circle1.transform.getTransform()[2].xy() - circle2.transform.getTransform()[2].xy()).magnitudeSquared();
	float radii = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);

	return radii < distance;
}

//void CollisionHandler::CircleCircleResolution(CollisionHandler::CollisionInformation collisionInfo)
//{
	//CircleCollider * circle1 = (CircleCollider *)collisionInfo.collider1.first;
	//CircleCollider * circle2 = (CircleCollider *)collisionInfo.collider2.first;
	//
	//float distance = (circle1->transform.getTransform()[2].xy() - circle2->transform.getTransform()[2].xy()).magnitude();
	//float radii = (circle1->radius + circle2->radius);
	//
	//float overlap = distance - radii;
	//LML::vec2 direction = circle1->transform.getTransform()[2].xy() - circle2->transform.getTransform()[2].xy();
	//direction.normalise();
	//direction = direction * (overlap / 2.f);
	//
	//if(circle1->dynamic && circle2->dynamic)
	//{
	//	circle1->transform.translateBy(LML::vec2(-direction.x, -direction.y));
	//	circle2->transform.translateBy(LML::vec2(direction.x, direction.y));
	//}
	//else if(circle1->dynamic)
	//{
	//	circle1->transform.translateBy(LML::vec2(-direction.x, -direction.y));
	//	circle1->transform.translateBy(LML::vec2(-direction.x, -direction.y));
	//}
	//else
	//{
	//	circle2->transform.translateBy(LML::vec2(direction.x, direction.y));
	//	circle2->transform.translateBy(LML::vec2(direction.x, direction.y));
	//}
//}
