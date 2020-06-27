#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float r;
uniform float g;
uniform float b;

void main() {
	
	gl_FragColor = vec4(r, g, b, 1.0);

}
