#include "OBJloader.h"

#include <fstream>
#include <iostream>

#include "Mesh.h"
#include "Loader.h"
#include "utility.h"

OBJloader::OBJloader() {
}

Mesh OBJloader::load(const char* file, bool hasTangents) {
	std::ifstream str(file);
	std::string line;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> vertexIndices;

	std::vector<Vertex> vertexData;
	std::vector<int> indices;

	std::vector<std::string> strVector;
	int i = 0;
	while (std::getline(str, line)) {
		strVector = split(line, ' ');
		if (strVector[0] == "v") {
			vertices.push_back(glm::vec3(stof(strVector[1]), stof(strVector[2]), stof(strVector[3])));
		}
		else if (strVector[0] == "vt") {
			textures.push_back(glm::vec2(stof(strVector[1]), stof(strVector[2])));
		}
		else if (strVector[0] == "vn") {
			normals.push_back(glm::vec3(stof(strVector[1]), stof(strVector[2]), stof(strVector[3])));
		}
		else if (strVector[0] == "f") {
			vertexIndices.resize(vertices.size(), glm::vec4(0,0,0,-2));
			break;
		}
	}

	do {
		if (line[0] != 'f')
			break;
		std::vector<std::string> indexData = split(line, ' ');
		for (int i = 1; i < 4; i++) {

			std::vector<std::string> ind = split(indexData[i], '/');
			glm::vec3 vertexIndex(stoi(ind[0]) - 1, stoi(ind[1]) - 1, stoi(ind[2]) - 1);

			dealWithDuplicateVertices(vertexIndex, vertexIndices, indices, vertexIndex.x);
		}
	} while (std::getline(str, line));

	generateVertices(vertices, textures, normals, vertexData, vertexIndices);

	if (hasTangents) {
		calculateTangents(vertexData, indices);
		return Loader::loadTangentMesh(vertexData, indices);
	}
	
	return Loader::loadMesh(vertexData, indices);
}

void OBJloader::processVertex(std::string& indexData, std::vector<glm::vec3>& v, std::vector<glm::vec2>& t,
		std::vector<glm::vec3>& n, std::vector<int>& indices, std::vector<Vertex>& vertexData) {
	std::vector<std::string> ind = split(indexData, '/');
	
	int currentVertex = stoi(ind[0]) - 1;
	int currentTexture = stoi(ind[1]) - 1;
	int currentNormal = stoi(ind[2]) - 1;

	indices.push_back(currentVertex);
	vertexData.push_back(Vertex(v[currentVertex], glm::vec2(t[currentTexture].x, 1 - t[currentTexture].y), n[currentNormal]));
	vertexData[currentVertex].setPosition(v[currentVertex]);
	vertexData[currentVertex].setTextureCoordinates(glm::vec2(t[currentTexture].x, 1 - t[currentTexture].y));
	vertexData[currentVertex].setNormals(n[currentNormal]);
}

void OBJloader::calculateTangents(std::vector<Vertex>& vertices, const std::vector<int>& indices) {
	glm::vec3 deltaPos1, deltaPos2, tangent;
	glm::vec2 deltaUv1, deltaUv2;
	float r;

	for (int i = 0; i < indices.size(); i += 3) {
		deltaPos1 = vertices[indices[i + 1]].getPosition() - vertices[indices[i]].getPosition();
		deltaPos2 = vertices[indices[i + 2]].getPosition() - vertices[indices[i]].getPosition();

		deltaUv1 = vertices[indices[i + 1]].getTextureCoordinates() - vertices[indices[i]].getTextureCoordinates();
		deltaUv2 = vertices[indices[i + 2]].getTextureCoordinates() - vertices[indices[i]].getTextureCoordinates();

		r = 1.0 / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
		tangent = (deltaPos1 * deltaUv2.y - deltaPos2*deltaUv1.y)*r;
		vertices[indices[i]].setTangent(tangent);
		vertices[indices[i + 1]].setTangent(tangent);
		vertices[indices[i + 2]].setTangent(tangent);
	}
}

void OBJloader::dealWithDuplicateVertices(glm::vec3& newIndex, std::vector<glm::vec4>& vertexIndices, std::vector<int>& indices, int currentIndex) {
	if (currentIndex >= 0 && currentIndex < vertexIndices.size()) {
		if (vertexIndices[currentIndex].y == newIndex.y && vertexIndices[currentIndex].z == newIndex.z) {
			indices.push_back(currentIndex);
			return;
		}
		if (vertexIndices[currentIndex].a > -1) {
			dealWithDuplicateVertices(newIndex, vertexIndices, indices, vertexIndices[currentIndex].a);
			return;
		}

		if (vertexIndices[currentIndex].a == -2) {
			vertexIndices[currentIndex] = glm::vec4(newIndex, -1);
			indices.push_back(currentIndex);
			return;
		}
	}

	vertexIndices.push_back(glm::vec4(newIndex, -1));
	vertexIndices[currentIndex].a = vertexIndices.size()-1;
	indices.push_back(vertexIndices.size()-1);
}

void OBJloader::generateVertices(std::vector<glm::vec3>& v, std::vector<glm::vec2>& t, std::vector<glm::vec3>& n, std::vector<Vertex>& vertices, std::vector<glm::vec4>& vertexIndices) {
	std::cout << vertexIndices.size() << std::endl;
	vertices.resize(vertexIndices.size());

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setPosition(v[vertexIndices[i].x]);
		vertices[i].setTextureCoordinates(glm::vec2((t[vertexIndices[i].y]).x, 1 - (t[vertexIndices[i].y]).y));
		vertices[i].setNormals(n[vertexIndices[i].z]);
	}
}

OBJloader::~OBJloader() {
}
