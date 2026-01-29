#ifndef LIGHT_H
# define LIGHT_H

# include "v3.h"
# include "color_def.h"

struct s_light
{
	t_v3 point;
	t_color color;
	float  brightness;
};
typedef struct s_light t_light;

#endif
