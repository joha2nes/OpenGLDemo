#version 430

uniform sampler2D texture;

in vec2 vsTexCoord;

out vec4 outColor;

void main()
{
	outColor = texture2D(texture, vsTexCoord);
}