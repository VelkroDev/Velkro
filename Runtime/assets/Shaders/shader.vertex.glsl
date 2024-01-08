#version 460 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColour;
layout (location = 3) in vec2 vertexTexCoord;
layout (location = 4) in int vertexTexID;

out vec3 position;
out vec3 normal;
out vec3 colour;
out vec2 texCoord;
out int texID;

uniform mat4 u_CameraMatrix;

uniform mat4 u_ModelMatrix;

void main()
{
	position = vec3(u_ModelMatrix * vec4(vertexPos, 1.0f));
	normal = vertexNormal;
	colour = vertexColour;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * vertexTexCoord;
	texID = vertexTexID;

	gl_Position = u_CameraMatrix * vec4(position.xyz, 1.0);
}