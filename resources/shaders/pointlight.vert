#version 330

in vec4 Position;
in vec4 Normal;

out vec3 vPosition;
out vec3 vNormal;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vPosition = Position.xyz;
	vNormal = Normal.xyz;
	gl_Position = projection * view * Position;
}

