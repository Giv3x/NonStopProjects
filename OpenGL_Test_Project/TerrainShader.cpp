#include "TerrainShader.h"

#include <iostream>

TerrainShader::TerrainShader() : Shader("terrainShader") {
}

void TerrainShader::init(unsigned int cnt) {
	Shader::init(cnt);
	//bindAttributes();
	getAllUniformLocations();
}

void TerrainShader::getAllUniformLocations() {
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
	locationBgTexture = glGetUniformLocation(program, "backgroundTexture");
	locationRTexture = glGetUniformLocation(program, "rTexture");
	locationGTexture = glGetUniformLocation(program, "gTexture");
	locationBTexture = glGetUniformLocation(program, "bTexture");
	locationBlendMap = glGetUniformLocation(program, "blendMapTexture");
	locationSpotLightPosition = glGetUniformLocation(program, "spotLightPosition");
	locationSpotLightIntensity = glGetUniformLocation(program, "spotLight.intensity");
	locationSpotLightDirection = glGetUniformLocation(program, "spotLight.direction");
	locationSpotExponent = glGetUniformLocation(program, "spotLight.exponent");
	locationSpotCutoff = glGetUniformLocation(program, "spotLight.cutoff");
	locationClipDistance = glGetUniformLocation(program, "clipingPlaneVec");
}

void TerrainShader::loadClipDistance(const glm::vec4& clipDistance) {
	glUniform4fv(locationClipDistance, 1, &clipDistance[0]);
}

void TerrainShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
}

void TerrainShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void TerrainShader::loadTextures() {
	glUniform1i(locationBgTexture, 0);
	glUniform1i(locationRTexture, 1);
	glUniform1i(locationGTexture, 2);
	glUniform1i(locationBTexture, 3);
	glUniform1i(locationBlendMap, 4);
}

void TerrainShader::loadView(const glm::mat4& view) {
	glUniformMatrix4fv(locationView, 1, false, &view[0][0]);
}

void TerrainShader::loadProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(locationProjection, 1, false, &projection[0][0]);
}

void TerrainShader::loadLightInfo(Light& light) {
	glUniform3fv(locationLightPosition, 1, light.getLightPosition());
	glUniform3fv(locationLightIntensity_A, 1, light.getAmbientIntensity());
	glUniform3fv(locationLightIntensity_D, 1, light.getDiffuseIntensity());
	glUniform3fv(locationLightIntensity_S, 1, light.getSpecularIntensity());
}

void TerrainShader::loadSpotLightInfo(SpotLight& spotLight) {
	glUniform3fv(locationSpotLightPosition, 1, spotLight.getPosition());
	glUniform3fv(locationSpotLightIntensity, 1, spotLight.getIntensity());
	glUniform3fv(locationSpotLightDirection, 1, spotLight.getDirection());
	glUniform1f(locationSpotExponent, spotLight.getExponent());
	glUniform1f(locationSpotCutoff, spotLight.getCutoff());
}

void TerrainShader::loadMaterialInfo(Terrain* terrain) {
	glUniform3fv(locationLightReflectivity_A, 1, terrain->getAmbientReflectivity());
	glUniform3fv(locationLightReflectivity_D, 1, terrain->getDiffuseReflectivity());
	glUniform3fv(locationLightReflectivity_S, 1, terrain->getSpecularReflectivity());
}

void TerrainShader::loadLightInfo(Light& light, Terrain* terrain) {
	this->loadLightInfo(light);
	this->loadMaterialInfo(terrain);
}

void TerrainShader::loadFogColor(const glm::vec3& fogColor) {
	glUniform3fv(locationFogColor, 1, &fogColor[0]);
}

TerrainShader::~TerrainShader() {
}
