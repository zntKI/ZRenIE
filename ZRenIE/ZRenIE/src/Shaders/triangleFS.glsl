#version 330 core

in vec3 fragPos;

out vec4 o_fragColor;

void main()
{
	o_fragColor = vec4(fragPos, 1.0);
}