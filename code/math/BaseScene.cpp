#include "BaseScene.h"
#include "GameObject.h"

namespace LML
{
	BaseScene::BaseScene()
	{
		sceneRoot = new GameObject();
	}

	BaseScene::~BaseScene()
	{
		delete sceneRoot;
	}

	void BaseScene::Update(float a_deltaTime)
	{
		sceneRoot->Update(a_deltaTime);
	}

	void BaseScene::Render()
	{
		sceneRoot->Render();
	}
}