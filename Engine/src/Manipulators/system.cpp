#include "system.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>

#include <glm/gtc/type_ptr.hpp>

#include "../Utilities/logger.h"
#include "../Compound/texture.h"
#include "../Compound/Vertex.h"
#include "../Compound/VertexArrayObject.h"
#include "../Compound/mesh.h"
#include "../Compound/material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static void System::error_callback(int error, const char* description) {

	Logger::getInstance()->customLog("GLFW ERROR", description);

}

bool System::initOpenGL() {

	glfwSetErrorCallback(System::error_callback);

	//Initialize GLFW library
	if (!glfwInit()) {

		Logger::getInstance()->errorLog("Failed to initialise GLFW");

		return false;

	}

	//Set window hints
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	/*
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::getInstance()->errorLog("Failed to initialize OpenGL context");
		return false;
	}

	Logger::getInstance()->infoLog((char*)glGetString(GL_VERSION));
	Logger::getInstance()->infoLog(glfwGetVersionString());

	if (!GLAD_GL_VERSION_3_3) {

		Logger::getInstance()->errorLog("Your device must support OpenGL 3.2+");

		glfwTerminate();

		return false;

	}
	*/

	return true;

}


bool System::initProgramObject_Shader(GLuint &programID, const GLuint &fragmentShader, const GLuint &vertexShader) {

	GLuint programObject = glCreateProgram();

	if (programObject == 0) { return false; }

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	//glBindAttribLocation(programObject, 0, "vPosition");
	//glBindAttribLocation(programObject, 1, "vColor");
	//glBindAttribLocation(programObject, 2, "vTexCoord");

	// Link the program
	glLinkProgram(programObject);

	GLint linked;

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) {

		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1) {

			char infoLog[1024];

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to link shader program %s", infoLog);

		}

		glDeleteProgram(programObject);

		return false;
	}

	// Store the program object
	programID = programObject;

	glDetachShader(programID, fragmentShader);
	glDetachShader(programID, vertexShader);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return true;

}

bool System::initTexture(GLuint &textureID, const GLsizei &size, const GLuint &resolutionWidth, const GLuint &resolutionHeight, GLint& internalFormat, GLenum& format) {

	glGenTextures(size, &textureID);
	if (!textureID) {

		Logger::getInstance()->errorLog("Texture generate error: can't generate %i texture!", size);
		return false;

	}


	glBindTexture(GL_TEXTURE_2D, textureID);

	internalFormat = GL_RGBA;
	format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolutionWidth, resolutionHeight, 0, format, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;

}

bool System::initTexture(const GLchar* dir, GLuint& textureID, GLint& width, GLint& height, GLint& internalFormat, GLenum& format)
{
	int channels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = SOIL_load_image(dir, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (!image) {

		Logger::getInstance()->errorLog("SOIL loading error: %s", SOIL_last_result());
		SOIL_free_image_data(image);

		return false;

	}

	glGenTextures(1, &textureID);
	if (!textureID) {

		Logger::getInstance()->errorLog("Texture generate error: can't generate a texture!");
		return false;

	}
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	switch (channels) {

	case SOIL_LOAD_L:
		internalFormat = GL_RED;
		format = GL_RED;
		break;

	case SOIL_LOAD_RGB:
		internalFormat = GL_RGB;
		format = GL_RGB;
		break;

	case SOIL_LOAD_RGBA:
		internalFormat = GL_RGBA;
		format = GL_RGBA;
		break;

	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // magnifying = near, linear = gradient
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // minifying = far, nearest = more pixel
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_LINEAR); // magnifying = near, linear = gradient
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //GL_NEAREST); // minifying = far, nearest = more pixel

	SOIL_free_image_data(image);

	return true;

}

bool System::saveTextureToImage(const GLchar* filename, const GLuint& textureID, const GLsizei& width, const GLsizei& height) {

	uint8_t* pixels = new uint8_t[width * height * 3];
	// copy pixels from screen
	glBindTexture(GL_TEXTURE_2D, textureID);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)pixels);

	// invert pixels (stolen from SOILs source code)
	for (int j = 0; j * 2 < height; ++j) {

		int x = j * width * 3;
		int y = (height - 1 - j) * width * 3;

		for (int i = width * 3; i > 0; --i) {

			uint8_t tmp = pixels[x];
			pixels[x] = pixels[y];
			pixels[y] = tmp;
			++x;
			++y;
		}
	}

	// save the image
	int err = SOIL_save_image(filename, SOIL_SAVE_TYPE_PNG, width, height, 3, pixels);
	if (err)
	{
		printf("Save Image Done\n");
		return true;
	}
	else
	{
		printf("Save Image Failed\n");
		return false;
	}

}

void System::loadImageToGLFWimage(const GLchar* dir, GLFWimage& image)
{
	image.pixels = SOIL_load_image(dir, &image.width, &image.height, 0, SOIL_LOAD_RGBA);
}

