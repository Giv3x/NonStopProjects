#pragma once
#include <glm\glm.hpp>
#include <vector>

#include "Texture.h"
#include "Loader.h"
#include "utility.h"
#include "Transform.h"
#include "TexturedModel.h"
#include "Loader.h"

class GUI
{
public:
	GUI(glm::vec3 position, glm::vec3 scale, Texture& texture);
	~GUI() {}

	Transform& getTransform() { return transform; }
	TexturedModel& getTexturedModel() { return texturedModel; }

	void bindTextures();
	void setTextures(Texture& texture);
	void unbindTextures();

private:
	Transform transform;
	TexturedModel texturedModel;

	glm::vec3 pos;
};

