#ifndef CYLINDER_INTERSECTION_DESC_H
# define CYLINDER_INTERSECTION_DESC_H

/**
 * Cylinder intersection descriptor.
 *
 * This describes all the information needed to calculate the closest cylinder
 * intersection.
 */

# include "cylinder_def.h"
# include "hit_def.h"
# include "ray_def.h"

struct s_cylinder_intersection_desc
{
	t_cylinder const	*cylinders;
	t_u32				cylinder_len;
	t_ray				ray;
	t_f32				dist_min;
	t_f32				dist_max;
	t_hit				*hit;
};
typedef struct s_cylinder_intersection_desc t_cylinder_intersection_desc;

#endif
