#ifndef BVHH
#define BVHH

#include <vector>
#include "algorithm.h"


class BVH
{
public:
	BVH(std::vector<Triangle*> &t, int d);

	void hit(const Ray &r, std::vector<Triangle*> &t);
	void divide();
	bool contains(const vec3 &center, const vec3 &dim, const vec3 &ve);

	int depth;
	bool hasLeaf;
	std::vector<Triangle*> triangles;
	BVH* child[2];
	Box box;
	vec3 dimensions;
	vec3 center;
	int longest;
};

#endif