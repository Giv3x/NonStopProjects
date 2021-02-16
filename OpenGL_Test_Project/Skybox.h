#pragma once
#include <vector>
#include <string>

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class Skybox
{
public:
	Skybox(const std::string& file);

	Mesh& getMesh() { return mesh; }
	Transform& getTransform() { return transform; }
	Texture& getTexture() { return texture; }


	~Skybox() {}

private:
	Mesh mesh;
	Texture texture;
	Transform transform;
};

