#include "Terrain.h"

#include "OBJloader.h"

#include <iostream>

Terrain::Terrain(const float& x, const float& z, Texture& texture, const glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity) 
		: x(x), z(z), blendMap(texture), diffuseReflectivity(diffuseReflectivity), specularReflectivity(specularReflectivity), ambientReflectivity(ambientReflectivity) {
	generateTerrain(x*SIZE, z*SIZE);
}

Terrain::~Terrain() {
}

void Terrain::generateTerrain(const float& x, const float& z) {
	int verticesCNT = VERTEX_CNT * VERTEX_CNT;
	unsigned char* heightMap;
	int heightMapWidth;
	int heightMapHeight;
	int numComponents;

	std::vector<Vertex> vertices(verticesCNT);
	heights.resize(VERTEX_CNT, std::vector<float>(VERTEX_CNT));
	std::vector<int> indices(6 * (VERTEX_CNT - 1)*(VERTEX_CNT - 1));
	heightMap = stbi_load("res/textures/Terrain/lake_height_map.png", &heightMapWidth, &heightMapHeight, &numComponents, 4);

	int vertexPointer = 0;
	float cellSize = SIZE / (float)(VERTEX_CNT - 1);
	for (int i = 0; i < VERTEX_CNT; i++) {
		for (int j = 0; j < VERTEX_CNT; j++) {
			heights[i][j] = getHeight(i, j, heightMapWidth, heightMapHeight, heightMap);
			vertices[vertexPointer].setPosition(glm::vec3(x + (float)j * cellSize, heights[i][j], z + (float)i  * cellSize));
			vertices[vertexPointer].setTextureCoordinates(glm::vec2((float)j / (float)(VERTEX_CNT - 1), (float)i / (float)(VERTEX_CNT - 1)));
			//vertices[vertexPointer].setNormals(calculateNormals(i, j));
			vertexPointer++;
		}
	}

	vertexPointer = 0;
	for (int i = 0; i < VERTEX_CNT; i++) {
		for (int j = 0; j < VERTEX_CNT; j++) {
			vertices[vertexPointer].setNormals(calculateNormals(i, j));
			vertexPointer++;
		}
	}

	vertexPointer = 0;
	for (int i = 0; i < VERTEX_CNT - 1; i++) {
		for (int j = 0; j < VERTEX_CNT - 1; j++) {
			int topLeft = i*VERTEX_CNT + j;
			int topRight = topLeft + 1;
			int bottomLeft = (i+1) * VERTEX_CNT + j;
			int bottomRight = bottomLeft + 1;

			indices[vertexPointer++] = bottomLeft;
			indices[vertexPointer++] = bottomRight;
			indices[vertexPointer++] = topLeft;
			indices[vertexPointer++] = topRight;
			indices[vertexPointer++] = topLeft;
			indices[vertexPointer++] = bottomRight;
		}
	}

	mesh = Loader::loadMesh(vertices, indices);
} 

void Terrain::bindTextures() {
	terrainTexture.getBgTexture().bind(0);
	terrainTexture.getRTexture().bind(1);
	terrainTexture.getGTexture().bind(2);
	terrainTexture.getBTexture().bind(3);
	blendMap.bind(4);
}

float Terrain::getHeight(float& worldX, float& worldZ) {
	float terrainX = worldX - x;
	float terrainZ = worldZ - z;
	float gridSquareSize = SIZE / (float)(heights.size() - 1);
	int gridX = terrainX / gridSquareSize;
	int gridZ = terrainZ / gridSquareSize;

	if (gridX < 0 && gridX >= heights.size() - 1 && gridZ < 0 && gridZ >= heights.size() - 1)
		return 0;

	float xOnGrid = (terrainX - (gridSquareSize * gridX)) / gridSquareSize;
	float zOnGrid = (terrainZ - (gridSquareSize * gridZ)) / gridSquareSize;
	int nextX = gridX + 1 < heights.size() ? gridX + 1 : gridX;
	int nextZ = gridZ + 1 < heights.size() ? gridZ + 1 : gridZ;

	if (xOnGrid <= (1 - zOnGrid)) 
		return getBarrycentricHeight(glm::vec3(0, heights[gridZ][gridX], 0), glm::vec3(1, heights[gridZ + 1][gridX], 0), glm::vec3(0, heights[gridZ][gridX + 1], 1), glm::vec2(zOnGrid, xOnGrid));
	else 
		return getBarrycentricHeight(glm::vec3(1, heights[gridZ + 1][gridX], 0), glm::vec3(1, heights[gridZ + 1][gridX + 1], 1), glm::vec3(0, heights[gridZ][gridX + 1], 1), glm::vec2(zOnGrid, xOnGrid));
}


float Terrain::getBarrycentricHeight(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& p) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::getHeight(int& x, int& y, int& width, int& height, unsigned char* heightMap) {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 0;
	int index = (x * (width) * 4 + y * 4);
	float pixelColor = (float)heightMap[index] * (float)heightMap[index + 1] * (float)heightMap[index + 2];
	pixelColor = ((int)heightMap[index + 3] << 24) | ((int)heightMap[index] << 16) | ((int)heightMap[index + 1] << 8) | ((int)heightMap[index + 2] << 0);
	pixelColor += (float)MAX_PIXEL_COLOR / 2.f;
	pixelColor *= 2.f / MAX_PIXEL_COLOR;
	
	pixelColor *= MAX_HEIGHT;
	if (pixelColor < -40)	pixelColor *= 1.1;

	return pixelColor;
}

glm::vec3 Terrain::calculateNormals(int& x, int& y) {
	if (x > 0 && x < VERTEX_CNT - 1 && y>0 && y < VERTEX_CNT - 1) {
		float heightL = heights[x + 1][y];
		float heightR = heights[x - 1][y];
		float heightU = heights[x][y + 1];
		float heightD = heights[x][y - 1];

		glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);
		return glm::normalize(normal);
	} 

	return glm::vec3(0, 1, 0);
}