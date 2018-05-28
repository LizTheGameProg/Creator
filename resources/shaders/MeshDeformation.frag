#version 330   

//-------------------------------------
// values sent from the vertex shader

in vec2 vUV;
in vec4 vColor;

//-------------------------------------

// output color
out vec4 outColor;

// textures
uniform sampler2D DiffuseTexture;

void main() 
{ 
	outColor = texture2D( DiffuseTexture, vUV.xy ) * vColor;
	outColor.a = 1;
}