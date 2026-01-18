#include "v3_def.h"

void	v3_scalar_add(t_v3 const *a, t_f32 b, t_v3 *dst)
{
	dst->x = a->x + b;
	dst->y = a->y + b;
	dst->z = a->z + b;
}

void	v3_scalar_sub(t_v3 const *a, t_f32 b, t_v3 *dst)
{
	dst->x = a->x - b;
	dst->y = a->y - b;
	dst->z = a->z - b;
}

void	v3_scalar_mul(t_v3 const *a, t_f32 b, t_v3 *dst)
{
	dst->x = a->x * b;
	dst->y = a->y * b;
	dst->z = a->z * b;
}

void	v3_scalar_div(t_v3 const *a, t_f32 b, t_v3 *dst)
{
	dst->x = a->x / b;
	dst->y = a->y / b;
	dst->z = a->z / b;
}
