#version 430

struct Light
{
	vec3 direction;
	vec3 diffusion;
	vec3 ambience;
};

uniform Light light;
uniform sampler2D texture;

in vec3 vsPosition;
in vec3 vsNormal;
in vec2 vsTexCoord;

out vec4 outColor;

void main()
{
	float brightness = dot(-light.direction, vsNormal);

	outColor = vec4(light.ambience + brightness * light.diffusion, 1.0f) * texture2D(texture, vsTexCoord);
}