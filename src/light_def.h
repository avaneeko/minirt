#ifndef LIGHT_DEF_H
# define LIGHT_DEF_H

# include "v3_def.h"

struct s_light
{
	t_v3	pos;	/*	Position.	*/
	t_v3	col;	/*	Color.		*/
	t_f32	bright;	/*	Brightness.	*/
};
typedef struct s_light	t_light;

#endif
