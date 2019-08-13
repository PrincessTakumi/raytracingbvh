#ifndef RAYH
#define RAYH

#include "vec3.h"

class Ray
{
public:
	Ray() { A = vec3(0.0, 0.0, 0.0); B = vec3(0.0, 0.0, 0.0); }
	Ray(const vec3 &a, const vec3 &b)
	{
		A = a;
		B = b;
		inv = vec3(1 / B.e[0], 1 / B.e[1], 1 / B.e[2]);
		sign[0] = (inv.e[0] < 0);
		sign[1] = (inv.e[1] < 0);
		sign[2] = (inv.e[2] < 0);
	}

	vec3 origin()	 const { return A; }
	vec3 direction() const { return B; }
	vec3 get_point_at(float t) const { return A + B * t; }

	vec3 A;
	vec3 B;
	vec3 inv;
	int sign[3];
};

#endif