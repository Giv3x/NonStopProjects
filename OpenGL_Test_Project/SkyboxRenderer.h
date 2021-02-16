#pragma once
#include "Skybox.h"
#include "SkyboxShader.h"

class SkyboxRenderer
{
public:
	SkyboxRenderer() {}
	~SkyboxRenderer() {}

	void render(Skybox& skybox, SkyboxShader& shader);

private:
	void initTexturedModel(Skybox& skybox, SkyboxShader& shader);
	void initInstance(Skybox& skybox, SkyboxShader& shader);
	void unbindTexturedModel(Skybox& skybox);
};

