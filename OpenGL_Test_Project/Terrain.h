#pragma once
#include <glm\glm.hpp>
#include <vector>

#include "Texture.h"
#include "Loader.h"
#include "utility.h"
#include "Transform.h"
#include "TerrainTexturePack.h"
#include "Loader.h"

class Terrain
{
public:
	Terrain(const float& x, const float& z, Texture& texture, const glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity);
	~Terrain();

	Mesh& getMesh() { return mesh; }
	Texture& getTexture() { return blendMap; }
	Transform& getTransform() { return transform; }
	float getHeight(float& worldX, float& worldZ);
	float* getAmbientReflectivity() { return &ambientReflectivity[0]; }
	float* getDiffuseReflectivity() { return &diffuseReflectivity[0]; }
	float* getSpecularReflectivity() { return &specularReflectivity[0]; }

	void bindTextures();

private:
	void generateTerrain(const float& x, const float& z);
	float getHeight(int& x, int& y, int& width, int& height, unsigned char*);
	float getBarrycentricHeight(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& p);
	glm::vec3 calculateNormals(int& x, int& y);

	Transform transform;
	Texture blendMap;
	TerrainTexturePack terrainTexture;
	Mesh mesh;
	std::vector<std::vector<float> > heights;
	glm::vec3 diffuseReflectivity;
	glm::vec3 specularReflectivity;
	glm::vec3 ambientReflectivity;

	int x;
	int z;
	const int SIZE = 1600;
	const int VERTEX_CNT = 512;
	const int MAX_HEIGHT = 50;
	const int MAX_PIXEL_COLOR = 256 * 256 * 256;
};

