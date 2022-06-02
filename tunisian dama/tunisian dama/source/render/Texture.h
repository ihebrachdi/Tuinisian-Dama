#pragma once

#include<glew.h>
#include"../files/stb_image.h"


namespace imatics {
	class texture {
	public:
		
		unsigned int* m_tbo;	 
		int* m_unit;

		int m_samplerloc;
		size_t m_size;//size of array 
		size_t m_count = 0;//how many texture we currently have 
	public:
		texture(int location,size_t size);
		void bind(unsigned int index, bool bind);
		void addtexture(const char* path,size_t unit);
		//~texture();
	};
}