#version 330 core

uniform vec3 u_Color;

out vec4 o_fragColor;

void main()
{
	o_fragColor = vec4(u_Color, 1.0);
}