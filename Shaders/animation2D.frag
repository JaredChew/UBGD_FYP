#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float row;
uniform float col;

uniform float eachRowNor;
uniform float eachColNor;

uniform int index;

void main() 
{
	/*
	float eachRow = 1.0f / row;
	float eachCol = 1.0f / col;
	
	float norRow = fTexCoord.x / row;
	float norCol = fTexCoord.y / col;
	
	int x = index % row;
	int y = index / row;
	
	float currentRow = x * eachRow;
	float currentCol = y * eachCol;
	
	float currentX = currentRow + norRow;
	float currentY = currentCol + norCol;
	*/
	
	// short form
	int x = index % row;
	int y = index / row;
	
	float currentX = (float(x) * eachRowNor) + (fTexCoord.x / row);
	float currentY = (float(y) * eachColNor) + (fTexCoord.y / col);

	vec2 uv = vec2(currentX, currentY);
	
	gl_FragColor = texture2D(sampler2d, uv);

}
