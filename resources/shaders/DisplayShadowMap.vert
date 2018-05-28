#version 150

in vec4 Position;	
in vec2 TexCoord;

out vec2 UV;
	
void main()
{
	UV = TexCoord;
	gl_Position = Position;
}