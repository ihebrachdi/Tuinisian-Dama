#pragma once
#include<ostream>

namespace imatics {

	struct vec3 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		vec3(){};
		vec3(float argx, float argy, float argz) {
			x = argx;
			y = argy;
			z = argz;
		}
	};


	vec3 operator+(const vec3& lvec3, const vec3& rvec3);
	vec3 operator-(const vec3& lvec3, const vec3& rvec3);
	vec3 operator*(const vec3& lvec3, const vec3& rvec3);
	

	void operator+=(vec3& lvec3, const vec3& rvec3);
	void operator-=(vec3& lvec3, const vec3& rvec3);
	void operator*=(vec3& lvec3, const vec3& rvec3);

	void operator*=(vec3& lvec3, const float rnbr);
	vec3 operator*(const float lnbr,vec3 rvec3);
	
	
	//dot product
	float dot(const vec3& lvec3, const vec3& rvec3);

	std::ostream& operator<<(std::ostream& lstream, const vec3& rvec3);
}