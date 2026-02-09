#ifndef SHADING_H
# define SHADING_H

# include "shading_desc.h"
# include "v3_def.h"
# include "hit_def.h"
# include "light_def.h"

/**
 * This file defines shading functions, they're run after
 * the intersection (raytracing) stage to determine the pixel's final color.
 */

t_v3
shade(t_hit const *hit, t_shading_desc const *desc);

#endif
