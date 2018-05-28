#version 330

in vec2 vTexCoord1;
in vec3 vNormal; 
in vec3 vLightDir;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;

uniform vec3 AmbientLightColor;
uniform vec3 LightColor;

uniform int toggle;

out vec4 outColor;

void main()
{
	// variable to store our color
	vec4 finalColor = vec4(0,0,0,0);

	// get the color from our textures
	vec3 normalColor	= texture( NormalTexture, vTexCoord1).xyz;
	vec4 diffuseColor	= texture( DiffuseTexture, vTexCoord1);
	vec4 specularColor	= texture( SpecularTexture,vTexCoord1);

	// calculate lighting with dot product
	// N = vNormal of our surface, added to the normal from our NormalMap
	// L = the direction of our light calculated in the vertex shader
	vec3 N = normalize((2.0 * normalColor - 1.0) + vNormal);
	vec3 L = vLightDir;

	// how bright should this pixel be based on our light and view direction
	float diffuseIntensity = max(0.0, dot(N, L));

	// for simplicity, will use the diffuse texture as the ambient color
	// or this could be a solid color passed as a uniform variable
	vec4 ambientColor = diffuseColor * vec4(AmbientLightColor, 1.0);	

	// Add the diffuse contribution blended with the standard texture lookup and add in the ambient light on top
	finalColor.rgb = (diffuseIntensity * LightColor.rgb) * diffuseColor.rgb + ambientColor.rgb;
 
	// specular hilight
	vec3 reflection = normalize( reflect( -normalize(vLightDir), N));
	float spec = max(0.0, dot( reflection, N));
	float fSpec = pow(spec, 5.0);

	// apply the specular.
	finalColor.rgb += vec3(fSpec, fSpec, fSpec) * specularColor.xyz;	

	outColor = finalColor;
	
}