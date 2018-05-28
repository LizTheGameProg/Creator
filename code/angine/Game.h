#pragma once

#include "GLFW\glfw3.h"
#include "Window_GLFW.h"
#include "InputHandler.h"

class BaseWindow;
struct WindowInfo;

class  Game
{
	//--------------------------------
	// Singleton Related
	//--------------------------------
public:
	static void Create(WindowInfo & windowInfo);
	static void Destroy();
	inline static Game * Get() { return m_game; }

protected:
	// Call Create instead
	Game(WindowInfo & windowInfo);
	// Singleton instance
	static Game * m_game;

	//--------------------------------
	// Instance Related
	//--------------------------------
	Game() = delete;
public:
	virtual ~Game();
	virtual void Run();

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual float TimeSinceLaunch();
	virtual BaseWindow * GetWindow() { return m_window; }

protected:
	// Time in seconds between frames
	float deltaTime;

	// Angin will shut down if this is true and the escape key is pressed
	bool quitOnEscape;

	// Angin will shut down if this is set to true
	bool quit;

private:
	void PollEvents();
	void UpdateDeltaTime();

	float timeSinceLaunch;

	BaseWindow * m_window;
	InputHandler * inputHandler;

	GLfloat thisTotalTicks;
	GLfloat lastTotalTicks;
};