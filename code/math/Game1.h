/*-----------------------------------------------------------------------------
Author:			Elizabeth Rowlands
Description:	Project that uses my math library
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "../aie gl/Application.h"

class SpriteBatch;
namespace LML
{	
	//class GameObject;
	class BaseScene;

	class Game1 : public AIE_GL::Application
	{
	public:

		// assets loaded in constructor
		Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);

		// assets destroyed in destructor
		virtual ~Game1();

		// update / draw called each frame automaticly
		virtual void Update(float deltaTime);
		virtual void Draw();

	protected:
		SpriteBatch * m_spritebatch;

	private:
		BaseScene * scene;
	};
}
#endif