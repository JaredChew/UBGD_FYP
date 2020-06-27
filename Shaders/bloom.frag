precision mediump float;

varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;

void main() {

	vec4 texColor = texture2D(sampler2d, fTexCoord);
	
	float colourIntensity = (texColor.r + texColor.g + texColor.b) / 3.0;

	if(colourIntensity < 0.9) { gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); }
	else { gl_FragColor = texColor; }

}
