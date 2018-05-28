#version 330   

in vec2 TexCoord;

// output color
out vec4 outColor;

// textures
uniform sampler2D DiffuseTexture;

void main() 
{ 
	outColor = texture(DiffuseTexture, TexCoord);
}