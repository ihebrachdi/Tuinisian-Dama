#pragma once

namespace imatics {
	class basicbuffer {
	private:
		unsigned int m_vao, m_vbo, m_ebo;
		bool m_status = true; // bind status // true :bcause we bind it in the constructor to avoid call functions
		unsigned int* m_indecis;
	public:
		basicbuffer(const char* layout,unsigned int* indecis);
		void transferdata(void* data, size_t objectsize, size_t tricount,unsigned int drawinghint);
		void bind(bool status);

	
	};


}