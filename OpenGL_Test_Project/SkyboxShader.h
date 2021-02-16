#pragma once
#include "Shader.h"

class SkyboxShader : public Shader
{
public:
	SkyboxShader();
	~SkyboxShader();

	void init(unsigned int cnt);
	void loadTransform(const glm::mat4& transform);
	void loadView(const glm::mat4& view);
	void loadProjection(const glm::mat4& projection);
	void loadFogColor(const glm::vec3& fogColor);

protected:
	virtual void getAllUniformLocations();
	virtual void bindAttributes();

private:
	const std::string& filename = "basic_shader";

	GLint locationTransform;
	GLint locationView;
	GLint locationProjection;
	GLint locationFogColor;
};

