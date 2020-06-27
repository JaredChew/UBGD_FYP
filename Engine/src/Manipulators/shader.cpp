#include "shader.h"

void Shader::defaultDraw(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgram_DefaultDraw = -1;

	if (shaderProgram_DefaultDraw == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/default.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_DefaultDraw, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Default\" shader program");
		}

	}

	glUseProgram(shaderProgram_DefaultDraw);

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_DEFAULT uniform \"sampler2d\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_DEFAULT uniform \"uMvpMatrix\" not found"); }

}

void Shader::editTexel(const glm::mat4 &mvpMatrix, const float colourRGB[3], const float position2D[2], const float dimensionXY[2]) {

	static GLuint shaderProgram_EditTexel = -1;

	if (shaderProgram_EditTexel == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/texelModify.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_EditTexel, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Texel Modify\" shader program");
		}

	}

	glUseProgram(shaderProgram_EditTexel);

	GLuint colour_Loc = glGetUniformLocation(shaderProgram_EditTexel, "colour");

	if (colour_Loc != -1) { glUniform1fv(colour_Loc, 3, colourRGB); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"colour\" not found"); }

	GLuint position_Loc = glGetUniformLocation(shaderProgram_EditTexel, "position");

	if (position_Loc != -1) { glUniform1fv(position_Loc, 2, position2D); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"position\" not found"); }

	GLuint dimension_Loc = glGetUniformLocation(shaderProgram_EditTexel, "dimension");

	if (dimension_Loc != -1) { glUniform1fv(dimension_Loc, 2, dimensionXY); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"dimension\" not found"); }

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_EditTexel, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"sampler2d\" not found"); }

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_EditTexel, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"uMvpMatrix\" not found"); }

}

void Shader::initTextureColour(const glm::mat4 &mvpMatrix, const float &r, const float &g, const float &b) {

	static GLuint shaderProgram_InitTextureColour = -1;

	if (shaderProgram_InitTextureColour == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/initTextureColour.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_InitTextureColour, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Init Texture Colour\" shader program");
		}

	}

	glUseProgram(shaderProgram_InitTextureColour);

	GLuint r_Loc = glGetUniformLocation(shaderProgram_InitTextureColour, "r");

	if (r_Loc != -1) { glUniform1f(r_Loc, r); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_INIT_TEXTURE_COLOUR uniform \"r\" not found"); }

	GLuint g_Loc = glGetUniformLocation(shaderProgram_InitTextureColour, "g");

	if (g_Loc != -1) { glUniform1f(g_Loc, g); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_INIT_TEXTURE_COLOUR uniform \"g\" not found"); }

	GLuint b_Loc = glGetUniformLocation(shaderProgram_InitTextureColour, "b");

	if (b_Loc != -1) { glUniform1f(b_Loc, b); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_INIT_TEXTURE_COLOUR uniform \"b\" not found"); }

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_InitTextureColour, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_INIT_TEXTURE_COLOUR uniform \"uMvpMatrix\" not found"); }

}

void Shader::cutFrameCell(const glm::mat4 &mvpMatrix, const int &textureWidth, const int &textureHeight, const int &frameRow, const int &frameCol) {

	static GLuint shaderProgram_DefaultDraw = -1;

	if (shaderProgram_DefaultDraw == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/spriteAnimation.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_DefaultDraw, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Sprite Animation\" shader program");
		}

	}

	glUseProgram(shaderProgram_DefaultDraw);

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"sampler2d\" not found"); }

	GLuint textureWidth_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "textureWidth");

	if (textureWidth_Loc != -1) { glUniform1i(textureWidth_Loc, textureWidth); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"textureWidth\" not found"); }

	GLuint textureHeight_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "textureHeight");

	if (textureHeight_Loc != -1) { glUniform1i(textureHeight_Loc, textureHeight); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"textureHeight\" not found"); }

	GLuint row_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "row");

	if (row_Loc != -1) { glUniform1i(row_Loc, frameRow); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"row\" not found"); }

	GLuint col_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "col");

	if (col_Loc != -1) { glUniform1i(col_Loc, frameCol); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"col\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_DefaultDraw, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"uMvpMatrix\" not found"); }

}

void Shader::filterLightPass(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgram_FilterLightPass = -1;

	if (shaderProgram_FilterLightPass == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/filterLight.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_FilterLightPass, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Filter Light Pass\" shader program");
		}

	}

	glUseProgram(shaderProgram_FilterLightPass);

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_FilterLightPass, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_LGHTPASS uniform \"sampler2d\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_FilterLightPass, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_LGHTPASS uniform \"uMvpMatrix\" not found"); }

}

void Shader::blendTexture(const glm::mat4 &mvpMatrix, const int &blendType, const GLuint &toBlend) {

	static GLuint shaderProgram_BlendTexture = -1;

	if (shaderProgram_BlendTexture == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/textureBlend.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_BlendTexture, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Blend Texture\" shader program");
		}

	}

	glUseProgram(shaderProgram_BlendTexture);

	GLuint blendType_Loc = glGetUniformLocation(shaderProgram_BlendTexture, "blendType");

	if (blendType_Loc != -1) { glUniform1i(blendType_Loc, blendType); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"blendType\" not found"); }

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, toBlend);

	GLuint toBlend_Loc = glGetUniformLocation(shaderProgram_BlendTexture, "toBlend");

	if (toBlend_Loc != -1) { glUniform1i(toBlend_Loc, 1); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"toBlend\" not found"); }

	glActiveTexture(GL_TEXTURE0 + 0);
	//glBindTexture(GL_TEXTURE_2D, toBlend2);

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_BlendTexture, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"sampler2d\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_BlendTexture, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"uMvpMatrix\" not found"); }

}

