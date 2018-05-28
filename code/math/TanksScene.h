#pragma once
#include "BaseScene.h"

class Texture;

namespace LML
{
	class TanksScene : public BaseScene
	{
	public:
		TanksScene();
		virtual ~TanksScene();

		virtual void Update(float deltaTime);
		virtual void Render();

		Texture * backgroundTexture;
	};
}