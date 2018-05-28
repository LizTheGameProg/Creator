#version 330   
 
//--------------------------    
// sent as vertex attributes
in vec4 Position;     
in vec4 Color;     
in vec2 TexCoord1;	
in vec4 Normal;
in vec4 Tangent;
in vec4 Bitangent;
//--------------------------  

//--------------------------    
// values sent to the fragment shader
out vec2 vUV;
out vec4 vNormal;
out vec4 wPos;
out vec4 vTangent;
out vec4 vBitangent;
//--------------------------    

uniform mat4 Model; 
uniform mat4 View;
uniform mat4 Projection;

void main() 
{
    vUV = TexCoord1;
	vTangent		= View * Model * Tangent;
	vBitangent		= View * Model * Bitangent;
	vNormal			= View * Model * Normal;

	vTangent.a		= 1;
	vBitangent.a	= 1;
	vNormal.a		= 1;

	//vNormal = normalize(Normal);
	wPos = Projection * View * Model * Position;
	gl_Position = wPos;
	wPos.a = 1;
}