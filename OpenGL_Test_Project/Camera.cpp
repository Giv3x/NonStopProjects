#include "Camera.h"

#include <SDL2\SDL.h>


Camera::Camera(float aRatio, const glm::vec3& position, float fov, float zNear, float zFar) {
	this->position = position;
	this->maxRange = zFar;
	this->minRange = zNear;
	this->aspectRatio = aRatio;
	this->fov = fov;
	this->up = glm::vec3(0, 1, 0);
	this->forward = glm::vec3(0, 0, 1);
	this->yAxis = glm::vec3(0, 1, 0);
	this->left = glm::cross(up, forward);
	this->pitch = glm::radians(20.);
	this->yaw = 0;
	this->distance = 20;
	this->angleAroundPlayer = 0;
	this->firstPerson = true;

	this->yAngle = 0;
}

void Camera::init() {
	this->projection = glm::perspective(fov, aspectRatio, minRange, maxRange);
}

glm::mat4& Camera::getView() {
	this->perspective = glm::lookAt(position, position + forward, up);
	return perspective;
}

void Camera::move(const float& amt, Display& display, std::map<int, bool>& keyPress) {
	if (keyPress[SDLK_w]) {
		this->position += amt*this->forward;
	}
	if (keyPress[SDLK_s]) {
		this->position -= amt*this->forward;
	}
	if (keyPress[SDLK_a]) {
		this->position += amt*this->left;
	}
	if (keyPress[SDLK_d]) {
		this->position -= amt*this->left;
	}
	if (keyPress[SDLK_q]) {
		this->position += amt*glm::vec3(0, 1, 0);
	}
	if (keyPress[SDLK_e]) {
		this->position -= amt*glm::vec3(0, 1, 0);
	}
	if (keyPress[SDL_BUTTON_RIGHT]) {
		glm::ivec2 mouseLocation;

		float halfLength = display.getLegth() / 2;
		float halfWidth = display.getWidth() / 2;

		SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
		SDL_WarpMouseInWindow(display.getWindow(), halfLength, halfWidth);
		glm::vec2 rotAngels = (glm::vec2(mouseLocation) - glm::vec2(halfLength, halfWidth)) / 50.f;

		yAngle += glm::radians(rotAngels.y);
		setYaw(-rotAngels.x);
		rotateX();
		rotateY(glm::radians(rotAngels.y));
	}
}

void Camera::move(Player& player, Display& display, std::map<int, bool>& keyPress) {
	if (keyPress[SDL_BUTTON_RIGHT]) {
		glm::ivec2 mouseLocation;
		float lengthHalf = display.getLegth() / 2;
		float widthHalf = display.getWidth() / 2;

		SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
		SDL_WarpMouseInWindow(display.getWindow(), lengthHalf, widthHalf);

		widthHalf = (mouseLocation.y - widthHalf) / 50.f;
		lengthHalf = (mouseLocation.x - lengthHalf) / 50.f;

		setPitch(widthHalf);
		setAngleAroundPlayer(-lengthHalf);
		setYaw(-lengthHalf);
		rotateX();
		rotateY(glm::radians(widthHalf));
	}
	calculatePosition(player);
}

void Camera::invertPitch() {
	yAngle *= -1;
	rotateY(yAngle * 2);
}

void Camera::calculatePosition(Player& player) {
	float hDistance, vDistance;
	calculateHorizontalDistance(hDistance);
	calculateVerticalDistance(vDistance);

	float theta = /*player.getTransform().getRotation().y + */glm::radians(angleAroundPlayer);
	float xOffset = glm::sin(theta) * hDistance;
	float zOffset = glm::cos(theta) * hDistance;

	this->position.x = player.getTransform().getPosition().x - xOffset;
	this->position.y = player.getTransform().getPosition().y + vDistance;
	this->position.z = player.getTransform().getPosition().z - zOffset;
}

void Camera::rotateX() {
	this->left = glm::normalize(glm::cross(yAxis, forward));

	float cosHalfAngle = glm::cos(yaw / 2);
	float sinHalfAngle = glm::sin(yaw / 2);
	glm::quat q(cosHalfAngle, yAxis*sinHalfAngle);

	forward = glm::normalize(glm::rotate(q, forward));
	up = glm::normalize(glm::cross(forward, this->left));
}

void Camera::rotateX(const float& angle) {
	this->left = glm::normalize(glm::cross(yAxis, forward));

	float cosHalfAngle = glm::cos(glm::radians(angle) / 2);
	float sinHalfAngle = glm::sin(glm::radians(angle) / 2);
	glm::quat q(cosHalfAngle, yAxis*sinHalfAngle);

	forward = glm::normalize(glm::rotate(q, forward));
	up = glm::normalize(glm::cross(forward, this->left));
}

void Camera::rotateY(const float& angle) {
	this->left = glm::normalize(glm::cross(yAxis, forward));

	float cosHalfAngle = glm::cos(angle /2);
	float sinHalfAngle = glm::sin(angle /2);
	glm::quat q(cosHalfAngle, this->left*sinHalfAngle);

	forward = glm::rotate(q, forward);
	forward = glm::normalize(forward);

	up = glm::cross(forward, this->left);
	up = glm::normalize(up);
}

void Camera::calculateHorizontalDistance(float& hDistance) {
	hDistance = glm::cos(pitch) * distance;
}

void Camera::calculateVerticalDistance(float& vDistance) {
	vDistance = glm::sin(pitch) * distance;
}