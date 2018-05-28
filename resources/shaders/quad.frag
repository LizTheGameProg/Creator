#version 330

uniform sampler2D DiffuseTexture;
uniform sampler2D LightingTexture;

uniform vec2 screenSize;

void main()
{
	vec2 UV = gl_FragCoord.xy / screenSize;

	gl_FragColor = texture(DiffuseTexture, UV) * texture(LightingTexture, UV);
}