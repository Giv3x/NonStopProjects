#include "utility.h"


Vertex::Vertex(const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normals) {
	this->position = position;
	this->texCoord = texCoord;
	this->normal = normals;
}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& tangents, const glm::vec2& texCoord, const glm::vec3& normals) {
	this->position = position;
	this->texCoord = texCoord;
	this->normal = normals;
	this->tangents = tangents;
}

glm::vec3& Vertex::getPosition() {
	return this->position;
}

glm::vec2& Vertex::getTextureCoordinates() {
	return this->texCoord;
}

glm::vec3& Vertex::getNormals() {
	return this->normal;
}

void Vertex::setPosition(const glm::vec3& position) {
	this->position = position;
}

void Vertex::setNormals(const glm::vec3& normals) {
	this->normal = normals;
}

void Vertex::setTangent(const glm::vec3& tangent) {
	this->tangents = tangent;
}

void Vertex::setTextureCoordinates(const glm::vec2& texCoords) {
	this->texCoord = texCoords;
}

std::vector<std::string> split(const std::string& s, const char& d) {
	std::string text = "";
	std::vector<std::string> result;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == d) {
			if (text.size() == 0)
				continue;
			result.push_back(text);
			text = "";
			continue;
		}

		text += s[i];
	}

	if (text.size() != 0)	result.push_back(text);

	return result;
}

void generateQuad(glm::vec3& position, const int& size, const int& vertexCNT, std::vector<Vertex>& vertices, std::vector<int>& indices) {
	int vertexPointer = 0;
	int verticesCNT = vertexCNT * vertexCNT;
	float cellSize = (float)size / (float)(vertexCNT - 1);

	for (int i = 0; i < vertexCNT; i++) {
		for (int j = 0; j < vertexCNT; j++) {
			vertices[vertexPointer].setPosition(glm::vec3(position.x + j*cellSize, position.y, position.z + i*cellSize));
			vertices[vertexPointer].setTextureCoordinates(glm::vec2((float)j / (vertexCNT - 1), (float)i / (vertexCNT - 1)));
			vertexPointer++;
		}
	}

	vertexPointer = 0;
	for (int i = 0; i < vertexCNT - 1; i++) {
		for (int j = 0; j < vertexCNT - 1; j++) {
			int topLeft = i*vertexCNT + j;
			int topRight = topLeft + 1;
			int bottomLeft = (i + 1) * vertexCNT + j;
			int bottomRight = bottomLeft + 1;

			indices[vertexPointer++] = bottomLeft;
			indices[vertexPointer++] = bottomRight;
			indices[vertexPointer++] = topLeft;
			indices[vertexPointer++] = topRight;
			indices[vertexPointer++] = topLeft;
			indices[vertexPointer++] = bottomRight;
		}
	}
}