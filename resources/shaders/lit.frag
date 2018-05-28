#version 330

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 lightAmbient;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 lightSpecular;

uniform vec3 cameraPosition;

void main()
{
	vec3 N = normalize( vNormal );
	vec3 L = normalize( -lightDirection );

	vec3 R = reflect( -L, N );
	vec3 E = normalize( cameraPosition - vPosition );

	// diffuse
	float d = max( 0, dot( N, L ) );

	gl_FragColor = vec4( d,d,d, 1 );
}