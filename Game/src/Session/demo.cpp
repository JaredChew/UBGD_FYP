#include "demo.h"

#include "Compound/texture.h"
#include "Compound/mesh.h"
#include "Compound/transform.h"
#include "Modules BackEnd/camera.h"
#include "Manipulators/renderer.h"

Demo::Demo() {

	texture = new Texture("../Media/fish.bmp");
	mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
	transform = new Transform();

	Renderer::getInstance()->useMesh(mesh);
	Renderer::getInstance()->useTexture(texture->getTextureID());

}

Demo::~Demo() { }

void Demo::update() {

	//

}

void Demo::render() {

	Renderer::getInstance()->render(glm::mat4(1.0f));
	//Renderer::getInstance()->renderToScreen();

}