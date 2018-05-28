#version 330

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec4 normal;
layout( location = 2 ) in vec4 tangent;
layout( location = 3 ) in vec4 biNormal;
layout( location = 4 ) in vec2 texCoord;

out vec4 worldPosition;
out vec4 worldNormal;
out vec4 worldTangent;
out vec4 worldBiNormal;
out vec2 textureCoord;

uniform mat4 transposeInvWorld;
uniform mat4 world;
uniform mat4 projectionView;

void main()
{
	textureCoord = texCoord;

	worldPosition = world * position;
	worldNormal = transposeInvWorld * normal;
	worldTangent = transposeInvWorld * tangent;
	worldBiNormal = transposeInvWorld * biNormal;

	gl_Position = projectionView * worldPosition;
}