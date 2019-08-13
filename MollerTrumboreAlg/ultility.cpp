#include "utility.h"

vec3 unit_circle()
{
	vec3 p;
	do
	{
		p = vec3(
			(rand() / (RAND_MAX + 1.0)),
			(rand() / (RAND_MAX + 1.0)), 0) - vec3(1, 1, 0);
	} while (p.dotproduct(p) >= 1.0);
	return p;
}

vec3 unit_sphere()
{
	vec3 p;
	do
	{
		p = vec3(
			(rand() / (RAND_MAX + 1.0)),
			(rand() / (RAND_MAX + 1.0)),
			(rand() / (RAND_MAX + 1.0))) * 2.0 - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
	return v - n * (v.dotproduct(n)) * 2;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted)
{
	vec3 uv = v.unit_vector();
	float dt = uv.dotproduct(n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = (uv - n * dt) * ni_over_nt - n * sqrt(discriminant);
		return true;
	}
	return false;
}

float schlick(float cos, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 - ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cos), 5);
}
