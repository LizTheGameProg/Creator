#pragma once


namespace LML
{
	class GameObject;
	class BaseScene
	{
	public:
		BaseScene();
		virtual ~BaseScene();

		virtual void Update(float deltaTime);
		virtual void Render();

		GameObject * sceneRoot;
	};
}