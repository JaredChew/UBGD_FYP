#include "text.h"

#include "../Manipulators/openGL.h"
#include "../Manipulators/geometry.h"
#include "../Manipulators/shader.h"

Text::Text(const char* directory, const int& fontSize, const glm::vec4& colour) {

	font = loadFont(directory, fontSize);

	textColour.r = colour.r;
	textColour.g = colour.g;
	textColour.b = colour.b;
	textColour.a = colour.a;

}

Text::~Text() {

	glDeleteTextures(1, &texture);

	TTF_CloseFont(font);

	delete font;
	font = nullptr;

}

TTF_Font* Text::loadFont(const char* directory, const int& fontSize) {

	TTF_Font* font = TTF_OpenFont(directory, fontSize);

	if (font) {

		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL Font failed to load font", NULL);

	}

	return font;

}

void Text::setMessage(const std::string& message) {

	SDL_Surface* renderedText = TTF_RenderText_Blended(font, message.c_str(), textColour);

	OpenGL::loadTexture(renderedText->pixels, texture, renderedText->w, renderedText->h);

	SDL_FreeSurface(renderedText);
	
	delete renderedText;
	renderedText = nullptr;

}

void Text::render(const GLuint& targetRender) {

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, targetRender, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		glBindTexture(GL_TEXTURE_2D, texture);

		Shader::defaultDraw(glm::mat4(1.0f)); //mvpMatrix
		Geometry::drawSquare(texture);

	}

}