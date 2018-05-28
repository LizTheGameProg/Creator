#include "CircleCollider.h"
#include "SpriteBatch.h"
#include "CollisionHandler.h"
#include <string>

CircleCollider::CircleCollider(LML::transform2D & a_transform, float a_radius) : radius(a_radius)//, BaseCollider(a_transform)
{
	//collisionHandler->AddCollider(this, std::string("Circle"));
}

void CircleCollider::Render()
{
	//if(spriteBatch)
	{
		//spriteBatch->DrawCircle(transform.getTransform()[2][0], transform.getTransform()[2][1], radius, 10.f);
	}
}