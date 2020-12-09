#include "shader.h"

#include "system.h"

#include "../Utilities/logger.h"
#include "../Compound/material.h"
#include "../Compound/lightingContainer.h"

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

void Shader::phongLightDraw(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const Material& material, LightingContainer& lightingContainer)
{

	static GLuint shaderProgramID = -1;


	static GLint uMaterual_Diffuse_Loc = -1;
	static GLint uMaterual_DiffuseColor_Loc = -1;
	static GLint uMaterual_Specular_Loc = -1;
	static GLint uMaterual_Emission_Loc = -1;
	static GLint uMaterual_Shininess_Loc = -1;

	static GLint uDirectionLightAmount_Loc = -1;
	static GLint uPointLightAmount_Loc = -1;
	static GLint uSpotLightAmount_Loc = -1;

	static GLint uDirectionLight_Direction_Loc[MAX_DIRECTION_LIGHTS];
	static GLint uDirectionLight_Ambient_Loc[MAX_DIRECTION_LIGHTS];
	static GLint uDirectionLight_Diffuse_Loc[MAX_DIRECTION_LIGHTS];
	static GLint uDirectionLight_Specular_Loc[MAX_DIRECTION_LIGHTS];

	static GLint uPointLight_Position_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Constant_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Linear_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Quadratic_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Ambient_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Diffuse_Loc[MAX_POINT_LIGHTS];
	static GLint uPointLight_Specular_Loc[MAX_POINT_LIGHTS];

	static GLint uSpotLight_Position_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Direction_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_CutOff_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_OuterCutOff_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Constant_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Linear_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Quadratic_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Ambient_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Diffuse_Loc[MAX_SPOT_LIGHTS];
	static GLint uSpotLight_Specular_Loc[MAX_SPOT_LIGHTS];

	static GLint uModelMatrix_Loc = -1;
	static GLint uViewMatrix_Loc = -1;
	static GLint uProjectionMatrix_Loc = -1;


	static bool initCheck = false;
	
	size_t directionLightAmount = lightingContainer.getDirectionLights().size();
	size_t pointLightAmount = lightingContainer.getPointLights().size();
	size_t spotLightAmount = lightingContainer.getSpotLights().size();

start2:

	if (shaderProgramID != -1) {

		glUseProgram(shaderProgramID);

		glUniformMatrix4fv(uModelMatrix_Loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(uViewMatrix_Loc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(uProjectionMatrix_Loc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.textures[0]->getTextureID());
		
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, material.textures[1]->getTextureID());

		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, material.textures[2]->getTextureID());

		glActiveTexture(GL_TEXTURE0);

		glUniform1i(uMaterual_Diffuse_Loc, 0);
		glUniform3fv(uMaterual_DiffuseColor_Loc, 1, glm::value_ptr(material.color));
		glUniform1i(uMaterual_Specular_Loc, 1);
		glUniform1i(uMaterual_Emission_Loc, 2);
		glUniform1f(uMaterual_Shininess_Loc, material.shininess);

		glUniform1i(uDirectionLightAmount_Loc, directionLightAmount);
		glUniform1i(uPointLightAmount_Loc, pointLightAmount);
		glUniform1i(uSpotLightAmount_Loc, spotLightAmount);

		
		for (size_t i = 0; i < directionLightAmount; i++)
		{
			glUniform3fv(uDirectionLight_Direction_Loc[i], 1, glm::value_ptr(lightingContainer.getDirectionLights()[i]->direction));
			glUniform3fv(uDirectionLight_Ambient_Loc[i], 1, glm::value_ptr(lightingContainer.getDirectionLights()[i]->ambient));
			glUniform3fv(uDirectionLight_Diffuse_Loc[i], 1, glm::value_ptr(lightingContainer.getDirectionLights()[i]->diffuse));
			glUniform3fv(uDirectionLight_Specular_Loc[i], 1, glm::value_ptr(lightingContainer.getDirectionLights()[i]->specular));
		}

		for (size_t i = 0; i < pointLightAmount; i++)
		{
			glUniform3fv(uPointLight_Position_Loc[i], 1, glm::value_ptr(lightingContainer.getPointLights()[i]->position));
			glUniform1f(uPointLight_Constant_Loc[i], lightingContainer.getPointLights()[i]->constant);
			glUniform1f(uPointLight_Linear_Loc[i], lightingContainer.getPointLights()[i]->linear);
			glUniform1f(uPointLight_Quadratic_Loc[i], lightingContainer.getPointLights()[i]->quadratic);
			glUniform3fv(uPointLight_Ambient_Loc[i], 1, glm::value_ptr(lightingContainer.getPointLights()[i]->ambient));
			glUniform3fv(uPointLight_Diffuse_Loc[i], 1, glm::value_ptr(lightingContainer.getPointLights()[i]->diffuse));
			glUniform3fv(uPointLight_Specular_Loc[i], 1, glm::value_ptr(lightingContainer.getPointLights()[i]->specular));
		}

		for (size_t i = 0; i < spotLightAmount; i++)
		{
			glUniform3fv(uSpotLight_Position_Loc[i], 1, glm::value_ptr(lightingContainer.getSpotLights()[i]->position));
			glUniform3fv(uSpotLight_Direction_Loc[i], 1, glm::value_ptr(lightingContainer.getSpotLights()[i]->direction));
			glUniform1f(uSpotLight_CutOff_Loc[i], lightingContainer.getSpotLights()[i]->cutOff);
			glUniform1f(uSpotLight_OuterCutOff_Loc[i], lightingContainer.getSpotLights()[i]->outerCutOff);
			glUniform1f(uSpotLight_Constant_Loc[i], lightingContainer.getSpotLights()[i]->constant);
			glUniform1f(uSpotLight_Linear_Loc[i], lightingContainer.getSpotLights()[i]->linear);
			glUniform1f(uSpotLight_Quadratic_Loc[i], lightingContainer.getSpotLights()[i]->quadratic);
			glUniform3fv(uSpotLight_Ambient_Loc[i], 1, glm::value_ptr(lightingContainer.getSpotLights()[i]->ambient));
			glUniform3fv(uSpotLight_Diffuse_Loc[i], 1, glm::value_ptr(lightingContainer.getSpotLights()[i]->diffuse));
			glUniform3fv(uSpotLight_Specular_Loc[i], 1, glm::value_ptr(lightingContainer.getSpotLights()[i]->specular));
		}

	}
	else {

		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		System::loadShaderFromFile(vertexShaderID, GL_VERTEX_SHADER, "../Shaders/phong.vert");
		System::loadShaderFromFile(fragmentShaderID, GL_FRAGMENT_SHADER, "../Shaders/phong.frag");

		if (!System::initProgramObject_Shader(shaderProgramID, fragmentShaderID, vertexShaderID)) {
			Logger::getInstance()->warningLog("Failed to init \"Phong\" shader program");
			return;
		}

		if (!initCheck) {

			glUseProgram(shaderProgramID);


			uMaterual_Diffuse_Loc = glGetUniformLocation(shaderProgramID, "uMaterial.diffuse");
			uMaterual_DiffuseColor_Loc = glGetUniformLocation(shaderProgramID, "uMaterial.diffuseColor");
			uMaterual_Specular_Loc = glGetUniformLocation(shaderProgramID, "uMaterial.specular");
			uMaterual_Emission_Loc = glGetUniformLocation(shaderProgramID, "uMaterial.emission");
			uMaterual_Shininess_Loc = glGetUniformLocation(shaderProgramID, "uMaterial.shininess");

			uDirectionLightAmount_Loc = glGetUniformLocation(shaderProgramID, "uDirectionLightAmount");
			uPointLightAmount_Loc = glGetUniformLocation(shaderProgramID, "uPointLightAmount");
			uSpotLightAmount_Loc = glGetUniformLocation(shaderProgramID, "uSpotLightAmount");

			for (size_t i = 0; i < MAX_DIRECTION_LIGHTS; i++)
			{
				std::string tempDirection = "uDirectionLights[" + std::to_string(i) + "].direction";
				std::string tempAmbient = "uDirectionLights[" + std::to_string(i) + "].ambient";
				std::string tempDiffuse = "uDirectionLights[" + std::to_string(i) + "].diffuse";
				std::string tempSpecular = "uDirectionLights[" + std::to_string(i) + "].specular";

				uDirectionLight_Direction_Loc[i] = glGetUniformLocation(shaderProgramID, tempDirection.c_str());
				uDirectionLight_Ambient_Loc[i] = glGetUniformLocation(shaderProgramID, tempAmbient.c_str());
				uDirectionLight_Diffuse_Loc[i] = glGetUniformLocation(shaderProgramID, tempDiffuse.c_str());
				uDirectionLight_Specular_Loc[i] = glGetUniformLocation(shaderProgramID, tempSpecular.c_str());
			}

			uDirectionLight_Direction_Loc[0] = glGetUniformLocation(shaderProgramID, "uDirectionLights[0].direction");
			uDirectionLight_Ambient_Loc[0] = glGetUniformLocation(shaderProgramID, "uDirectionLights[0].ambient");
			uDirectionLight_Diffuse_Loc[0] = glGetUniformLocation(shaderProgramID, "uDirectionLights[0].diffuse");
			uDirectionLight_Specular_Loc[0] = glGetUniformLocation(shaderProgramID, "uDirectionLights[0].specular");

			for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
			{
				std::string tempPosition = "uPointLights[" + std::to_string(i) + "].position";
				std::string tempConstant = "uPointLights[" + std::to_string(i) + "].constant";
				std::string tempLinear = "uPointLights[" + std::to_string(i) + "].linear";
				std::string tempQuadratic = "uPointLights[" + std::to_string(i) + "].quadratic";
				std::string tempAmbient = "uPointLights[" + std::to_string(i) + "].ambient";
				std::string tempDiffuse = "uPointLights[" + std::to_string(i) + "].diffuse";
				std::string tempSpecular = "uPointLights[" + std::to_string(i) + "].specular";

				uPointLight_Position_Loc[i] = glGetUniformLocation(shaderProgramID, tempPosition.c_str());
				uPointLight_Constant_Loc[i] = glGetUniformLocation(shaderProgramID, tempConstant.c_str());
				uPointLight_Linear_Loc[i] = glGetUniformLocation(shaderProgramID, tempLinear.c_str());
				uPointLight_Quadratic_Loc[i] = glGetUniformLocation(shaderProgramID, tempQuadratic.c_str());
				uPointLight_Ambient_Loc[i] = glGetUniformLocation(shaderProgramID, tempAmbient.c_str());
				uPointLight_Diffuse_Loc[i] = glGetUniformLocation(shaderProgramID, tempDiffuse.c_str());
				uPointLight_Specular_Loc[i] = glGetUniformLocation(shaderProgramID, tempSpecular.c_str());
			}

			for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
			{
				std::string tempPosition = "uSpotLights[" + std::to_string(i) + "].position";
				std::string tempDirection = "uSpotLights[" + std::to_string(i) + "].direction";
				std::string tempCutOff = "uSpotLights[" + std::to_string(i) + "].cutOff";
				std::string tempOuterCutOff = "uSpotLights[" + std::to_string(i) + "].outerCutOff";
				std::string tempConstant = "uSpotLights[" + std::to_string(i) + "].constant";
				std::string tempLinear = "uSpotLights[" + std::to_string(i) + "].linear";
				std::string tempQuadratic = "uSpotLights[" + std::to_string(i) + "].quadratic";
				std::string tempAmbient = "uSpotLights[" + std::to_string(i) + "].ambient";
				std::string tempDiffuse = "uSpotLights[" + std::to_string(i) + "].diffuse";
				std::string tempSpecular = "uSpotLights[" + std::to_string(i) + "].specular";

				uSpotLight_Position_Loc[i] = glGetUniformLocation(shaderProgramID, tempPosition.c_str());
				uSpotLight_Direction_Loc[i] = glGetUniformLocation(shaderProgramID, tempDirection.c_str());
				uSpotLight_CutOff_Loc[i] = glGetUniformLocation(shaderProgramID, tempCutOff.c_str());
				uSpotLight_OuterCutOff_Loc[i] = glGetUniformLocation(shaderProgramID, tempOuterCutOff.c_str());
				uSpotLight_Constant_Loc[i] = glGetUniformLocation(shaderProgramID, tempConstant.c_str());
				uSpotLight_Linear_Loc[i] = glGetUniformLocation(shaderProgramID, tempLinear.c_str());
				uSpotLight_Quadratic_Loc[i] = glGetUniformLocation(shaderProgramID, tempQuadratic.c_str());
				uSpotLight_Ambient_Loc[i] = glGetUniformLocation(shaderProgramID, tempAmbient.c_str());
				uSpotLight_Diffuse_Loc[i] = glGetUniformLocation(shaderProgramID, tempDiffuse.c_str());
				uSpotLight_Specular_Loc[i] = glGetUniformLocation(shaderProgramID, tempSpecular.c_str());
			}

			uModelMatrix_Loc = glGetUniformLocation(shaderProgramID, "uModelMatrix");
			uViewMatrix_Loc = glGetUniformLocation(shaderProgramID, "uViewMatrix");
			uProjectionMatrix_Loc = glGetUniformLocation(shaderProgramID, "uProjectionMatrix");


			if (uMaterual_Diffuse_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uMaterial.diffuse\" not found"); }
			if (uMaterual_DiffuseColor_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uMaterial.diffuseColor\" not found"); }
			if (uMaterual_Specular_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uMaterial.specular\" not found"); }
			if (uMaterual_Emission_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uMaterial.emission\" not found"); }
			if (uMaterual_Shininess_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uMaterial.shininess\" not found"); }

			if (uDirectionLightAmount_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uDirectionLightAmount\" not found"); }
			if (uPointLightAmount_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uPointLightAmount\" not found"); }
			if (uSpotLightAmount_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uSpotLightAmount\" not found"); }
			
			for (size_t i = 0; i < MAX_DIRECTION_LIGHTS; i++)
			{
				std::string tempDirection = "SHADER_PROGRAM_PHONG uniform \"uDirectionLights[" + std::to_string(i) + "].direction\" not found";
				std::string tempAmbient = "SHADER_PROGRAM_PHONG uniform \"uDirectionLights[" + std::to_string(i) + "].ambient\" not found";
				std::string tempDiffuse = "SHADER_PROGRAM_PHONG uniform \"uDirectionLights[" + std::to_string(i) + "].diffuse\" not found";
				std::string tempSpecular = "SHADER_PROGRAM_PHONG uniform \"uDirectionLights[" + std::to_string(i) + "].specular\" not found";

				if (uDirectionLight_Direction_Loc[i] == -1) { Logger::getInstance()->warningLog(tempDirection.c_str()); }
				if (uDirectionLight_Ambient_Loc[i] == -1) { Logger::getInstance()->warningLog(tempAmbient.c_str()); }
				if (uDirectionLight_Diffuse_Loc[i] == -1) { Logger::getInstance()->warningLog(tempDiffuse.c_str()); }
				if (uDirectionLight_Specular_Loc[i] == -1) { Logger::getInstance()->warningLog(tempSpecular.c_str()); }
			}

			for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
			{
				std::string tempPosition = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].position\" not found";
				std::string tempConstant = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].constant\" not found";
				std::string tempLinear = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].linear\" not found";
				std::string tempQuadratic = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].quadratic\" not found";
				std::string tempAmbient = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].ambient\" not found";
				std::string tempDiffuse = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].diffuse\" not found";
				std::string tempSpecular = "SHADER_PROGRAM_PHONG uniform \"uPointLights[" + std::to_string(i) + "].specular\" not found";

				if (uPointLight_Position_Loc[i] == -1) { Logger::getInstance()->warningLog(tempPosition.c_str()); }
				if (uPointLight_Constant_Loc[i] == -1) { Logger::getInstance()->warningLog(tempConstant.c_str()); }
				if (uPointLight_Linear_Loc[i] == -1) { Logger::getInstance()->warningLog(tempLinear.c_str()); }
				if (uPointLight_Quadratic_Loc[i] == -1) { Logger::getInstance()->warningLog(tempQuadratic.c_str()); }
				if (uPointLight_Ambient_Loc[i] == -1) { Logger::getInstance()->warningLog(tempAmbient.c_str()); }
				if (uPointLight_Diffuse_Loc[i] == -1) { Logger::getInstance()->warningLog(tempDiffuse.c_str()); }
				if (uPointLight_Specular_Loc[i] == -1) { Logger::getInstance()->warningLog(tempSpecular.c_str()); }
			}

			for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
			{
				std::string tempPosition = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].position\" not found";
				std::string tempDirection = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].direction\" not found";
				std::string tempCutOff = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].cutOff\" not found";
				std::string tempOuterCutOff = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].outerCutOff\" not found";
				std::string tempConstant = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].constant\" not found";
				std::string tempLinear = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].linear\" not found";
				std::string tempQuadratic = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].quadratic\" not found";
				std::string tempAmbient = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].ambient\" not found";
				std::string tempDiffuse = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].diffuse\" not found";
				std::string tempSpecular = "SHADER_PROGRAM_PHONG uniform \"uSpotLights[" + std::to_string(i) + "].specular\" not found";

				if (uSpotLight_Position_Loc[i] == -1) { Logger::getInstance()->warningLog(tempPosition.c_str()); }
				if (uSpotLight_Direction_Loc[i] == -1) { Logger::getInstance()->warningLog(tempDirection.c_str()); }
				if (uSpotLight_CutOff_Loc[i] == -1) { Logger::getInstance()->warningLog(tempCutOff.c_str()); }
				if (uSpotLight_OuterCutOff_Loc[i] == -1) { Logger::getInstance()->warningLog(tempOuterCutOff.c_str()); }
				if (uSpotLight_Constant_Loc[i] == -1) { Logger::getInstance()->warningLog(tempConstant.c_str()); }
				if (uSpotLight_Linear_Loc[i] == -1) { Logger::getInstance()->warningLog(tempLinear.c_str()); }
				if (uSpotLight_Quadratic_Loc[i] == -1) { Logger::getInstance()->warningLog(tempQuadratic.c_str()); }
				if (uSpotLight_Ambient_Loc[i] == -1) { Logger::getInstance()->warningLog(tempAmbient.c_str()); }
				if (uSpotLight_Diffuse_Loc[i] == -1) { Logger::getInstance()->warningLog(tempDiffuse.c_str()); }
				if (uSpotLight_Specular_Loc[i] == -1) { Logger::getInstance()->warningLog(tempSpecular.c_str()); }
			}

			if (uModelMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uModelMatrix\" not found"); }
			if (uViewMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uViewMatrix\" not found"); }
			if (uProjectionMatrix_Loc == -1) { Logger::getInstance()->warningLog("SHADER_PROGRAM_PHONG uniform \"uProjectionMatrix\" not found"); }


			initCheck = true;

		}

		goto start2;

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