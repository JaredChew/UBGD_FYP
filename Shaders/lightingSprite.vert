#version 330 core

layout (Location = 0) in vec3 vPosition;
layout (Location = 1) in vec3 vNormal;
layout (Location = 2) in vec2 vTexCoord;

out vec3 fPos;
out vec3 fNormal;
out vec2 fTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
	fPos = vec3(uModelMatrix * vec4(vPosition, 1.0));
	fNormal = mat3(transpose(inverse(uModelMatrix))) * vNormal;
	fTexCoord = vTexCoord;
	
	gl_Position = (uProjectionMatrix * uViewMatrix * uModelMatrix) * vec4(vPosition, 1.0);

}
