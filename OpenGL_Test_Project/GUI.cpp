#include "GUI.h"


GUI::GUI(glm::vec3 position, glm::vec3 scale, Texture& texture) : pos(position) {
	float vertices[12] = { -1, -1, 1, 1, -1, 1, 
			1, 1,-1, -1, 1, -1 };
	Mesh mesh = Loader::loadMesh(vertices, 12, 6);
	this->texturedModel.setMesh(mesh);
	transform.setScale(scale);
	transform.setPosition(position);
	texturedModel.addTexture(texture);
}

void GUI::bindTextures() {
	texturedModel.bindTextures();
}

void GUI::unbindTextures() {
	texturedModel.unbindTextures();
}