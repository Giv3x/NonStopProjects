#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Texture.h"

class Loader
{
public:
	Loader();
	~Loader();

	static Mesh loadMesh(std::vector<Vertex>& vertices, const std::vector<int>& indices);
	static Mesh loadMesh(float* vertices, const int& size, const int& drawCount);
	static Mesh loadTangentMesh(std::vector<Vertex>& vertices, const std::vector<int>& indices);
	static Mesh loadMesh(const std::vector<float>& vertices);
	static Texture loadTexture2D(const std::string& texLoc, bool transparent = false);
	static Texture loadTextureCubeMap(const std::vector<std::string>& texLoc, bool transparent);
	static void loadImage(int& width, int& height, unsigned char* imgData, const char* loc);
	Mesh loadMesh(const std::vector<Vertex>& vertices);

private:

};

