#version 330

in vec4 Position;
in vec3 Normal;
in vec3 Tangent;
in vec3 BiNormal;
in vec2 TexCoord1;

out vec2 vTexCoord1;
out vec3 vNormal; 
out vec3 vLightDir;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NormalMatrix;

uniform vec3 LightPosition;

void main()
{
	// calculate the surface normals in eye coordinates
	vec3 eye_normal = NormalMatrix * Normal;
	vec3 eye_tangent = NormalMatrix * Tangent;
	vec3 eye_binormal = NormalMatrix * BiNormal;
	
	// get the vertex position and Light position in eye coordinates
	vec3 eye_position = (MV * Position).xyz;
	vec3 eye_lightPos = (MV * vec4(LightPosition, 1)).xyz;
	
	// calculate the dir to the light from the vertex position
	vec3 lightDir = normalize(eye_lightPos - eye_position );
	
	// use dot product with light direction and normals
	// this is ued to adjust shading based on the direction 
	// of the surface
	vLightDir = lightDir;
	vLightDir.x = dot(lightDir, eye_tangent);
	vLightDir.y = dot(lightDir, eye_binormal);
	vLightDir.z = dot(lightDir, eye_normal);
	
	// pass through the surface normal to the frag shader
	vNormal = eye_normal;
	
	// pass through the texcoord to the frag shader
	vTexCoord1 = TexCoord1;

	// finally set the position over the vertex
	gl_Position = MVP * Position;

}