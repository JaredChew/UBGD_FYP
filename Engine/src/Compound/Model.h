#pragma once

#include <vector>
#include <string>

class Mesh;
class Material;



class Model {
private:
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;

	std::string directory;
	bool isTemp;

public:
	Model(std::string const& path);
	Model(Mesh* mesh, Material* material);
	Model(std::vector<Mesh*>& meshes, std::vector<Material*>& materials);
	~Model();

	const bool& getIsTemp();

	std::vector<Mesh*>& getMesh();
	std::vector<Material*>& getMaterials();
	std::string& getDirectory();

};
