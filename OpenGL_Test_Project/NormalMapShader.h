#pragma once
#include "Shader.h"

#include "Lights.h"
#include "Entity.h"

class NormalMapShader : public Shader
{
public:
	NormalMapShader();
	~NormalMapShader();

	void loadTransform(const glm::mat4& transform);
	void loadView(const glm::mat4& view);
	void loadProjection(const glm::mat4& projection);
	void init(unsigned int cnt);
	void loadSpotLightInfo(SpotLight& spotLight);
	void loadLightInfo(Light& light);
	void loadLightInfo(Light& light, TexturedModel* model);
	void loadMaterialInfo(TexturedModel* model);
	void useFakeLighting(bool& fakeLighting);
	void loadFogColor(const glm::vec3& fogColor);
	void loadCameraPos(const glm::vec3& cameraPos);
	void loadTextures();
	void loadClipDistance(const glm::vec4& clipDistance);

protected:
	virtual void getAllUniformLocations();
	virtual void bindAttributes();

private:
	const std::string& filename = "basic_shader";

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
	GLint locationFakeLighting;
	GLint locationFogColor;
	GLint locationMaterialTexture;
	GLint locationNormalMap;
	GLint locationCameraPos;
	GLint locationClipDistance;
};

