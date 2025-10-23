#version 330 core

layout (location = 0) in vec3 a_pos;

out vec3 fragPos;

void main()
{
	fragPos = a_pos;
	gl_Position = vec4(a_pos, 1.0);
}