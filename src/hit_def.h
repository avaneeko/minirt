#ifndef HIT_DEF_H
# define HIT_DEF_H

/**
 * This file defines the hit struct.
 */

# include "v3_def.h"

struct s_hit
{
	t_v3	pos;	/*	Position.			*/
	t_v3	norm;	/*	Normal. 			*/
	t_f32	dist;	/*	Distance.			*/
	t_u8	front;	/*	Front or back hit?	*/
	t_v3	col;	/*	Color.				*/
};
typedef struct s_hit t_hit;

#endif
