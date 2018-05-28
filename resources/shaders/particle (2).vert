in vec4 Position;
in vec4 Colour;

out vec4 colour;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	colour = Colour;
	gl_Position = projection * view * Position;
}