#include <iso646.h>
#include <math.h>
#include "v3_def.h"

t_f32	v3_len(t_v3 const *a)
{
	return (sqrtf(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_f32	v3_len2(t_v3 const *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

void	v3_normalize(t_v3 *a)
{
	t_f32 const norm = v3_len(a);

	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

void	v3_normalize_to(t_v3 const *a, t_v3 *dst)
{
	t_f32 const norm = v3_len(a);

	dst->x = a->x / norm;
	dst->y = a->y / norm;
	dst->z = a->z / norm;
}

int	v3_normalize_safe(t_v3 *a)
{
	t_f32 const epsilon = __FLT_EPSILON__ * 10.f;
	t_f32 const norm = v3_len(a);

	if (isnan(norm) or norm < epsilon)
		return (0);

	a->x /= norm;
	a->y /= norm;
	a->z /= norm;

	return (not isnan(a->x) and not isnan(a->y) and not isnan(a->z));
}
