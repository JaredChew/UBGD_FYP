attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vTexCoord;

varying vec3 fTexCoord;
varying vec4 fColor;

uniform mat4 uMvpMatrix;

void main() {

	fTexCoord = vPosition.xyz;
	fTexCoord.y = -fTexCoord.y;
	
    gl_Position = uMvpMatrix * vPosition;
	
}
