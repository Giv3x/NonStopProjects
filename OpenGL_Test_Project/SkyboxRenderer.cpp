#include "SkyboxRenderer.h"


void SkyboxRenderer::initTexturedModel(Skybox& skybox, SkyboxShader& shader) {
	glBindVertexArray(skybox.getMesh().getVAO());
	glEnableVertexAttribArray(0);
	skybox.getTexture().bindCubeMap(0);
}

void SkyboxRenderer::initInstance(Skybox& skybox, SkyboxShader& shader) {
	shader.loadTransform(skybox.getTransform().getModelMatrix());
}

void SkyboxRenderer::unbindTexturedModel(Skybox& skybox) {
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	//skybox.getTexture().unbind(0);
}

void SkyboxRenderer::render(Skybox& skybox, SkyboxShader& shader) {
		initTexturedModel(skybox, shader);

		initInstance(skybox, shader);
		skybox.getMesh().drawArrays();

		unbindTexturedModel(skybox);
}
