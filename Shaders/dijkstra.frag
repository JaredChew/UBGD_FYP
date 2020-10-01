#version 460 core

#define GRID_WIDTH 60 //960
#define GRID_HEIGHT 60 //540

#define EMPTY 0
#define WALL 1
#define START 2
#define END 3
#define CLOSED 4
#define VISITED 5

precision mediump float;

varying vec2 fTexCoord;
varying vec4 fColor;
varying vec4 fPosition;

uniform sampler2D sampler2d;

uniform int grid[GRID_WIDTH * GRID_HEIGHT];

void main() {

	if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == EMPTY) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == WALL) {
		gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);
	}
	else if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == START) {
		gl_FragColor = vec4(0.0, 0.7, 0.0, 1.0);
	}
	else if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == END) {
		gl_FragColor = vec4(0.7, 0.0, 0.0, 1.0);
	}
	else if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == CLOSED) {
		gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
	}
	else if(grid[int(gl_FragCoord.x) * GRID_HEIGHT + int(gl_FragCoord.y)] == VISITED) {
		gl_FragColor = vec4(0.0, 0.7, 0.7, 1.0);
	}
	else {
		gl_FragColor = texture2D(sampler2d, fTexCoord);
	}

}
