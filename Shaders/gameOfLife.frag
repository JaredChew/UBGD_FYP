#version 460 core

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform float gridSizeX;
uniform float gridSizeY;

bool samePosition(const in vec2 position) {

	if(position == fTexCoord) { return true; }

	return false;

}

bool withinBounds(const in vec2 position) {

	if(position.x < 0.0 || position.x >= gridSizeX) { return false; }
	if(position.y < 0.0 || position.y >= gridSizeY) { return false; }

	return true;

}

void cellStatusUpdate(inout vec4 colour, inout int statusCount) {

	bool cellAlive = texture2D(sampler2d, fTexCoord).r == 1.0 ? true : false;

	if(cellAlive) {

		if(statusCount == 2 || statusCount == 3) { colour = vec4(1.0, 1.0, 1.0, 1.0); }
		else { colour = vec4(0.0, 0.0, 0.0, 1.0); }

	}
	else {

		if(statusCount == 3) { colour = vec4(1.0, 1.0, 1.0, 1.0); }
		else { colour = vec4(0.0, 0.0, 0.0, 1.0); }

	}

}

void neighbourCheck(inout vec4 colour, inout int statusCount) {

	float x = fTexCoord.x - (1.0 / gridSizeX);
	float y = fTexCoord.y - (1.0 / gridSizeY);

	for(float i = 0.0; i < 3.0; i += 1.0) {

		for(float j = 0.0; j < 3.0; j += 1.0) {

			vec2 uv = vec2(x + (i / gridSizeX), y + (j / gridSizeY));

			if(!withinBounds(uv)) { continue; }
			else if(samePosition(uv)) { continue; }

			if(texture2D(sampler2d, uv).r == 1.0) { ++statusCount; }

		}

	}

}

void main() {

	vec4 colour;

	int statusCount = 0;

	neighbourCheck(colour, statusCount);
	cellStatusUpdate(colour, statusCount);
	
	gl_FragColor = colour; //texture2D(sampler2d, fTexCoord)

}

// **		DEBUG 		** //

/*
	if(cellAlive) {

		if(statusCount == 2 || statusCount == 3) {
			colour = vec4(1.0, 1.0, 1.0, 1.0); //white - allive to alive
		}
		else {
			colour = vec4(0.0, 0.0, 1.0, 1.0); //blue - alive to dead
		}

	}
	else {

		if(statusCount == 3) {
			colour = vec4(1.0, 0.0, 0.0, 1.0); //red - dead to alive
		}
		else {
			colour = vec4(0.0, 1.0, 0.0, 1.0); //green - dead to dead
		}

	}
*/
/*
	if(statusCount == 0) {
		colour = vec4(0.0, 0.0, 0.0, 1.0); //black
	}
	else if(statusCount == 1) {
		colour = vec4(1.0, 0.0, 0.0, 1.0); //red
	}
	else if(statusCount == 2) {
		colour = vec4(0.0, 1.0, 0.0, 1.0); //green
	}
	else if(statusCount == 3) {
		colour = vec4(0.0, 0.0, 1.0, 1.0); //blue
	}
	else if(statusCount >= 4) {
		colour = vec4(1.0, 1.0, 1.0, 1.0); //white
	}

	if(texture2D(sampler2d, fTexCoord).r > 0.0) {
		//colour = vec4(0.7, 0.3, 0.5, 1.0);
	}
*/
/*
	if(fTexCoord.y < 0.25) {
		colour = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if(fTexCoord.y >= 0.25 && fTexCoord.y < 0.5) {
		colour = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else if(fTexCoord.y >= 0.5 && fTexCoord.y < 0.75) {
		colour = vec4(0.0, 0.0, 1.0, 1.0);
	}
	else if(fTexCoord.y >= 0.75 && fTexCoord.y < 1.0) {
		colour = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if(fTexCoord.y >= 1.0) {
		colour = vec4(0.25, 0.5, 0.3, 1.0);
	}
*/
/*
	if(fTexCoord.x < 0.25) {
		colour = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if(fTexCoord.x >= 0.25 && fTexCoord.x < 0.5) {
		colour = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else if(fTexCoord.x >= 0.5 && fTexCoord.x < 0.75) {
		colour = vec4(0.0, 0.0, 1.0, 1.0);
	}
	else if(fTexCoord.x >= 0.75 && fTexCoord.x < 1.0) {
		colour = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if(fTexCoord.x >= 1.0) {
		colour = vec4(0.25, 0.5, 0.3, 1.0);
	}
*/
/*
	if(texture2D(sampler2d, fTexCoord).r > 0.0) {
		colour = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else {
		colour = vec4(0.0, 0.0, 0.0, 1.0);
	}
*/