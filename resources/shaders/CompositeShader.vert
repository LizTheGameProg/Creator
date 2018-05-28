#version 330   
 
in vec4 Position;
in vec2 TexCoord1;

//Send to Fragment
out vec2 vUV;

void main() 
{
	vUV			= TexCoord1;
	gl_Position = Position; 
}