bool System::initDepthBufferTexture(GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight, GLint& internalFormat, GLenum& format) {

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	internalFormat = GL_DEPTH_COMPONENT32;
	format = GL_DEPTH_COMPONENT;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolutionWidth, resolutionHeight, 0, format, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true ? textureID != 0 : false;

}

bool System::initDepthBufferTexture(Texture& texture, const GLuint& resolutionWidth, const GLuint& resolutionHeight)
{
	texture.getWidth() = resolutionWidth;
	texture.getHeight() = resolutionHeight;

	initDepthBufferTexture(texture.getTextureID(), texture.getWidth(), texture.getHeight(), texture.getInternalFormat(), texture.getFormat());

	return false;
}

bool System::checkIsFramebufferReady() {

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {

		switch (status) {

			case GL_FRAMEBUFFER_UNDEFINED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNDEFINED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNSUPPORTED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
				break;

		}

		return false;

	}

	return true;

}

void System::loadMesh(GLuint& vbo, GLuint& ebo, GLuint& vao, const Vertex* vertices, const GLuint& verticesSize, const GLuint* indices, const GLuint& indicesSize) {

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(GLfloat), (void*)vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), (void*)indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //TexCoord

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

static Texture* loadMaterialTextures(aiMaterial*& material, const aiTextureType& textureType, std::vector<Texture*>& textures_loaded, std::string& directory)
{
	if (material->GetTextureCount(textureType) == 0) return nullptr;

	aiString str;
	material->GetTexture(textureType, 0, &str);
	std::string texturePath = directory + static_cast<std::string>(str.C_Str());

	for (unsigned int j = 0; j < textures_loaded.size(); j++)
	{
		if (textures_loaded[j]->getPath().compare(texturePath) == 0)
		{
			return textures_loaded[j];
		}
	}

	Texture* texture = new Texture(texturePath.c_str());
	textures_loaded.push_back(texture);

	return texture;

}

static Material* processMaterial(aiMesh*& mesh, const aiScene*& scene, std::vector<Texture*>& textures_loaded, std::string& directory)
{
	aiMaterial*& material = scene->mMaterials[mesh->mMaterialIndex];

	Texture* diffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE, textures_loaded, directory);
	if (diffuse == nullptr)
	{
		diffuse = new Texture(512, 512);
	}
	Texture* specular = loadMaterialTextures(material, aiTextureType_SPECULAR, textures_loaded, directory);
	if (specular == nullptr)
	{
		specular = new Texture(512, 512);
	}
	Texture* emissive = loadMaterialTextures(material, aiTextureType_EMISSIVE, textures_loaded, directory);
	if (emissive == nullptr)
	{
		emissive = new Texture(512, 512);
	}
	//loadTextures(material, aiTextureType_HEIGHT);
	//loadTextures(material, aiTextureType_AMBIENT);

	return new Material(diffuse, specular, emissive, 32.0f, false, glm::vec3(1.0f));

}

static Mesh* processMesh(aiMesh*& mesh, const aiScene*& scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(Vertex());

		vertices[i].Position[0] = mesh->mVertices[i][0];
		vertices[i].Position[1] = mesh->mVertices[i][1];
		vertices[i].Position[2] = mesh->mVertices[i][2];

		if (mesh->HasNormals())
		{
			vertices[i].Normal[0] = mesh->mNormals[i][0];
			vertices[i].Normal[1] = mesh->mNormals[i][1];
			vertices[i].Normal[2] = mesh->mNormals[i][2];
		}

		if (mesh->mTextureCoords[0])
		{
			vertices[i].TexCoords[0] = mesh->mTextureCoords[0][i][0];
			vertices[i].TexCoords[1] = mesh->mTextureCoords[0][i][1];

			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;

			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
		}
		else
		{
			vertices[i].TexCoords = glm::vec2(0.0f, 0.0f);
		}

	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new Mesh( new VertexArrayObject(vertices.size(), vertices.data(), indices.size(), indices.data()) );

}

static void processNode(const aiNode* node, const aiScene*& scene, std::vector<Mesh*>& meshes, std::vector<Material*>& materials, std::vector<Texture*>& textures_loaded, std::string& directory)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh*& mesh = scene->mMeshes[node->mMeshes[i]];

		meshes.push_back(processMesh(mesh, scene));
		materials.push_back(processMaterial(mesh, scene, textures_loaded, directory));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshes, materials, textures_loaded, directory);
	}

}

void System::loadModel(const GLchar* dir, std::vector<Mesh*>& meshes, std::vector<Material*>& materials)
{
	if (meshes.size() > 0) meshes.clear();
	if (materials.size() > 0) materials.clear();

	std::string directory(dir);
	if (directory.find_last_of('/') != std::string::npos)
	{
		directory = directory.substr(0, directory.find_last_of('/') + 1);
	}
	else if (directory.find_last_of('\\') != std::string::npos) 
	{
		directory = directory.substr(0, directory.find_last_of('\\') + 1);
	}
	else
	{
		Logger::getInstance()->errorLog("Model path are invalid!");
		return;
	}

	std::vector<Texture*> textures_loaded;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(dir, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::getInstance()->errorLog("ERROR::ASSIMP:: %s\n", importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene, meshes, materials, textures_loaded, directory);

}

bool System::loadShaderRaw(GLuint& shaderID, const GLenum& type, const char *shaderSrc) {

	GLint compiled;

	// Create the shader object
	shaderID = glCreateShader(type);

	if (shaderID == 0) { return false; }

	// Load the shader source
	glShaderSource(shaderID, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shaderID);

	// Check the compile status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		GLint infoLen = 0;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1) {

			char infoLog[4096];

			glGetShaderInfoLog(shaderID, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to compile shader %s", infoLog);

		}

		glDeleteShader(shaderID);

		return false;

	}

	return true;

}

