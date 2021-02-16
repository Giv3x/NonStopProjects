#include "WaterRenderer.h"



WaterRenderer::WaterRenderer() {
	waterShader.init(2);
	waterShader.bind();
	waterShader.connectTextures();
	waterShader.unbind();
	moveFactor = 0;
}

void WaterRenderer::render(Camera& camera, Light& light) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	moveFactor += WAVE_SPEED;
	if(moveFactor > 1)
		moveFactor -= 1;
	waterShader.bind();
	waterShader.loadProjection(camera.getProjection());
	waterShader.loadLightInfo(light); //entity
	//waterShader.loadSpotLightInfo(spotLight);
	waterShader.loadFogColor(glm::vec3(0.529f, 0.808f, 0.922f));
	waterShader.loadView(camera.getView());
	waterShader.loadCameraPos(camera.getPostion());
	waterShader.loadMoveFactor(moveFactor);
	for (std::list<Water>::iterator it = water.begin(); it != water.end(); it++) {
		initTexturedModel(*it, waterShader);

		initInstance(*it, waterShader);
		it->getTexturedModel().getModel().draw();

		unbindTexturedModel(*it);
	}
	waterShader.unbind();
	glDisable(GL_BLEND);
}

void WaterRenderer::initTexturedModel(Water& water, WaterShader& shader) {
	glBindVertexArray(water.getTexturedModel().getModel().getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	shader.loadMaterialInfo(&water.getTexturedModel());
	water.bindTextures();
}

void WaterRenderer::unbindTexturedModel(Water& water) {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	water.unbindTextures();
}

void WaterRenderer::initInstance(Water& water, WaterShader& shader) {
	shader.loadTransform(water.getTransform().getModelMatrix());
}


void WaterRenderer::addWater(Water& waterTile) {
	water.push_back(waterTile);
}
