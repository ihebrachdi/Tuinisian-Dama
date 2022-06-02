#pragma once
#include<ostream>

namespace imatics {

	struct vec4 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;
	};


	vec4 operator+(const vec4& lvec4, const vec4& rvec4);
	vec4 operator-(const vec4& lvec4, const vec4& rvec4);
	vec4 operator*(const vec4& lvec4, const vec4& rvec4);

	void operator+=(vec4& lvec4, const vec4& rvec4);
	void operator-=(vec4& lvec4, const vec4& rvec4);
	void operator*=(vec4& lvec4, const vec4& rvec4);

	//dot product
	float dot(const vec4& lvec4, const vec4& rvec4);

	std::ostream& operator<<(std::ostream& lstream, const vec4& rvec4);
}