#include "demo.h"

#include "Compound/texture.h"
#include "Compound/mesh.h"
#include "Compound/transform.h"
#include "Compound/model.h"
#include "Compound/material.h"
#include "Compound/VertexArrayObject.h"

#include "Modules FrontEnd/Text.h"

#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/eventHandle.h"

#include "Manipulators/renderer.h"
#include "Manipulators/system.h"
#include "Manipulators/shader.h"

#include "Specification/entity.h"

#include "../global.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Compound/lightingContainer.h"

struct GameObject : public Entity
{
private:
	Material* material;
	Mesh* mesh;

public:
	Model* model;

	GameObject(Texture* texture, Mesh* mesh)
	{
		this->mesh = mesh;
		model = new Model(this->mesh, new Material(texture, 32.0f, false));
	}
	GameObject(std::string path)
	{
		model = new Model(path.c_str());
	}
	~GameObject()
	{
		delete material;
		delete mesh;
		delete model;
	}

};

Demo::Demo() {

	DirectionLight* direction = new DirectionLight;
	direction->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	direction->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	direction->diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	direction->specular = glm::vec3(0.5f, 0.5f, 0.5f);

	lightingContainer = new LightingContainer(true);
	lightingContainer->addDirectionLight(direction);

	PointLight* point;
	for (size_t i = 0; i < 3; i++)
	{
		point = new PointLight;
		if(i == 0)
			point->position = glm::vec3(0.7f, 0.2f, 2.0f);
		if (i == 1)
			point->position = glm::vec3(-0.7f, 0.2f, -2.0f);
		else
			point->position = glm::vec3(0.2f, 2.0f, 2.0f);
		point->constant = 1.0f;
		point->linear = 0.09f;
		point->quadratic = 0.032f;
		point->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		point->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		point->specular = glm::vec3(1.0f, 1.0f, 1.0f);

		lightingContainer->addPointLight(point);
	}

	Texture* texture = new Texture("../Assets/Medias/glass.png");
	gameObjects.push_back(new GameObject(texture, new Mesh(Mesh::DefaultGeometry::TORUS)));
	gameObjects.back()->transform->setPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	gameObjects.push_back(new GameObject(texture, new Mesh(Mesh::DefaultGeometry::SPHERE)));
	gameObjects.back()->transform->setPosition(glm::vec3(0.0f, 0.0f, -1.0f));

	gameObjects.push_back(new GameObject(texture, new Mesh(Mesh::DefaultGeometry::CYLINDER)));
	gameObjects.back()->transform->setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	

	//gameObjects.push_back( new GameObject("../Media/backpack/backpack.obj") );
	//gameObjects.back()->transform->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//System::loadModelToVertexArrayObjectData("../Media/cude/sphere.obj", "../sphere");
	//System::loadModelToVertexArrayObjectData("../Media/cude/circle.obj", "../circle");
	//System::loadModelToVertexArrayObjectData("../Media/cude/cone.obj", "../cone");
	//System::loadModelToVertexArrayObjectData("../Media/cude/cylinder.obj", "../cylinder");
	//System::loadModelToVertexArrayObjectData("../Media/cude/pyramid.obj", "../pyramid");
	//System::loadModelToVertexArrayObjectData("../Media/cude/torus.obj", "../torus");
	//System::loadModelToVertexArrayObjectData("../Media/cude/stadium.obj", "../stadium");
	
	//gameObjects.push_back(new GameObject("../Media/cude/cone.obj"));
	//gameObjects.back()->transform->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));

	//gameObjects.push_back(new GameObject("../Media/cude/stadium.obj"));
	//gameObjects.back()->transform->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	
	text = new Text("../Assets/Fonts/arial.ttf", 48);
	text->changeTextScreenSize(Global::window->getWidth(), Global::window->getHeight());

	text2 = new Text("../Assets/Fonts/GloriaHallelujah.ttf", 48);
	text2->changeTextScreenSize(Global::window->getWidth(), Global::window->getHeight());

	Renderer::getInstance()->useLightingContainer(lightingContainer);

}

Demo::~Demo() { }

void Demo::update() {

	//

}

void Demo::render() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(2.5f);

	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		
		for (size_t j = 0; j < gameObjects[i]->model->getMesh().size(); j++)
		{
			Renderer::getInstance()->useMesh(gameObjects[i]->model->getMesh()[j]);
			Renderer::getInstance()->useMaterial(gameObjects[i]->model->getMaterials()[j]);
			Renderer::getInstance()->render(gameObjects[i]->transform->getModelMatrix());
		}
	}

	text->renderText("Geometry", 555.0f, 500.0f, 80.0f, glm::vec3(0.4f, 0.4f, 1.0f));
	text2->renderText("I Am Special Font!", 520.0f, 200.0f, 50.0f, glm::vec3(0.3f, 0.7f, 1.0f));
	
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