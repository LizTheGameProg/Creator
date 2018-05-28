#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 TextureCoordinates;
//layout(location = 3) in vec4 Normal;

out vec4 vColor;
out vec2 vTextureCoordinates;

uniform mat4 Model;
uniform mat4 ProjectionView;

void main() 
{
	vColor = Color;
	vTextureCoordinates = TextureCoordinates;

	gl_Position = ProjectionView * Model * Position;
}