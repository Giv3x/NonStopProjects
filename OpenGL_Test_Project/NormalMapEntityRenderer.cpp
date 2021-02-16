#include "NormalMapEntityRenderer.h"

#include "MasterRenderer.h"

void NormalMapEntityRenderer::init() {
	glClearColor(0.529f, 0.808f, 0.922f, 1.f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NormalMapEntityRenderer::render(std::map < TexturedModel*, std::list<Entity> >& entities, NormalMapShader& shader) {
	for (std::map<TexturedModel*, std::list<Entity> >::iterator it = entities.begin(); it != entities.end(); it++) {
		initTexturedModel(it->first, shader);

		for (std::list<Entity>::iterator entity = it->second.begin(); entity != it->second.end(); entity++) {
			initInstance(*entity, shader);
			it->first->getModel().draw();
		}

		unbindTexturedModel(it->first);
	}
}

void NormalMapEntityRenderer::initTexturedModel(TexturedModel* texturedModel, NormalMapShader& shader) {
	glBindVertexArray(texturedModel->getModel().getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	if (texturedModel->getTexture(0).hasTransparency())
		MasterRenderer::disableCulling();
	shader.loadMaterialInfo(texturedModel);
	shader.useFakeLighting(texturedModel->getFakeLighting());

	texturedModel->bindTextures();
}

void NormalMapEntityRenderer::unbindTexturedModel(TexturedModel* texturedModel) {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindVertexArray(0);
	texturedModel->unbindTextures();
	if (texturedModel->getTexture(0).hasTransparency())
		MasterRenderer::enableCulling();
}

void NormalMapEntityRenderer::initInstance(Entity& entity, NormalMapShader& shader) {
	shader.loadTransform(entity.getTransform().getModelMatrix());

	//std::cout << entity.getTransform().getPosition().z << std::endl;
}