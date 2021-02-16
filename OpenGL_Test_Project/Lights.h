#pragma once
#include <glm\glm.hpp>

class Light {
public:
	Light(const glm::vec3& lightPosition, const glm::vec3& diffuseIntensity, const glm::vec3& ambientIntensity, const glm::vec3& specularIntensity)
		: position(lightPosition), 
		intensityDiffuse(diffuseIntensity), 
		intensitySpecular(specularIntensity),
		intensityAmbient(ambientIntensity) {}
	float* getLightPosition() { return &position[0]; }
	float* getDiffuseIntensity() { return &intensityDiffuse[0]; }
	float* getSpecularIntensity() { return &intensitySpecular[0]; }
	float* getAmbientIntensity() { return &intensityAmbient[0]; }

private:
	glm::vec3 position;
	glm::vec3 intensityDiffuse;
	glm::vec3 intensitySpecular;
	glm::vec3 intensityAmbient;
};

class SpotLight {
public:
	SpotLight(const glm::vec3& lightPosition, const glm::vec3& intensity, const glm::vec3& direction, const float& exp, const float& cutoff)
		: position(lightPosition),
		intensity(intensity),
		direction(direction),
		exponent(exp),
		cutoff(glm::radians(cutoff)) {}
	
	void setPosition(const glm::vec3& position) { this->position = position; }

	float* getPosition() { return &position[0]; }
	float* getIntensity() { return &intensity[0]; }
	float* getDirection() { return &direction[0]; }
	float& getExponent() { return exponent; }
	float& getCutoff() { return cutoff; }

private:
	glm::vec3 position;
	glm::vec3 intensity;
	glm::vec3 direction;
	float exponent;
	float cutoff;
};