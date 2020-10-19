#include "geometry.h"

#include <vector>

#include <glm/gtc/constants.hpp>

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

}

void Geometry::drawSquare(const GLuint &texture) {

	static GLfloat vVertices[] = {

		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f

	};

	static GLfloat vColors[] = {

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f

	};

	static GLfloat vTexCoords[] = {

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

	};
	
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

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void *)sizeof(vVertices));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, (void *)(sizeof(vVertices) + sizeof(vColors)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Geometry::drawCircle(const GLuint &texture, const float &smoothness) {

	static std::vector<float> circleVertices;

	if (circleVertices.empty()) {

		GLfloat prevX = 0;
		GLfloat prevY = 0;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 0; i < (smoothness + 1); i++) {

			//z = length

			float nextX = 1.0f * cos(i * radian);
			float nextY = 1.0f * sin(i * radian);

			circleVertices.push_back(1.0f);
			circleVertices.push_back(1.0f);
			circleVertices.push_back(1.0f);

			circleVertices.push_back(1.0f + prevX);
			circleVertices.push_back(1.0f + prevY);
			circleVertices.push_back(1.0f);

			circleVertices.push_back(1.0f + nextX);
			circleVertices.push_back(1.0f + nextY);
			circleVertices.push_back(1.0f);

			prevX = nextX;
			prevY = nextY;

		}

	}

}

void Geometry::drawPyramid(const GLuint &texture) {

	static float pyramidVertices[] = {

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

void Geometry::drawCube(const GLuint &texture) {

	static float cubeVertices[] = {

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f

	};

}

void Geometry::drawSphere(const GLuint &texture, const float &smoothness) {

	static std::vector<float> sphereVertices;

	if (sphereVertices.empty()) {

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

					sphereVertices.push_back(prevX);
					sphereVertices.push_back(curveY);
					sphereVertices.push_back(prevZ);

					sphereVertices.push_back(nextX);
					sphereVertices.push_back(curveY);
					sphereVertices.push_back(nextZ);

					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos(j * radian));
					sphereVertices.push_back(prevCurveY);
					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin(j * radian));

					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos(j * radian));
					sphereVertices.push_back(prevCurveY);
					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin(j * radian));

					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * cos((j - 1) * radian));
					sphereVertices.push_back(prevCurveY);
					sphereVertices.push_back(sin(1.0f * cos((i - 1) * radian)) * sin((j - 1) * radian));

					sphereVertices.push_back(prevX);
					sphereVertices.push_back(curveY);
					sphereVertices.push_back(prevZ);

				}

				prevX = nextX;
				prevZ = nextZ;

			}

			prevCurveX = curveX;
			prevCurveY = curveY;

		}

	}

}

void Geometry::drawCone(const GLuint &texture, const float &smoothness) {

	static std::vector<float> coneVertices;

	if (coneVertices.empty()) {

		GLfloat prevX = 0.0f;
		GLfloat prevZ = 0.0f;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 0; i < (smoothness + 1); i++) {

			//z = length

			float nextX = 1.0f * cos(i * radian);
			float nextZ = 1.0f * sin(i * radian);

			coneVertices.push_back(1.0f);
			coneVertices.push_back(1.0f);
			coneVertices.push_back(1.0f);

			coneVertices.push_back(1.0f + prevX);
			coneVertices.push_back(1.0f);
			coneVertices.push_back(1.0f + prevZ);

			coneVertices.push_back(1.0f + nextX);
			coneVertices.push_back(1.0f);
			coneVertices.push_back(1.0f + nextZ);

			if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle


				coneVertices.push_back(1.0f + prevX);
				coneVertices.push_back(1.0f);
				coneVertices.push_back(1.0f + prevZ);

				coneVertices.push_back(1.0f + nextX);
				coneVertices.push_back(1.0f);
				coneVertices.push_back(1.0f + nextZ);

				coneVertices.push_back(1.0f);
				coneVertices.push_back(1.0f);
				coneVertices.push_back(1.0f);

			}

			prevX = nextX;
			prevZ = nextZ;

		}

	}

}

