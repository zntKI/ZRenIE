#version 330 core

layout (location = 0) in vec3 a_pos;

uniform mat4 u_MVP;

out vec3 fragPos;

void main()
{
	fragPos = a_pos;
	gl_Position = u_MVP * vec4(a_pos, 1.0);
}