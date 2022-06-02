#include"basicbuffer.h"
#include"../Log.h"
#include<glew.h>

/***********************u need to add PUSH data to a certain index*****************/
namespace imatics {

	basicbuffer::basicbuffer(const char* layout,unsigned int* indecis):m_indecis(indecis) {
		
		const size_t attribnbr = strlen(layout);
		unsigned int attype = 0;
		short int offset = 0;
		size_t stride = 0;
		////////////////calculating the stride : summing the numbers and avoiding letters//////////////
		for (int i = 0; i < attribnbr; i += 2) {
			switch (layout[i + 1]) {
			case 'f': attype = GL_FLOAT; break;
			case 'i': attype = GL_INT; break;
			default: Log("there no define type forthis type ");
				Log(layout[i + 1]);
				attype = GL_FLOAT; // default case will take float
			}
			stride += atoi(&(layout[i])) * sizeof(attype);
		}
		Log("stride =" << stride);
		attype = 0;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
		glBindVertexArray(m_vao);
		//////////////////taking care of the types and the offsets///////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		int j = 0;//this for the index off the vao in the vertexattribpointer link to vbo
		for (int i = 0; i < attribnbr; i+=2) {
			glEnableVertexAttribArray(j);
			switch (layout[i + 1]) {
			case 'f': attype = GL_FLOAT; break;
			case 'i': attype = GL_INT; break;
			default: Log("there no define type forthis type");
				Log(layout[i + 1]);
				attype = GL_FLOAT;
			}
			glVertexAttribPointer(j,atoi(&(layout[i])),attype, GL_FALSE,stride, (void*)offset);
			Log("the "<<j<<" attribute has: " << atoi(&(layout[i]))<< layout[i+1] << " and start at offset off : " << offset);
			offset += atoi(&(layout[i])) * sizeof(attype);
			j++;
		}
		//
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo);
		
		bind(false);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void basicbuffer::transferdata(void* data,size_t objectsize,size_t tricount ,unsigned int drawinghint) {
		bind(true);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ARRAY_BUFFER, objectsize,data,GL_STATIC_DRAW);			
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*tricount* sizeof(unsigned int),m_indecis,drawinghint);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		bind(false);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	}
	/*
	note:it will bind the vao to false after it finish 
	*/
	void basicbuffer::bind(bool status) {
		if (status == false) {
			glBindVertexArray(0);
			m_status = false;
		}else {
			glBindVertexArray(m_vao);
			m_status = true;
		}
	}

}