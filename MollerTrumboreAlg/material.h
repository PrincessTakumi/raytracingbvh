#ifndef MATERIALH
#define MATERIALH

#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "utility.h"

class Material {
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;
};


class lambertian : public Material 
{
public:
	lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
	vec3 albedo;
};

class metal : public Material {
public:
	metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
	vec3 albedo;
	float fuzz;
};

class dielectric : public Material 
{
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const;

	float ref_idx;
};

class Barycentric : public Material
{
public:
	Barycentric(const float &uin, const float &vin) { u = uin; v = vin; }
	Barycentric() {}
	virtual bool scatter(const Ray &r, const hit_record &rec, vec3 &attenuation, Ray &scatter) const;
	

	float u;
	float v;
};

#endif

