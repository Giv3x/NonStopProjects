#pragma once

#include <glm\glm.hpp>

#include "utility.h"
#include "Mesh.h"

class OBJloader
{
public:
	OBJloader();
	~OBJloader();
	static Mesh load(const char* file, bool hasTangents = false);

protected:
private:
	static void processVertex(std::string& vertices, std::vector<glm::vec3>& v, std::vector<glm::vec2>& t, 
		std::vector<glm::vec3>& n, std::vector<int>& indices, std::vector<Vertex>& vertexData);
	static void calculateTangents(std::vector<Vertex>& vertices, const std::vector<int>& indices);
	static void dealWithDuplicateVertices(glm::vec3& newIndex, std::vector<glm::vec4>& vertexIndices, std::vector<int>& indices, int nextIndex);
	static void generateVertices(std::vector<glm::vec3>& v, std::vector<glm::vec2>& t,
		std::vector<glm::vec3>& n, std::vector<Vertex>& vertices, std::vector<glm::vec4>& vertexIndices);

};

