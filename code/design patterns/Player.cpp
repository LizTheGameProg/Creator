#include "Player.h"
#include "Input.h"
#include "GLFW/glfw3.h"
#include "vec2.h"

Input * Player::input = nullptr;

Player::Player()
{

}

Player::~Player()
{

}

void Player::Update(float a_deltaTime)
{
	float movementSpeed = 320.f * a_deltaTime;

	if(input->IsKeyDown(GLFW_KEY_W))
	{
		//m_transform.translateBy(Vector2(0.f, -movementSpeed));
	}
	if(input->IsKeyDown(GLFW_KEY_S))
	{
		//m_transform.translateBy(Vector2(0.f, movementSpeed));
	}
	if(input->IsKeyDown(GLFW_KEY_A))
	{
		//m_transform.translateBy(Vector2(-movementSpeed, 0.f));
	}
	if(input->IsKeyDown(GLFW_KEY_D))
	{
		//m_transform.translateBy(Vector2(movementSpeed, 0.f));
	}
}