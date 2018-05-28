#version 330 core
  
layout (location = 0) in vec4 in_position;
layout (location = 1) in vec2 in_texCoords;

out vec2 vert_texCoords;

uniform mat4 uniform_transform;

void main()
{
	vert_texCoords = in_texCoords;
	gl_Position = uniform_transform * in_position;
}