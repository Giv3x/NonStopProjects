#include "Player.h"

#include <iostream>

#include "SDL2\SDL.h"

Player::Player() : Entity(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5)) {
	airBourne = false;
	doubleJump = false;
}

void Player::move(const float& frameSpeed, std::map<int, bool>& keyPress, Terrain& terrain) {
	checkInputs(keyPress);

	float distance = frameSpeed * currentMoveSpeed;
	
	this->getTransform().getPosition().x += glm::sin(this->getTransform().getRotation().y) * distance;
	this->getTransform().getPosition().z += glm::cos(this->getTransform().getRotation().y) * distance;
	float yPos = terrain.getHeight(this->getTransform().getPosition().x, this->getTransform().getPosition().z);

	std::cout << this->getTransform().getPosition().x<<' '<< this->getTransform().getPosition().z<<' '<<yPos << std::endl;

	if (upSpeed != 0) {
		upSpeed += GRAVITY;
		jumpStartFrame++;
		this->getTransform().getPosition().y += upSpeed * frameSpeed;
		if (this->getTransform().getPosition().y < yPos) {
			this->getTransform().getPosition().y = yPos;
			upSpeed = 0;
			airBourne = false;
			doubleJump = false;
		}
	}

	if (upSpeed == 0) {
		this->getTransform().getPosition().y = yPos;
	}	

}

void Player::rotate(const float& frameSpeed) {
	float turnAMNT = frameSpeed * TURN_SPEED;

	this->getTransform().getRotation().y += turnAMNT;
}

void Player::jump(float speed) {

}

void Player::checkInputs(std::map<int, bool>& keyPress) {
	if (keyPress[SDLK_w]) {
		currentMoveSpeed = RUN_SPEED;
	} else if (keyPress[SDLK_s]) {
		currentMoveSpeed = -RUN_SPEED;
	} else {
		currentMoveSpeed = 0;
	}

	if (keyPress[SDLK_a]) {
		rotate(0.0006);
	}
	if (keyPress[SDLK_d]) {
		rotate(-0.0006);
	}
	if (keyPress[SDLK_SPACE]) {
		if (!airBourne) {
			jumpStartFrame = 0;
			upSpeed = JUMP_SPEED;
			airBourne = true;
		}
		if (airBourne && !doubleJump && jumpStartFrame > 8) {
			std::cout << "Aaa" << std::endl;
			upSpeed = JUMP_SPEED;
			doubleJump = true;
		}
	}
}

Player::~Player(){
}
