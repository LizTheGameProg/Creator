#version 330   

//-------------------------------------
// values sent from the vertex shader
in vec2 vUV;
in vec4 vNormal;
in vec4 wPos;
in vec4 vTangent;
in vec4 vBitangent;
//-------------------------------------

// output color
out vec4 Diffuse;
out vec4 Normal;
out vec4 World;
out vec4 Tangent;
out vec4 Bitangent;

// textures
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;

uniform mat4 Model; 
uniform mat4 View;
uniform mat4 Projection;

void main() 
{ 
	Diffuse = texture(DiffuseTexture, vUV);
	Normal = vNormal;
	World = wPos;
	Tangent = vTangent;
	Bitangent = vBitangent;

	Normal = texture(NormalTexture, vUV);
	Normal = Projection * View * Model * Normal;
	//vec4 tNormal = texture(NormalTexture, vUV);
	//Normal = normalize(tNormal);
	//Normal = Model * View * Normal;
}