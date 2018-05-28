#pragma once

class IApplication
{
public:
	IApplication() {}
	virtual ~IApplication() = 0;

	virtual bool startUp() = 0;
	virtual void shutDown() = 0;
	virtual bool update() = 0;
	virtual void render() = 0;
};