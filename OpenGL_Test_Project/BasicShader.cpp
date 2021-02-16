#include "BasicShader.h"

#include <iostream>

BasicShader::BasicShader() : Shader("basic_shader") {
}

void BasicShader::init(unsigned int cnt) {
	Shader::init(cnt);
	//bindAttributes();
	getAllUniformLocations();
}

void BasicShader::getAllUniformLocations() {
	locationTransform = glGetUniformLocation(program, "model");
	locationView = glGetUniformLocation(program, "view");
	locationProjection = glGetUniformLocation(program, "projection");
	locationLightPosition = glGetUniformLocation(program, "lightPosition");
	locationLightIntensity_S = glGetUniformLocation(program, "lightInfo.Ls");
	locationLightIntensity_A = glGetUniformLocation(program, "lightInfo.La");
	locationLightIntensity_D = glGetUniformLocation(program, "lightInfo.Ld");
	locationLightReflectivity_S = glGetUniformLocation(program, "materialInfo.Ks");
	locationLightReflectivity_A = glGetUniformLocation(program, "materialInfo.Ka");
	locationLightReflectivity_D = glGetUniformLocation(program, "materialInfo.Kd");
	locationFakeLighting = glGetUniformLocation(program, "useFakeLighting");
	locationFogColor = glGetUniformLocation(program, "fogColor");
	locationSpotLightPosition = glGetUniformLocation(program, "spotLightPosition");
	locationSpotLightIntensity = glGetUniformLocation(program, "spotLight.intensity");
	locationSpotLightDirection = glGetUniformLocation(program, "spotLight.direction");
	locationSpotExponent = glGetUniformLocation(program, "spotLight.exponent");
	locationSpotCutoff = glGetUniformLocation(program, "spotLight.cutoff");
	locationClipDistance = glGetUniformLocation(program, "clipingPlaneVec");
}

void BasicShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
}

void BasicShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void BasicShader::loadView(const glm::mat4& view) {
	glUniformMatrix4fv(locationView, 1, false, &view[0][0]);
}

void BasicShader::loadProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(locationProjection, 1, false, &projection[0][0]);
}

void BasicShader::loadLightInfo(Light& light) {
	glUniform3fv(locationLightPosition, 1, light.getLightPosition());
	glUniform3fv(locationLightIntensity_A, 1, light.getAmbientIntensity());
	glUniform3fv(locationLightIntensity_D, 1, light.getDiffuseIntensity());
	glUniform3fv(locationLightIntensity_S, 1, light.getSpecularIntensity());
}

void BasicShader::loadSpotLightInfo(SpotLight& spotLight) {
	glUniform3fv(locationSpotLightPosition, 1, spotLight.getPosition());
	glUniform3fv(locationSpotLightIntensity, 1, spotLight.getIntensity());
	glUniform3fv(locationSpotLightDirection, 1, spotLight.getDirection());
	glUniform1f(locationSpotExponent, spotLight.getExponent());
	glUniform1f(locationSpotCutoff, spotLight.getCutoff());
}

void BasicShader::loadMaterialInfo(TexturedModel* model) {
	glUniform3fv(locationLightReflectivity_A, 1, model->getAmbientReflectivity());
	glUniform3fv(locationLightReflectivity_D, 1, model->getDiffuseReflectivity());
	glUniform3fv(locationLightReflectivity_S, 1, model->getSpecularReflectivity());
}

void BasicShader::loadLightInfo(Light& light, TexturedModel* model) {
	this->loadLightInfo(light);
	this->loadMaterialInfo(model);
}

void BasicShader::useFakeLighting(bool& fakeLighting) {
	glUniform1f(locationFakeLighting, fakeLighting);
}

void BasicShader::loadFogColor(const glm::vec3& fogColor) {
	glUniform3fv(locationFogColor, 1, &fogColor[0]);
}

void BasicShader::loadClipDistance(const glm::vec4& clipDistance) {
	glUniform4fv(locationClipDistance, 1, &clipDistance[0]);
}

BasicShader::~BasicShader() {
}
