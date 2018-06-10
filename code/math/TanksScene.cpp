#include "TanksScene.h"
#include "GameObject.h"
#include "vec2.h"
#include "Texture.h"
#include "Player.h"
#include "Tree.h"
#include "Game1.h"

namespace LML
{
	TanksScene::TanksScene()
	{
		sceneRoot->transform.translateBy(LML::vec2(616, 439));

		backgroundTexture = new openGL::Texture("./Images/Racing Pack/PNG/Tiles/Dirt Road/road_dirt21.png");

		float width = backgroundTexture->GetDimensions().x;
		float height = backgroundTexture->GetDimensions().y;

		float numberOn2 = 16.f / 2.f;
		for(float i = -numberOn2; i <= numberOn2; i++)
		{
			for(float j = -numberOn2; j <= numberOn2; j++)
			{
				GameObject * go = new GameObject();
				go->texture = backgroundTexture;
				LML::vec2 translation(i * width, j * height);
				go->transform.setTranslation(translation);
				sceneRoot->AddChild(go);
			}
		}

		sceneRoot->AddChild(new Player());

		sceneRoot->AddChild(new Tree());
	}

	TanksScene::~TanksScene()
	{
		delete backgroundTexture;
	}

	void TanksScene::Update(float a_deltaTime)
	{
		BaseScene::Update(a_deltaTime);
	}

	void TanksScene::Render()
	{
		BaseScene::Render();
	}
}