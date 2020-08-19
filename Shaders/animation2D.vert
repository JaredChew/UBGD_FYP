#version 460 core

attribute vec4 vPosition;
attribute vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fPosition;

uniform mat4 uMvpMatrix;

void main() {

	fTexCoord = vTexCoord;
	fPosition = vPosition;

	gl_Position = uMvpMatrix * vPosition;

}
