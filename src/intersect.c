#include "intersect.h"
#include "sphere_intersection.h"
#include "plane_intersection.h"
#include "cylinder_intersection.h"

t_hit	intersect(t_world const *world, t_ray const *ray)
{
	t_hit	hit;

	hit.dist = __FLT_MAX__;
	intersect_spheres(&(t_sphere_intersection_desc const){
		world->objs.spheres, world->objs.sphere_len, *ray, 0.f, hit.dist, &hit,
	});
	intersect_planes(&(t_plane_intersection_desc const){
		world->objs.planes, world->objs.plane_len, *ray, 0.f, hit.dist, &hit});
	intersect_cylinders(&(t_cylinder_intersection_desc const){
		world->objs.cylinders, world->objs.cylinder_len, *ray, 0.f, hit.dist,
		&hit});
	return (hit);
}
