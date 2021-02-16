#pragma once
#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

#include "utility.h"

class Mesh
{
public:
	Mesh();
	Mesh(GLuint vao, const std::vector<GLuint>& vbos, int drawCount);
	~Mesh();

	void init();
	void draw();
	void drawArrays();
	void drawStrips();
	void clean();

	void addVBufferObj(GLuint vbo) { vertexArrayBuffers.push_back(vbo); }
	void setVertices(const std::vector<Vertex>& vertices, unsigned int size);
	void setVertices(const std::vector<Vertex>& vertices, const std::vector<int>& indices, unsigned int size);
	std::vector<Vertex>& getVertices();

	GLuint& getVAO() { return vertexArrayObject; }

private:
	enum bufferTypes {
		POSITION_VB,
		ELEMENT_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	std::vector<GLuint> vertexArrayBuffers;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	unsigned int maxBufferSize;
	unsigned int numVertices;
	unsigned int drawCount;
};
#endif MESH_H

