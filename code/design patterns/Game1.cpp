#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "IEntity.h"
#include "Player.h"
#include "TextureManager.h"
#include "vec2.h"

SpriteBatch * IEntity::m_spriteBatch = nullptr;
namespace DESGIN_PATTERNS
{
	Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title)
		: AIE_GL::Application(windowWidth, windowHeight, fullscreen, title)
	{
		m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

		// Assign static pointers
		IEntity::m_spriteBatch = m_spritebatch;
		//Player::input = GetInput();

		// Create the texture manager
		TextureManager::Create();
		// use the texture manager to load all the textures that we need for our game
		TextureManager::Get()->LoadTexture("./Images/playerTexture.png");
		TextureManager::Get()->LoadTexture("./Images/bulletTexture.png");

		// Make the player
		Player * player = new Player();
		//player->m_transform.setTranslation(Vector2(windowWidth / 2.f, windowHeight / 2.f));
		player->m_texture = TextureManager::Get()->GetTexture("./Images/playerTexture.png");
		// Add the player to the entities list
		gameObjects.push_back(player);

		m_arialFont = new Font("./Fonts/arial_20px.fnt");
	}

	Game1::~Game1()
	{
		delete m_arialFont;

		//delete crate;
		TextureManager::Destroy();

		for(auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		{
			if(!dynamic_cast<Bullet*>(*iter))
			{
				delete (*iter);
				iter = gameObjects.erase(iter);
				if(iter == gameObjects.end())
					break;
			}
		}

		SpriteBatch::Factory::Destroy(m_spritebatch);
	}

	void Game1::Update(float deltaTime)
	{
		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_ESCAPE))
		{
			//Quit();
		}

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
		{
			Bullet * temp = bulletPool.Request();
			if(temp)
			{
				temp->m_texture = TextureManager::Get()->GetTexture("./Images/bulletTexture.png");
				//temp->m_velocity = Vector2((rand() % 100) - 50, (rand() % 100) - 50);
				//temp->m_transform.setTranslation(Vector2(GetInput()->GetMouseX(), GetInput()->GetMouseY()));
				gameObjects.push_back(temp);
			}
		}

		for(auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		{
			(*iter)->Update(deltaTime);
		}

		//for(auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		//{
		//	Bullet * bullet = dynamic_cast<Bullet*>(*iter);
		//	if(bullet)
		//	{
		//		if((*iter)->m_transform.getTranslation().x < 0 ||
		//			(*iter)->m_transform.getTranslation().x > GetWindowWidth() ||
		//			(*iter)->m_transform.getTranslation().y < 0 ||
		//			(*iter)->m_transform.getTranslation().y > GetWindowHeight())
		//		{
		//			bulletPool.Release(bullet);
		//			iter = gameObjects.erase(iter);
		//			if(iter == gameObjects.end())
		//			{
		//				break;
		//			}
		//		}
		//	}
		//}
	}

	void Game1::Draw()
	{
		// clear the back buffer
		//ClearScreen();

		m_spritebatch->Begin();

		for(auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		{
			(*iter)->Draw();
		}

		m_spritebatch->DrawString(m_arialFont, "Hello World", 0.f, 0.f);

		m_spritebatch->End();

	}
}