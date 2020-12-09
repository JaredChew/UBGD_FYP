#include "model.h"

#include <glm/gtc/matrix_transform.hpp>


#include "../Manipulators/system.h"

#include "material.h"
#include "texture.h"
#include "mesh.h"

Model::Model(std::string const& path)
{
	
	this->directory = path;
	System::loadModel(path.c_str(), this->meshes, this->materials);

	isTemp = true;

}

Model::Model(Mesh* mesh, Material* material)
{

	this->directory = "";

	this->meshes.push_back(mesh);
	this->materials.push_back(material);

	isTemp = false;

}

Model::Model(std::vector<Mesh*>& meshes, std::vector<Material*>& materials)
{
	this->directory = "";

	this->meshes = meshes;
	this->materials = materials;

	isTemp = false;

}
Model::~Model()
{
	this->directory = "";

	if (!isTemp) return;


	for (size_t i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
	}

	for (size_t i = 0; i < meshes.size(); i++)
	{
		delete materials[i];
	}

	/*
	if ((destroyWithMeshFlag & DestroyWithModelFlag_None) != 0) return;

	if ((destroyWithMeshFlag & DestroyWithModelFlag_Mesh) != 0)
	{
		for (size_t i = 0; i < meshes.size(); i++)
		{
			delete meshes[i];
		}
	}

	if ((destroyWithMeshFlag & DestroyWithModelFlag_Material) != 0)
	{
		for (size_t i = 0; i < meshes.size(); i++)
		{
			delete materials[i];
		}
	}
	*/

}

const bool& Model::getIsTemp()
{
	return isTemp;
}

std::vector<Mesh*>& Model::getMesh()
{
	return meshes;
}

std::vector<Material*>& Model::getMaterials()
{
	return materials;
}

std::string& Model::getDirectory()
{
	return directory;
}