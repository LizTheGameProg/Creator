#version 150

in vec2 TexCoord;

uniform sampler2D textureMap;

void main()
{
	gl_FragColor = texture( textureMap, TexCoord );
}