bool System::loadShaderFromFile(GLuint& shaderID, const GLenum& type, const std::string& path) {

	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	if (!sourceFile) {

		Logger::getInstance()->warningLog("Unable to open file %s", path.c_str());

		return false;

	}

	shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());

	const GLchar* shaderSource = shaderString.c_str();

	return System::loadShaderRaw(shaderID, type, shaderSource);

}

bool System::loadCubemapTexture(GLuint& textureID, const std::vector<std::string>& facesPath) {

	unsigned char* image;

	int resolutionWidth, resolutionHeight;

	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_TEXTURE_CUBE_MAP);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < facesPath.size(); i++) {

		image = SOIL_load_image(facesPath[i].c_str(), &resolutionWidth, &resolutionHeight, NULL, SOIL_LOAD_AUTO);

		//if(image) { printf("SOIL loading error: '%s'\n", SOIL_last_result()); }

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, resolutionWidth, resolutionWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glDisable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true ? textureID != 0 : false;

}

void System::editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	uint8_t data[3] = { r, g, b };

	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void System::applyBillboard(glm::mat4& modelViewMatrix) {

	// 1st colunm
	glm::value_ptr(modelViewMatrix)[0] = 1.0;
	glm::value_ptr(modelViewMatrix)[1] = 0.0;
	glm::value_ptr(modelViewMatrix)[2] = 0.0;

	// 2nd colunm
	glm::value_ptr(modelViewMatrix)[4] = 0.0;
	glm::value_ptr(modelViewMatrix)[5] = 1.0;
	glm::value_ptr(modelViewMatrix)[6] = 0.0;

	// 3rd colunm
	glm::value_ptr(modelViewMatrix)[8] = 0.0;
	glm::value_ptr(modelViewMatrix)[9] = 0.0;
	glm::value_ptr(modelViewMatrix)[10] = 1.0;

}

static std::string processMeshToVertexArrayObjectData(aiMesh*& mesh)
{
	std::string data = "";

	data = "static Vertex m_vertices[] = {\n";
	data += "\t//					Vertex							Normal					TexCoord\n";

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		data += "\tVertex(glm::vec3(" + std::to_string(mesh->mVertices[i][0]);
		data += "f, " + std::to_string(mesh->mVertices[i][1]);
		data += "f, " + std::to_string(mesh->mVertices[i][2]);

		if (mesh->HasNormals())
		{
			data += "f), glm::vec3(" + std::to_string(mesh->mNormals[i][0]);
			data += "f, " + std::to_string(mesh->mNormals[i][1]);
			data += "f, " + std::to_string(mesh->mNormals[i][2]);
		}
		else
		{
			data += "f), glm::vec3(0.0f, 0.0f, 0.0";
		}

		if (mesh->mTextureCoords[0])
		{
			data += "f), glm::vec2(" + std::to_string(mesh->mTextureCoords[0][i][0]);
			data += "f, " + std::to_string(mesh->mTextureCoords[0][i][1]) + "f))";
		}
		else
		{
			data += "f), glm::vec2(0.0f, 0.0f))";
		}
		if (i < (mesh->mNumVertices - 1)) data += ",";
		data += "\n";
	}
	data += "};\n\n";
	data += "static GLuint m_indices[] = {\n";
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];

		data += "\t";
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			data += std::to_string(face.mIndices[j]);
			if(i < (mesh->mNumFaces - 1) || j < (face.mNumIndices -1)) data += ",";
		}
		data += "\n";
	}
	data += "};\n\n";

	return data;
}

static std::string processNodeToVertexArrayObjectData(const aiNode* node, const aiScene*& scene)
{
	std::string data = "";
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh*& mesh = scene->mMeshes[node->mMeshes[i]];

		data += std::string(processMeshToVertexArrayObjectData(mesh));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		data += std::string(processNodeToVertexArrayObjectData(node->mChildren[i], scene));
	}

	return data;

}

void System::loadModelToVertexArrayObjectData(const GLchar* modelDir, const GLchar* saveFileDir)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelDir, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::getInstance()->errorLog("ERROR::ASSIMP:: %s\n", importer.GetErrorString());
		return;
	}

	std::string text = processNodeToVertexArrayObjectData(scene->mRootNode, scene);

	std::ofstream MyFile(std::string(saveFileDir) + ".txt");
	MyFile << text.c_str();
	MyFile.close();

}
