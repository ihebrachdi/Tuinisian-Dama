#vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in int flag;

out float index;

uniform mat4 ortho;

void main() {
	index = float(flag % 1000);
	//index = float((flag / 10) % 100);
	gl_Position = ortho * vec4(position, 1.0f);
}