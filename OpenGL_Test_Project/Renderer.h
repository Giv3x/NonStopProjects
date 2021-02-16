#pragma once
#include "BasicShader.h"
#include "Camera.h"
#include "Entity.h"

#include <map>
#include <list>

class Renderer
{
public:
	Renderer() {};
	~Renderer() {};

	void init();
	void render(std::map < TexturedModel*, std::list<Entity> >& entities, BasicShader& shader);

private:
	void initTexturedModel(TexturedModel* texturedModel, BasicShader& shader);
	void initInstance(Entity& entity, BasicShader& shader);
	void unbindTexturedModel(TexturedModel* texturedModel);
};

