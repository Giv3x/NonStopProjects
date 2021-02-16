#include "TerrainRenderer.h"



void TerrainRenderer::render(std::list<Terrain>& terrain, TerrainShader& shader) {
	for (std::list<Terrain>::iterator it = terrain.begin(); it != terrain.end(); it++) {
		initTexturedModel(*it, shader);
		
		initInstance(*it, shader);
		it->getMesh().draw();
		
		unbindTexturedModel(*it);
	}
}

void TerrainRenderer::initTexturedModel(Terrain& terrain, TerrainShader& shader) {
	glBindVertexArray(terrain.getMesh().getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	shader.loadMaterialInfo(&terrain);
	terrain.bindTextures();
}

void TerrainRenderer::unbindTexturedModel(Terrain& terrain) {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	terrain.getTexture().unbind(0);
}

void TerrainRenderer::initInstance(Terrain& terrain, TerrainShader& shader) {
	shader.loadTransform(terrain.getTransform().getModelMatrix());
}