#vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in int flag;
layout(location = 2) in vec2 texcoord;


out vec2 s_texcoord;
flat out int s_indextexture;
out vec3 s_quadecolor;

uniform mat4 orth;
uniform vec3 quadecolor[5];

void main()
{
	s_texcoord = texcoord;
	s_indextexture = flag % 10; // 0 = black , white = 1 ,2 = none

	s_quadecolor = quadecolor[flag / 1000];

	gl_Position = orth * vec4(position,1.0);
	
	
}
