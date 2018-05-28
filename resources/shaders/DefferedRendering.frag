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
uniform vec2 screenSize;
uniform sampler2D LightingTexture;

void main() 
{ 
	vec2 UV = gl_FragCoord.xy / screenSize;

	vec3 Diffuse = texture(DiffuseTexture, UV).rgb;
	vec3 Light = texture(LightingTexture, UV).rgb;

	outColor = vec4(Diffuse * Light, 1);
	
}