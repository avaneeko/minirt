#ifndef PLANE_INTERSECTION_DESC_H
# define PLANE_INTERSECTION_DESC_H

/**
 * Plane intersection descriptor.
 *
 * This describes all the information needed to calculate the closest plane
 * intersection.
 */

# include "plane_def.h"
# include "hit_def.h"
# include "ray_def.h"

struct s_plane_intersection_desc
{
	t_plane const	*planes;
	t_u32			plane_len;
	t_ray			ray;
	t_f32			dist_min;
	t_f32			dist_max;
	t_hit			*hit;
};
typedef struct s_plane_intersection_desc t_plane_intersection_desc;

#endif
