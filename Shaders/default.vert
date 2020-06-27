#version 460 core

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform mat4 uMvpMatrix;

void main() {
	
	fColor = vColor;
	fTexCoord = vTexCoord;
	fPosition = vPosition;

	gl_Position = uMvpMatrix * vPosition;

}
