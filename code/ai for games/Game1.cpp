#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "IEntity.h"
#include "Player.h"
#include "vec2.h"
#include <time.h>
#include <iostream>

SpriteBatch * ::IEntity::m_spriteBatch = nullptr;

namespace AI_GAMES
{

	Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) 
		: AIE_GL::Application(windowWidth, windowHeight, fullscreen, title)
	{
		m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
		IEntity::m_spriteBatch = m_spritebatch;

		//SetVSync(false);

		crate = new Texture("./Images/box0_256.png");

		//Player::input = GetInput();

		Player *player = new Player();
		//player->m_transform.setTranslation(Vector2(windowWidth / 2.f, windowHeight / 2.f));
		player->m_texture = crate;

		entities.push_back(player);

		graph.LoadTexture();

		int scale = 50;

		int xOffset = scale / 1;
		int yOffset = scale / 1;

		//int iMax = ((GetWindowWidth()  - (xOffset)) / scale);
		//int jMax = ((GetWindowHeight() - (yOffset)) / scale);
		//
		//vector<vector<Node *>> nodes;
		//
		//for(int i = 0; i < iMax; i++) 
		//{
		//	nodes.push_back(vector<Node *>());
		//	for(int j = 0; j < jMax; j++) 
		//	{
		//		nodes[i].push_back(new Node(Vector2((float)(i * scale + xOffset), (float)(j * scale + yOffset))));
		//		graph.AddNode(*nodes[i][j]);
		//	}
		//}

		//for(int i = 0; i < iMax; i++) {
		//	for(int j = 0; j < jMax; j++) {
		//		// Edge to the left
		//		if (i > 0) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i - 1][j]);
		//		}
		//		// Edge to the right
		//		if (i < iMax - 1) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i + 1][j]);	
		//		}
		//		// Edge to the top
		//		if (j > 0) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i][j - 1]);
		//		}
		//		// Edge to the bottom
		//		if (j < jMax - 1) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i][j + 1]);
		//		}
		//		// Edge to the top left
		//		if (i > 0 && j > 0) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i - 1][j - 1]);
		//		}
		//		// Edge to the top right
		//		if (i < iMax - 1 && j > 0) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i + 1][j - 1]);
		//		}
		//		// Edge to the bottom left
		//		if (i > 0 && j < jMax - 1) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i - 1][j + 1]);
		//		}
		//		// Edge to the bottom right
		//		if (i < iMax - 1 && j < jMax - 1) {
		//			graph.ConnectNodes(*nodes[i][j], *nodes[i + 1][j + 1]);
		//		}
		//	}
		//}
		//
		//srand((unsigned int)time(NULL));
		//
		//for(auto iter = graph.nodes.begin(); iter != graph.nodes.end(); ++iter)
		//{
		//	for(auto jiter = (*iter)->edges.begin(); jiter != (*iter)->edges.end(); ++jiter)
		//	{
		//		if(rand() % 100 >= 25)
		//		{
		//			delete (*jiter);
		//			jiter = (*iter)->edges.erase(jiter);
		//
		//			if(jiter == (*iter)->edges.end())
		//			{
		//				break;
		//			}
		//		}
		//	}
		//	(*iter)->edges.shrink_to_fit();
		//}
		//
		//int i1 = rand() % nodes.size();
		//int j1 = rand() % nodes[0].size();
		//
		//int i2 = rand() % nodes.size();
		//int j2 = rand() % nodes[0].size();
		//
		//graph.InitAStar(*nodes[i1][j1], *nodes[i2][j2], path);
		//
		//i1 = rand() % nodes.size();
		//j1 = rand() % nodes[0].size();
		//
		//i2 = rand() % nodes.size();
		//j2 = rand() % nodes[0].size();
		//
		//graph.InitAStar(*nodes[i1][j1], *nodes[i2][j2], path2);
		//
		//calculateTimer = 0.f;
	}

	Game1::~Game1()
	{
		delete crate;

		std::vector<IEntity*>::iterator iter;
		for(iter = entities.begin(); iter != entities.end(); iter++)
		{
			delete (*iter);
			iter = entities.erase(iter);
			if(iter == entities.end())
				break;
		}

		SpriteBatch::Factory::Destroy(m_spritebatch);
	}


	void Game1::Update(float deltaTime)
	{
		static float timer = 1.f;

		static int count = 0;
		count++;

		timer -= deltaTime;

		if(timer <= 0.f)
		{
			timer = 1.f;
			//std::cout << GetFPS() << std::endl;
		}

		if(Input::GetSingleton()->WasKeyPressed(GLFW_KEY_ESCAPE))
		{
			//Quit();
		}

		if(calculateTimer > 0.f)
			calculateTimer -= deltaTime;

		static bool calculateAStar = true;
		static bool calculateAStar2 = true;

		if(!calculateAStar)// && calculateTimer <= 0.f && Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
		{
			calculateAStar = true;


			int i1 = rand() % graph.nodes.size();
			int i2 = rand() % graph.nodes.size();

			graph.InitAStar(*graph.nodes[i1], *graph.nodes[i2], path);
		}
		/*if(!calculateAStar2)
		{
			calculateAStar2 = true;

			int i1 = rand() % graph.nodes.size();
			int i2 = rand() % graph.nodes.size();

			graph.InitAStar(*graph.nodes[i1], *graph.nodes[i2], path2);
		}*/

		if(calculateAStar)// && calculateTimer <= 0.f)
		{
			//if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_SPACE))
			{
				if(graph.AStar(path) != PATHRESULTS::STILL_CALCULATING)
				{
					calculateAStar = false;
					calculateTimer = 2.5f;
				}
				else
				{
					calculateTimer = 0.5f;
				}
			}
		}

		//if(calculateAStar2)
		//{
		//	if(/*Input::GetSingleton()->IsKeyDown(GLFW_KEY_ENTER) &&*/
		//		graph.AStar(path2) == PATHRESULTS::PATH_FOUND)
		//	{
		//		calculateAStar2 = false;
		//	}
		//}

		if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_Z))
		{
			calculateAStar = true;
			int i1 = rand() % graph.nodes.size();
			int i2 = rand() % graph.nodes.size();

			graph.InitAStar(*graph.nodes[i1], *graph.nodes[i2], path);
		}

		/*if(Input::GetSingleton()->IsKeyDown(GLFW_KEY_X))
		{
			calculateAStar2 = true;
			int i1 = rand() % graph.nodes.size();
			int i2 = rand() % graph.nodes.size();

			graph.InitAStar(*graph.nodes[i1], *graph.nodes[i2], path2);
		}*/

		std::vector<IEntity*>::iterator iter;
		for(iter = entities.begin(); iter != entities.end(); iter++)
		{
			(*iter)->Update(deltaTime);
		}
	}

	void Game1::Draw()
	{
		// clear the back buffer
		//ClearScreen();

		m_spritebatch->Begin();

		graph.DrawNodes(*m_spritebatch);

		graph.DrawPath(*m_spritebatch, path);

		//graph.DrawPath(*m_spritebatch, path2);

		// Draw all the entities in the game
		/*std::vector<IEntity*>::iterator iter;
		for(iter = entities.begin(); iter != entities.end(); iter++)
		{
			(*iter)->Draw();
		}*/

		m_spritebatch->End();

	}
}