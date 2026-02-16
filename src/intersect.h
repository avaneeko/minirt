#ifndef INTERSECT_H
# define INTERSECT_H

/*
	World-ray intersection function.
*/

# include "world_def.h"
# include "ray_def.h"
# include "hit_def.h"

t_hit	intersect(t_world const *world, t_ray const *ray);

#endif
