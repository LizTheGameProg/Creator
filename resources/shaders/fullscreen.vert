#version 330

layout( location = 0 ) in vec4 position;

out vec2 textureCoord;

void main()
{
	textureCoord = position.xy * 0.5f + 0.5f;

	gl_Position = position;
}