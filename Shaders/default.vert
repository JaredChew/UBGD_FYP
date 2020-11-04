#version 330 core

attribute vec3 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;

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
