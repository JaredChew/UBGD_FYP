#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float colour[3];
uniform float position[2];
uniform float dimension[2];

void main() {
	
	if(fTexCoord.x == (position[0] / dimension[0]) && fTexCoord.y == (position[1] / dimension[1])) {
		gl_FragColor = vec4(colour[0] / 255.0, colour[1] / 255.0, colour[2] / 255.0, 1.0);
		return;
	}
	
	gl_FragColor = texture2D(sampler2d, fTexCoord);

}
