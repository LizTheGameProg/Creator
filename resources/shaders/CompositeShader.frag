#version 330   

//-------------------------------------
// values sent from the vertex shader
in vec2 vUV;
// output color
out vec4 outColor;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D LightTexture;

uniform vec2 screenSize;
uniform mat4 invProjection;
uniform float farDistance = 1000;

//Decode normal from spherical to euclidean space
vec3 decode (vec2 encodedNormals)
{
	vec2 fenc = encodedNormals * 4 - 2;
	float f = dot(fenc,fenc);
	float g = sqrt(1-f/4);
	vec3 n;
	n.xy = fenc*g;
	n.z = 1-f/2;
	return n;
}

void main() 
{ 
	vec2 UV = gl_FragCoord.xy / screenSize;

	vec4 normalTexVal = texture(NormalTexture, UV);
	vec4 vsNormals = vec4( decode(normalTexVal.xy), 0 );
	vec4 lightValues = texture(LightTexture, UV);

	float specular = lightValues.a;
	//For now just output the Normals Texture to the Screen
	vec4 diffuse = (texture( DiffuseTexture, UV) * vec4( lightValues.xyz, 1.0 )) + specular;
	
	outColor	= vec4( diffuse.xyz, 1.0 ) ;
}