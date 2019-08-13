#ifndef OBJECTH
#define OBJECTH

#include "ray.h"

class Material;

// Record for when ray hits object
struct hit_record
{
	float t;		// Number required for ray to intersect object
	vec3 p;			// Location of intersection
	vec3 normal;	// normal vector of the intersection
	Material *mat;
};

class Object
{
public:
	// Test to see if object is intersected by ray
	virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) = 0;
};

#endif
