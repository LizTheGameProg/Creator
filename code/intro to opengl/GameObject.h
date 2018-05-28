#pragma once
#include "Transform3D.h"
namespace INTRO_OPENGL
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

	protected:
		Transform3D		m_transform;
		GameObject *	m_parent;

	private:

	};
}