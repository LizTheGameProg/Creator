#version 150

in vec4 Position;

uniform mat4 lightProjectionViewWorld;
	
void main()
{
	gl_Position = lightProjectionViewWorld * Position;
}