#version 410

in vec2 vTexCoord;

out vec4 FragColour;

uniform sampler2D albedoTexture;
uniform sampler2D lightTexture;

void main() {
	
	vec3 light = texture(lightTexture, vTexCoord).rgb;
	vec3 albedo = texture(albedoTexture, vTexCoord).rgb;

	FragColour = vec4(albedo * light, 1);
}