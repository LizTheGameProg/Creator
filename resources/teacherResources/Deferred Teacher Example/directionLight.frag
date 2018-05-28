#version 410

in vec2 vTexCoord;

out vec3 LightOutput;

// direction in view-space
uniform vec3 lightDirection;
uniform vec3 lightDiffuse;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;

void main() {
	
	vec3 normal = normalize( texture(normalTexture, vTexCoord).xyz );
	vec3 position = texture(positionTexture, vTexCoord).xyz;

	float d = max(0, dot(normal, -lightDirection));

	LightOutput = lightDiffuse * d;
}