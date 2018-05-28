#version 330   
 
//--------------------------    
// sent as vertex attributes
in vec4 Position;     
in vec4 Color;     
in vec2 TexCoord1;	
//--------------------------  

//--------------------------    
// values sent to the fragment shader
out vec2 vUV;
out vec4 vColor;	
//--------------------------    


uniform mat4 Model; 
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

void main() 
{
    vUV = TexCoord1;
    
	float heightScale = 0.5;

	vec4 P = Position;
	P.y += sin(Time + Position.x) * heightScale;
	P.y += cos(Time + Position.z) * heightScale;

	vec4 C = Color;
	C.r += sin(Time * Color.r * P.x);
	C.g += cos(Time * Color.g * P.z);
	C.b += sin(Time * Color.b * P.y);
	vColor = C;

    gl_Position = Projection * View * Model * P; 
}