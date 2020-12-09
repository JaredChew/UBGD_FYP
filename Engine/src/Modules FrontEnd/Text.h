#pragma once

#include <GLAD/glad.h>

//#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Compound/shaderProgram.h"
#include <map>
#include <string>

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text {

private:

	unsigned int VAO, VBO;
	std::map<GLchar, Character> characters;

public:

	Text(const std::string& fontPath, const unsigned int& size = 48);
	~Text();

	void changeTextScreenSize(const GLfloat& screenWidth, const GLfloat& screenHeight);

	void renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color = glm::vec3(1.0f));


};