#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "common.h"
#include "GameObject.h"
#include "vec2.h"
#include "TanksScene.h"
#include "BaseCollider.h"
#include "CollisionHandler.h"

namespace LML
{
	Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
	{
		m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

		LML::GameObject::SetSpriteBatch(m_spritebatch);
		BaseCollider::collisionHandler = new CollisionHandler();

		scene = new TanksScene();
	}

	Game1::~Game1()
	{
		delete scene;

		delete BaseCollider::collisionHandler;

		SpriteBatch::Factory::Destroy(m_spritebatch);
	}

	void Game1::Update(float deltaTime)
	{
		if(GetInput()->IsKeyDown(GLFW_KEY_ESCAPE))
			Quit();

		if(GetInput()->WasKeyPressed(GLFW_KEY_F1)) // turn debug off and on
		{
			// if spritebatch is not null, make it null, if its already null, assign m_spritebatch to it.
			BaseCollider::spriteBatch ? nullptr : BaseCollider::spriteBatch = m_spritebatch;
		}

		scene->Update(deltaTime);

		// Number of time to check for collisions before continuing the game loop
		static int physicsIterations = 7;
		int i = 0;

		while(i < physicsIterations && BaseCollider::collisionHandler->DetectCollisions())
		{
			BaseCollider::collisionHandler->ResolveCollisions();
			i++;
		}
	}

	void Game1::Draw()
	{
		ClearScreen();

		m_spritebatch->Begin();

		scene->Render();

		m_spritebatch->End();
	}
}