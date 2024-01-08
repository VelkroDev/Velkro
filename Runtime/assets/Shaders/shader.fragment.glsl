#version 460 core

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec3 colour;
in vec2 texCoord;
in int texID;

uniform vec3 u_CameraPos;

uniform sampler2D diffuse;
uniform sampler2D specular;

void main()
{
	float distance = distance(u_CameraPos, position);
	
	FragColor = (vec4(colour, 1.0) + texture(diffuse, texCoord)) / vec4(distance, distance, distance, 1.0);
}