precision highp float;

varying vec3 fTexCoord;

uniform samplerCube samplerCube1;

void main()
{
	gl_FragColor = textureCube(samplerCube1, fTexCoord);
}
