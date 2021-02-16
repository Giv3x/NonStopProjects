#include "TexturedModel.h"

#include "OBJloader.h"


TexturedModel::TexturedModel(Mesh m, Texture t, glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity, bool fakeLighting) : model(m) {
	textures.push_back(t);
	this->diffuseReflectivity = diffuseReflectivity;
	this->specularReflectivity = specularReflectivity;
	this->ambientReflectivity = ambientReflectivity;
	this->fakeLighting = fakeLighting;
}


TexturedModel::~TexturedModel() {
}

void TexturedModel::bindTextures() {
	for (int i = 0; i < textures.size(); i++) {
		textures[i].bind(i);
	}
}

void TexturedModel::bindTexture(int index, int unit) {
	textures[unit].bind(unit);
}

void TexturedModel::unbindTextures() {

}

void TexturedModel::clean() {
	for (Texture& t : textures) {
		t.clean();
	}
}