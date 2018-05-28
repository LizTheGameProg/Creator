#pragma once

class Application {
public:

	Application() {}
	virtual ~Application() {}

	virtual bool startup() = 0;
	virtual void shutdown() = 0;

	virtual bool update(float deltaTime) = 0;
	virtual void draw() = 0;

};