#version 410

in vec4 vColor;
in vec2 vTextureCoordinates;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;

void main()	
{ 
	FragColor = texture(DiffuseTexture, vTextureCoordinates); 
}