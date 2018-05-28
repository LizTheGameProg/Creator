#version 150

out vec4 Lighting;

uniform sampler2D world_tex;
uniform sampler2D normal_tex;

uniform vec3 camera_pos;
uniform vec2 screenSize;

// this would be a directional light, as an example
uniform vec3 light_dir;

void main()
{
	//gl_FragCoord is a built in fragment shader variable that contains 
	//the value of the pixel currently being drawn. We can convert that 
	//to 0-1 UV coords by dividing by a unifrom set the dimensions of the screen
	vec2 UV = gl_FragCoord.xy / screenSize;
	
	vec3 Normal = normalize(texture(normal_tex, UV).xyz);
	vec3 WorldPosition = texture(world_tex, UV).xyz;
	vec3 Eye = normalize(camera_pos - texture(world_tex, UV).xyz);
	vec3 Light = normalize(light_dir);
	float d = max( 0, dot( Normal, Light ) );
	
	Lighting = vec4(d,d,d,1);
}