#ifndef ALGORITHMH
#define ALGORITHMH

#include "material.h"
#include "box.h"

class Triangle : public Object
{
public:
	Triangle(vec3 a, vec3 b, vec3 c, Material *m);
		virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec);

	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 N;
	Box box;
	vec3 center;
	Material *mat;
};

#endif




