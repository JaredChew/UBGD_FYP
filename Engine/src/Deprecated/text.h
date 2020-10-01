#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <SDL_ttf.h>

#include "glm/vec4.hpp"

class Text {

private:

	TTF_Font* font;

	GLuint texture;
	
	SDL_Color textColour;

	std::string message;

private:

	TTF_Font* loadFont(const char* fontFileDir, const int& fontSize);

public:

	Text(const char* directory, const int& fontSize, const glm::vec4& colour);
	~Text();

	void setMessage(const std::string& textString);

	void render(const GLuint& targetRender);

};