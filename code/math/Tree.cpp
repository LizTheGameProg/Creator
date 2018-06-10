#include "Tree.h"
#include "Texture.h"
#include "CircleCollider.h"
#include "vec2.h"
#include "common.h"

namespace LML
{
	Tree::Tree()
	{
		texture = new openGL::Texture("./Images/topdowntanks/Environment/treeLarge.png");
		//collider = new CircleCollider(transform, texture->GetWidth()/2.f);

		transform.setTranslation(LML::vec2(float(rand() % 1280), float(rand() & 720)));
		transform.translateBy(LML::vec2(-640.f, -360.f));
		transform.setRotation(23.f);
	}

	Tree::~Tree()
	{
		delete texture;
	}

	void Tree::Update(float a_deltaTime)
	{
		GameObject::Update(a_deltaTime);
	}

	void Tree::Render()
	{
		GameObject::Render();
	}
}