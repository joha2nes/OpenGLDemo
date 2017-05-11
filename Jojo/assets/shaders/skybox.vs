#version 430

uniform mat4 projection;
uniform mat4 view;
uniform vec3 cameraPosition;

in vec3 position;
in vec2 texCoord;

out vec2 vsTexCoord;

void main()
{
	gl_Position = projection * view * vec4(position + cameraPosition, 1.0f);
	vsTexCoord = texCoord;
}