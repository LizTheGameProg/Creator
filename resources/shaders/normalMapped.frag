#version 330

in vec4 worldPosition;
in vec4 worldNormal;
in vec4 worldTangent;
in vec4 worldBiNormal;
in vec2 textureCoord;

out vec4 fragColour;

uniform vec3 cameraPosition;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;

uniform float time;

void main()
{
	// sample normal
	mat3 TBN = mat3( normalize(worldTangent.xyz), normalize(worldBiNormal.xyz), normalize(worldNormal.xyz) );
	vec3 N = texture( normalMap, textureCoord ).xyz * 2 - 1;
	N = normalize( TBN * N );

	// calculate view vector
	vec3 V = normalize( worldPosition.xyz - cameraPosition );

	// fake light
	vec3 L = vec3( sin(time), 0, cos(time) );

	// reflected light
	vec3 R = reflect( -L, N );

	// phong lighting
	float lightIntensity = 2.5f;
	float d = max( 0, dot( N, -L ) ) * lightIntensity;
	float s = pow( max( 0, dot( V, R ) ), 128 ) * d * lightIntensity;

	vec3 diffTex = texture( diffuseMap, textureCoord ).rgb;
	vec3 specTex = texture( specularMap, textureCoord ).rgb;

	// combine ambient, diffuse and specular
	fragColour.rgb = diffTex * 0.25f + diffTex * d + specTex * s;

	fragColour.a = 1;
}