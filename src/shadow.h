# ifndef SHADOW_H
#define SHADOW_H

#include "ray_def.h"
#include "hit_def.h"
#include "light_def.h"
#include "v3.h"
#include <math.h>

int is_shadow(t_hit const *hit);

#endif