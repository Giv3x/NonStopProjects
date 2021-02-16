#pragma once
#include <glm\glm.hpp>
#include <vector>

#include "Texture.h"
#include "Loader.h"
#include "utility.h"
#include "Transform.h"
#include "TexturedModel.h"
#include "Loader.h"
#include "WaterFrameBuffer.h"

class Water
{
public:
	Water(const glm::vec3& position, const glm::vec3& diffuseReflectivity, const glm::vec3& specularReflectivity, const glm::vec3& ambientReflectivity);
	~Water() {}

	Transform& getTransform() { return transform; }
	TexturedModel& getTexturedModel() { return texturedModel; }
	glm::vec3& getPos() { return pos; }

	void addTextures(WaterFrameBuffer& fbo, Texture& dudv, Texture& normalMap);
	void bindTextures();
	void unbindTextures();

private:
	Transform transform;
	TexturedModel texturedModel;

	glm::vec3 pos;
	const int SIZE = 1400;
	const int VERTEX_CNT = 128;
};

