#include "basegame.h"


#include "string"
#include "vector"

using namespace std;

#include "world.h"
World world;

#include "systemHandler.h"

using namespace GAME_ENGINE;

GAME_ENGINE::SystemHandler systemHandler;

double msPerUpdate = 1.0/60.0;

void handleStartUpArgs(int argc, char** argv)
{
	// setup the arguements into a dynamic array of strings
	vector<string> args = vector<string>();
	for(int i = 0; i < argc; i++)
	{
		args.push_back(string(argv[i]));
	}
	
	
}

BaseGame::BaseGame(int argc, char** argv)
	: runGame(true)
{
	handleStartUpArgs(argc, argv);
}

BaseGame::~BaseGame()
{
	
}

bool BaseGame::Init()
{
	bool systemInitialized = systemHandler.Initialize();
	if(systemInitialized)
	{
		OnInit();
	}
	
	return systemInitialized;
}

void BaseGame::Load()
{
	OnLoad();
}

void BaseGame::Run()
{
	double current = 0.0;
	double elapsed = 0.0;
	unsigned int updateIterations = 0;
	const unsigned int maxUpdateIterations = 5;
	double lag = 0.0;
	double previous = systemHandler.GetCurrentTime();
	while(runGame && !systemHandler.ShouldExit())
	{
		current = systemHandler.GetCurrentTime();
		elapsed = current - previous;
		previous = current;
		lag += elapsed;
		
		systemHandler.ProcessEvents();
		
		updateIterations = 0;
		while(lag >= msPerUpdate && updateIterations < maxUpdateIterations)
		{
			Update(msPerUpdate);
			lag -= msPerUpdate;
			updateIterations++;
		}
		Render(lag / msPerUpdate);
	}
}

void BaseGame::DeLoad()
{
	OnDeLoad();
}

void BaseGame::DeInit()
{
	OnDeInit();
	systemHandler.DeInitialize();
}

int BaseGame::Exit()
{
	return 0;
}

const World & BaseGame::GetWorld()
{
	return world;
}

World & BaseGame::AccessWorld()
{
	return world;
}

const GAME_ENGINE::SystemHandler & BaseGame::GetSystemHandler()
{
	return systemHandler;
}

GAME_ENGINE::SystemHandler & BaseGame::AccessSystemHandler()
{
	return systemHandler;
}

void BaseGame::PreUpdate()
{
	
}

void BaseGame::Update(const double msPerUpdate)
{
	PreUpdate();
	OnUpdate();
	PostUpdate();
}

void BaseGame::PostUpdate()
{
	
}

void BaseGame::PreRender()
{
	
}

void BaseGame::Render(const double extraTime)
{
	PreRender();
	OnRender();
	PostRender();
}

void BaseGame::PostRender()
{
	
}