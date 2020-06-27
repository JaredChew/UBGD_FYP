#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "openGL.h"

namespace Shader {

	void defaultDraw(const glm::mat4 &mvpMatrix);

	void initTextureColour(const glm::mat4 &mvpMatrix, const float &r, const float &g, const float &b);
	void editTexel(const glm::mat4 &mvpMatrix, const float colourRGB[3], const float position2D[2], const float dimensionXY[2]);
	void cutFrameCell(const glm::mat4 &mvpMatrix, const int &textureWidth, const int &textureHeight, const int &frameRow, const int &frameCol);

	void filterLightPass(const glm::mat4 &mvpMatrix);
	void blendTexture(const glm::mat4 &mvpMatrix, const int &blendType, const GLuint &toBlend);
	void blur(const glm::mat4 &mvpMatrix, const int &direction, const float &blurRadius, const float &totalWeight, const int &textureWidth, const int &textureHeight);
	void blendColour(const glm::mat4 &mvpMatrix, const int &blendType, const float &r, const float &g, const float &b, const float &a); //, const bool &alphaBlend

	void drawSkyBox(const glm::mat4 &mvpMatrix);

}