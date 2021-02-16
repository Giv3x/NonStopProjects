#version 330

attribute vec2 position;

varying vec2 texCoords;

uniform mat4 model;
uniform float useFakeLighting;

void main() {
	gl_Position = model * vec4(position, 0.0, 1.0);

	texCoords = vec2((position.x + 1)/2, 1 - (position.y + 1)/2);
}