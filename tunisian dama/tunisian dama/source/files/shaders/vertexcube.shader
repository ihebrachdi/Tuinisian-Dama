#vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texpos;

out vec2 o_texcoord;

uniform mat4 orth;
uniform mat4 rotation;
uniform mat4 scale;

void main() {
	o_texcoord = texpos;
	gl_Position = orth * rotation * scale *  vec4(position, 1.0f);
}
