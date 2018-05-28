#version 330   

//-------------------------------------
// values sent from the vertex shader
in vec4 vPosition;
in vec2 vUV;
in vec4 vColor;
in vec4 vNormal;
in float vDepth;
//-------------------------------------

// output color
out vec4 DiffuseTexture;
out vec4 NormalTexture;

// textures
uniform sampler2D Diffuse;
//Used to eoncode normal to spherical coordinate angles
vec2 encode (vec3 vsNormal)
{
	float f = sqrt(8 * vsNormal.z + 8);
	return vsNormal.xy / f + 0.5;
}


void main() 
{ 
	DiffuseTexture	= texture(Diffuse, vUV) * vColor;
	NormalTexture	= vec4( encode(vNormal.xyz), vDepth, 1.0 );
}