#version 330   

in vec4 Position;
in vec4 Normal;
in vec2 TexCoord1;

out vec4 vPosition;
out vec4 vNormal;
out vec2 vTexCoord1;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() 
{
	vPosition = Projection * View * Model * Position;
	vNormal = Normal;
	vTexCoord1 = TexCoord1;
	gl_Position = vPosition;
}