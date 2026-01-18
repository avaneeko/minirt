#include "v3_def.h"

void	v3_add(t_v3 const *a, t_v3 const *b, t_v3 *dst)
{
	dst->x = a->x + b->x;
	dst->y = a->y + b->y;
	dst->z = a->z + b->z;
}

void	v3_sub(t_v3 const *a, t_v3 const *b, t_v3 *dst)
{
	dst->x = a->x - b->x;
	dst->y = a->y - b->y;
	dst->z = a->z - b->z;
}

void	v3_mul(t_v3 const *a, t_v3 const *b, t_v3 *dst)
{
	dst->x = a->x * b->x;
	dst->y = a->y * b->y;
	dst->z = a->z * b->z;
}

void	v3_div(t_v3 const *a, t_v3 const *b, t_v3 *dst)
{
	dst->x = a->x / b->x;
	dst->y = a->y / b->y;
	dst->z = a->z / b->z;
}
