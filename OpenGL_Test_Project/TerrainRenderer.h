#pragma once
#include "TerrainShader.h"
#include "Camera.h"
#include "Terrain.h"

#include <map>
#include <list>

class TerrainRenderer
{
public:
	TerrainRenderer() {};
	~TerrainRenderer() {};

	void render(std::list<Terrain>& terrain, TerrainShader& shader);

private:
	void initTexturedModel(Terrain& terrain, TerrainShader& shader);
	void initInstance(Terrain& terrain, TerrainShader& shader);
	void unbindTexturedModel(Terrain& terrain);
};

