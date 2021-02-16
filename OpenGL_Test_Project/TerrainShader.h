#pragma once
#include "Shader.h"

#include "Lights.h"
#include "Terrain.h"

class TerrainShader : public Shader
{
public:
	TerrainShader();
	~TerrainShader();

	void loadTransform(const glm::mat4& transform);
	void loadView(const glm::mat4& view);
	void loadProjection(const glm::mat4& projection);
	void init(unsigned int cnt);
	void loadSpotLightInfo(SpotLight& spotLight);
	void loadLightInfo(Light& light);
	void loadLightInfo(Light& light, Terrain* terrain);
	void loadMaterialInfo(Terrain* terrain);
	void loadFogColor(const glm::vec3& fogColor);
	void loadTextures();
	void loadClipDistance(const glm::vec4& clipDistance);

protected:
	virtual void getAllUniformLocations();
	virtual void bindAttributes();

private:
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
	GLint locationBgTexture;
	GLint locationRTexture;
	GLint locationGTexture;
	GLint locationBTexture;
	GLint locationBlendMap;
	GLint locationClipDistance;

	const std::string& filename = "basic_shader";
};


