#version 460 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec3 vertexColour;
layout (location = 3) in vec2 vertexTexCoord;

out vec3 currentPos;

out vec3 position;
out vec3 normal;
out vec3 colour;
out vec2 texCoord;

uniform mat4 u_CameraMatrix;

uniform mat4 u_ModelMatrix;
uniform mat4 u_TranslationMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ScaleMatrix;

void main()
{
	currentPos = vec3(u_ModelMatrix * u_TranslationMatrix * u_RotationMatrix * u_ScaleMatrix * vec4(vertexPos, 1.0f));

	position = vertexPos;
	normal = vertexNormal;
	colour = vertexColour;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * vertexTexCoord;

	gl_Position = u_CameraMatrix * vec4(currentPos.xyz, 1.0);
}