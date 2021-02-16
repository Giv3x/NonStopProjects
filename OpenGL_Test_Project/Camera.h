#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

#include "Player.h"
#include "Display.h"

class Camera
{
public:
	Camera() {}
	Camera(float aRatio, const glm::vec3& position = glm::vec3(0, 4, -10), float fov = 70, float zNear = 5, float zFar = 2000.f);
	~Camera() {}

	void init();
	void move(const float& amt, Display& display, std::map<int, bool>& keyPress);
	void move(Player& player, Display& display, std::map<int, bool>& keyPress);
	void calculatePosition(Player& player);

	bool isFirstPerson() { return this->firstPerson; }
	void changeCameraMod() { this->firstPerson = !firstPerson; std::cout << firstPerson << std::endl; }
	void setPosition(const glm::vec3& position) { this->position = position; }
	void setMaxRange(const float maxRange) { this->maxRange = maxRange; }
	void setMinRange(const float minRange) { this->minRange = minRange; }
	void setFov(const float fov) { this->fov = fov; }
	void setAspectRatio(const float aspectRatio) { this->aspectRatio = aspectRatio; }
	void setTPPForward(const glm::vec3& f) { this->forward = f - this->position; }
	void rotateX();
	void rotateX(const float& angle);
	void rotateY(const float& angle);
	void setPitch(const float& pitch) { this->pitch += glm::radians(pitch); }
	void setYaw(const float& yaw) { this->yaw = glm::radians(yaw); }
	void setDistance(const float& d) { distance = d; }
	void setAngleAroundPlayer(const float& angle) { angleAroundPlayer += angle; }
	void invertPitch();

	glm::mat4& getView();
	glm::vec3& getPostion() { return position; }
	glm::mat4& getProjection() { return projection; }
	glm::vec3& getForward() { return forward; }
	glm::vec3& getLeft() { return left; }
	glm::vec3& getBack() { return -forward; }
	glm::vec3& getRight() { return -left; }
	float getPitch() { return pitch; }
	float getYaw() { return yaw; }

private:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 left;
	glm::vec3 yAxis;
	
	glm::mat4 perspective;
	glm::mat4 projection;

	float maxRange;
	float minRange;
	float fov;
	float aspectRatio;
	float pitch;
	float yaw;
	float distance;
	float angleAroundPlayer;
	float yAngle;
	bool firstPerson;

	void calculateHorizontalDistance(float& hDistance);
	void calculateVerticalDistance(float& vDistance);
	void calculateZoom();
};

