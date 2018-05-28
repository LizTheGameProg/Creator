#version 150

in vec4 position;
in vec4 colour; // we'll ignore it
in vec2 textureCoordinate;

out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * position;
	texCoord = textureCoordinate;
}