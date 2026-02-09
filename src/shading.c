#include "shading.h"
#include "v3.h"
#include <math.h>

static
t_v3 shade_diffuse(t_light const *l, t_hit const *hit)
{
	t_v3	to_l; /* To light */
	t_f32	dist2;
	t_f32	inv_dist;
	t_v3	ldir;
	t_f32	ndotl;
	t_v3	c;

	/* to_l = LightPos - HitPos */
	v3_sub(&l->pos, &hit->pos, &to_l);
	dist2 = v3_dot(&to_l, &to_l);
	if (dist2 <= 1e-12f) /* Anti Self-Shadowing. */
		return ((t_v3){0, 0, 0});

	inv_dist = 1.f / sqrtf(dist2);
	ldir.x = to_l.x * inv_dist;
	ldir.y = to_l.y * inv_dist;
	ldir.z = to_l.z * inv_dist;

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
