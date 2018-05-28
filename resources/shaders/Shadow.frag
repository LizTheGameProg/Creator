#version 150

out vec4 FragColor;
in vec4 normals;
in vec2 texCoord;
in vec4 shadowCoord;
uniform vec3 ambientLight;
uniform vec3 lightPos;
uniform sampler2D diffuseMap;
uniform sampler2D shadowMap;
const float SHADOW_BIAS = 0.01f;

void main()
{
	float shadowFactor = 1;

	// calculate shadow by testing depth
	if ( texture( shadowMap, shadowCoord.xy ).z < shadowCoord.z - SHADOW_BIAS )
	{
		shadowFactor = 0;
	}

	// sample diffuse texture and perform lambert lighting
	float NdL = max( 0, dot( normalize(normals), vec4(normalize(lightPos),1) ));
	vec3 texColour = texture( diffuseMap, texCoord ).rgb;

	

	// combine diffuse + ambient
	FragColor.rgb = texColour * NdL * shadowFactor + texColour * ambientLight;
	FragColor.a = 1;
}