#version 330

in vec2 textureCoord;

out vec4 fragColour;

uniform sampler2D originalMap;

uniform int horizontal;

void main()
{		
	vec2 texelSize = 1.0f / textureSize( originalMap, 0 );

	if (horizontal == 1)
		texelSize.y = 0;
	else
		texelSize.x = 0;

	fragColour.rgb = texture(originalMap, textureCoord - vec2(4) * texelSize).rgb * 0.05f;
	fragColour.rgb += texture(originalMap, textureCoord - vec2(3) * texelSize).rgb * 0.09f;
	fragColour.rgb += texture(originalMap, textureCoord - vec2(2) * texelSize).rgb * 0.12f;
	fragColour.rgb += texture(originalMap, textureCoord - vec2(1) * texelSize).rgb * 0.15f;
	fragColour.rgb += texture(originalMap, textureCoord).rgb * 0.16f;
	fragColour.rgb += texture(originalMap, textureCoord + vec2(1) * texelSize).rgb * 0.15f;
	fragColour.rgb += texture(originalMap, textureCoord + vec2(2) * texelSize).rgb * 0.12f;
	fragColour.rgb += texture(originalMap, textureCoord + vec2(3) * texelSize).rgb * 0.09f;
	fragColour.rgb += texture(originalMap, textureCoord + vec2(4) * texelSize).rgb * 0.05f;

	fragColour.a = 1;
}