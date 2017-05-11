#version 430

uniform sampler2D texture;
uniform vec4 color;

in vec2 vsTexCoord;

out vec4 fsColor;

void main()
{
	fsColor = color * vec4(1.0f, 1.0f, 1.0f, texture2D(texture, vsTexCoord).r);
}