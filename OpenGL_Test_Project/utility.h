#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <glm\glm.hpp>
#include <vector>
#include <string>

class Vertex {
public:
	Vertex() {}
	Vertex(const glm::vec3& position, const glm::vec2& texCoord = glm::vec2(0.f, 0.f), const glm::vec3& normals = glm::vec3(0, 0, 0));
	Vertex(const glm::vec3& position, const glm::vec3& tangents, const glm::vec2& texCoord = glm::vec2(0.f, 0.f), const glm::vec3& normals = glm::vec3(0, 1, 0));

	glm::vec3& getPosition();
	glm::vec2& getTextureCoordinates();
	glm::vec3& getNormals();

	void setPosition(const glm::vec3& position);
	void setTextureCoordinates(const glm::vec2& texCoords);
	void setNormals(const glm::vec3& normals);
	void setTangent(const glm::vec3& tangent);

private:
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 tangents;
};

std::vector<std::string> split(const std::string& s, const char& d);
void generateQuad(glm::vec3& position, const int& size, const int& vertexCNT, std::vector<Vertex>& vertices, std::vector<int>& indices);

#endif UTILITY_H