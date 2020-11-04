#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <list>

#include <glm/mat4x4.hpp>

class Camera;
class Mesh;

class Renderer {

public:
	static enum class Effects { NONE, BLUR, BLEND_COLOUR,  };
	static enum class BlendType { BLEND_ADDITIVE, BLEND_MULTIPLY, BLEND_ALPHA };
	static enum class PostProcessing { BLOOM };

	static enum class DefaultGeometry { BLEND_ADDITIVE, BLEND_MULTIPLY, BLEND_ALPHA };
	static enum class DefaultShader { BLEND_ADDITIVE, BLEND_MULTIPLY, BLEND_ALPHA };


private:

	static Renderer* instance;

	GLuint frameBuffer;
	GLuint depthBuffer;

	GLuint swapTexture[2];
	GLuint frontBuffer;
	GLuint backBuffer;
	GLuint textureBinded;

	int resolutionWidth;
	int resolutionHeight;

	int renderWidth;
	int renderHeight;
	int renderQuality;

	int swapTextureIndex;

	float renderRatio;

	Effects effectType; //list of effects?
	std::list<PostProcessing> postProcesses; //list of effects?

	Mesh* screenMesh;

	Mesh* mesh;
	Camera* camera;

private:
	Renderer(const int& resolutionWidth, const int& resolutionHeight);
	~Renderer();

	void swapScreenTexture();
	void bindMesh(Mesh* const mesh);
	void applyPostProcessing();

public:
	static Renderer* getInstance();

	static void start(const int& resolutionWidth, const int& resolutionHeight);
	static void end();

	void render(const glm::mat4& modelMatrix);
	void renderToScreen();

	void effectRender(const Effects& effectType);

	void useMesh(Mesh* const mesh);
	//void useShader(const DefaultShader& type); //use custom
	void useWindow(GLFWwindow* const window);
	void useCamera(Camera* const camera);
	void useTexture(const GLuint& textureID);

	void appendPostProcessing(const PostProcessing& type);
	void detacthPostProcessing(const PostProcessing& type);

	void setBlendType(const BlendType& blendType);
	void setRenderResolution(const int& resolutionWidth, const int& resolutionHeight);
	void setRenderQuality(const int& renderQuality);

};