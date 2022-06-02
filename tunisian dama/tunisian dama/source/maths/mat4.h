#pragma once
#include"vec4.h"
#include"mathfun.h"

namespace imatics{


	struct mat4{
		union {
			float m_mat[16];
			vec4 m_vec4[4];
		};
		mat4() {};
		mat4(float n);

	};
	
	void ortho(float left, float right, float buttom, float top, float near, float far, mat4& matr);
	void rotation(float beta, mat4& matl);
	void scale(float vscale, mat4& matl);
	vec4& operator*(const mat4& lmat4, vec4& rvec4);
	mat4& operator*(const mat4& lmat4, const mat4& rmat4);
	void operator*=(mat4& lmat4, const mat4& rmat4);
	
	std::ostream& operator<<(std::ostream& lcout ,const mat4& rmat4);
	
}