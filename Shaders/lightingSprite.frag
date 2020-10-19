#version 330 core
precision mediump float;

in vec3 fPos;
in vec3 fNormal;
in vec2 fTexCoord;

uniform float uAmbientStrength;
uniform float uSpecularStrength;

uniform vec3 uViewPosition;

uniform vec3 uLightPosition;
uniform vec3 uLightColor;

uniform vec4 uColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D sampler2d;

out vec4 FragColor;

void main()
{
	// Ambient map
	vec3 ambient = uAmbientStrength * uLightColor;
	vec4 objectColor = texture2D(sampler2d, fTexCoord);

	// Normal map
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(uLightPosition - fPos);
	
	// Diffuse map
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightDir;
	
	// Specular map
	float shininess = 32.0; // 2, 4, 8, 16, 32, 64, 128, 256
	
	vec3 viewDir = normalize(uViewPosition - fPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = uSpecularStrength * spec * uLightColor;
	
	// Final Color
	//gl_FragColor = vec4((ambient + diffuse + specular), 1.0f) * objectColor;
	//gl_FragColor = vec4((ambient + diffuse), 1.0) * objectColor;
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);//objectColor;
}