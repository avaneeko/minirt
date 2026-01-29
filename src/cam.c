#include <math.h>
#include "cam_def.h"
#include "v3.h"
#include "config.h"

/**
 * +Y is forward, +X is right, +Z is up.
 */

/**
 * We prefer to have +Z up by default, but swap to +Y
 * if the forward vector is too parallel to the up vector.
 */
static
t_v3	choose_up(t_cam *cam)
{
	t_v3 up;

	up = (t_v3){0.0f, 0.0f, 1.0f};
	if (fabsf(v3_dot(&cam->fwd, &up)) < 0.999f)
		return up;

	up = (t_v3){0.0f, 1.0f, 0.0f};
	if (fabsf(v3_dot(&cam->fwd, &up)) < 0.999f)
		return up;

	return (t_v3){1.0f, 0.0f, 0.0f};
}

int	cam_init(t_cam *cam)
{
	t_v3 const	up_hint = choose_up(cam);

	v3_cross(&cam->fwd, &up_hint, &cam->right);
	if (!v3_normalize_safe(&cam->right))
		return (0);

	v3_cross(&cam->right, &cam->fwd, &cam->up);
    cam->aspect = (t_f32)WINDOW_WIDTH / (t_f32)WINDOW_HEIGHT;
    cam->half_h = tanf(cam->fov * 0.5f);
    cam->half_w = cam->aspect * cam->half_h;

	return (v3_normalize_safe(&cam->up));
}
