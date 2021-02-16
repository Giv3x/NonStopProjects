#pragma once
#include "TexturedModel.h"
#include "Transform.h"

class Entity
{
public:
	Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	Entity() {}
	Transform& getTransform() { return transform; }
	~Entity();

private:
	Transform transform;
};

