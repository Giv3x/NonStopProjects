#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normals;
attribute vec3 tangents;

varying vec2 texCoords;
varying vec3 normal;
varying vec3 toLightVector;
varying vec3 toCameraVector;
varying vec3 toSpotLighVector;
varying float visibility;
varying vec3 normalTex;
varying vec3 tangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 clipingPlaneVec;
uniform vec3 lightPosition;
uniform vec3 spotLightPosition;
uniform vec3 cameraPos;
uniform float useFakeLighting;

//uniform sampler2D normalMap;

const float density = 0.0015;
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

	vec3 tang = normalize(model * vec4(tangents, 0)).xyz;
	vec3 bitang = normalize(cross(normal, tang));
	mat3 toTangentSpace = mat3(
		tang.x, bitang.x, normal.x,
		tang.y, bitang.y, normal.y,
		tang.z, bitang.z, normal.z
	);

	visibility = clamp(exp(-pow(distance2Camera * density, gradient)), 0, 1);
	toLightVector =  toTangentSpace * normalize(lightPosition - worldPosition.xyz);
	toCameraVector = toTangentSpace * normalize(cameraPos - worldPosition.xyz);
	toSpotLighVector = worldPosition.xyz - spotLightPosition;
	if(length(toSpotLighVector) <= 100 && length(toSpotLighVector) >= -100  ) {
		toSpotLighVector = normalize(toSpotLighVector);
	} else {
		toSpotLighVector.x = -101;
	}

	texCoords = texCoord;
	tangent = tang;
}