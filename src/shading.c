#include "shading.h"
#include "v3.h"
#include <math.h>

/**
 * dist2 and inv_dist are shortened into dist[2].
 *
 * dist[0] is dist2. Distance squared.
 * dist[1] is inv_dist. Inverse distance.
 */
static
t_v3	shade_diffuse(t_light const *l, t_hit const *hit)
{
	t_v3	to_l;
	t_v3	ldir;
	t_f32	ndotl;
	t_f32	dist[2];
	t_v3	c;

	v3_sub(&l->pos, &hit->pos, &to_l);
	dist[0] = v3_dot(&to_l, &to_l);
	if (dist[0] <= 1e-12f)
		return ((t_v3){0, 0, 0});
	dist[1] = 1.f / sqrtf(dist[0]);
	ldir.x = to_l.x * dist[1];
	ldir.y = to_l.y * dist[1];
	ldir.z = to_l.z * dist[1];
	ndotl = v3_dot(&hit->norm, &ldir);
	if (ndotl < 0.0f)
		ndotl = 0.0f;
	v3_mul(&l->col, &hit->col, &c);
	c.x *= l->bright * ndotl;
	c.y *= l->bright * ndotl;
	c.z *= l->bright * ndotl;
	return (c);
}

t_v3	shade(t_hit const *hit, t_shading_desc const *desc)
{
	t_v3	ret;

	if (desc->flags & SHADE_AMBIENT)
	{
		__builtin_printf("%s:%u %s: %s",
			__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(),
			"t_desc_shading_desc.flags & SHADE_AMBIENT is not implemented.\n");
		__builtin_abort();
	}
	if (desc->flags & SHADE_DIFFUSE)
		ret = shade_diffuse(desc->light, hit);
	if (desc->flags & SHADE_SHADOWS)
	{
		__builtin_printf("%s:%u %s: %s",
			__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(),
			"t_desc_shading_desc.flags & SHADE_SHADOWS is not implemented.\n");
		__builtin_abort();
	}
	return (ret);
}
