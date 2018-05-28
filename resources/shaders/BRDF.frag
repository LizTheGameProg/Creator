#version 330   

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord1;

out vec4 outColor;

uniform sampler2D DiffuseTexture;
uniform sampler2D SpecularTexture;

uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform vec3 AmbientColor;

uniform vec4 CameraPosition;

uniform float Roughness;

void main() 
{ 
	vec3 N = normalize( vNormal.xyz );
	vec3 L = normalize( -LightDirection );

	vec3 R = reflect( -L, N );
	vec3 E = normalize( CameraPosition - vPosition ).xyz;

	// Oren-Nayer Diffuse Reflectance
	float NdL = max( 0.0f, dot( N, L ) ); 
	float NdE = max( 0.0f, dot( N, E ) ); 
	 
	float R2 = Roughness * Roughness; 
	 
	// Oren-Nayar Diffuse Term 
	float A = 1.0f - 0.5f * R2 / (R2 + 0.33f); 
	float B = 0.45f * R2 / (R2 + 0.09f); 
	 
	// CX = Max(0, cos(l,e)) 
	vec3 lightProjected = normalize( L - N * NdL ); 
	vec3 viewProjected = normalize( E - N * NdE); 
	float CX = max( 0.0f, dot( lightProjected, viewProjected ) ); 
	 
	// DX = sin(alpha) * tan(beta) 
	float alpha = sin( max( acos( NdE ), acos( NdL ) ) ); 
	float beta = tan( min( acos( NdE ), acos( NdL ) ) ); 
	float DX = alpha * beta; 
	 
	// Calculate Oren-Nayar, replaces the Phong Lambertian Term 
	float OrenNayar = NdL * (A + B * CX * DX); 

	// diffuse
	float d = max( 0, dot( N, L ) );
	vec3 diffuse = texture(DiffuseTexture, vTexCoord1).rgb * LightColor * OrenNayar;

	// ambient
	vec3 ambient = AmbientColor * texture(DiffuseTexture, vTexCoord1).xyz;

	// specular
	float s = pow( max( 0, dot( E, R ) ), 128 );
	vec3 specular = texture(SpecularTexture, vTexCoord1).rgb * s;

	outColor = vec4(ambient + diffuse + specular, 1);
}