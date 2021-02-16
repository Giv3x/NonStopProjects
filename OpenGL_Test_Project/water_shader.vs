#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normals;

varying vec2 texCoords;
varying vec4 clipSpace;
varying vec3 toLightVector;
varying vec3 toCameraVector;
varying vec3 toSpotLighVector;
varying float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;
uniform vec3 spotLightPosition;
uniform vec3 cameraPos;

const float density = 0.001;
const float gradient = 4;

void main() {
	vec4 worldPosition = model * vec4(position, 1.0);
	vec4 positionRelative2Camera = view * worldPosition;

	float distance2Camera = length(positionRelative2Camera.xyz);
	clipSpace = projection * positionRelative2Camera;

	gl_Position = clipSpace;

	visibility = clamp(exp(-pow(distance2Camera * density, gradient)), 0, 1);
	toLightVector =  normalize(lightPosition - worldPosition.xyz);
	toCameraVector = normalize(cameraPos - worldPosition.xyz);
	toSpotLighVector = worldPosition.xyz - spotLightPosition;
	texCoords = texCoord;
}