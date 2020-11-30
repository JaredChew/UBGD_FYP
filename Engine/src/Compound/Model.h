#pragma once

#include "ShaderProgram.h"

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL2/stb_image.h>

#include <utility>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

enum struct TextureType : unsigned int {
	Null = 0,
	Diffuse,
	Specular,
	Normal,
	Height
};

struct Texture2 {
	GLuint id;

	TextureType type;
	std::string path;

	int width, height;
	GLenum format;

	Texture2()
	{
		this->id = 0;

		this->type = TextureType::Null;
		this->path = "";

		this->width = this->height = 0;
		this->format = 0;
	}

	Texture2(GLuint id, TextureType type, std::string path, int width, int height, GLenum format)
	{
		this->id = id;

		this->type = type;
		this->path = path;

		this->width = width;
		this->height = height;
		this->format = format;
	}

	bool operator() (Texture2& texture) 
	{
		return (texture.id != 0);
	}

};

// Function
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
Texture2 TextureFromFile(const char* path, const std::string& directory);

class Mesh2 {
private:
	unsigned int VBO, EBO;

	void setupMesh();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture2> textures;

	unsigned int VAO;

public:
	Mesh2(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2> textures);

	void draw(ShaderProgram& shader);

};


class Model {
private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh2 processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture2> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);

public:
	std::vector<Texture2> textures_loaded;
	std::vector<Mesh2> meshes;
	std::string directory;
	bool gammaCorrection;
	//std::vector < std::pair< Mesh2, std::vector<GLuint> > > mesh_textureIndex;

public:
	Model(std::string const& path, bool gamma = false);

	void draw(ShaderProgram& shader);

};
