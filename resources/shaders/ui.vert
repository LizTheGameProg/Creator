#version 330

layout( location = 0) in vec3 position;

out vec2 texCoord;

uniform vec2 textureCoords[4];
uniform vec2 dimensions;
uniform mat3 transform;
uniform mat4 projection;

void main()
{
	vec3 p = position;
	p.xy *= dimensions;

	texCoord = textureCoords[ gl_VertexID ];

	gl_Position = projection * vec4(transform * p, 1);
}