#include "SkyboxShader.h"



SkyboxShader::SkyboxShader() : Shader("res/shaders/skybox_shader") {
}

void SkyboxShader::init(unsigned int cnt) {
	Shader::init(cnt);
	//bindAttributes();
	getAllUniformLocations();
}

void SkyboxShader::getAllUniformLocations() {
	locationTransform = glGetUniformLocation(program, "model");
	locationView = glGetUniformLocation(program, "view");
	locationProjection = glGetUniformLocation(program, "projection");
	locationFogColor = glGetUniformLocation(program, "fogColor");
}

void SkyboxShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
}

void SkyboxShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void SkyboxShader::loadView(const glm::mat4& view) {
	glm::mat4 skyBoxView = view;
	skyBoxView[3][0] = 0;
	skyBoxView[3][1] = 0;
	skyBoxView[3][2] = 0;
	glUniformMatrix4fv(locationView, 1, false, &skyBoxView[0][0]);
}

void SkyboxShader::loadFogColor(const glm::vec3& fogColor) {
	glUniform3fv(locationFogColor, 1, &fogColor[0]);
}

void SkyboxShader::loadProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(locationProjection, 1, false, &projection[0][0]);
}

SkyboxShader::~SkyboxShader() {
}
