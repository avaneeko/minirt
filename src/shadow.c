#include "shadow.h"
#include "v3.h"
#include "shading_desc.h"

/* 1. build shadow ray */
/* 2. compute dist_to_light */
/* 3. shadow_hit.dist = dist_to_light */
/* 4. call intersection system */
/* 5. if block_hit.dist < dist_to_light -> shadow */
t_hit intersect(t_world const *world, t_ray const *ray);

int is_in_shadow(t_hit const *hit, t_shading_desc const *desc)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_v3	dir_to_light;
	t_f32	dist_to_light;

	/*hit position on surface*/
	shadow_ray.pos = hit->pos;

	/*move the start point a tiny bit outside the surface(in the normal direction), if you start the ray exactly at hit->pos,
	the ray will immediately hit the same object again. That’s called self-intersection.*/
	/*1e-4f is around  1 x 10^{-4}*/
	shadow_ray.pos.x += hit->norm.x * (1e-4);
	shadow_ray.pos.y += hit->norm.y * (1e-4);
	shadow_ray.pos.z += hit->norm.z * (1e-4);

	/*direction = destination − start (need to normalize it)*/
	v3_sub(&desc->light->pos, &shadow_ray.pos, &dir_to_light);

	/* length of vector(hit point to light point) */
	dist_to_light = v3_len(&dir_to_light);

	/*normalize to_light vector
	Dotting a vector with itself results in the square of its magnitude (length)*/
	v3_normalize(&dir_to_light);
	shadow_ray.dir = dir_to_light;
	shadow_hit = intersect(desc->world, &shadow_ray);
	if (shadow_hit.dist < dist_to_light)
		return (1);
	return (0);
}
