#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Colour;

out vec4 vColour;

uniform mat4 ProjectionView;
uniform float time;
uniform float heightScale;

void main() 
{
	vec4 P = Position;
	P.y += sin( time + Position.x ) * heightScale;
	P.y -= cos( time + Position.z ) * heightScale;
	vColour = Colour;
	vColour.r = sin(P.y);
	vColour.g = cos(P.y);
	vColour.b = tan(P.y);
	gl_Position = ProjectionView * P;
}