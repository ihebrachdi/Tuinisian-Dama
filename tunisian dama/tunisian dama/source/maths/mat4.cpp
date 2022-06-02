#include"mat4.h"
#include<iostream>
#include<sstream>

namespace imatics {
	

	std::ostream& operator<<(std::ostream& lcout,const mat4& rmat4) {
		std::stringstream stream;
		for (int i = 0; i < 4; i++) {
			stream << rmat4.m_mat[0 + i] << "\t" << rmat4.m_mat[4 + i] << "\t" << rmat4.m_mat[8 + i] << "\t" << rmat4.m_mat[12 + i] <<std::endl;
		}
		return lcout<<stream.str();
	}

	mat4::mat4(float n) {
		memset(this, 0.0f, 16 * sizeof(float));
		for (int i = 0; i < 16; i += 5) {
			m_mat[i] = n;
		}
	}
	  
	//Orthographic Projection Matrix  
	void ortho(float left, float right, float buttom, float top, float near, float far, mat4& matr) {
		matr.m_vec4[0] = { 2 / (right - left),0,0,0 };
		matr.m_vec4[1] = {0,2 / (top - buttom),0,0 };
		matr.m_vec4[2] = { 0,0,2 / (far - near),0 };
		matr.m_vec4[3] = { -(right + left) / (right - left),-(top + buttom) / (top - buttom),-(far + near) / (far - near),1 };
	}

	void rotation(float beta, mat4& matl) {
		
		matl.m_vec4[0] = { cos((float)(beta * (PI / 180.0f))),0,-sin((float)(beta * (PI / 180.0f))),0 };
		matl.m_vec4[1] = { 0,1,0,0 };
		matl.m_vec4[2] = { sin((float)(beta * (PI / 180.0f))),0,cos((float)(beta * (PI / 180.0f))),0 };
		matl.m_vec4[3] = { 0,0,0,1 };

	}

	void scale(float vscale, mat4& matl) {
		matl.m_vec4[0] = { vscale,0,0,0 };
		matl.m_vec4[1] = { 0,vscale,0,0 };
		matl.m_vec4[2] = { 0, 0, vscale,0 };
		matl.m_vec4[3] = { 0, 0, 0, 1 };
	}
	
		

	vec4& operator*(const mat4& lmat4, vec4& rvec4) {
		float vec[4];
		for (int j = 0; j < 4; j++) {
			vec[j] = rvec4.x * lmat4.m_mat[0 + j] + rvec4.y * lmat4.m_mat[4 + j] + rvec4.z * lmat4.m_mat[8 + j] + rvec4.w * lmat4.m_mat[12 + j];
		}
		return rvec4;
	}

	mat4& operator*(const mat4& lmat4, const mat4& rmat4) {
		mat4 mat;
		int j;
		float sum = 0;
		int l, m;
		int i = 0, k = 0;
		
		for (int u = 0; u < 4; u++) {
			
			l = 12;
			i = u * 4;
			int t = i;
			for (m = 0; m < 4; m++) {
				j = m;
				while (j <= l) {
					sum += rmat4.m_mat[i] * lmat4.m_mat[j];
					i += 1;
					j += 4;
				}
				i = t;
				l += 1;
				mat.m_mat[k] = sum;
				k += 1;
				sum = 0;
			}

		}
		return mat;
	}
	void operator*=(mat4& lmat4, const mat4& rmat4) {
		mat4 mat;
		int j;
		float sum = 0;
		int l, m;
		int i = 0, k = 0;
		
		for (int u = 0; u < 4; u++) {
			
			l = 12;
			i = u * 4;
			int t = i;
			for (m = 0; m < 4; m++) {
				j = m;
				while (j <= l) {
					sum += rmat4.m_mat[i] * lmat4.m_mat[j];
					i += 1;
					j += 4;
				}
				i = t;
				l += 1;
				mat.m_mat[k] = sum;
				k += 1;
				sum = 0;
			}

		}
		memcpy(&lmat4, mat.m_mat, 16 * sizeof(float));
	}
	
}