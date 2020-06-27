#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float r;
uniform float g;
uniform float b;
uniform float a;

uniform int blendType;
//uniform int alphaBlend;

#define BLEND_TYPE_ADDITIVE 0
#define BLEND_TYPE_MULTIPLY 1

void main() {
	
	//vec4 final;

	if(blendType == BLEND_TYPE_ADDITIVE) { gl_FragColor = texture2D(sampler2d, fTexCoord) + vec4(r, g, b, a); } //vec4(r, g, b, alphaBlend == 1 ? a : 0.0f)
	else if(blendType == BLEND_TYPE_MULTIPLY) { gl_FragColor = texture2D(sampler2d, fTexCoord) * vec4(r, g, b, a); } //vec4(r, g, b, alphaBlend == 1 ? a : 1.0f)

	//if(alphaBlend == 0) { final.z = texture2D(sampler2d, fTexCoord).a; }

	//gl_FragColor = final;

}
