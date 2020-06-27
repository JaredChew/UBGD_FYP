precision mediump float;

varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform sampler2D toBlend;

uniform int blendType;

#define BLEND_TYPE_ADDITIVE 0
#define BLEND_TYPE_MULTIPLY 1

void main() {

	if(blendType == BLEND_TYPE_ADDITIVE) { gl_FragColor = texture2D(sampler2d, fTexCoord) + texture2D(toBlend, fTexCoord); }
	else if(blendType == BLEND_TYPE_MULTIPLY) { gl_FragColor = texture2D(sampler2d, fTexCoord) * texture2D(toBlend, fTexCoord); }
	 
}
