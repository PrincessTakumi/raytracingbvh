#include "algorithm.h"

Triangle::Triangle(vec3 a, vec3 b, vec3 c, Material *m) : v0(a), v1(b), v2(c), mat(m)
{
	N = (v1 - v0).crossproduct(v2 - v0);
	box.expand(v0.e[0], v0.e[1], v0.e[2]);
	box.expand(v1.e[0], v1.e[1], v1.e[2]);
	box.expand(v2.e[0], v2.e[1], v2.e[2]);
	center = box.getCenter();
}

bool Triangle::hit(const Ray &r, float tmin, float tmax, hit_record &rec)
{
	if (!box.hitBox(r))
		return false;

	vec3 e0 = v0 - v2;
	vec3 e1 = v1 - v2;

	vec3 pvec = (r.direction()).crossproduct(e1);
	float determinant = (pvec).dotproduct(e0);

	if ((determinant) < FLT_EPSILON)
		return false;

	float invDet = 1 / determinant;

	vec3 tvec = r.origin() - v2;
	float temp = tvec.dotproduct(pvec) *invDet;
	if (temp < 0 || temp > 1)
		return false;

	vec3 qvec = tvec.crossproduct(e0);
	float temp2 = (r.direction()).dotproduct(qvec) *invDet;
	if (temp2 < 0 || temp + temp2 > 1)
		return false;

	float t = e1.dotproduct(qvec) *invDet;
	if (t < tmin || t > tmax)
		return false;

	rec.t = t;
	rec.p = r.get_point_at(t);
	rec.normal = N.unit_vector();
	rec.mat = mat;

	return true;

}