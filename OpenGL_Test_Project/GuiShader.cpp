#include "GuiShader.h"



GuiShader::GuiShader() : Shader("res/shaders/gui_shader") {
}

void GuiShader::init(unsigned int cnt) {
	Shader::init(cnt);
	getAllUniformLocations();
}

void GuiShader::getAllUniformLocations() {
	locationTransform = glGetUniformLocation(program, "model");
	locationFakeLighting = glGetUniformLocation(program, "useFakeLighting");
}

void GuiShader::bindAttributes() {
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
}

void GuiShader::loadTransform(const glm::mat4& transform) {
	glUniformMatrix4fv(locationTransform, 1, false, &transform[0][0]);
}

void GuiShader::useFakeLighting(bool& fakeLighting) {
	glUniform1f(locationFakeLighting, fakeLighting);
}

GuiShader::~GuiShader() {
}


