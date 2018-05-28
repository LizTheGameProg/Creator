#version 330

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec4 normal;

out vec4 worldPosition;
out vec4 worldNormal;

uniform mat4 projectionView;
uniform mat4 model;
uniform mat4 invTransposeModel;

void main()
{
	worldPosition = model * position;
	worldNormal = invTransposeModel * normal;
	gl_Position = projectionView * worldPosition;
}