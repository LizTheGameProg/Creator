#pragma once

#include "transform2D.h"
#include "SpriteBatch.h"

namespace openGL
{
	class Texture;
}

class SpriteBatch;
class BaseCollider;
class RigidBody;

#include <vector>
namespace LML
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Update(float deltaTime);
		virtual void Render();

		static void SetSpriteBatch(SpriteBatch * spriteBatch);
		void AddChild(GameObject * child);
		void SetParent(GameObject * parent);
		LML::mat3 GetGlobalTransform();

		openGL::Texture * texture;
		LML::transform2D transform;

	protected:
		std::vector<GameObject *> children;
		LML::mat3 globalTransform;

		GameObject * parent;

		BaseCollider * collider;
		RigidBody * rigidBody;

		static SpriteBatch * spriteBatch;
	};
}