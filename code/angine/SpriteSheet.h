#pragma once

class SpriteSheet
{
public:
	 SpriteSheet();
	 ~SpriteSheet();

	 unsigned int getID() { return textureID; }

protected:
	unsigned int textureID;
};