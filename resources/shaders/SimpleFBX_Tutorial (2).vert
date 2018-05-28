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

void main() 
{
    vUV     = TexCoord1;
    vColor  = Color;
	    
    gl_Position = Projection * View * Model * Position; 
}