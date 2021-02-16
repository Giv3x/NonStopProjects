#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normals;

varying vec2 texCoords;
varying vec3 normal;
varying vec3 toLightVector;
varying vec3 toCameraVector;
varying vec3 toSpotLighVector;
varying float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 clipingPlaneVec;
uniform vec3 lightPosition;
uniform vec3 spotLightPosition;

const float density = 0.001;
const float gradient = 4;

void main() {
	vec4 worldPosition = model *  vec4(position, 1.0);
	
	gl_ClipDistance[0] = dot(worldPosition, clipingPlaneVec);

	vec4 positionRelative2Camera = view * worldPosition;
	float distance2Camera = length(positionRelative2Camera.xyz);
	gl_Position = projection * worldPosition;
	
	visibility = clamp(exp(-pow(distance2Camera * density, gradient)), 0, 1);
	normal = normalize((model * vec4(normals,0.0)).xyz);
	toLightVector = (lightPosition - worldPosition.xyz);
	toCameraVector = normalize(-positionRelative2Camera.xyz);
	toSpotLighVector = normalize(worldPosition.xyz - spotLightPosition);
	if(length(toSpotLighVector) <= 100 && length(toSpotLighVector) >= -100) {
		toSpotLighVector = normalize(toSpotLighVector);
	} else {
		toSpotLighVector.x = -101;
	}
	texCoords = texCoord;
}