#pragma once
#include <GL\glew.h>

#include "Texture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack();
	~TerrainTexturePack();

	Texture& getBgTexture() { return backgroundTexture; }
	Texture& getRTexture() { return rTexture; }
	Texture& getGTexture() { return gTexture; }
	Texture& getBTexture() { return bTexture; }

private:
	Texture backgroundTexture;
	Texture rTexture;
	Texture gTexture;
	Texture bTexture;
};

