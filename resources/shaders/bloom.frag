#version 330

in vec2 textureCoord;

out vec4 fragColour;

uniform sampler2D originalMap;
uniform sampler2D blurredMap;

void main()
{
	fragColour.rgb = texture( originalMap, textureCoord ).rgb;

	// add bloom
	fragColour.rgb += texture( blurredMap, textureCoord ).rgb;
		
	fragColour.a = 1;
}