#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

uniform mat4 ProjectionView;

void main() 
{
	gl_Position = ProjectionView * Position;
}