#vertex
#version 420 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texpos;

out vec2 o_texcoord;



void main() {
	o_texcoord = texpos;
	gl_Position = vec4(position,0.9f, 1.0f);
}