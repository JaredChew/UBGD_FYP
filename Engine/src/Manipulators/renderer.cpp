#include "renderer.h"

#include <unordered_set>

#include "system.h"

#include "../Modules BackEnd/camera.h"
#include "../Compound/mesh.h"
#include "../Manipulators/shader.h" //temp
#include "../Compound/vertexArrayObject.h"
#include "../Compound/material.h"
#include "../Compound/lightingContainer.h"

Renderer* Renderer::instance;

Renderer::Renderer(const int& resolutionWidth, const int& resolutionHeight) {

	//Init Opengl state
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f); // Depth Buffer Setup

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glViewport(0, 0, resolutionWidth, resolutionHeight);

	this->resolutionWidth = renderWidth = resolutionWidth;
	this->resolutionHeight = renderHeight = resolutionHeight;

	renderRatio = resolutionWidth / resolutionHeight;

	glGenFramebuffers(1, &frameBuffer);


	GLint internalFormat;
	GLenum format;
	System::initDepthBufferTexture(depthBuffer, 1280, 720, internalFormat, format);

	for (int i = 0; i < 2; ++i) {
		System::initTexture(swapTexture[i], 2, 1280, 720, internalFormat, format);
	}

	renderQuality = 100;
	swapTextureIndex = 0;

	backBuffer = swapTexture[swapTextureIndex];
	frontBuffer = swapTexture[(swapTextureIndex + 1) % 2];

	effectType = Effects::NONE;

	screenMesh = new Mesh(Mesh::DefaultGeometry::RENDER_BOARD);

	meshBinded = nullptr;
	materialBinded = nullptr;
	lightingContainerBinded = nullptr;
	camera = nullptr;

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backBuffer, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

}

Renderer::~Renderer() { }

Renderer* Renderer::getInstance() {

	return instance;

}

void Renderer::start(const int& resolutionWidth, const int& resolutionHeight) {

	if (!instance) { instance = new Renderer(resolutionWidth, resolutionHeight); }

}

void Renderer::end() {

	if (instance) { delete instance; }

}

void Renderer::swapScreenTexture() {

	swapTextureIndex = ++swapTextureIndex % 2;

	backBuffer = swapTexture[swapTextureIndex];
	frontBuffer = swapTexture[(swapTextureIndex + 1) % 2];

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backBuffer, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::applyPostProcessing() {

	if (postProcesses.empty() || !System::checkIsFramebufferReady()) { return; }

	for (int i = 0; i < postProcesses.size(); ++i) {

		glBindTexture(GL_TEXTURE_2D, frontBuffer);

		switch (postProcesses.front()) {

			case PostProcessing::BLOOM:
				//Shader::filterLightPass(glm::mat4(1.0f));
				//Shader::blur(glm::mat4(1.0f));
				//Shader::blendTexture (glm::mat4(1.0f));
				break;

		}

		bindMesh(screenMesh);
		swapScreenTexture();

	}

}

void Renderer::render(const glm::mat4& modelMatrix) {

	if (!System::checkIsFramebufferReady()) { return; }

	glm::mat4 mvpMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

	switch (effectType) {

		case Effects::NONE:
			Shader::phongLightDraw(modelMatrix, camera->getViewMatrix(), camera->getProjectionMatrix(), *materialBinded, *lightingContainerBinded);
			//bindMaterial(materialBinded);
			//Shader::defaultDraw(glm::mat4(mvpMatrix));
			break;

		case Effects::BLUR:
			//Shader::blur(glm::mat4(mvpMatrix));
			break;

		case Effects::BLEND_COLOUR:
			//Shader::blendColour(glm::mat4(mvpMatrix));
			break;

	}

	
	bindMesh(meshBinded);
	//swapScreenTexture();

}

void Renderer::renderToScreen() {

	applyPostProcessing();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glLineWidth(2.5f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (System::checkIsFramebufferReady()) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, frontBuffer);

		Shader::defaultDraw(glm::mat4(1.0f));

		bindMesh(screenMesh);

	}


	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backBuffer, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	swapScreenTexture();

}

void Renderer::effectRender(const Effects& type) {

	effectType = type;

}

void Renderer::bindMesh(Mesh* const mesh) {

	//for (size_t i = 0; i < mesh->getIndicesSize(); i++)
	//{
	//	printf("vao = %u, indice = %u  | ", mesh->getVAO(), mesh->getIndices()[i]);
	//}
	//printf("\n\n");
	
	glBindVertexArray(mesh->getVertexArrayObject()->vaoID);
	glDrawElements(GL_TRIANGLES, mesh->getVertexArrayObject()->indicesSize, GL_UNSIGNED_INT, 0);

}

void Renderer::bindMaterial(Material* const material) {

	for (size_t i = 0; i < 3; i++) {

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, materialBinded->textures[i]->getTextureID());
	
	}

	glActiveTexture(GL_TEXTURE0);

}

void Renderer::useLightingContainer(LightingContainer* const lightingContainer)
{
	this->lightingContainerBinded = lightingContainer;
}

void Renderer::useMesh(Mesh* const mesh) {

	this->meshBinded = mesh;

}

void Renderer::useWindow(GLFWwindow* const window) {

	glfwMakeContextCurrent(window);

}

void Renderer::useCamera(Camera* const camera) {

	this->camera = camera;

}

void Renderer::useMaterial(Material* const  material) {

	this->materialBinded = material;

}

void Renderer::appendPostProcessing(const PostProcessing& type) {

	postProcesses.push_back(type);

	// !! https://stackoverflow.com/questions/4885676/remove-duplicates-from-a-listint !! //

	std::unordered_set<PostProcessing> s;

	postProcesses.remove_if(

		[&](PostProcessing n) {
			return (s.find(n) == s.end()) ? (s.insert(n), false) : true;
		}

	);

}

void Renderer::detacthPostProcessing(const PostProcessing& type) {

	postProcesses.remove(type);

}

void Renderer::setBlendType(const BlendType& blendType) {

	switch (blendType) {

		case BlendType::BLEND_ADDITIVE:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			break;

		case BlendType::BLEND_MULTIPLY:
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBlendEquation(GL_FUNC_ADD);
			break;

		case BlendType::BLEND_ALPHA:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendEquation(GL_FUNC_ADD);
			break;

	}

}

void Renderer::setRenderResolution(const int& resolutionWidth, const int& resolutionHeight) {

	this->resolutionWidth = resolutionWidth;
	this->resolutionHeight = resolutionHeight;

	setRenderQuality(renderQuality);

}

void Renderer::setRenderQuality(const int& renderQuality) {

	this->renderQuality = renderQuality;

	if (this->renderQuality <= 0) { this->renderQuality = 1; }

	renderWidth = resolutionWidth * (renderQuality / 100);
	renderHeight = resolutionHeight * (renderQuality / 100);

	renderRatio = renderWidth / renderHeight;

	glViewport(0, 0, renderWidth, renderHeight);

}