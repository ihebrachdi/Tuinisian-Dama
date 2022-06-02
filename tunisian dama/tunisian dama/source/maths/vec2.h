#pragma once
#include<ostream>

namespace imatics {
	
	struct vec2 {
		float x = 0.0f;
		float y = 0.0f;
		vec2() = default;
		vec2(float argx, float argy) {
			x = argx;
			y = argy;
		}
	};


	vec2 operator+(const vec2& lvec2, const vec2& rvec2);
	vec2 operator-(const vec2& lvec2, const vec2& rvec2);
	vec2 operator*(const vec2& lvec2, const vec2& rvec2);
	
	void operator+=(vec2& lvec2,const vec2& rvec2);
	void operator-=(vec2& lvec2,const vec2& rvec2);
	void operator*=(vec2& lvec2,const vec2& rvec2);

	//dot producet
	float dot(const vec2& lvec2, const vec2& rvec2);

	std::ostream& operator<<(std::ostream& lstream, const vec2& rvec2);
}