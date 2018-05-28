#version 330   

// values sent from the vertex shader
in vec2 vUV;
in vec4 vColor;


// output color
out vec4 outColor;

// textures
uniform sampler2D DiffuseTexture;
uniform sampler2D DecayTexture;

// other uniforms
uniform float DecayValue;

void main() 
{ 
	outColor = texture2D( DiffuseTexture, vUV.xy ) * vColor;
	
	float decay = 0.0;
	
	if( texture2D( DecayTexture, vUV.xy ).r < DecayValue )
		decay = 1.0;

	outColor.a = decay;
}