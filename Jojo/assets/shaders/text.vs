#version 430

uniform mat4 transformation;
uniform mat4 projection;

in vec2 position;
in vec2 texCoord;

out vec2 vsTexCoord;

void main()
{
	gl_Position = projection * transformation * vec4(position, 0.0f, 1.0f);
	vsTexCoord = texCoord;
}