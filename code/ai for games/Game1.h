
/*-----------------------------------------------------------------------------
Author:			Elizabeth Rowlands
Description:	IEntity Demo
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "../aie gl/Application.h"
#include <vector>
#include "Graph.h"

class SpriteBatch;
class IEntity;
class Texture;
namespace AI_GAMES
{
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

		std::vector<IEntity *> entities;

		Texture * crate;

		Graph graph;

		Path path;
		Path path2;

		float calculateTimer;

	private:
	};
}
#endif