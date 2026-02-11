# ifndef SHADOW_H
#define SHADOW_H

#include "ray_def.h"
#include "hit_def.h"
#include "light_def.h"
#include "shading_desc.h"
#include "v3.h"
#include <math.h>

int is_in_shadow(t_hit const *hit, t_shading_desc const *desc);

#endif