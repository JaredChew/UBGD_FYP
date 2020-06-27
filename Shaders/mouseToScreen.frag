#version 460 core

precision mediump float;

varying vec4 fColor;
varying vec2 fTexCoord;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float mousePosX;
uniform float mousePosY;

uniform int mouseIsPressed;

float pixelPerTexelX = 1920.0 / 500.0; //for every value of pixelPerTexelX is 1 texel
float pixelPerTexelY = 1080.0 / 500.0; //for every value of pixelPerTexelY is 1 texel

float texelSize = 1.0 / 500.0; //1 uv coordinate of a texel

float rowsPerWidth = 500.0 / 1920.0;
float columnsPerWidth = 500.0 / 1080.0;

float glslMousePosY = 1080.0 - mousePosY; //inverse mouse position to fit glsl coordinate starting position

bool sameMouseToScreenPos() {

	if(gl_FragCoord.x != mousePosX) { return false; }
	if(gl_FragCoord.y != glslMousePosY) { return false; }

	return true;

}

bool withinTexel() {

	float u = ceil(rowsPerWidth * mousePosX) / 500.0;
	float v = ceil(columnsPerWidth * glslMousePosY) / 500.0;

	float textureU = fTexCoord.x;
	float textureV = fTexCoord.y;

	if(u != fTexCoord.x) { return false; }
	//if(v != textureV) { return false; }

	return true;

}

bool withinUV() {

	float u = 0.5;
	float v = 0.5;

	float textureU = fTexCoord.x;
	float textureV = fTexCoord.y;

	if(u != textureU) { return false; }
	//if(v != textureV) { return false; }

	return true;

}

void main() {

	vec4 colour;// = withinUV();

	if(!withinTexel()) { colour = vec4(0.0, 1.0, 0.0, 1.0); }
	else { colour = vec4(1.0, 0.0, 0.0, 1.0); }

	gl_FragColor = colour;

}

// **		DEBUG 		** //

/*

if(mousePosX >= 0.0 && mousePosX < 480.0) {
	colour = vec4(1.0, 0.0, 0.0, 1.0);
}
else if(mousePosX >= 480.0 && mousePosX < 960.0) {
	colour = vec4(0.0, 1.0, 0.0, 1.0);
}
else if(mousePosX >= 960.0 && mousePosX < 1440.0) {
	colour = vec4(0.0, 0.0, 1.0, 1.0);
}
else if(mousePosX >= 1440.0 && mousePosX < 1920.0) {
	colour = vec4(1.0, 1.0, 1.0, 1.0);
}
else if(mousePosX >= 1920.0) {
	colour = vec4(1.0, 1.0, 0.0, 1.0);
}
else {
	colour = vec4(0.0, 1.0, 1.0, 1.0);
}

*/