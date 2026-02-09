#ifndef AMBIENT_DEF_H
# define AMBIENT_DEF_H

# include "v3_def.h"

struct s_ambient
{
	t_v3	col;	/*	Color.		*/
	t_f32	bright;	/*	Brightness.	*/
};
typedef struct s_ambient	t_ambient;

#endif
