#include "TerrainTexturePack.h"



TerrainTexturePack::TerrainTexturePack() {
	backgroundTexture.initTex2D("res/textures/grass.png", false);
	rTexture.initTex2D("res/textures/mud.png", false);
	gTexture.initTex2D("res/textures/grassFlowers.png", false);
	bTexture.initTex2D("res/textures/path.png", false);
}


TerrainTexturePack::~TerrainTexturePack() {
}
