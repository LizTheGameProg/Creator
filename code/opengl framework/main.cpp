/*// Needed to output memory leaks to the output window
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Copy this into any file that might be generating memory leaks
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#include "Application.h"

int main()
{
	{
		Application * app = new Application();

		if(app->StartUp() == GL_TRUE)
		{
			app->Run();
			app->ShutDown();
		}

		delete app;
	}

	// Output memory leaks to the output window
	_CrtDumpMemoryLeaks();

	return 0;
}*/