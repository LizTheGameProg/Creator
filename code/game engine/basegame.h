#pragma once

class World;

namespace GAME_ENGINE
{
	class SystemHandler;
}

class BaseGame
{
	BaseGame() {}
public:
	BaseGame(int argc, char** argv);
	virtual ~BaseGame();
	
	bool Init();
	void Load();
	void Run();
	void DeLoad();
	void DeInit();
	int Exit();
	
protected:
	virtual void OnInit() = 0;
	virtual void OnLoad() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDeLoad() = 0;
	virtual void OnDeInit() = 0;
	
	const World & GetWorld();
	World & AccessWorld();
	
	const GAME_ENGINE::SystemHandler & GetSystemHandler();
	GAME_ENGINE::SystemHandler & AccessSystemHandler();
	
private:
	void PreUpdate();
	void Update(const double deltaTime);
	void PostUpdate();
	
	void PreRender();
	void Render(const double extraTime);
	void PostRender();
	
	bool runGame;
};