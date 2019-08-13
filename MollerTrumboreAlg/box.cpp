#include "box.h"

#include "Box.h"

vec3 Box::getCenter()
{
	return (vec3(bounds[0], bounds[2], bounds[4]) + vec3(bounds[1], bounds[3], bounds[5])) / 2;
}

float Box::getMaxLength()
{
	float a = bounds[1] - bounds[0];
	float b = bounds[3] - bounds[2];
	float c = bounds[5] - bounds[4];
	if (a > b) return (a > c ? a : c);
	else return (b > c ? b : c);
}

int Box::getMaxDimension()
{
	float a = bounds[1] - bounds[0];
	float b = bounds[3] - bounds[2];
	float c = bounds[5] - bounds[4];
	if (a > b) return (a > c ? 0 : 2);
	else return (b > c ? 1 : 2);
}

void Box::expand(const float &a, const float &b, const float &c)
{
	if (a < bounds[0]) bounds[0] = a;
	if (a > bounds[1]) bounds[1] = a;
	if (b < bounds[2]) bounds[2] = b;
	if (b > bounds[3]) bounds[3] = b;
	if (c < bounds[4]) bounds[4] = c;
	if (c > bounds[5]) bounds[5] = c;
}

void Box::expand(float b[6])
{
	this->expand(b[0], b[2], b[4]);
	this->expand(b[1], b[3], b[5]);
}

bool Box::hitBox(const Ray &r)
{
	float txmin, txmax, tymin, tymax, tzmin, tzmax;

	txmin = (bounds[	r.sign[0]] - r.A.e[0]) * r.inv.e[0];
	txmax = (bounds[1 - r.sign[0]] - r.A.e[0]) * r.inv.e[0];
	tymin = (bounds[2 + r.sign[1]] - r.A.e[1]) * r.inv.e[1];
	tymax = (bounds[3 - r.sign[1]] - r.A.e[1]) * r.inv.e[1];

	if ((txmin > tymax) || (tymin > txmax))
		return false;

	if (tymin > txmin)
		txmin = tymin;
	if (tymax < txmax)
		txmax = tymax;

	tzmin = (bounds[4 + r.sign[2]] - r.A.e[2]) * r.inv.e[2];
	tzmax = (bounds[5 - r.sign[2]] - r.A.e[2]) * r.inv.e[2];

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;

	if (tzmin > txmin)
		txmin = tzmin;
	if (tzmax < txmax)
		txmax = tzmax;

	return true;
}