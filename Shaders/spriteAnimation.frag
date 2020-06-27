#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float textureWidth;
uniform float textureHeight;

uniform float row;
uniform float col;

void main() {

	float startX = textureWidth / row;
	float startY = textureHeight / col;

	vec2 uv = vec2(fTexCoord.x + startX, fTexCoord.y + startY);
	
	gl_FragColor = texture2D(sampler2d, uv);

}
