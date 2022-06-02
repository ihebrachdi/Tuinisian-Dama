#pragma once
#include"../maths/vec2.h"
#include"../maths/vec3.h"
#include"../files/program.h"

namespace imatics {
	class picking {
	public:
		unsigned int m_fbo, m_tbo;
		int m_lastpickedindex;
	private:
	public:
		picking(vec2 dimport);
		void bind(vec3 backgroundcolor);
		void unbind(vec3 backgroundcolor);
		vec3 readpixel(double x_mouse, double y_mouse, int height) ; // you need to bind() first then drawscene then readpixel() and unbind() 
		
		//~picking();
	};
}