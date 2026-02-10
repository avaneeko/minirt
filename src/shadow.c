#include "shadow.h"

//shoots a ray from the surface
//directon -> to light postion
//then check if it reaches the light position

int is_shadow(t_hit const *hit)
{
	t_ray shadow_ray;

	shadow_ray.pos.x = hit->pos.x;
	shadow_ray.pos.y = hit->pos.y;
	shadow_ray.pos.y = hit->pos.y;
	printf("shadow ray x: %f y: %f z: %f\n", shadow_ray.pos.x, shadow_ray.pos.y, shadow_ray.pos.z);
}