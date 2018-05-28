#version 330 core

in vec2 vert_texCoords;

out vec4 color;

uniform sampler2D uniform_texture;

void main()
{
    color = texture(uniform_texture, vert_texCoords);
} 