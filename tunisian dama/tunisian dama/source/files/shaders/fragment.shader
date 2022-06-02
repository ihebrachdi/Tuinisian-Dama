#fragment
#version 420 core

//in vec4 vertexcolor;
in vec2 s_texcoord;
flat in int s_indextexture;
in vec3 s_quadecolor;

out vec4 Fragcolor;

uniform sampler2D textureunits[2];

void main()
{
	int index = s_indextexture;
	if (index != 2) {
		vec4 samplercolor = texture(textureunits[index], s_texcoord);
		if (samplercolor.a != 0.0f) {
			Fragcolor = samplercolor;
		}
		else {	
			if(s_quadecolor.x == 0.5){
				discard;
			}else {
				Fragcolor = vec4(s_quadecolor, 1.0f);
			}
		}
	}
	else {
		Fragcolor = vec4(s_quadecolor, 1.0f);
	}
	
}
