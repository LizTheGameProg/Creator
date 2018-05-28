#version 330   

//-------------------------------------
// values sent from the vertex shader
in vec4 vPosition;
in vec2 vUV;
in vec4 vColor;
in vec4 vNormal;
in float vDepth;
in vec4 vLightPosition;
//-------------------------------------

// output color
out vec4 LightTexture;
//Uniforms 
uniform vec2 screenSize;
uniform mat4 invProjection;
uniform float farDistance = 1000;
// textures
uniform sampler2D NormalTexture;

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
	//Get the Euclidian View Space Normal from the Spherical co-ordinates in the RG channels of the image
	vec4 geometryNormal = normalize(vec4( decode(normalTexVal.xy), 0 ));
	
	//Calculate the View Space position of our geometry
	vec4 E = invProjection * vec4( UV * 2 - 1, 1, 1 );
	//P is the view space positon of our geometry
	vec4 P = E * normalTexVal.z * farDistance;
	//E is the vector from the camera to our geometry
	E = vec4( -normalize(E.xyz), 0.0 );

	
	//We can use vNormal as our view space light's direction for pointlights only
	vec3 L = P.xyz - vLightPosition.xyz;
	float fDist = length(L);
	L = normalize(L);
	float intensity = 1 - smoothstep( 6, 12, fDist );
	if( intensity < 0.4 )
	{
		discard;
	}
	//calculate the lambertian
	float d = max( 0, dot( geometryNormal.xyz, -L ));
	vec3 lambertian = vColor.xyz * d * intensity;

	//Calcualte our speculosity :)
	vec3 R = normalize( reflect( L, geometryNormal.xyz));
	float S = pow( max( 0, dot( E.xyz, R)), 128 ) * intensity;

	LightTexture = vec4( lambertian, S );

}