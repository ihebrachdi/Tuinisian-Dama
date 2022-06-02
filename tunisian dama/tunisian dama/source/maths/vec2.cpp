#include"vec2.h"

namespace imatics {
	
	vec2 operator+(const vec2& lvec2, const vec2& rvec2) {
		return { lvec2.x + rvec2.x,lvec2.y + rvec2.y };
	}
	vec2 operator-(const vec2& lvec2, const vec2& rvec2) {
		return { lvec2.x - rvec2.x,lvec2.y - rvec2.y };
	}
	vec2 operator*(const vec2& lvec2, const vec2& rvec2) {
		return { lvec2.x * rvec2.x,lvec2.y * rvec2.y };
	}

	void operator+=(vec2& lvec2,const vec2& rvec2) {
		lvec2.x += rvec2.x;
		lvec2.y += rvec2.y;
	}
	void operator-=(vec2& lvec2, const vec2& rvec2) {
		lvec2.x -= rvec2.x;
		lvec2.y -= rvec2.y;
	}
	void operator*=(vec2& lvec2, const vec2& rvec2) {
		lvec2.x *= rvec2.x;
		lvec2.y *= rvec2.y;
	}
	
	float dot(const vec2& lvec2, const vec2& rvec2) {
		return (lvec2.x * rvec2.x) + (lvec2.y * rvec2.y);
	}

	std::ostream& operator<<(std::ostream& lstream, const vec2& rvec2) {
		return lstream << "(" << rvec2.x << " , " << rvec2.y << ")";
	}


}