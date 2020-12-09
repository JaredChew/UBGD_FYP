#include "vertexArrayObject.h"
#include "vertex.h"
#include "../Utilities/logger.h"

VertexArrayObject::VertexArrayObject()
{
	this->vaoID = this->vboID = this->eboID = 0;

	this->vertices = nullptr;
	this->indices = nullptr;

	this->verticesSize = this->indicesSize = 0;
}
VertexArrayObject::VertexArrayObject(const GLint& vertexSize, Vertex* vertex, const GLint& indicesSize, GLuint* indices)
{
	if (vertex == nullptr || indices == nullptr)
	{
		// Logger::warningLog("");
		return;
	}
	this->vertices = vertex;
	this->indices = indices;

	this->verticesSize = vertexSize;
	this->indicesSize = indicesSize;

	startGenerateVertexArrays();
	{

		bindArrayBufferData(this->verticesSize * sizeof(Vertex), (void*)&vertex[0], GL_STATIC_DRAW);
		bindElementArrayBufferData(this->indicesSize * sizeof(GLuint), (void*)&indices[0], GL_STATIC_DRAW);

		applyVertexAttribPointer(VSAPI_Sprite_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		applyVertexAttribPointer(VSAPI_Sprite_Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		applyVertexAttribPointer(VSAPI_Sprite_TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	}
	finishGenerateVertexArrays();

	/*
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &eboID);

	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, this->verticesSize * sizeof(Vertex), (void*)&vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesSize * sizeof(GLuint), (void*)&indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(VSAPI_Sprite_Position);
	glEnableVertexAttribArray(VSAPI_Sprite_Normal);
	glEnableVertexAttribArray(VSAPI_Sprite_TexCoord);

	glVertexAttribPointer(VSAPI_Sprite_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glVertexAttribPointer(VSAPI_Sprite_Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(VSAPI_Sprite_TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(VSAPI_Sprite_Position);
	glDisableVertexAttribArray(VSAPI_Sprite_Normal);
	glDisableVertexAttribArray(VSAPI_Sprite_TexCoord);
	*/
}
VertexArrayObject::~VertexArrayObject()
{
	clear();
}

void VertexArrayObject::init(const GLint& vertexSize, Vertex* vertex, const GLint& indicesSize, GLuint* indices)
{
	if (vertex == nullptr || indices == nullptr)
	{
		// Logger::warningLog("");
		return;
	}
	this->vertices = vertex;
	this->indices = indices;

	this->verticesSize = vertexSize;
	this->indicesSize = indicesSize;

	startGenerateVertexArrays();
	{

		bindArrayBufferData(this->verticesSize * sizeof(Vertex), (void*)&vertex[0], GL_STATIC_DRAW);
		bindElementArrayBufferData(this->indicesSize * sizeof(GLuint), (void*)&indices[0], GL_STATIC_DRAW);

		applyVertexAttribPointer(VSAPI_Sprite_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		applyVertexAttribPointer(VSAPI_Sprite_Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		applyVertexAttribPointer(VSAPI_Sprite_TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	}
	finishGenerateVertexArrays();
}

void VertexArrayObject::startGenerateVertexArrays()
{
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &eboID);

	glBindVertexArray(vaoID);
}

void VertexArrayObject::bindArrayBufferData(const GLsizeiptr& size, const void* pointer, const GLenum& usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, pointer, usage);
}

void VertexArrayObject::bindElementArrayBufferData(const GLsizeiptr& size, const void* pointer, const GLenum& usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pointer, usage);
}

void VertexArrayObject::applyVertexAttribPointer(const GLuint& index, const GLint& size, const GLenum& type, const GLboolean& normalized, const GLsizei& stride, const void* pointer)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArrayObject::finishGenerateVertexArrays()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(vaoID);
	
}

void VertexArrayObject::clear()
{
	/*
	GLint nAttr = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttrib);
	glBindVertexArray(vaoId);
	for (int iAttr = 0; iAttr < nAttr; ++iAttr) {
		GLint vboId = 0;
		glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
		if (vboId > 0) {
			...
		}
	}
	*/

	if (eboID == 0)
		glDeleteBuffers(1, &eboID);
	if (vboID == 0) return;
		glDeleteBuffers(1, &vboID);
	if (vaoID == 0) return;
		glDeleteBuffers(1, &vaoID);

	vaoID = vboID = eboID = 0;
	
	vertices = nullptr;
	indices = nullptr;
	
	verticesSize = indicesSize = 0;
}

bool VertexArrayObject::empty()
{
	return (vaoID == 0);
}