#ifndef WORLD_DEF_H
# define WORLD_DEF_H

/**
 * This file defines t_world which stores geometry, diffuse lights and
 * unique parameters like ambient light and background color.
 */

# include "minitypes.h"
# include "cam_def.h"

/* fw */
struct s_sphere;
typedef struct s_sphere t_sphere;

struct s_objs
{
	t_sphere	*spheres;
	t_u32		sphere_len;
	t_u32		sphere_cap;
};
typedef struct s_objs t_objs;

struct s_world
{
	t_objs	objs;
	t_cam	cam;
	t_u32	bg_col;	/* xrgb */
};
typedef struct s_world t_world;

#endif
