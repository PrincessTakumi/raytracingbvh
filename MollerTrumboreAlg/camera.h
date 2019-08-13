#define _USE_MATH_DEFINES

#ifndef CAMERAH
#define CAMERAH

#include <math.h>
#include "ray.h"
#include "utility.h"
#include "vec3.h"

class Camera
{
public:
	Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);

	Ray get_ray(float s, float t);

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};
#endif
