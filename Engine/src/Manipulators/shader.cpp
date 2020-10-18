#include "shader.h"

#include "system.h"

#include "../Utilities/logger.h"

#include <glm/gtc/type_ptr.hpp>

void Shader::defaultDraw(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgramID = -1;

	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	
	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/default.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Default\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (sampler2d_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_DEFAULT uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_DEFAULT uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::animation2DDraw(const glm::mat4& mvpMatrix, const float& row, const float& column, const float& eachRowNor, const float& eachColNor, const float& index) {

	static GLuint shaderProgramID = -1;

	static GLuint row_Loc = -1;
	static GLuint column_Loc = -1;
	static GLuint eachRowNor_Loc = -1;
	static GLuint eachColNor_Loc = -1;
	static GLuint index_Loc = -1;
	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1f(row_Loc, row);
		glUniform1f(column_Loc, column);
		glUniform1f(eachRowNor_Loc, eachRowNor);
		glUniform1f(eachColNor_Loc, eachColNor);
		glUniform1i(index_Loc, index);
		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/animation2D.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/animation2D.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Default\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			row_Loc = glGetUniformLocation(shaderProgramID, "row");
			column_Loc = glGetUniformLocation(shaderProgramID, "column");
			eachRowNor_Loc = glGetUniformLocation(shaderProgramID, "eachRowNor");
			eachColNor_Loc = glGetUniformLocation(shaderProgramID, "eachColNor");
			index_Loc = glGetUniformLocation(shaderProgramID, "index");
			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (row_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"row\" not found"); }
			if (column_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"column\" not found"); }
			if (eachRowNor_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"eachRowNor\" not found"); }
			if (eachColNor_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"eachColNor\" not found"); }
			if (index_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"index\" not found"); }
			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_ANIMATION2D uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}
	
}

