#version 330   

//--------------------------  
in vec4 vNormal;
in vec2 vTexCoord;
in vec3 vPosition_W;
in vec3 vLightDirection_C;
in vec3 vEyeDirection_C;
in vec3 vLightDirection_T;
in vec3 vEyeDirection_T;
//--------------------------  
out vec3 OUTCOLOUR;
//--------------------------  
uniform sampler2D DiffuseTexture;
uniform sampler2D AmbientTexture;
uniform sampler2D GlowTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D GlossTexture;
uniform sampler2D NormalTexture;
uniform sampler2D AlphaTexture;
uniform sampler2D DisplacementTexture;
uniform vec3 LightPosition_W[6];
uniform mat4 CameraPos;
//--------------------------  

void main() 
{ 
	vec3 LightColour = vec3(1,1,1);
	float LightPower = 5.0f;
	float finalCosThetaDivideDistance = 0.0f;
	float finalCosAlphaDivideDistance = 0.0f;		
	
	vec3 Diffuse	= texture(DiffuseTexture, vTexCoord).rgb;
	vec3 Ambient	= Diffuse * 0.1f;
	vec3 Specular	= texture(SpecularTexture, vTexCoord).rgb * 0.3f;
	
	vec3 Normal_T = normalize(texture( NormalTexture, vTexCoord).rgb * 2.0 - 1.0);
	vec3 N = normalize( Normal_T);
	vec3 E = normalize( vEyeDirection_T);

	for(int i = 0; i < 6; i++)
	{
		float Distance = length( LightPosition_W[i] - vPosition_W);
		
		vec3 L = normalize( -LightPosition_W[i]);
		vec3 R = reflect( -L, N);
		
		float cosTheta = clamp( dot( N, L), 0, 1);
		float cosAlpha = clamp( dot( E, R), 0, 1);

		finalCosThetaDivideDistance += cosTheta / (Distance * Distance);
		finalCosAlphaDivideDistance += pow(cosAlpha, 5) / (Distance * Distance);
	}

	OUTCOLOUR = 
		// Ambient
		Ambient +
		// Diffuse
		Diffuse * LightColour * LightPower * finalCosThetaDivideDistance;// +
		// Specular
		//Specular * LightColour * LightPower * finalCosAlphaDivideDistance;
}