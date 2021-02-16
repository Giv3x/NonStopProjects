#include "MasterRenderer.h"



MasterRenderer::MasterRenderer() : skybox(Skybox("res/add_ons/box.ao"))/*: basicShader(BasicShader())*/ {
	basicShader.init(2);
	skyboxShader.init(2);
	normalMapShader.init(2);
	normalMapShader.bind();
	normalMapShader.loadTextures();
	normalMapShader.unbind();
	
	terrainShader.init(2);
	terrainShader.bind();
	terrainShader.loadTextures();
	terrainShader.unbind();
	enableCulling();
}


MasterRenderer::~MasterRenderer() {
}

void MasterRenderer::addEntity(TexturedModel* texturedModel, Entity& entity) {
	entities[texturedModel].push_back(entity);
}

void MasterRenderer::addNormalMapEntity(TexturedModel* texturedModel, Entity& entity) {
	normalEntities[texturedModel].push_back(entity);
}

void MasterRenderer::addEntities(TexturedModel* texturedModel, std::list<Entity>& entities) {
	this->entities[texturedModel] = entities;
}

void MasterRenderer::addNormalMapEntities(TexturedModel* texturedModel, std::list<Entity>& entities) {
	this->normalEntities[texturedModel] = entities;
}

void MasterRenderer::addTerrain(Terrain& terrain) {
	terrains.push_back(terrain);
}

void MasterRenderer::render(Camera& camera, Light& light, SpotLight& spotLight, const glm::vec4& clipDistance) {
	renderer.init();
	
	basicShader.bind();
	basicShader.loadProjection(camera.getProjection());
	basicShader.loadLightInfo(light); //entity
	basicShader.loadSpotLightInfo(spotLight);
	basicShader.loadFogColor(glm::vec3(0.9f, 0.9f, 0.9f));
	basicShader.loadView(camera.getView());
	basicShader.loadClipDistance(clipDistance);
	renderer.render(entities, basicShader);
	basicShader.unbind();

	normalMapShader.bind();
	normalMapShader.loadProjection(camera.getProjection());
	normalMapShader.loadLightInfo(light); //entity
	normalMapShader.loadSpotLightInfo(spotLight);
	normalMapShader.loadFogColor(glm::vec3(0.9f, 0.9f, 0.9f));
	normalMapShader.loadView(camera.getView());
	normalMapShader.loadCameraPos(camera.getPostion());
	basicShader.loadClipDistance(clipDistance);
	normalRenderer.render(normalEntities, normalMapShader);
	normalMapShader.unbind();

	terrainShader.bind();
	terrainShader.loadProjection(camera.getProjection() * camera.getView());
	terrainShader.loadLightInfo(light); //entity
	terrainShader.loadSpotLightInfo(spotLight);
	terrainShader.loadFogColor(glm::vec3(0.9f, 0.9f, 0.9f));
	terrainShader.loadView(camera.getView());
	basicShader.loadClipDistance(clipDistance);
	terrainRenderer.render(terrains, terrainShader);
	terrainShader.unbind();
	
	this->disableCulling();
	skyboxShader.bind();
	skyboxShader.loadProjection(camera.getProjection());
	skyboxShader.loadFogColor(glm::vec3(0.9f, 0.9f, 0.9f));
	skyboxShader.loadView(camera.getView());
	skyboxRenderer.render(skybox, skyboxShader);
	skyboxShader.unbind();
	this->enableCulling();
}

void MasterRenderer::render(Camera& camera, Light& light) {
	renderer.init();

	basicShader.bind();
	basicShader.loadProjection(camera.getProjection());
	basicShader.loadLightInfo(light); //entity
	basicShader.loadFogColor(glm::vec3(0.7f, 0.7f, 0.7f));
	basicShader.loadView(camera.getView());
	renderer.render(entities, basicShader);
	basicShader.unbind();

	terrainShader.bind();
	terrainShader.loadProjection(camera.getProjection() * camera.getView());
	terrainShader.loadLightInfo(light); //entity
	terrainShader.loadFogColor(glm::vec3(0.7f, 0.7f, 0.7f));
	terrainShader.loadView(camera.getView());
	terrainRenderer.render(terrains, terrainShader);
	terrainShader.unbind();

	cleanEntities();
}

void checkUniforms(GLuint program) {
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}
}

void MasterRenderer::enableCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::cleanEntities() {
	entities.clear();
	normalEntities.clear();
}