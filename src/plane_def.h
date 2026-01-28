#ifndef PLANE_DEF_H
# define PLANE_DEF_H

/**
 * This file defines the plane struct.
 */

# include "v3_def.h"

struct s_plane
{
	t_v3	pos;	/* Position.	*/
	t_v3	ang;	/* Angles.		*/
	t_v3	col;	/* Color.		*/
};
typedef struct s_plane t_plane;

#endif
