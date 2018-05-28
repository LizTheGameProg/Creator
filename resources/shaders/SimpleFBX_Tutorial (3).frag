#version 330   

//-------------------------------------
// values sent from the vertex shader

in vec2 vUV;
in vec4 vColor;

// textures
uniform sampler2D DiffuseTexture;

void main() 
{ 
	gl_FragColor = texture(DiffuseTexture, vUV);
}