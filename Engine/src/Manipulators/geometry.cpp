#include "geometry.h"

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