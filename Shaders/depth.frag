precision mediump float;

varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform sampler2D bgTexture;
uniform sampler2D bgDepthTexture;

uniform float windowW;
uniform float windowH;

void main() {

	float bgU = gl_FragCoord.x/windowW;
	float bgV = gl_FragCoord.y/windowH;

	float bgDepth = texture2D(bgDepthTexture, vec2(bgU,bgV)).r;

	if(bgDepth >= gl_FragCoord.z) {
		gl_FragColor = texture2D(bgTexture, fTexCoord);
		//gl_FragColor = bgColor;// + vec4(0.1);
	}
	else {
		gl_FragColor = texture2D(sampler2d, fTexCoord);
		//discard;
	}

}