void Shader::editTexel(const glm::mat4 &mvpMatrix, const float colourRGB[3], const float position2D[2], const float dimensionXY[2]) {

	static GLuint shaderProgramID = -1;

	static GLuint colour_Loc = -1;
	static GLuint position_Loc = -1;
	static GLuint dimension_Loc = -1;
	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		if (colour_Loc == -1) { glUniform1fv(colour_Loc, 3, colourRGB); }
		if (position_Loc == -1) { glUniform1fv(position_Loc, 2, position2D); }
		if (dimension_Loc == -1) { glUniform1fv(dimension_Loc, 2, dimensionXY); }
		if (sampler2d_Loc == -1) { glUniform1i(sampler2d_Loc, 0); }
		if (uMvpMatrix_Loc == -1) { glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); }

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/texelModify.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Texel Modify\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			colour_Loc = glGetUniformLocation(shaderProgramID, "colour");
			position_Loc = glGetUniformLocation(shaderProgramID, "position");
			dimension_Loc = glGetUniformLocation(shaderProgramID, "dimension");
			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (colour_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"colour\" not found"); }
			if (position_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"position\" not found"); }
			if (dimension_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"dimension\" not found"); }
			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_TEXEL_MODIFY uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::colourTexture(const glm::mat4 &mvpMatrix, const float &r, const float &g, const float &b) {

	static GLuint shaderProgramID = -1;

	GLuint r_Loc = -1;
	GLuint g_Loc = -1;
	GLuint b_Loc = -1;
	GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1f(r_Loc, r);
		glUniform1f(g_Loc, g);
		glUniform1f(b_Loc, b);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/initTextureColour.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Init Texture Colour\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			r_Loc = glGetUniformLocation(shaderProgramID, "r");
			g_Loc = glGetUniformLocation(shaderProgramID, "g");
			b_Loc = glGetUniformLocation(shaderProgramID, "b");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (r_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_COLOUR_TEXTURE uniform \"r\" not found"); }
			if (g_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_COLOUR_TEXTURE uniform \"g\" not found"); }
			if (b_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_COLOUR_TEXTURE uniform \"b\" not found"); }
			if (uMvpMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_COLOUR_TEXTURE uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::cutFrameCell(const glm::mat4 &mvpMatrix, const int &textureWidth, const int &textureHeight, const int &frameRow, const int &frameCol) {

	static GLuint shaderProgramID = -1;

	static GLuint sampler2d_Loc = -1;
	static GLuint textureWidth_Loc = -1;
	static GLuint textureHeight_Loc = -1;
	static GLuint row_Loc = -1;
	static GLuint col_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1i(sampler2d_Loc, 0);
		glUniform1i(textureWidth_Loc, textureWidth);
		glUniform1i(textureHeight_Loc, textureHeight);
		glUniform1i(row_Loc, frameRow);
		glUniform1i(col_Loc, frameCol);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/spriteAnimation.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Sprite Animation\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			textureWidth_Loc = glGetUniformLocation(shaderProgramID, "textureWidth");
			textureHeight_Loc = glGetUniformLocation(shaderProgramID, "textureHeight");
			row_Loc = glGetUniformLocation(shaderProgramID, "row");
			col_Loc = glGetUniformLocation(shaderProgramID, "col");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (sampler2d_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"sampler2d\" not found"); }
			if (textureWidth_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"textureWidth\" not found"); }
			if (textureHeight_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"textureHeight\" not found"); }
			if (row_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"row\" not found"); }
			if (col_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"col\" not found"); }
			if (uMvpMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SPRITE_ANIMATION uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::filterLightPass(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgramID = -1;

	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/filterLight.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Filter Light Pass\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_LGHTPASS uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_LGHTPASS uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::blendTexture(const glm::mat4 &mvpMatrix, const int &blendType, const GLuint &toBlend) {

	static GLuint shaderProgramID = -1;

	static 	GLuint blendType_Loc = -1;
	static GLuint toBlend_Loc = -1;
	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);
		
		glUniform1i(blendType_Loc, blendType);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, toBlend);

		glUniform1i(toBlend_Loc, 1);

		glActiveTexture(GL_TEXTURE0 + 0);
		//glBindTexture(GL_TEXTURE_2D, toBlend2);

		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/textureBlend.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Blend Texture\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			blendType_Loc = glGetUniformLocation(shaderProgramID, "blendType");
			toBlend_Loc = glGetUniformLocation(shaderProgramID, "toBlend");
			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (blendType_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"blendType\" not found"); }
			if (toBlend_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"toBlend\" not found"); }
			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_TEXTURE uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::blur(const glm::mat4 &mvpMatrix, const int &direction, const float &blurRadius, const float &totalWeight, const int &textureWidth, const int &textureHeight) {

	static GLuint shaderProgramID = -1;

	static GLuint uTextureW_Loc = -1;
	static GLuint uTextureH_Loc = -1;
	static GLuint uBlurDirection_Loc = -1;
	static GLuint radius_Loc = -1;
	static GLuint weight_Loc = -1;
	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1f(uTextureW_Loc, textureHeight);
		glUniform1f(uTextureH_Loc, textureWidth);
		glUniform1i(uBlurDirection_Loc, direction);
		glUniform1f(radius_Loc, blurRadius);
		glUniform1f(weight_Loc, totalWeight);
		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/animation2D.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/animation2D.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Blur\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			uTextureW_Loc = glGetUniformLocation(shaderProgramID, "uTextureW");
			uTextureH_Loc = glGetUniformLocation(shaderProgramID, "uTextureH");
			uBlurDirection_Loc = glGetUniformLocation(shaderProgramID, "uBlurDirection");
			weight_Loc = glGetUniformLocation(shaderProgramID, "weight");
			radius_Loc = glGetUniformLocation(shaderProgramID, "radius");
			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (uTextureW_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uTextureW\" not found"); }
			if (uTextureH_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uTextureH\" not found"); }
			if (uBlurDirection_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uBlurDirection\" not found"); }
			if (radius_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"radius\" not found"); }
			if (weight_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"weight\" not found"); }
			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLUR uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::blendColour(const glm::mat4 &mvpMatrix, const int &blendType, const float &r, const float &g, const float &b, const float &a) { //, const bool &alphaBlend

	static GLuint shaderProgramID = -1;

	static GLuint r_Loc = -1;
	static GLuint g_Loc = -1;
	static GLuint b_Loc = -1;
	static GLuint a_Loc = -1;
	static GLuint blendType_Loc = -1;
	static GLuint sampler2d_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1f(r_Loc, r);
		glUniform1f(g_Loc, g);
		glUniform1f(b_Loc, b);
		glUniform1f(a_Loc, a);
		glUniform1i(blendType_Loc, blendType);
		glUniform1i(sampler2d_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/default.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/colourBlend.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Blend Colour\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			r_Loc = glGetUniformLocation(shaderProgramID, "r");
			g_Loc = glGetUniformLocation(shaderProgramID, "g");
			b_Loc = glGetUniformLocation(shaderProgramID, "b");
			a_Loc = glGetUniformLocation(shaderProgramID, "a");
			blendType_Loc = glGetUniformLocation(shaderProgramID, "blendType");
			sampler2d_Loc = glGetUniformLocation(shaderProgramID, "sampler2d");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (r_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"r\" not found"); }
			if (g_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"g\" not found"); }
			if (b_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"b\" not found"); }
			if (a_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"a\" not found"); }
			if (blendType_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"blendType\" not found"); }
			if (sampler2d_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"sampler2d\" not found"); }
			if (uMvpMatrix_Loc == -1) {  Logger::getInstance()->warningLog("SHADER_PROGRAM_BLEND_COLOUR uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}

void Shader::drawSkyBox(const glm::mat4 &mvpMatrix) {

	static GLuint shaderProgramID = -1;

	static GLuint samplerCube1_Loc = -1;
	static GLuint uMvpMatrix_Loc = -1;

	static bool initCheck = false;

start:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniform1i(samplerCube1_Loc, 0);
		glUniformMatrix4fv(uMvpMatrix_Loc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/skybox.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/skybox.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Sky Box\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);

			samplerCube1_Loc = glGetUniformLocation(shaderProgramID, "samplerCube1");
			uMvpMatrix_Loc = glGetUniformLocation(shaderProgramID, "uMvpMatrix");

			if (samplerCube1_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SKYBOX uniform \"samplerCube1\" not found"); }
			if (uMvpMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_SKYBOX uniform \"uMvpMatrix\" not found"); }

			initCheck = true;

		}

		goto start;

	}

}