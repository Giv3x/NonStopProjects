#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>
#include <vector>
#include <string>

#include "stb_image.h"

class Texture
{
public:
	Texture();
	~Texture();

	void initTex2D(const char* textureName, bool transparent);
	void initTexCubeMap(const std::vector<std::string>& textureName, bool transparent);
	void initTextureAttachment(int& width, int& height, const int& attachment);
	void initTextureDepthAttachment(int& width, int& height);
	void bind(int unit);
	void bindCubeMap(int unit);
	void unbind(int unit);
	void clean();

	bool hasTransparency() { return isTransparent; }
	GLuint texture;

private:
	bool isTransparent;
};

#endif

