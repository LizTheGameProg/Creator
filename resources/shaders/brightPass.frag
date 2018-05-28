#version 330

in vec2 textureCoord;

out vec4 fragColour;

uniform sampler2D originalMap;

uniform float brightnessThreshold;

void main()
{
	// pre-defined value used to calculate pixel luminance
	vec3 luminanceVector = vec3(0.2125f, 0.7154f, 0.0721f);

	vec3 rgb = texture( originalMap, textureCoord ).rgb;

	// determine pixel luminance
	float luminance = dot( luminanceVector, rgb );

	// cutoff pixels that aren't above our brightness threshold
	luminance = max( 0.0f, luminance - brightnessThreshold );
	fragColour.rgb = rgb * sign(luminance);
	fragColour.a = 1;
}