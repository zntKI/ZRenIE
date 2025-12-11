#version 330 core

in vec2 texCoords;

uniform sampler2D u_Texture;

out vec4 outColor;

void main()
{
	outColor = texture(u_Texture, texCoords);
}