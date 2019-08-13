#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iomanip>


#ifndef VEC3H
#define VEC3H

class vec3
{
public:
	vec3() { e[0] = 0; e[1] = 0; e[2] = 0; }
	vec3(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z; }

	inline void operator = (const vec3 &v)
	{
		e[0] = v.e[0]; e[1] = v.e[1]; e[2] = v.e[2];
	}

	inline vec3 operator + (const vec3 &v) const
	{
		return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
	}

	inline vec3 operator - (const vec3 &v) const
	{
		return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
	}

	inline vec3 operator * (const vec3 &v) const
	{
		return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
	}

	inline vec3 operator / (const vec3 &v) const
	{
		return vec3(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
	}

	inline vec3 operator * (const float f) const
	{
		return vec3(e[0] * f, e[1] * f, e[2] * f);
	}

	inline vec3 operator / (const float f) const
	{
		return vec3(e[0] / f, e[1] / f, e[2] / f);
	}

	inline vec3& operator += (const vec3 &v)
	{
		*this = *this + v; return *this;
	}

	inline vec3& operator -= (const vec3 &v)
	{
		*this = *this - v; return *this;
	}

	inline vec3& operator *= (const vec3 &v)
	{
		*this = *this * v; return *this;
	}

	inline vec3& operator /= (const vec3 &v)
	{
		*this = *this / v; return *this;
	}

	inline vec3& operator *= (const float f)
	{
		*this = *this * f; return *this;
	}

	inline vec3& operator /= (const float f)
	{
		*this = *this / f; return *this;
	}

	float length() const
	{
		return sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2));
	}

	float squared_length() const
	{
		return pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2);
	}

	inline float dotproduct(const vec3 &v) const
	{
		return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
	}

	inline vec3 crossproduct(const vec3 &v) const
	{
		return vec3((e[1] * v.e[2] - e[2] * v.e[1]),
			(e[2] * v.e[0] - e[0] * v.e[2]),
			(e[0] * v.e[1] - e[1] * v.e[0]));
	}

	inline vec3 unit_vector() const
	{
		return *this / (this->length());
	}

	float e[3];
};

#endif