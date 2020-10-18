#include "geometry.h"

#include <vector>

#include <glm/gtc/constants.hpp>

void Geometry::generateTriangleMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

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

	for (int i = 0; i < sizeof(_vertices) / sizeof(GLfloat); ++i) {

		vertices.push_back(_vertices[i]);

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