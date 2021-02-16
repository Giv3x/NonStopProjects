#pragma once
#include "Entity.h"
#include "Terrain.h"

#include <map>

class Player : public Entity
{
public:
	Player();
	~Player();

	void move(const float& frameSpeed, std::map<int, bool>& keyPress, Terrain& terrain);
	void rotate(const float& frameSpeed);
	void jump(float frameSpeed);
private:
	const static int GRAVITY = -9;
	const static int TURN_SPEED = 126;
	const static int RUN_SPEED = 30;
	const static int JUMP_SPEED = 150;
	const static int MAX_JUMP_HEIGHT = 100;

	float currentMoveSpeed;
	float currentTurnSpeed;
	float upSpeed;
	bool airBourne;
	bool doubleJump;
	int jumpStartFrame;

	void checkInputs(std::map<int, bool>& keyPress);
};