#pragma once
#include <map>
#include <string>
#include <vector>

class BaseCollider;
class CircleCollider;

class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	bool DetectCollisions();
	void ResolveCollisions();

	void AddCollider(BaseCollider * collider, std::string type);

protected:
	struct Manifold
	{
		//LML::vec2 collisionNormal;
		float penetrationDepth;
	};

	bool CircleCircleDetection(const CircleCollider & circle1, const CircleCollider & circle2);
	//void CircleCircleResolution(CollisionInformation collisionInfo);

	std::map<BaseCollider *, std::string> colliders;
	//std::vector<CollisionInformation> collisions;
};