#pragma once
#include "BaseScene.h"

namespace openGL
{
	class Texture;
}

namespace LML
{
	class TanksScene : public BaseScene
	{
	public:
		TanksScene();
		virtual ~TanksScene();

		virtual void Update(float deltaTime);
		virtual void Render();

		openGL::Texture * backgroundTexture;
	};
}