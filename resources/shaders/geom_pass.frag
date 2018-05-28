#version 330

in vec2 texCoord;
in vec4 normal;
in vec4 wPos;

// We create three 'out' variables for the textures
// These names must match up to the ones you passed into the Utility::loadShader() function
out vec4 Diffuse;
out vec4 Normal;
out vec4 World;

uniform sampler2D DiffuseTexture;

void main()
{
    // Just pass the data directly in
	Diffuse = texture(DiffuseTexture, texCoord);
	Normal = normal;
	Normal.a = 1;
	World = wPos;
}