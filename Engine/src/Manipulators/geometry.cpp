#include "geometry.h"

#include <vector>

#include <glm/gtc/constants.hpp>

<<<<<<< HEAD
/*
typedef void(*GeometryCreateShadeP1Func)(const GLuint& texture);
typedef void(*GeometryCreateShadeP2Func)(const GLuint& texture, const float& smoothness);

void nullGeometryShadeP1Func(const GLuint& texture);
void nullGeometryShadeP2Func(const GLuint& texture, const float& smoothness);

GeometryCreateShadeP1Func Triangle_Func = triangle;
GeometryCreateShadeP1Func Square_Func = Geometry::drawSquare;
GeometryCreateShadeP2Func Circle_Func = Geometry::drawCircle;

GeometryCreateShadeP1Func Pyramid_Func = Geometry::drawPyramid;
GeometryCreateShadeP1Func Cube_Func = Geometry::drawCube;
GeometryCreateShadeP2Func Sphere_Func = Geometry::drawSphere;
GeometryCreateShadeP2Func Cone_Func = Geometry::drawCone;
GeometryCreateShadeP2Func Cylinder_Func = Geometry::drawCylinder;
GeometryCreateShadeP1Func SkyBox_Func = Geometry::drawSkyBox;

void nullGeometryCreateShadeP1Func(const GLuint& texture)
{
	return;
}

void nullGeometryCreateShadeP2Func(const GLuint& texture, const float& smoothness)
{
	return;
}

void triangle(const GLuint& texture) {

	static GLfloat vVertices[] = {

		-1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f

	};

	static GLfloat vColors[] = {

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

	};

	static GLfloat vTexCoords[] = {

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

	};

	Triangle_Func = nullGeometryCreateShadeP1Func;
}
*/

void Geometry::squareLighting(GLuint& texture)
{
	static GLfloat vVertices[] = {
		//		vertices			norm				texcoord
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f

	};

	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vertexArrayObject_Square = 0;
	static GLuint vertexBufferObject_Square = 0;

	if (vertexArrayObject_Square != 0)
	{
		glBindVertexArray(vertexArrayObject_Square);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		return;
	}

	glGenVertexArrays(1, &vertexArrayObject_Square);
	glBindVertexArray(vertexArrayObject_Square);

	glGenBuffers(1, &vertexBufferObject_Square);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), (void*)vVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Geometry::cudeLighting(GLuint& texture)
{
	static GLfloat cudeLighting_Vertices[] = {

		// Front plane
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,


		// Back plane			 	   
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,


		// Left plane				   
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,


		// Right plane				   		   
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,

		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,


		// Top plane			 	   		   
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,


		// Bottom plane			 			   
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,

		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f


	};

	/*
	static GLfloat cudeLighting_Vertices[] = {

		// Front plane
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,

		 // Back plane			 	   
		  0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,

		 // Left plane				   
		 -0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,

		 // Right plane				   		   
		  0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

		  // Top plane			 	   		   
		  -0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		  -0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,

		   // Bottom plane			 			   
		   -0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f
	};

	static GLuint cudeLighting_indices[] = {

		0, 1, 2,
		3, 2, 1,

		4, 5, 6,
		7, 6, 5,

		8, 9, 10,
		11, 10, 9,

		12, 13, 14,
		15, 14, 13,

		16, 17, 18,
		19, 18, 17,

		20, 21, 22,
		23, 22, 21
	};
	*/


	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vertexArrayObject_Cude = 0;
	static GLuint vertexBufferObject_Cude = 0;
	//static GLuint elementBufferObject_Cude = 0;

	/*
	if (vertexArrayObject_Cude != 0)
	{
		glBindVertexArray(vertexArrayObject_Cude);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, sizeof(cudeLighting_indices), GL_UNSIGNED_INT, 0);
		return;
	}
	*/

	if (vertexArrayObject_Cude == 0)
	{
		glGenVertexArrays(1, &vertexArrayObject_Cude);
		glGenBuffers(1, &vertexBufferObject_Cude);
		//glGenBuffers(1, &elementBufferObject_Cude);
	}

	glBindVertexArray(vertexArrayObject_Cude);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Cude);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cudeLighting_Vertices), cudeLighting_Vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject_Cude);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cudeLighting_indices), (void*)cudeLighting_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	
	//glDrawElements(GL_TRIANGLES, (sizeof(cudeLighting_indices) / sizeof(cudeLighting_indices[0])), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}



