#include"vec3.h"

namespace imatics {



	vec3 operator+(const vec3& lvec3, const vec3& rvec3) {
		return { lvec3.x + rvec3.x,lvec3.y + rvec3.y,lvec3.z + rvec3.z };
	}
	vec3 operator-(const vec3& lvec3, const vec3& rvec3) {
		return { lvec3.x - rvec3.x,lvec3.y - rvec3.y ,lvec3.z - rvec3.z };
	}
	vec3 operator*(const vec3& lvec3, const vec3& rvec3) {
		return { lvec3.x * rvec3.x,lvec3.y * rvec3.y,lvec3.z * rvec3.z };
	}

	void operator+=(vec3& lvec3, const vec3& rvec3) {
		lvec3.x += rvec3.x;
		lvec3.y += rvec3.y;
		lvec3.z += rvec3.z;
	}
	void operator-=(vec3& lvec3, const vec3& rvec3) {
		lvec3.x -= rvec3.x;
		lvec3.y -= rvec3.y;
		lvec3.z -= rvec3.z;
	}
	void operator*=(vec3& lvec3, const vec3& rvec3) {
		lvec3.x *= rvec3.x;
		lvec3.y *= rvec3.y;
		lvec3.z *= rvec3.z;
	}


	//****************************************with numbers*****************************************//
	
	void operator*=(vec3& lvec3, const float rnbr) {
		lvec3.x *= rnbr;
		lvec3.y *= rnbr;
		lvec3.z *= rnbr;
	}

	vec3 operator*(const float lnbr, vec3 rvec3) {
		return{ rvec3.x * lnbr,rvec3.y * lnbr,rvec3.z * lnbr };
	}



	float dot(const vec3& lvec3, const vec3& rvec3) {
		return (lvec3.x * rvec3.x) + (lvec3.y * rvec3.y) + (lvec3.z * rvec3.z);
	}

	std::ostream& operator<<(std::ostream& lstream, const vec3& rvec3) {
		return lstream << "(" << rvec3.x << " , " << rvec3.y << " , " << rvec3.z << ")";
	}


}