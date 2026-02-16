#ifndef RAY_FROM_PIXEL_H
# define RAY_FROM_PIXEL_H

# include "ray_def.h"
# include "cam_def.h"

t_ray	ray_from_pixel(t_cam const *cam, int x, int y);

#endif