void Geometry::triangle(GLuint& texture)
{
	static GLfloat vVertices[] = {
		//		vertices				color				texcoord
		 0.0f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.5f, 1.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f

	};

	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vertexArrayObject_Square = 0;
	static GLuint vertexBufferObject_Square = 0;

	if (vertexArrayObject_Square != 0)
	{
		glBindVertexArray(vertexArrayObject_Square);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		return;
	}

	glGenVertexArrays(1, &vertexArrayObject_Square);
	glBindVertexArray(vertexArrayObject_Square);

	glGenBuffers(1, &vertexBufferObject_Square);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), (void*)vVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Geometry::square(GLuint& texture)
{
	static GLfloat vVertices[] = {
		//		vertices				color				texcoord
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f,

		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f

	};

	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vertexArrayObject_Square = 0;
	static GLuint vertexBufferObject_Square = 0;

	if (vertexArrayObject_Square != 0)
	{
		glBindVertexArray(vertexArrayObject_Square);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		return;
	}

	glGenVertexArrays(1, &vertexArrayObject_Square);
	glBindVertexArray(vertexArrayObject_Square);

	glGenBuffers(1, &vertexBufferObject_Square);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), (void*)vVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Geometry::circle(GLuint& texture)
{
	static std::vector<GLfloat> circleVertices;

	if (circleVertices.empty()) {

		GLfloat smoothness = 32.0f;
		GLfloat radian = (2.0f * glm::pi<float>()) / smoothness;
		GLfloat radius = 0.5f;

		GLfloat prevX = radius * sinf(0.0f * radian);
		GLfloat prevY = radius * cosf(0.0f * radian);

		for (float i = 1.0f; i <= smoothness; i++) {

			//z = length
			
			GLfloat nextX = radius * sinf(i * radian);
			GLfloat nextY = radius * cosf(i * radian);

			circleVertices.push_back(0.0f); // x
			circleVertices.push_back(0.0f); // y
			circleVertices.push_back(0.0f); // z

			circleVertices.push_back(1.0f); // r
			circleVertices.push_back(1.0f); // g
			circleVertices.push_back(1.0f); // b
			circleVertices.push_back(1.0f); // a

			circleVertices.push_back(0.5f); // u
			circleVertices.push_back(0.5f); // v


			circleVertices.push_back(prevX); // x
			circleVertices.push_back(prevY); // y
			circleVertices.push_back(0.0f);  // z

			circleVertices.push_back(1.0f); // r
			circleVertices.push_back(1.0f); // g
			circleVertices.push_back(1.0f); // b
			circleVertices.push_back(1.0f); // a

			circleVertices.push_back(prevX + 0.5f); // u
			circleVertices.push_back(prevY + 0.5f); // v


			circleVertices.push_back(nextX); // x
			circleVertices.push_back(nextY); // y
			circleVertices.push_back(0.0f);  // z

			circleVertices.push_back(1.0f); // r
			circleVertices.push_back(1.0f); // g
			circleVertices.push_back(1.0f); // b
			circleVertices.push_back(1.0f); // a

			circleVertices.push_back(nextX + 0.5f); // u
			circleVertices.push_back(nextY + 0.5f); // v

			prevX = nextX;
			prevY = nextY;

		}

	}

	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vertexArrayObject_Square = 0;
	static GLuint vertexBufferObject_Square = 0;

	if (vertexArrayObject_Square != 0)
	{
		glBindVertexArray(vertexArrayObject_Square);
		glDrawArrays(GL_TRIANGLES, 0, (circleVertices.size() / 9));
		return;
	}

	glGenVertexArrays(1, &vertexArrayObject_Square);
	glBindVertexArray(vertexArrayObject_Square);

	glGenBuffers(1, &vertexBufferObject_Square);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Square);
	glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), (void*)circleVertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, (circleVertices.size() / 9));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Geometry::drawTriangle(const GLuint &texture) {
=======
void Geometry::generateTriangleMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

	static GLfloat _vertices[] = {

		-1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f

	};

}

