#include "Mesh.h"


Mesh::Mesh() {
	vertexArrayBuffers.reserve(NUM_BUFFERS);
}

Mesh::Mesh(GLuint vao, const std::vector<GLuint>& vbos, int drawCount) {
	vertexArrayObject = vao;
	vertexArrayBuffers.reserve(NUM_BUFFERS);
	this->drawCount = drawCount;

	for (GLuint vbo : vbos) {
		vertexArrayBuffers.push_back(vbo);
	}
}

Mesh::~Mesh() {
}

void Mesh::draw() {
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, (GLvoid*)0);
}

void Mesh::drawArrays() {
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
}

void Mesh::drawStrips() {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, drawCount);
}

void Mesh::clean() {
	glDeleteBuffers(maxBufferSize, &vertexArrayBuffers[0]);
	glDeleteVertexArrays(1, &vertexArrayObject);
}