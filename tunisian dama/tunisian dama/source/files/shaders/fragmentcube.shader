#fragment
#version 420 core


out vec4 Fragcolor;

in vec2 o_texcoord;

uniform sampler2D textureunit[2];

uniform int index;

void main() {

	vec4 samplercolor = texture(textureunit[index], o_texcoord);

	Fragcolor = samplercolor;
}