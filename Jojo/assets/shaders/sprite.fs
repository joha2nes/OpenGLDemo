#version 430

uniform sampler2D texture;

in vec2 vsTexCoord;

out vec4 fsColor;

void main()
{
	fsColor = texture2D(texture, vsTexCoord);
}