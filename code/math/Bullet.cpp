#include "Bullet.h"
#include "Texture.h"

namespace LML
{
	Bullet::Bullet()
	{
		texture = new Texture("./Images/topdowntanks/Bullets/bulletBlue_outline.png");
	}

	Bullet::~Bullet()
	{
		delete texture;
	}

	void Bullet::Update(float a_deltaTime)
	{
		static float speed = 20.f;

		GameObject::Update(a_deltaTime);
		LML::vec2 forward(transform.getTransform()[1].x, transform.getTransform()[1].y);
		forward.normalise();
		forward = forward * speed;
		transform.translateBy(forward);
	}

	void Bullet::Render()
	{
		GameObject::Render();
	}
}