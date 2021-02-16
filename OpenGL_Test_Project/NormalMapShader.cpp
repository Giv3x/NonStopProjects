#include "NormalMapShader.h"

#include <iostream>

NormalMapShader::NormalMapShader() : Shader("res/shaders/normal_model_shader") {
}

void NormalMapShader::init(unsigned int cnt) {
	Shader::init(cnt);
	//bindAttributes();
	getAllUniformLocations();
}

void NormalMapShader::getAllUniformLocations() {
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
	locationMaterialTexture = glGetUniformLocation(program, "materialTexture");
	locationNormalMap = glGetUniformLocation(program, "normalMap");
	locationCameraPos = glGetUniformLocation(program, "cameraPos");
	locationClipDistance = glGetUniformLocation(program, "clipingPlaneVec");
}

void NormalMapShader::loadClipDistance(const glm::vec4& clipDistance) {
	glUniform4fv(locationClipDistance, 1, &clipDistance[0]);
}

void NormalMapShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
}

void NormalMapShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void NormalMapShader::loadView(const glm::mat4& view) {
	glUniformMatrix4fv(locationView, 1, false, &view[0][0]);
}

void NormalMapShader::loadProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(locationProjection, 1, false, &projection[0][0]);
}

void NormalMapShader::loadLightInfo(Light& light) {
	glUniform3fv(locationLightPosition, 1, light.getLightPosition());
	glUniform3fv(locationLightIntensity_A, 1, light.getAmbientIntensity());
	glUniform3fv(locationLightIntensity_D, 1, light.getDiffuseIntensity());
	glUniform3fv(locationLightIntensity_S, 1, light.getSpecularIntensity());
}

void NormalMapShader::loadSpotLightInfo(SpotLight& spotLight) {
	glUniform3fv(locationSpotLightPosition, 1, spotLight.getPosition());
	glUniform3fv(locationSpotLightIntensity, 1, spotLight.getIntensity());
	glUniform3fv(locationSpotLightDirection, 1, spotLight.getDirection());
	glUniform1f(locationSpotExponent, spotLight.getExponent());
	glUniform1f(locationSpotCutoff, spotLight.getCutoff());
}

void NormalMapShader::loadMaterialInfo(TexturedModel* model) {
	glUniform3fv(locationLightReflectivity_A, 1, model->getAmbientReflectivity());
	glUniform3fv(locationLightReflectivity_D, 1, model->getDiffuseReflectivity());
	glUniform3fv(locationLightReflectivity_S, 1, model->getSpecularReflectivity());
}

void NormalMapShader::loadLightInfo(Light& light, TexturedModel* model) {
	this->loadLightInfo(light);
	this->loadMaterialInfo(model);
}

void NormalMapShader::loadTextures() {
	glUniform1i(locationMaterialTexture, 0);
	glUniform1i(locationNormalMap, 1);
}

void NormalMapShader::useFakeLighting(bool& fakeLighting) {
	glUniform1f(locationFakeLighting, fakeLighting);
}

void NormalMapShader::loadCameraPos(const glm::vec3& cameraPos) {
	glUniform3fv(locationCameraPos, 1, &cameraPos[0]);
}

void NormalMapShader::loadFogColor(const glm::vec3& fogColor) {
	glUniform3fv(locationFogColor, 1, &fogColor[0]);
}

NormalMapShader::~NormalMapShader() {
}
