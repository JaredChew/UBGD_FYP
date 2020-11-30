#include "Text.h"

#include "ft2build.h"
//#include <freetype/freetype.h>
#include FT_FREETYPE_H

Text::Text(const std::string& fontPath, const unsigned int& size)
{
	if (shader.getGprogramID() == 0) {

		shader.init("Text.vert", "Text.frag");
		changeTextScreenSize(1280, 700);
	}

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		printf("ERROR::FREETYPE: Could not init FreeType Library\n");
	}

	//"Fonts/GloriaHallelujah.ttf"

	FT_Face face;
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {

		printf("ERROR::FREETYPE: Failed to load font\n");

	}
	else {

		FT_Set_Pixel_Sizes(face, 0, size);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; c++)
		{

			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				printf("ERROR::FREETYTPE: Failed to load Glyph\n");
				continue;
			}

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};

			characters.insert(std::pair<char, Character>(c, character));

		}

		glBindTexture(GL_TEXTURE_2D, 0);

	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::~Text()
{
	glDeleteProgram(shader.getGprogramID());
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	for (size_t i = 0; i < characters.size(); i++)
	{
		glDeleteTextures(1, &characters[i].TextureID);
	}
	
}

void Text::changeTextScreenSize(const GLfloat& screenWidth, const GLfloat& screenHeight)
{
	screenMatrix = glm::ortho<GLfloat>(0.0f, screenWidth, 0.0f, screenHeight, 0.0f, 100.0f);
}

void Text::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color)
{
	// activate corresponding render state	
	shader.use();
	shader.uniform_Matrix4fv("projection", screenMatrix);
	shader.uniform_3float("textColor", color.r, color.g, color.b);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		float xpos = x + (ch.Bearing.x * 0.01f) * scale;
		float ypos = y - ((ch.Size.y - ch.Bearing.y) * 0.01f) * scale;

		float w = (ch.Size.x * 0.01f) * scale;
		float h = (ch.Size.y * 0.01f) * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos,		0.0f, 1.0f },
			{ xpos + w, ypos,		1.0f, 1.0f },
			{ xpos,     ypos + h,	0.0f, 0.0f },

			{ xpos + w, ypos + h,	1.0f, 0.0f },
			{ xpos,     ypos + h,	0.0f, 0.0f },
			{ xpos + w, ypos,		1.0f, 1.0f }
		};
		// render glyph texture over quad
		shader.uniform_Sampler(ch.TextureID, "text");

		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += ((ch.Advance >> 6) * 0.01f) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}