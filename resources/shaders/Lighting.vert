#version 330

in vec4 Position;
in vec4 Colour;
in vec2 TexCoord;

void main()
{
	gl_Position = Position;
}