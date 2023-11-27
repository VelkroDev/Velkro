#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_CameraMatrix;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}