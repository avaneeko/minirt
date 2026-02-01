#ifndef SPHERE_INTERSECTION_DESC_H
# define SPHERE_INTERSECTION_DESC_H

/**
 * Sphere intersection descriptor.
 *
 * This describes all the information needed to calculate the closest sphere
 * intersection.
 */

# include "sphere_def.h"
# include "hit_def.h"
# include "ray_def.h"

struct s_sphere_intersection_desc
{
	t_sphere const	*spheres;
	t_u32			sphere_len;
	t_ray			ray;
	t_f32			dist_min;
	t_f32			dist_max;
	t_hit			*hit;
};
typedef struct s_sphere_intersection_desc t_sphere_intersection_desc;

#endif
