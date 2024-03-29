#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/mat4x4.hpp>

class LightingContainer;
class Material;

namespace Shader {

	void defaultDraw(const glm::mat4 &mvpMatrix);
	void phongLightDraw(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const Material& material, LightingContainer& lightingContainer);
	void animation2DDraw(const glm::mat4& mvpMatrix, const float& row, const float& column, const float& eachRowNor, const float& eachColNor, const float& index);
	void drawSkyBox(const glm::mat4& mvpMatrix);

	void colourTexture(const glm::mat4 &mvpMatrix, const float &r, const float &g, const float &b);
	void editTexel(const glm::mat4 &mvpMatrix, const float colourRGB[3], const float position2D[2], const float dimensionXY[2]);
	void cutFrameCell(const glm::mat4 &mvpMatrix, const int &textureWidth, const int &textureHeight, const int &frameRow, const int &frameCol);
	void filterLightPass(const glm::mat4 &mvpMatrix);
	void blendTexture(const glm::mat4 &mvpMatrix, const int &blendType, const GLuint &toBlend);
	void blur(const glm::mat4 &mvpMatrix, const int &direction, const float &blurRadius, const float &totalWeight, const int &textureWidth, const int &textureHeight);
	void blendColour(const glm::mat4 &mvpMatrix, const int &blendType, const float &r, const float &g, const float &b, const float &a); //, const bool &alphaBlend

}