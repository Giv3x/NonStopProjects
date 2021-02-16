#include "GuiRenderer.h"



GuiRenderer::GuiRenderer() {
	guiShader.init(2);
}

void GuiRenderer::render() {
	guiShader.bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (std::list<GUI>::iterator it = guis.begin(); it != guis.end(); it++) {
		initTexturedModel(*it);

		initInstance(*it);
		it->getTexturedModel().getModel().drawArrays();

		unbindTexturedModel(*it);
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	guiShader.unbind();
}

void GuiRenderer::initTexturedModel(GUI& gui) {
	glBindVertexArray(gui.getTexturedModel().getModel().getVAO());
	glEnableVertexAttribArray(0);
	gui.bindTextures();
}

void GuiRenderer::unbindTexturedModel(GUI& gui) {
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	gui.unbindTextures();
}

void GuiRenderer::initInstance(GUI& gui) {
	guiShader.loadTransform(gui.getTransform().getModelMatrix());
}


void GuiRenderer::addGui(GUI& gui) {
	guis.push_back(gui);
}
