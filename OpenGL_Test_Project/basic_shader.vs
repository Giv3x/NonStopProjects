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
uniform float useFakeLighting;

const float density = 0.001;
const float gradient = 4;

void main() {
	vec4 worldPosition = model *  vec4(position, 1.0);
	
	gl_ClipDistance[0] = dot(worldPosition, clipingPlaneVec);
	
	vec4 positionRelative2Camera = view * worldPosition;
	float distance2Camera = length(positionRelative2Camera.xyz);

	gl_Position = projection * positionRelative2Camera;

	if(useFakeLighting > 0.5) {
		normal = normalize((model * vec4(0, 1, 0, 0)).xyz);
	} else {
		normal = normalize((model * vec4(normals,0.0)).xyz);
	}

	visibility = clamp(exp(-pow(distance2Camera * density, gradient)), 0, 1);
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = normalize(-positionRelative2Camera).xyz;//normalize((inverse(view) * vec4(0, 0, 0, 1)).xyz - worldPosition.xyz);
	toSpotLighVector = worldPosition.xyz - spotLightPosition;
	if(length(toSpotLighVector) <= 100 && length(toSpotLighVector) >= -100  ) {
		toSpotLighVector = normalize(toSpotLighVector);
	} else {
		toSpotLighVector.x = -101;
	}

	texCoords = texCoord;
}