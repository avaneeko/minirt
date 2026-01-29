#ifndef WORLD_DEF_H
# define WORLD_DEF_H

/**
 * This file defines t_world which stores geometry, diffuse lights and
 * unique parameters like ambient light and background color.
 */

# include "minitypes.h"
# include "cam_def.h"
# include "amb.h"
# include "light.h"

/* fw */
struct s_sphere;
typedef struct s_sphere t_sphere;

struct s_plane;
typedef struct s_plane t_plane;

struct s_cylinder;
typedef struct s_cylinder t_cylinder;

struct s_objs
{
	t_sphere	*spheres;
	t_u32		sphere_len;
	t_u32		sphere_cap;
	t_plane		*planes;
	t_u32		plane_len;
	t_u32		plane_cap;
	t_cylinder	*cylinders;
	t_u32		cylinder_len;
	t_u32		cylinder_cap;
};
typedef struct s_objs t_objs;

struct s_world
{
	t_objs	objs;
	t_cam	cam;
	t_amb   amb;
	t_light light;
	t_u32	bg_col;	/* xrgb */
};
typedef struct s_world t_world;

#endif
