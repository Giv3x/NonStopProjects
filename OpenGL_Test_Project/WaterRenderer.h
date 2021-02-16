#pragma once
#include "WaterShader.h"
#include "Camera.h"
#include "water.h"

#include <map>
#include <list>
class WaterRenderer
{
public:
	WaterRenderer();
	~WaterRenderer() {};

	void render(Camera& camera, Light& light);
	void addWater(Water& waterTile);

private:
	void initTexturedModel(Water& terrain, WaterShader& shader);
	void initInstance(Water& water, WaterShader& shader);
	void unbindTexturedModel(Water& terrain);

	WaterShader waterShader;
	std::list<Water> water;

	float moveFactor;
	const float WAVE_SPEED = 0.0007f;
};

