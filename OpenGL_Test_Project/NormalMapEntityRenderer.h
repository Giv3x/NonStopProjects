#pragma once
#include "NormalMapSHader.h"
#include "Camera.h"
#include "Entity.h"

#include <map>
#include <list>

class NormalMapEntityRenderer
{
public:
	NormalMapEntityRenderer() {}
	~NormalMapEntityRenderer() {}

	void init();
	void render(std::map < TexturedModel*, std::list<Entity> >& entities, NormalMapShader& shader);

private:
	void initTexturedModel(TexturedModel* texturedModel, NormalMapShader& shader);
	void initInstance(Entity& entity, NormalMapShader& shader);
	void unbindTexturedModel(TexturedModel* texturedModel);
};

