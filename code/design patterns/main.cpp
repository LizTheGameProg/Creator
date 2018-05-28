/*#include "Game1.h"

#ifdef _DEBUG
	#define _CRTCBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>

	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif

int main(int argc, char **argv)
{
	{
		Game1 *pGame = new Game1(1680, 900, false, "Singleton Demo");
		pGame->RunGame();
		delete pGame;
	}
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
};*/