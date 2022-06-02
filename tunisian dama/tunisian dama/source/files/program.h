#pragma once
#include<string>

namespace imatics {
	
	class program {
	private:
		unsigned int m_id;
		bool m_bind = false;
	public:
		program(const std::string& vertex, const std::string& fragment);
		void use(bool bind);
		unsigned int findlocation(const char* name);
		void draw(size_t nbr_triangle);
		~program();
	};
}