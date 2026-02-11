#ifndef SHADING_DESC_H
# define SHADING_DESC_H

/**
 * Shading descriptor. Contains all of the information needed for
 * the final color shading pass, which itself consists of:
 *
 * 1) Ambient lighting pass.			SHADE_AMBIENT flag.
 * 2) Lambert model diffuse pass.		SHADE_DIFFUSE flag.
 * 3) Hard shadow ray vis-check pass.	SHADE_SHADOWS flag.
 *
 * Even though these passes are separate, they are forward-driven, meaning
 * they are ran for sequentially per pixel and combined immediately.
 *
 * Use SHADE_* defines in shading_desc.flags to enable passes.
 */

/**
 * UNDONE: How do we encorporate world data or tracing interface
 * for hard shadows?
 */

# include "light_def.h"
# include "ambient_def.h"
# include "world_def.h"
# define SHADE_AMBIENT 1
# define SHADE_DIFFUSE 2
# define SHADE_SHADOWS 4

struct s_shading_desc
{
	t_light const	*light;		/*	Point light.			*/
	t_ambient const	*ambient;	/*	Ambient light.			*/
	t_world const	*world;		/*	Shadows require world.	*/
	int				flags;		/*	Shading flags.			*/
};
typedef struct s_shading_desc	t_shading_desc;

#endif
