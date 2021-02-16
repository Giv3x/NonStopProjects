#pragma once
#ifndef SHADER_H
#define SHADER_H
#define NUM_SHADERS 4

#include <string>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>

class Shader
{
public:
	Shader() {}
	Shader(const std::string& filename) : shaderFilename(filename) {}
	~Shader() {}

	void init(unsigned int cnt);
	void bind();
	void unbind();
	void clean();

	GLuint program;

protected:
	virtual void getAllUniformLocations() = 0;
	virtual void bindAttributes() = 0;
	
	enum {
		TRANSFORM_U,
		VIEW_U,
		PROJECTION_U,
		LIGHT_POSITION,
		LIGHT_INTENSITY_S,
		LIGHT_INTENSITY_A,
		LIGHT_INTENSITY_D,
		REFLECTIVITY_S,
		REFLECTIVITY_A,
		REFLECTIVITY_D,
		FAKE_LIGHTING_U,
		FOG_COLOR_U,
		NUM_UNIFORMS
	};
	GLuint uniforms[NUM_UNIFORMS];
	GLuint shaders[NUM_SHADERS];

private:
	std::vector<GLenum> shaderTypes{
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER,
		GL_COMPUTE_SHADER,
		GL_GEOMETRY_SHADER
	}; 

	std::vector<char*> extensions{
		".vs",
		".sf",
		".cs",
		".gs"
	};

	unsigned int cntShaders = 0;
	std::string shaderFilename;

	void checkShaderError(GLuint target, GLuint flag, bool isProgram, const std::string errorMessage);
	GLuint computeShader(const std::string& shaderText, GLenum shaderType);
	std::string loadShader(char* ext);
};

#endif

