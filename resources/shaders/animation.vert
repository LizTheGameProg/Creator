#version 330

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec2 texCoord;
layout( location = 2 ) in vec4 indices;
layout( location = 3 ) in vec4 weights;

out vec2 TexCoord;

uniform mat4 projectionView;
uniform mat4 global;

// we need to give our bone array a limit
const int MAX_BONES = 128;
uniform mat4 bones[MAX_BONES];

void main()
{
	// cast the indices to integer's so they can index an array
	ivec4 index = ivec4(indices);
	
	// sample bones and blend up to 4
	vec4 P = bones[ index.x ] * position * weights.x;
	P += bones[ index.y ] * position * weights.y;
	P += bones[ index.z ] * position * weights.z;
	P += bones[ index.w ] * position * weights.w;
	
	TexCoord = texCoord;
	gl_Position = projectionView * global * P;
}