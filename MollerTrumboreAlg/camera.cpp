#include "camera.h"

Camera::Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) 
{
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	w = (lookfrom - lookat).unit_vector();
	u = (vup.crossproduct(w)).unit_vector();
	v = w.crossproduct(u);

	origin = lookfrom;
	lower_left_corner = lookfrom - u * focus_dist * half_width - v * focus_dist * half_height - w * focus_dist;
	horizontal = u * 2 * half_width * focus_dist;
	vertical = v * 2 * half_height * focus_dist;
}


Ray Camera::get_ray(float s, float t) {
	vec3 rd = unit_circle() * lens_radius;
	vec3 offset = u * rd.e[0] + v * rd.e[1];
	return Ray(origin + offset, lower_left_corner + horizontal * s + vertical * t - origin - offset);

};
