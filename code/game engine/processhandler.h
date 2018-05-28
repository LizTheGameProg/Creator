#pragma once
#include "handler.h"

class ProcessHandler : public GAME_ENGINE::Handler<ProcessHandler>
{
public:
	ProcessHandler();
	~ProcessHandler();
	
	bool OnInitialize();
	void OnDeInitialize();
	
	bool ShouldExit();
	
	void ProcessEvents();
	double GetCurrentTime();
	
private:
	bool shouldExit;
};