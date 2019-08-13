#ifndef UTILITYH
#define UTILITYH

#include "vec3.h"

vec3 unit_circle();
vec3 unit_sphere();
vec3 reflect(const vec3 &v, const vec3 &n);

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);
float schlick(float cos, float ref_idx);

#endif
