#ifndef OCTREEH
#define OCTREEH

#include <vector>
#include "algorithm.h"

class Octree
{
public:

	Octree(std::vector<Triangle*> &t, int d);
	static bool contains(const vec3 &center, const float &le, const vec3 &ve);
	void divide();
	void hit(const Ray &r, std::vector<Triangle*> &t);

	int depth;
	bool hasLeaf;
	std::vector<Triangle*> triangles;
	Octree* child[8];
	Box box;
	vec3 center;
	float length;
};

#endif
