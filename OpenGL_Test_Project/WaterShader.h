#pragma once
#include "Shader.h"

#include "Lights.h"
#include "water.h"

class WaterShader : public Shader
{
public:
	WaterShader();
	~WaterShader();

	void loadTransform(const glm::mat4& transform);
	void loadView(const glm::mat4& view);
	void loadProjection(const glm::mat4& projection);
	void init(unsigned int cnt);
	void loadSpotLightInfo(SpotLight& spotLight);
	void loadLightInfo(Light& light);
	void loadLightInfo(Light& light, TexturedModel* model);
	void loadMaterialInfo(TexturedModel* model);
	void loadFogColor(const glm::vec3& fogColor);
	void loadCameraPos(const glm::vec3& cameraPos);
	void loadMoveFactor(float& factor);
	void connectTextures();

protected:
	virtual void getAllUniformLocations();
	virtual void bindAttributes();

private:
	const std::string& filename = "water_shader";

	GLint locationTransform;
	GLint locationView;
	GLint locationProjection;
	GLint locationLightPosition;
	GLint locationSpotLightPosition;
	GLint locationSpotLightIntensity;
	GLint locationSpotLightDirection;
	GLint locationSpotExponent;
	GLint locationSpotCutoff;
	GLint locationLightIntensity_S;
	GLint locationLightIntensity_A;
	GLint locationLightIntensity_D;
	GLint locationLightReflectivity_S;
	GLint locationLightReflectivity_A;
	GLint locationLightReflectivity_D;
	GLint locationFogColor;
	GLint locationCameraPos;
	GLint locationDudvmap;
	GLint locationNormalmap;
	GLint locationReflectionTexture;
	GLint locationRefractionTexture;
	GLint locationRefractionDepthTexture;
	GLint locationMoveFactor;
};

