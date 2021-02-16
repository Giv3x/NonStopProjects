#include "Entity.h"

#include "OBJloader.h"
#include "Texture.h"
#include "Loader.h"

Entity::Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
	this->transform.setPosition(position);
	this->transform.setRotation(rotation);
	this->transform.setScale(scale);
}

Entity::~Entity() {
	//this->model.clean();
}