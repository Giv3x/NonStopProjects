#pragma once
#include "BasicShader.h"
#include "SkyboxShader.h"
#include "NormalMapShader.h"
#include "WaterShader.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Lights.h"

#include "Renderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "NormalMapEntityRenderer.h"
#include "WaterRenderer.h"

#include <list>
#include <map>

void checkUniforms(GLuint program);

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void addEntity(TexturedModel* texturedModel, Entity& entity);
	void addEntities(TexturedModel* texturedModel, std::list<Entity>& entities);
	void addNormalMapEntity(TexturedModel* texturedModel, Entity& entity);
	void addNormalMapEntities(TexturedModel* texturedModel, std::list<Entity>& entities);
	void addTerrain(Terrain& terrain);

	void render(Camera& camera, Light& light);
	void render(Camera& camera, Light& light, SpotLight& spotLight, const glm::vec4& clipDistance);

	void cleanEntities();

	void static enableCulling();
	void static disableCulling();
private:
	BasicShader basicShader;
	TerrainShader terrainShader;
	SkyboxShader skyboxShader;
	NormalMapShader normalMapShader;

	Renderer renderer;
	TerrainRenderer terrainRenderer;
	SkyboxRenderer skyboxRenderer;
	NormalMapEntityRenderer normalRenderer;

	std::map< TexturedModel*, std::list<Entity> > entities;
	std::map< TexturedModel*, std::list<Entity> > normalEntities;
	std::list<Terrain> terrains;
	Skybox skybox;
};

