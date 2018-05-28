#include "GameObject.h"
#include "SpriteBatch.h"
#include "BaseCollider.h"
#include "RigidBody.h"

namespace LML
{
	SpriteBatch * GameObject::spriteBatch = nullptr;

	GameObject::GameObject()
	{
		parent = nullptr;
		texture = nullptr;
		collider = nullptr;
		rigidBody = nullptr;
	}

	GameObject::~GameObject()
	{
		for(unsigned int i = 0; i < children.size(); i++)
		{
			delete children[i];
		}

		if(collider)
			delete collider;
		collider = nullptr;

		if(rigidBody)
			delete rigidBody;
		rigidBody = nullptr;
	}

	void GameObject::Update(float a_deltaTime)
	{
		globalTransform = GetGlobalTransform();

		for(std::vector<GameObject*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			(*iter)->Update(a_deltaTime);

			if((*iter)->GetGlobalTransform()[2].x < -100 ||
				(*iter)->GetGlobalTransform()[2].x > 1700 ||
				(*iter)->GetGlobalTransform()[2].y < -100 ||
				(*iter)->GetGlobalTransform()[2].y > 1000)
			{
				delete(*iter);
				iter = children.erase(iter);
				if(iter == children.end())
					break;
			}
		}
	}

	void GameObject::Render()
	{
		spriteBatch->DrawSpriteTransformed3x3(texture, globalTransform.data);

		if(collider)
		{
			collider->Render();
		}

		for(std::vector<GameObject*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			(*iter)->Render();
		}
	}

	void GameObject::SetSpriteBatch(SpriteBatch * a_spriteBatch)
	{
		spriteBatch = a_spriteBatch;
	}

	void GameObject::AddChild(GameObject * a_child)
	{
		a_child->parent = this;
		children.push_back(a_child);
	}

	void GameObject::SetParent(GameObject * a_parent)
	{
		parent = a_parent;
		parent->AddChild(this);
	}

	LML::mat3 GameObject::GetGlobalTransform()
	{
		if(parent != nullptr)
		{
			return transform.getTransform() * parent->globalTransform;
		}
		else
		{
			return transform.getTransform();
		}
	}
}