#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/constants.hpp>

namespace Geometry {

	void drawTriangle(const GLuint &texture);
	void drawSquare(const GLuint &texture);
	void drawCircle(const GLuint &texture, const float &smoothness);
	//void drawStadium(const GLuint& texture, const float& smoothness);

	void drawPyramid(const GLuint &texture);
	void drawCube(const GLuint &texture);
	void drawSphere(const GLuint &texture, const float &smoothness);
	void drawCone(const GLuint &texture, const float &smoothness);
	void drawCylinder(const GLuint &texture, const float &smoothness);

	void drawSkyBox(const GLuint &texture);

}