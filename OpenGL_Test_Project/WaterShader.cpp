#include "WaterShader.h"

#include <iostream>

WaterShader::WaterShader() : Shader("water_shader") {
}

void WaterShader::init(unsigned int cnt) {
	Shader::init(cnt);
	//bindAttributes();
	getAllUniformLocations();
}

void WaterShader::getAllUniformLocations() {
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
	locationFogColor = glGetUniformLocation(program, "fogColor");
	locationSpotLightPosition = glGetUniformLocation(program, "spotLightPosition");
	locationSpotLightIntensity = glGetUniformLocation(program, "spotLight.intensity");
	locationSpotLightDirection = glGetUniformLocation(program, "spotLight.direction");
	locationSpotExponent = glGetUniformLocation(program, "spotLight.exponent");
	locationSpotCutoff = glGetUniformLocation(program, "spotLight.cutoff");
	locationCameraPos = glGetUniformLocation(program, "cameraPos");
	locationDudvmap = glGetUniformLocation(program, "dudvMap");
	locationNormalmap = glGetUniformLocation(program, "normalMap");
	locationReflectionTexture = glGetUniformLocation(program, "reflectionTexture");
	locationRefractionTexture = glGetUniformLocation(program, "refractionTexture");
	locationRefractionDepthTexture = glGetUniformLocation(program, "refractionDepthTexture");
	locationMoveFactor = glGetUniformLocation(program, "moveFactor");
}

void WaterShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
}

void WaterShader::connectTextures() {
	glUniform1i(locationReflectionTexture, 0);
	glUniform1i(locationRefractionTexture, 1);
	glUniform1i(locationRefractionDepthTexture, 2);
	glUniform1i(locationDudvmap, 3);
	glUniform1i(locationNormalmap, 4);
}

void WaterShader::loadMoveFactor(float& factor) {
	glUniform1f(locationMoveFactor, factor);
}

void WaterShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void WaterShader::loadView(const glm::mat4& view) {
	glUniformMatrix4fv(locationView, 1, false, &view[0][0]);
}

void WaterShader::loadProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(locationProjection, 1, false, &projection[0][0]);
}

void WaterShader::loadCameraPos(const glm::vec3& cameraPos) {
	glUniform3fv(locationCameraPos, 1, &cameraPos[0]);
}

void WaterShader::loadLightInfo(Light& light) {
	glUniform3fv(locationLightPosition, 1, light.getLightPosition());
	glUniform3fv(locationLightIntensity_A, 1, light.getAmbientIntensity());
	glUniform3fv(locationLightIntensity_D, 1, light.getDiffuseIntensity());
	glUniform3fv(locationLightIntensity_S, 1, light.getSpecularIntensity());
}

void WaterShader::loadSpotLightInfo(SpotLight& spotLight) {
	glUniform3fv(locationSpotLightPosition, 1, spotLight.getPosition());
	glUniform3fv(locationSpotLightIntensity, 1, spotLight.getIntensity());
	glUniform3fv(locationSpotLightDirection, 1, spotLight.getDirection());
	glUniform1f(locationSpotExponent, spotLight.getExponent());
	glUniform1f(locationSpotCutoff, spotLight.getCutoff());
}

void WaterShader::loadMaterialInfo(TexturedModel* model) {
	glUniform3fv(locationLightReflectivity_A, 1, model->getAmbientReflectivity());
	glUniform3fv(locationLightReflectivity_D, 1, model->getDiffuseReflectivity());
	glUniform3fv(locationLightReflectivity_S, 1, model->getSpecularReflectivity());
}

void WaterShader::loadLightInfo(Light& light, TexturedModel* model) {
	this->loadLightInfo(light);
	this->loadMaterialInfo(model);
}

void WaterShader::loadFogColor(const glm::vec3& fogColor) {
	glUniform3fv(locationFogColor, 1, &fogColor[0]);
}

WaterShader::~WaterShader() {
}