void Geometry::drawCylinder(const GLuint &texture, const float &smoothness) {

	static std::vector<float> cylinderVertices;

	if (cylinderVertices.empty()) {

		GLfloat prevX = 0;
		GLfloat prevZ = 0;

		GLfloat radian = glm::pi<float>() * 2 / smoothness;

		for (int i = 1; i < (smoothness + 1); i++) {

			float nextX = 1.0f * cos(i * radian);
			float nextZ = 1.0f * sin(i * radian);

			cylinderVertices.push_back(1.0f);
			cylinderVertices.push_back(1.0f);
			cylinderVertices.push_back(1.0f);

			cylinderVertices.push_back(prevX);
			cylinderVertices.push_back(1.0f);
			cylinderVertices.push_back(prevZ);

			cylinderVertices.push_back(nextX);
			cylinderVertices.push_back(1.0f);
			cylinderVertices.push_back(nextZ);

			cylinderVertices.push_back(1.0f);
			cylinderVertices.push_back(-1.0f);
			cylinderVertices.push_back(1.0f);

			cylinderVertices.push_back(prevX);
			cylinderVertices.push_back(-1.0f);
			cylinderVertices.push_back(prevZ);

			cylinderVertices.push_back(nextX);
			cylinderVertices.push_back(-1.0f);
			cylinderVertices.push_back(nextZ);

			//Body of cylinder
			if (i > 1) { //> 1 is to avoid an inner triangle caused when creating the first triangle of the circle

				cylinderVertices.push_back(prevX);
				cylinderVertices.push_back(1.0f);
				cylinderVertices.push_back(prevZ);

				cylinderVertices.push_back(prevX);
				cylinderVertices.push_back(-1.0f);
				cylinderVertices.push_back(prevZ);

				cylinderVertices.push_back(nextX);
				cylinderVertices.push_back(-1.0f);
				cylinderVertices.push_back(nextZ);

				cylinderVertices.push_back(prevX);
				cylinderVertices.push_back(1.0f);
				cylinderVertices.push_back(prevZ);

				cylinderVertices.push_back(nextX);
				cylinderVertices.push_back(1.0f);
				cylinderVertices.push_back(nextZ);

				cylinderVertices.push_back(nextX);
				cylinderVertices.push_back(-1.0f);
				cylinderVertices.push_back(nextZ);

			}

			prevX = nextX;
			prevZ = nextZ;

		}

	}

}

void Geometry::drawSkyBox(const GLuint &texture) {

	static float skyboxVertices[] = {

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f

	};

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	static GLuint vao_Cube;
	if (vao_Cube == 0) { glGenVertexArrays(1, &vao_Cube); }
	glBindVertexArray(vao_Cube);

	static unsigned int verticesBuffer_Cube;
	if (verticesBuffer_Cube == 0) { glGenBuffers(1, &verticesBuffer_Cube); }
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, skyboxVertices);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Geometry::setSquare(const GLuint& shaderProgramID, GLuint& vertexArrayObject, SetVertexArrayBufferFunction function) 
{
	static GLfloat vertices[] = {
			-1.0f,  1.0f, 0.0f,		0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,		1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,		0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,		1.0f, 1.0f
	};

	static GLuint indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	function(shaderProgramID, vertexArrayObject, vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

}

void Geometry::setVertexArrayObject(const GLuint& shaderProgramID, GLuint& vertexArrayObject, GLfloat* vertices, const GLuint& verticesSize, GLuint* indices, const GLuint& indicesSize)
{
	// |*  VSAPI = Vertex Shader Attribute Pointer Index  *|
#define VSAPI_Sprite_Position 0
#define VSAPI_Sprite_TexCoord 1

	GLuint vertexBufferObject, elementBufferObject;

	glUseProgram(shaderProgramID);

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(GLfloat), (void*)vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), (void*)indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(VSAPI_Sprite_Position);
	glEnableVertexAttribArray(VSAPI_Sprite_TexCoord);

	glVertexAttribPointer(VSAPI_Sprite_Position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(VSAPI_Sprite_TexCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Geometry::drawVertexArrayObject(GLuint& vertexArrayObject, const GLuint& indicesSize)
{
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0);

}