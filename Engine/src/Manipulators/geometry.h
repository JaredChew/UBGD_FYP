#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Geometry {

	void generateTriangleMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateSquareMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCircleMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	//void generateStadiumMesh(const float& smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);

	void generatePyramidMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateSphereMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateConeMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateCylinderMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);

}

