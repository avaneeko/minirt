#ifndef SPHERE_DEF_H
# define SPHERE_DEF_H

# include "v3.h"

/**
 * This file contains the definition of the sphere.
 */

struct s_sphere
{
	t_v3 	pos;	/* Position in world space. */
	t_f32	r;		/* Radius. */
	t_v3	col;	/* Color. */
};
typedef struct s_sphere t_sphere;

#endif
