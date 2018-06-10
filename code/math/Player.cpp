#include "Player.h"
#include "Texture.h"
#include "vec2.h"
#include "Input.h"
#include "GLFW\glfw3.h"
#include "common (2).h"
#include "SpriteBatch.h"
#include "RigidBody.h"
//#include "Bullet.h"
//#include "CircleCollider.h"

using namespace LML;

Player::Player()
{
	texture = new Texture("./Images/Racing Pack/PNG/Cars/car_black_1.png");
	rigidBody = new RigidBody();
	rigidBody->friction = 1.1f;
	
	transform.scaleBy(LML::vec2(0.5f, 0.5f));

	//turret = new Texture("./Images/topdowntanks/Tanks/barrelBlue_outline.png");
	//collider = new CircleCollider(transform, texture->GetWidth()/2.f);
	//collider->dynamic = true;
	
}

Player::~Player()
{
	delete texture;
	//delete turret;
}

void Player::Update(float a_deltaTime)
{
	GameObject::Update(a_deltaTime);

	float movementSpeed = 250.f;
	float rotationSpeed = LML::PI / 0.5f;

	bool moving = false;

	if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_W))
	{
		moving = true;

		//rigidBody->AddForce(transform.getForward() * -movementSpeed);

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_A))
		{
			rigidBody->AddTorque(-rotationSpeed * 0.5f);
		}

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_D))
		{
			rigidBody->AddTorque(rotationSpeed * 0.5f);
		}
	}

	if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_S))
	{
		moving = true;

		//rigidBody->AddForce(transform.getForward() * movementSpeed);

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_A))
		{
			rigidBody->AddTorque(rotationSpeed * 0.5f);
		}

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_D))
		{
			rigidBody->AddTorque(-rotationSpeed * 0.5f);
		}
	}

	/*if(!moving)
	{
		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_A))
		{
			rigidBody->AddTorque(-rotationSpeed);
		}

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_D))
		{
			rigidBody->AddTorque(rotationSpeed);
		}
	}*/



	//LML::vec2 globalPosition = globalTransform[2].xy();
	//LML::vec2 difference = globalPosition - LML::vec2(Input::GetSingleton()->GetMouseX(), Input::GetSingleton()->GetMouseY());

	//difference.normalise();
	//float angle = difference.angle();
	//barrelTransform.setRotation(angle - LML::PI/2.f - transform.getRotation());

	//if(Input::GetSingleton()->WasKeyPressed(GLFW_KEY_SPACE))
	//{
	//	Bullet * bullet = new Bullet();
	//	parent->AddChild(bullet);
	//	bullet->transform.setTranslation(transform.getTransform()[2].xy());
	//	bullet->transform.setRotation(angle + LML::PI / 2.f);
	//}

	if(rigidBody)
	{
		rigidBody->Update(a_deltaTime);

		//transform.translation[2].x += rigidBody->velocity.x;
		//transform.translation[2].y += rigidBody->velocity.y;
		transform.rotateBy(rigidBody->angularVelocity);

		transform.translateBy(rigidBody->velocity);
	}
}

void Player::Render()
{
	GameObject::Render();
	//spriteBatch->DrawSpriteTransformed3x3(turret, (barrelTransform.getTransform() * GetGlobalTransform()).data, 0.f, 0.f, 0.5f, 0.8f);
}