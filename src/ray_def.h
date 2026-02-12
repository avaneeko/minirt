#ifndef RAY_DEF_H
# define RAY_DEF_H

/**
 * Defines ray struct which has an origin and a direction.
 */

# include "v3_def.h"

struct s_ray
{
	t_v3	pos;
	t_v3	dir;
};
typedef struct s_ray	t_ray;

#endif
