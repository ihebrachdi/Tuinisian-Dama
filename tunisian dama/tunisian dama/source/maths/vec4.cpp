#include"vec4.h"

namespace imatics {

	vec4 operator+(const vec4& lvec4, const vec4& rvec4) {
		return { lvec4.x + rvec4.x,lvec4.y + rvec4.y,lvec4.z + rvec4.z,lvec4.w + rvec4.w };
	}
	vec4 operator-(const vec4& lvec4, const vec4& rvec4) {
		return { lvec4.x - rvec4.x,lvec4.y - rvec4.y ,lvec4.z - rvec4.z,lvec4.w - rvec4.w };
	}
	vec4 operator*(const vec4& lvec4, const vec4& rvec4) {
		return { lvec4.x * rvec4.x,lvec4.y * rvec4.y,lvec4.z * rvec4.z,lvec4.w * rvec4.w };
	}

	void operator+=(vec4& lvec4, const vec4& rvec4) {
		lvec4.x += rvec4.x;
		lvec4.y += rvec4.y;
		lvec4.z += rvec4.z;
		lvec4.w += rvec4.w;
	}
	void operator-=(vec4& lvec4, const vec4& rvec4) {
		lvec4.x -= rvec4.x;
		lvec4.y -= rvec4.y;
		lvec4.z -= rvec4.z;
		lvec4.w -= rvec4.w;
	}
	void operator*=(vec4& lvec4, const vec4& rvec4) {
		lvec4.x *= rvec4.x;
		lvec4.y *= rvec4.y;
		lvec4.z *= rvec4.z;
		lvec4.w *= rvec4.w;
	}

	float dot(const vec4& lvec4, const vec4& rvec4) {
		return (lvec4.x * rvec4.x) + (lvec4.y * rvec4.y) + (lvec4.z * rvec4.z) + (lvec4.w * rvec4.w);
	}

	std::ostream& operator<<(std::ostream& lstream, const vec4& rvec4) {
		return lstream << "(" << rvec4.x << " , " << rvec4.y << " , " << rvec4.z << " , " << rvec4.w << ")";
	}


}