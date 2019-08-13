#include "material.h"

bool lambertian::scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const 
{
	vec3 target = rec.p + rec.normal + unit_sphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}

bool metal::scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	vec3 reflected = reflect((r_in.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + unit_sphere() * fuzz);
	attenuation = albedo;
	return ((scattered.direction()).dotproduct(rec.normal) > 0);
}

bool dielectric::scatter(const Ray& r_in, const hit_record& rec, vec3& attenuation, Ray& scattered) const
{
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0, 1.0, 1.0);
	vec3 refracted;
	float reflect_prob;
	float cosine;
	if ((r_in.direction()).dotproduct(rec.normal) > 0)
	{
		outward_normal = rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx * (r_in.direction()).dotproduct(rec.normal) / r_in.direction().length();
	}
	else {
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -(r_in.direction()).dotproduct(rec.normal) / r_in.direction().length();
	}
	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
		reflect_prob = schlick(cosine, ref_idx);
	}
	else {
		scattered = Ray(rec.p, reflected);
		reflect_prob = 1.0;

	}
	if ((rand() / (RAND_MAX + 1.0)) < reflect_prob) {
		scattered = Ray(rec.p, reflected);
	}
	else {
		scattered = Ray(rec.p, refracted);
	}
	return true;
}

bool Barycentric::scatter(const Ray &r, const hit_record &rec, vec3 &attenuation, Ray &scatter) const
{
	vec3 target = rec.p + rec.normal + unit_sphere();
	scatter = Ray(rec.p, target - rec.p);
	attenuation = vec3(0.7, 0.7, 0);
	return true;
}