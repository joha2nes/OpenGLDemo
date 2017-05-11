#version 430

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec3 vsPosition;
out vec3 vsNormal;
out vec2 vsTexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);

	vsPosition = position;
	vsNormal = normalize(mat3(model) * normal);
	vsTexCoord = texCoord;
}