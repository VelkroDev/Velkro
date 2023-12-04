#version 460 core

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec3 colour;
in vec2 texCoord;

uniform vec3 u_CameraPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	float distance = distance(u_CameraPos, position);
	
	FragColor = texture(specular0, texCoord);
}