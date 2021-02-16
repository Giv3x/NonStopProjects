#pragma once
#include "Texture.h"
#include "Mesh.h"

class TexturedModel
{
public:
	TexturedModel(Mesh m) : model(m) {};
	TexturedModel(Mesh m, Texture t, glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity, bool fakeLighting = false);
	TexturedModel() {}
	~TexturedModel();

	Texture& getTexture(int unit) { return textures[unit]; }
	std::vector<Texture>& getTextures() { return textures; }
	Mesh& getModel() { return model; }
	float* getDiffuseReflectivity() { return &diffuseReflectivity[0]; }
	float* getSpecularReflectivity() { return &specularReflectivity[0]; }
	float* getAmbientReflectivity() { return &ambientReflectivity[0]; }
	bool& getFakeLighting() { return fakeLighting; }

	void addTexture(Texture& texture) { textures.push_back(texture); }
	void setDiffuseReflectivity(const glm::vec3& dReflectivity) { diffuseReflectivity = dReflectivity; }
	void setSpecularReflectivity(const glm::vec3& sReflectivity) { diffuseReflectivity = sReflectivity; }
	void setAmbientReflectivity(const glm::vec3& aReflectivity) { diffuseReflectivity = aReflectivity; }
	void setMesh(Mesh& mesh) { this->model = mesh; }

	void bindTextures();
	void bindTexture(int index, int unit);
	void unbindTextures();
	void clean();

	bool operator<(TexturedModel* pointer) { return this < pointer; }
	bool operator>(TexturedModel* pointer) { return this > pointer; }
	bool operator==(TexturedModel* pointer) { return this == pointer; }

private:
	std::vector<Texture> textures;
	Mesh model;
	bool fakeLighting;
	glm::vec3 diffuseReflectivity;
	glm::vec3 specularReflectivity;
	glm::vec3 ambientReflectivity;
};

