#include "Skybox.h"

#include <fstream>

#include "Loader.h"

Skybox::Skybox(const std::string& file) {
	std::vector<float> cube;
	std::vector<std::string> textures = {
		"res/textures/skybox/right.png",
		"res/textures/skybox/left.png",
		"res/textures/skybox/top.png",
		"res/textures/skybox/bottom.png",
		"res/textures/skybox/back.png",
		"res/textures/skybox/front.png"
	};
	cube.resize(108);
	std::ifstream cubeNodes(file);

	for (int i = 0; i < 108; i++) {
		cubeNodes >> cube[i];
		cube[i] *= 1300;
	}

	mesh = Loader::loadMesh(cube);
	texture = Loader::loadTextureCubeMap(textures, false);
}