void Geometry::generateSquareMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static GLfloat _vertices[] = {

			-1.0f,  1.0f, 0.0f,		0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,		1.0f, 0.0f,

			-1.0f, -1.0f, 0.0f,		0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,		1.0f, 1.0f

	};

	static GLuint _indices[] = {

		0, 1, 2,
		1, 2, 3

	};
<<<<<<< HEAD
	
	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vao_Square;
	if (vao_Square == 0) { glGenVertexArrays(1, &vao_Square); }
	glBindVertexArray(vao_Square);

	static unsigned int verticesBuffer_Square;
	if (verticesBuffer_Square == 0) { glGenBuffers(1, &verticesBuffer_Square); }
		
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer_Square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices) + sizeof(vColors) + sizeof(vTexCoords), vVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vVertices), vVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vVertices), sizeof(vColors), vColors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vVertices) + sizeof(vColors), sizeof(vTexCoords), vTexCoords);
=======

	for (int i = 0; i < sizeof(_vertices) / sizeof(GLfloat); ++i) {

		vertices.push_back(_vertices[i]);
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487

	}

	for (int i = 0; i < sizeof(_indices) / sizeof(GLuint); ++i) {

		indices.push_back(_indices[i]);

	}

}

void Geometry::generateCircleMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static std::vector<float> _vertices;

	if (vertices.empty()) {

		GLfloat prevX = 0;
		GLfloat prevY = 0;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 0; i < (smoothness + 1); i++) {

			//z = length

			float nextX = 1.0f * cos(i * radian);
			float nextY = 1.0f * sin(i * radian);

			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);

			vertices.push_back(1.0f + prevX);
			vertices.push_back(1.0f + prevY);
			vertices.push_back(1.0f);

			vertices.push_back(1.0f + nextX);
			vertices.push_back(1.0f + nextY);
			vertices.push_back(1.0f);

			prevX = nextX;
			prevY = nextY;

		}

	}

}

void Geometry::generatePyramidMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static float _vertices[] = {

		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,

		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,

		 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f

	};

}

void Geometry::generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static GLfloat _vertices[] = {

		// Front plane
		-1.0f,  1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

		 1.0f, -1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,


		 // Back plane			 	   
		  0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,


		 // Left plane				   
		 -0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,

		 -0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,


		 // Right plane				   		   
		  0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,

		  0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,


		  // Top plane			 	   		   
		  -0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		  -0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,

		   0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		  -0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,


		   // Bottom plane			 			   
		   -0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,

			0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
		   -0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f


	};

	static GLuint _indices[] = {

		0, 1, 2,
		3, 2, 1,

		4, 5, 6,
		7, 6, 5,

		8, 9, 10,
		11, 10, 9,

		12, 13, 14,
		15, 14, 13,

		16, 17, 18,
		19, 18, 17,

		20, 21, 22,
		23, 22, 21
	};

}

