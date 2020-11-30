#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdlib.h>

// |*  VSAPI = Vertex Shader Attribute Pointer Index  *|
#define VSAPI_Sprite_Position 0
// |*  VSAPI = Vertex Shader Attribute Pointer Index  *|
#define VSAPI_Sprite_Normal 1
// |*  VSAPI = Vertex Shader Attribute Pointer Index  *|
#define VSAPI_Sprite_TexCoord 2

struct Vertex;

struct VertexArrayObject
{
	GLuint vaoID;
	GLuint vboID;
	GLuint eboID;

	Vertex* vertices;
	GLuint* indices;

	GLint verticesSize;
	GLint indicesSize;

	VertexArrayObject();
	~VertexArrayObject();

	void init(const GLint& verticesSize, Vertex* vertices, const GLint& indicesSize, GLuint* indices);

	void startGenerateVertexArrays();
	void bindBufferData(const GLenum& target, const GLuint& bufferID, const GLsizeiptr& size, const void* pointer, const GLenum& usage);
	void applyVertexAttribPointer(const GLuint& index, const GLint& size, const GLenum& type, const GLboolean& normalized, const GLsizei& stride, const void* pointer);
	void finishGenerateVertexArrays();

	void bind();
	void clear();
	bool empty();

};