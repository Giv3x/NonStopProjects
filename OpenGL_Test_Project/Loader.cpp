#include "Loader.h"


#include <iostream>

Loader::Loader() {
}


Mesh Loader::loadMesh(std::vector<Vertex>& vertices, const std::vector<int>& indices) {
	GLuint vao = 0;
	std::vector<GLuint> vbo(2);

	glGenVertexArrays(1, &vao);
	glGenBuffers(2, &vbo[0]);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return Mesh(vao, vbo, indices.size());
}

Mesh Loader::loadMesh(float* vertices, const int& size, const int& drawCount) {
	GLuint vao = 0;
	std::vector<GLuint> vbo(2);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo[0]);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	return Mesh(vao, vbo, drawCount);
}

Mesh Loader::loadTangentMesh(std::vector<Vertex>& vertices, const std::vector<int>& indices) {
	GLuint vao = 0;
	std::vector<GLuint> vbo(2);

	glGenVertexArrays(1, &vao);
	glGenBuffers(2, &vbo[0]);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	return Mesh(vao, vbo, indices.size());
}

Mesh Loader::loadMesh(const std::vector<float>& vertices) {
	GLuint vao;
	std::vector<GLuint> vbo(1);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo[0]);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), (void*)&vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	return Mesh(vao, vbo, vertices.size() / 3);
}


Texture Loader::loadTexture2D(const std::string& texLoc, bool transparent) {
	Texture texture;
	texture.initTex2D(texLoc.c_str(), transparent);

	return texture;
}


Texture Loader::loadTextureCubeMap(const std::vector<std::string>& texLoc, bool transparent) {
	Texture texture;
	texture.initTexCubeMap(texLoc, transparent);

	return texture;
}

void Loader::loadImage(int& width, int& height, unsigned char* imgData, const char* loc) {
	int numComponents;

	imgData = stbi_load(loc, &width, &height, &numComponents, 4);
}

Loader::~Loader() {
}
