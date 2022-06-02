#fragment
#version 420 core


out vec4 Fragcolor;

in float index;

void main() {
	
	Fragcolor = vec4(0.0f,index / 1000.0f, 0.0f, 1.0f);
}