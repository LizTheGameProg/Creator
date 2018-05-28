#pragma once

namespace ANGINE
{
	class BaseScene
	{
	public:
		BaseScene();
		~BaseScene();

		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;

	protected:

	};
}