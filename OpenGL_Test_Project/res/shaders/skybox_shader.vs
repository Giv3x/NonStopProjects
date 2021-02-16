#version 420

attribute vec3 position;

varying vec3 texCoords;
varying float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec4 worldPosition = vec4(position, 1.0);
	vec4 positionRelative2Camera = view * worldPosition;

	float distance2Camera = length(positionRelative2Camera.xyz);

	gl_Position = projection * positionRelative2Camera;

	texCoords = position;
}