void Shader::blur(const glm::mat4 &mvpMatrix, const int &direction, const float &blurRadius, const float &totalWeight, const int &textureWidth, const int &textureHeight) {

	static GLuint shaderProgram_Blur = -1;

	if (shaderProgram_Blur == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/blur.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_Blur, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Blur\" shader program");
		}

	}

	glUseProgram(shaderProgram_Blur);

	GLuint uTextureW_Loc = glGetUniformLocation(shaderProgram_Blur, "uTextureW");

	if (uTextureW_Loc != -1) { glUniform1f(uTextureW_Loc, textureHeight); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uTextureW\" not found"); }

	GLuint uTextureH_Loc = glGetUniformLocation(shaderProgram_Blur, "uTextureH");

	if (uTextureH_Loc != -1) { glUniform1f(uTextureH_Loc, textureWidth); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uTextureH\" not found"); }

	GLuint uBlurDirection_Loc = glGetUniformLocation(shaderProgram_Blur, "uBlurDirection");

	if (uBlurDirection_Loc != -1) { glUniform1i(uBlurDirection_Loc, direction); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uBlurDirection\" not found"); }

	GLuint radius_Loc = glGetUniformLocation(shaderProgram_Blur, "radius");

	if (radius_Loc != -1) { glUniform1f(radius_Loc, blurRadius); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"radius\" not found"); }

	GLuint weight_Loc = glGetUniformLocation(shaderProgram_Blur, "weight");

	if (weight_Loc != -1) { glUniform1f(weight_Loc, totalWeight); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"weight\" not found"); }

	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_Blur, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"sampler2d\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_Blur, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uMvpMatrix\" not found"); }

}

void Shader::blendColour(const glm::mat4 &mvpMatrix, const int &blendType, const float &r, const float &g, const float &b, const float &a) { //, const bool &alphaBlend

	static GLuint shaderProgram_BlendColour = -1;

	if (shaderProgram_BlendColour == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/colourBlend.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_BlendColour, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Blend Colour\" shader program");
		}

	}

	glUseProgram(shaderProgram_BlendColour);

	GLuint r_Loc = glGetUniformLocation(shaderProgram_BlendColour, "r");

	if (r_Loc != -1) { glUniform1f(r_Loc, r); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"r\" not found"); }

	GLuint g_Loc = glGetUniformLocation(shaderProgram_BlendColour, "g");

	if (g_Loc != -1) { glUniform1f(g_Loc, g); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"g\" not found"); }

	GLuint b_Loc = glGetUniformLocation(shaderProgram_BlendColour, "b");

	if (b_Loc != -1) { glUniform1f(b_Loc, b); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"b\" not found"); }

	GLuint a_Loc = glGetUniformLocation(shaderProgram_BlendColour, "a");

	if (a_Loc != -1) { glUniform1f(a_Loc, a); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"a\" not found"); }

	GLuint blendType_Loc = glGetUniformLocation(shaderProgram_BlendColour, "blendType");

	if (blendType_Loc != -1) { glUniform1i(blendType_Loc, blendType); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"blendType\" not found"); }
	/*
	GLuint alphaBlend_Loc = glGetUniformLocation(shaderProgram_BlendColour, "alphaBlend");
	
	if (alphaBlend_Loc != -1) { glUniform1i(alphaBlend_Loc, alphaBlend ? 1 : 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"alphaBlend\" not found"); }
	*/
	GLuint sampler2d_Loc = glGetUniformLocation(shaderProgram_BlendColour, "sampler2d");

	if (sampler2d_Loc != -1) { glUniform1i(sampler2d_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"sampler2d\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_BlendColour, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"uMvpMatrix\" not found"); }

}

void Shader::drawSkyBox(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgram_DrawSkyBox = -1;

	if (shaderProgram_DrawSkyBox == -1) {

		GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/skybox.vert");
		GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/skybox.frag");

		if (!OpenGL::initProgramObject_Shader(shaderProgram_DrawSkyBox, fragmentShader, vertexShader)) {
			Logger::getInstance()->warningLog("Failed to init \"Sky Box\" shader program");
		}

	}

	glUseProgram(shaderProgram_DrawSkyBox);

	GLuint samplerCube1_Loc = glGetUniformLocation(shaderProgram_DrawSkyBox, "samplerCube1");
	glUniform1i(glGetUniformLocation(shaderProgram_DrawSkyBox, "samplerCube1"), 0);

	if (samplerCube1_Loc != -1) { glUniform1i(samplerCube1_Loc, 0); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SKYBOX uniform \"samplerCube1\" not found"); }

	GLuint uMvpMatrix_Loc = glGetUniformLocation(shaderProgram_DrawSkyBox, "uMvpMatrix");

	if (uMvpMatrix_Loc != -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }
	else { Logger::getInstance()->warningLog("SHADER_PROGRAM_SKYBOX uniform \"uMvpMatrix\" not found"); }

}