#version 330

in vec2 texCoord;
layout( location = 0) out vec4 fragColour;

uniform vec4 colour;
uniform sampler2D diffuseMap;

void main()
{
	fragColour = texture(diffuseMap, texCoord) * colour;
}