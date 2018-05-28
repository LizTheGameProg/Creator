#include "BaseCollider.h"
#include "CollisionHandler.h"

SpriteBatch * BaseCollider::spriteBatch = nullptr;
CollisionHandler * BaseCollider::collisionHandler = nullptr;

BaseCollider::BaseCollider() : transform(LML::transform2D()), dynamic(false)
{
	 
}

BaseCollider::BaseCollider(bool a_dynamic) : transform(LML::transform2D()), dynamic(a_dynamic)
{

}

BaseCollider::BaseCollider(LML::transform2D a_transform) : transform(a_transform)
{

}

BaseCollider::BaseCollider(LML::transform2D a_transform, bool a_dynamic) : transform(a_transform), dynamic(a_dynamic)
{

}

BaseCollider::~BaseCollider()
{

}