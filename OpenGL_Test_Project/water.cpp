#include "water.h"

#include "utility.h"
#include "OBJloader.h"

Water::Water(const glm::vec3& position, const glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity)
	: pos(position) {
	int verticesCNT = VERTEX_CNT * VERTEX_CNT;
	std::vector<Vertex> vertices(verticesCNT);
	std::vector<int> indices(6 * (VERTEX_CNT - 1)*(VERTEX_CNT - 1));

	generateQuad(pos, SIZE, VERTEX_CNT, vertices, indices);

	Mesh mesh = Loader::loadMesh(vertices, indices);

	this->texturedModel.setDiffuseReflectivity(diffuseReflectivity);
	this->texturedModel.setSpecularReflectivity(specularReflectivity);
	this->texturedModel.setAmbientReflectivity(ambientReflectivity);
	this->texturedModel.setMesh(mesh);
}

void Water::bindTextures() {
	texturedModel.bindTextures();
}

void Water::unbindTextures() {
	texturedModel.unbindTextures();
}

void Water::addTextures(WaterFrameBuffer& fbo, Texture& dudv, Texture& normalMap) {
	texturedModel.addTexture(fbo.getReflectionTexture());
	texturedModel.addTexture(fbo.getRefractionTexture());
	texturedModel.addTexture(fbo.getRefractionDepthTexture());
	texturedModel.addTexture(dudv);
	texturedModel.addTexture(normalMap);
}
