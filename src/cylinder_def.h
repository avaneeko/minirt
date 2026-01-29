#ifndef CYLINDER_DEF_H
# define CYLINDER_DEF_H

/**
 * This file defines the cylinder struct.
 */

# include "v3_def.h"

struct s_cylinder
{
	t_v3	pos;	/* Position.	*/
	t_v3	ang;	/* Angles.		*/
	t_f32	r;		/* Radius.		*/
	t_f32	h;		/* Height.		*/
};

#endif