void Geometry::generateSphereMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static std::vector<float> _vertices;

	if (vertices.empty()) {

		GLfloat prevCurveX = 0;
		GLfloat prevCurveY = 0;

		GLfloat prevX = 0;
		GLfloat prevZ = 0;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 1; i <= smoothness; i++) {

			//Curvature of sphere

			float curveX = 1.0f * cos(i * radian);
			float curveY = 1.0f * sin(i * radian);

			for (int j = 1; j <= smoothness; j++) {

				//Triangles to connect into a sphere

				float nextX = sin(curveX) * cos(j * radian);
				float nextZ = sin(curveX) * sin(j * radian);

				if (i > 1) {

					vertices.push_back(prevX);
					vertices.push_back(curveY);
					vertices.push_back(prevZ);

					vertices.push_back(nextX);
					vertices.push_back(curveY);
					vertices.push_back(nextZ);

					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos(j * radian));
					vertices.push_back(prevCurveY);
					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin(j * radian));

					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos(j * radian));
					vertices.push_back(prevCurveY);
					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin(j * radian));

					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos((j - 1) * radian));
					vertices.push_back(prevCurveY);
					vertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin((j - 1) * radian));

					vertices.push_back(prevX);
					vertices.push_back(curveY);
					vertices.push_back(prevZ);

				}

				prevX = nextX;
				prevZ = nextZ;

			}

			prevCurveX = curveX;
			prevCurveY = curveY;

		}

	}

}

void Geometry::generateConeMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static std::vector<float> _vertices;

	if (vertices.empty()) {

		GLfloat prevX = 0.0f;
		GLfloat prevZ = 0.0f;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 0; i < (smoothness + 1); i++) {

			//z = length

			float nextX = 1.0f * cos(i * radian);
			float nextZ = 1.0f * sin(i * radian);

			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);

			vertices.push_back(1.0f + prevX);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f + prevZ);

			vertices.push_back(1.0f + nextX);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f + nextZ);

			if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle


				vertices.push_back(1.0f + prevX);
				vertices.push_back(1.0f);
				vertices.push_back(1.0f + prevZ);

				vertices.push_back(1.0f + nextX);
				vertices.push_back(1.0f);
				vertices.push_back(1.0f + nextZ);

				vertices.push_back(1.0f);
				vertices.push_back(1.0f);
				vertices.push_back(1.0f);

			}

			prevX = nextX;
			prevZ = nextZ;

		}

	}

}

void Geometry::generateCylinderMesh(const float &smoothness, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	static std::vector<float> _vertices;

	if (vertices.empty()) {

		GLfloat prevX = 0;
		GLfloat prevZ = 0;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 1; i < (smoothness + 1); i++) {

			float nextX = 1.0f * cos(i * radian);
			float nextZ = 1.0f * sin(i * radian);

			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);

			vertices.push_back(prevX);
			vertices.push_back(1.0f);
			vertices.push_back(prevZ);

			vertices.push_back(nextX);
			vertices.push_back(1.0f);
			vertices.push_back(nextZ);

			vertices.push_back(1.0f);
			vertices.push_back(-1.0f);
			vertices.push_back(1.0f);

			vertices.push_back(prevX);
			vertices.push_back(-1.0f);
			vertices.push_back(prevZ);

			vertices.push_back(nextX);
			vertices.push_back(-1.0f);
			vertices.push_back(nextZ);

			//Body of cylinder
			if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

				vertices.push_back(prevX);
				vertices.push_back(1.0f);
				vertices.push_back(prevZ);

				vertices.push_back(prevX);
				vertices.push_back(-1.0f);
				vertices.push_back(prevZ);

				vertices.push_back(nextX);
				vertices.push_back(-1.0f);
				vertices.push_back(nextZ);

				vertices.push_back(prevX);
				vertices.push_back(1.0f);
				vertices.push_back(prevZ);

				vertices.push_back(nextX);
				vertices.push_back(1.0f);
				vertices.push_back(nextZ);

				vertices.push_back(nextX);
				vertices.push_back(-1.0f);
				vertices.push_back(nextZ);

			}

			prevX = nextX;
			prevZ = nextZ;

		}

	}

}