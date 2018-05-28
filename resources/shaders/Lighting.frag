#version 150

out vec4 Lighting;

uniform sampler2D world_tex;
uniform sampler2D normal_tex;
uniform sampler2D tangent_tex;
uniform sampler2D bitangent_tex;

uniform vec3 camera_pos;
uniform vec3 View;
uniform vec2 screenSize;

// this would be a directional light, as an example
uniform vec3 light_pos;

void main()
{
	vec2 UV = gl_FragCoord.xy / screenSize;
	
	//vec3 N = normalize(texture(normal_tex, UV).xyz);
	//vec3 L = normalize(light_pos);
	//vec3 E = normalize(camera_pos - texture(world_tex, UV).xyz);
	//vec3 R = reflect(-L, N);
	//
	////vec3 L = normalize(LightDirection_T);
	////vec3 E = normalize(EyeDirection_T);
	//
	//float d = clamp(dot(N, L), 0, 1);
	//float s = clamp(dot(E, R), 0, 1);
	//
	//vec3 diffuse = vec3(1,1,1) * d;
	//vec3 specular = vec3(0.25f, 0.25f, 0.25f) * s;
	//
	//Lighting = vec4(diffuse, 1);













	vec3 M = texture(world_tex, UV).xyz;
	vec3 VM = View * M;
	
	mat3 TBN = transpose(mat3(	texture(tangent_tex, UV).rgb,
								texture(bitangent_tex, UV).rgb,
								texture(normal_tex, UV).rgb));
	
	vec3 VertexPosition_C	= M;
	vec3 LightPosition_C	= light_pos;
	vec3 EyeDirection_C		= vec3(0,0,0) - VertexPosition_C;
	vec3 LightDirection_C	= LightPosition_C; //+ EyeDirection_C;
	
	vec3 LightDirection_T	= TBN * LightDirection_C;
	vec3 EyeDirection_T		= TBN * EyeDirection_C;
	
	vec3 N = normalize(texture(normal_tex, UV).xyz);
	vec3 L = normalize(LightDirection_T);
	//vec3 E = normalize(EyeDirection_T);
	//vec3 L = normalize(light_pos);
	//vec3 E = normalize(camera_pos - texture(world_tex, UV).xyz);
	
	//vec3 R = reflect(L, N);
	
	float d = clamp(dot(N, L), 0, 1);
	//float s = clamp(dot(E, R), 0, 1);
	
	vec3 diffuse = vec3(1,1,1) * d;
	//vec3 specular = vec3(0.25f, 0.25f, 0.25f) * s;
	
	Lighting = vec4(diffuse,1);
}