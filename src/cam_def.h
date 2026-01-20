#ifndef CAM_H
# define CAM_H

# include "v3.h"

struct s_cam
{
	t_v3	pos;	/* Position in world space. */
	t_v3	dir;	/* View angles (normalized). */
	t_f32	fov;	/* Field of view (in radians). */
};
typedef struct s_cam t_cam;

#endif
