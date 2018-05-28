#version 330

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 lightAmbient;

uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform vec3 lightSpecular;

uniform vec3 cameraPosition;

void main()
{
	vec3 direction = lightPosition - vPosition;
	float l = length(direction);


	float att = 1 - smoothstep(7, 20, l);
	vec4 light = vec4(lightColour, 1.0);
	light *= att;


	vec3 N = normalize( vNormal );
	vec3 L = normalize( lightPosition );

	vec3 R = reflect( -L, N );
	vec3 E = normalize( cameraPosition - vPosition );

	// diffuse
	float d = max( 0, dot( N, L ));
	vec3 diffuse = light.rgb * d;

	// ambient
	vec3 ambient = lightAmbient;

	// specular
	float s = pow( max( 0, dot( E, R )), 128 );
	vec3 specular = lightSpecular * s;

	gl_FragColor = vec4( ambient + diffuse + specular, 1 ) * light;
}


