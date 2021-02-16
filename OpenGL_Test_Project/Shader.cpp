#include "Shader.h"

#include <fstream>
#include <iostream>

void Shader::init(unsigned int cnt) {
	cntShaders = cnt;

	program = glCreateProgram();

	for (unsigned int i = 0; i < cntShaders; i++) 
		shaders[i] = computeShader(loadShader(extensions[i]), shaderTypes[i]);

	for (unsigned int i = 0; i < cntShaders; i++)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");
	glBindAttribLocation(program, 3, "tangents");
	
	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed");

	glValidateProgram(program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
}

void Shader::bind() {
	glUseProgram(program);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::clean() {
	for (unsigned int i = 0; i < cntShaders; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::checkShaderError(GLuint target, GLuint flag, bool isProgram, const std::string errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	isProgram ? glGetProgramiv(target, flag, &success) : glGetShaderiv(target, flag, &success);

	if (success == GL_FALSE) {
		isProgram ? glGetProgramInfoLog(target, sizeof(error), NULL, error) : glGetShaderInfoLog(target, sizeof(error), NULL, error);
		std::cerr << errorMessage << ':' << error << std::endl;
	}


}

std::string Shader::loadShader(char* ext) {
	std::ifstream fin(shaderFilename + ext);

	std::string output;
	std::string line;

	if (fin.is_open()) {
		while (fin.good()) {
			getline(fin, line);
			output.append(line + '\n');
		}
	}
	else {
		std::cerr << "Error: Can't load the shader" << std::endl;	
	}

	return output;
}

GLuint Shader::computeShader(const std::string& shaderText, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	
	if (shader == 0)
		std::cerr << "Error: shader creation failed" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = shaderText.c_str();
	shaderSourceStringLengths[0] = shaderText.size();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}