#version 330 core

precision mediump float;

in vec4 fColor;
in vec2 fTexCoord;

uniform sampler2D sampler2d;

uniform float row;
uniform float col;

uniform float eachRowNor;
uniform float eachColNor;

uniform int index;

uniform vec4 uColor;

void main() 
{
	int x = index % int(row);
	int y = index / int(row); 

	float currentX = (float(x) * eachRowNor) + (fTexCoord.x / row);
	float currentY = (float(y) * eachColNor) + (fTexCoord.y / col);

	vec2 uv = vec2(currentX, currentY);
	
	vec4 colorTexture = texture2D(sampler2d, uv);
	
	vec4 colorCombine = colorTexture * uColor * fColor;
	
	gl_FragColor = colorCombine;

}
