#pragma once
#include "Shader.h"

class GuiShader : public Shader 
{
public:
	GuiShader();
	~GuiShader();

	void loadTransform(const glm::mat4& transform);
	void init(unsigned int cnt);
	void useFakeLighting(bool& fakeLighting);

protected:
	virtual void getAllUniformLocations();
	virtual void bindAttributes();

private:
	const std::string& filename = "gui_shader";

	GLint locationTransform;
	GLint locationFakeLighting;
};

