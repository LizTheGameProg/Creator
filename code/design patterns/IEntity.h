#pragma once

#include "SpriteBatch.h"

#include "transform2D.h"

class IEntity
{
public:
	IEntity() : m_texture(nullptr)/*, m_transform(Transform2D())*/	{}
	virtual ~IEntity() {}

	virtual void Update(float deltaTime) = 0;
	virtual void Draw()
	{
		//m_spriteBatch->DrawSpriteTransformed3x3(m_texture, m_transform.getTransform().data);
	}

	static SpriteBatch * m_spriteBatch;
	openGL::Texture * m_texture;
	//Transform2D m_transform;
};

