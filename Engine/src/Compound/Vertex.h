#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//glm::vec3 Tangent;
	//glm::vec3 Bitangent;

	Vertex()
	{
		Position = glm::vec3(0.0f);
		Normal = glm::vec3(0.0f);
		TexCoords = glm::vec2(0.0f);
	}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoords)
	{
		Position = position;
		Normal = normal;
		TexCoords = texCoords;
	}
};