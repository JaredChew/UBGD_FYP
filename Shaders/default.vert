#version 330 core

layout (Location = 0) in vec3 vPosition;
layout (Location = 1) in vec4 vColor;
layout (Location = 2) in vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform mat4 uMvpMatrix;

void main() {
	
	fColor = vColor;
	fTexCoord = vTexCoord;
	fPosition = vec4(vPosition, 1.0f);

	gl_Position = uMvpMatrix * vec4(vPosition, 1.0f);

}
