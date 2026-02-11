# ifndef SHADOW_H
#define SHADOW_H

# include "hit_def.h"
# include "shading_desc.h"

int	is_in_shadow(t_hit const *hit, t_shading_desc const *desc);

#endif
