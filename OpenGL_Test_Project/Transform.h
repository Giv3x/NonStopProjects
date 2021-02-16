#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& p = glm::vec3(), const glm::vec3& r = glm::vec3(), const glm::vec3& s = glm::vec3(1.f))
			: position(p), rotation(r), scale(s) {}
	~Transform() {}

	glm::mat4 getModelMatrix() {
		glm::mat4 transform = glm::translate(position);
		glm::mat4 scale = glm::scale(this->scale);

		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 rotate = rotZ*rotY*rotX;

		return transform*rotate*scale;
	}

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	glm::vec3& getScale() { return scale; }

	void setPosition(const glm::vec3& p) { this->position = p; }
	void setRotation(const glm::vec3& r) { this->rotation = r; }
	void setScale(const glm::vec3& s) { this->scale = s; }

private:
	glm::vec3 position, rotation, scale;
};

