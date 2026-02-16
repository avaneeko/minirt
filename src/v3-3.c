#include "v3_def.h"

t_f32	v3_dot(t_v3 const *a, t_v3 const *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	v3_cross(t_v3 const *a, t_v3 const *b, t_v3 *dst)
{
	dst->x = a->y * b->z - a->z * b->y;
	dst->y = a->z * b->x - a->x * b->z;
	dst->z = a->x * b->y - a->y * b->x;
}

t_u32	v3_rgb_to_u32(t_v3 c)
{
	t_u32 const	r = (t_u32)(c.x * 255.0f + 0.5f);
	t_u32 const	g = (t_u32)(c.y * 255.0f + 0.5f);
	t_u32 const	b = (t_u32)(c.z * 255.0f + 0.5f);

	return ((r << 16) | (g << 8) | b);
}
