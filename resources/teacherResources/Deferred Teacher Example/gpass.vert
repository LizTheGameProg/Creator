#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

// view-space normal and position
out vec4 vPosition;
out vec4 vNormal;

uniform mat4 View;
uniform mat4 ProjectionView;

void main() {
	// first store view-space position and normal
	vPosition = View * Position;
	vNormal = normalize(View * Normal);

	gl_Position = ProjectionView * Position;
}