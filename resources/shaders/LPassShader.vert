#version 330   
 
//--------------------------    
// sent as vertex attributes
in vec4 Position;     
in vec4 Color;    
in vec2 TexCoord1;	
in vec4 Normal; 
//--------------------------  

//--------------------------    
// values sent to the fragment shader
out vec4 vPosition;
out vec2 vUV;
out vec4 vColor;	
out vec4 vNormal;
out float vDepth;
out vec4 vLightPosition;
//--------------------------    

uniform float farDistance = 1000;
uniform mat4 Model; 
uniform mat4 View;
uniform mat4 Projection;

void main() 
{
	//This will transform directions into viewSpace
	mat4 invViewModel = transpose(inverse(View * Model));
	vPosition = View * Model * Position;
	vUV     = TexCoord1;
	vColor  = Color;
	vNormal = normalize(invViewModel * Normal);
	vDepth = -vPosition.z / farDistance;
	vLightPosition = (View * Model)[3] ;

	gl_Position = Projection * vPosition; 
}