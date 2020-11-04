#include "demo.h"

#include "Compound/texture.h"
#include "Compound/mesh.h"
#include "Compound/transform.h"
#include "Modules BackEnd/camera.h"
#include "Manipulators/renderer.h"

#include "Manipulators/system.h"
#include "Manipulators/shader.h"

#include "../global.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Demo::Demo() {

	texture = new Texture("../Media/TreasureNormal.png");

	mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
	transform = new Transform();

	Renderer::getInstance()->useMesh(mesh);
	//Renderer::getInstance()->useTexture(texture->getTextureID());

}

Demo::~Demo() { }

void Demo::update() {

	//

}

void Demo::render() {

	Renderer::getInstance()->useTexture(texture->getTextureID());
	Renderer::getInstance()->render(transform->getModelMatrix());
	Renderer::getInstance()->renderToScreen();

	/*
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);


	if (System::checkIsFramebufferReady()) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		Shader::defaultDraw(glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)));

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);

	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (System::checkIsFramebufferReady()) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindTexture(GL_TEXTURE_2D, frontBuffer);

		glm::mat4 mvpMatrix = Renderer::getInstance()->camera->getProjectionMatrix() * Renderer::getInstance()->camera->getViewMatrix() * transform->getModelMatrix();
		Shader::defaultDraw(glm::mat4(1.0f));
		
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);

	}
	*/
	
}