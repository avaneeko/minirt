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

static
t_v3	shade_ambient(t_ambient const *a, t_v3 obj_color)
{
	t_v3	ret;

	v3_mul(&a->col, &obj_color, &ret);
	ret.x *= a->bright;
	ret.y *= a->bright;
	ret.z *= a->bright;
	return (ret);
}

/**
 * Blends the final colors from all passes. Clamps to 1 meaning that the object
 * is fully lit.
 */
static
t_v3	clamp_blend(t_v3 ambient, t_v3 diffuse, t_v3 shadows)
{
	t_v3	color;

	v3_add(&ambient, &diffuse, &color);
	v3_add(&color, &shadows, &color);
	return ((t_v3){
		fminf(color.x, 1.f), fminf(color.y, 1.f), fminf(color.z, 1.f)
	});
}

t_v3	shade(t_hit const *hit, t_shading_desc const *desc)
{
	t_v3	ambient;
	t_v3	diffuse;
	t_v3	shadows;

	ambient = (t_v3){0, 0, 0};
	diffuse = (t_v3){0, 0, 0};
	shadows = (t_v3){0, 0, 0};
	if (desc->flags & SHADE_AMBIENT)
		ambient = shade_ambient(desc->ambient, hit->col);
	if (desc->flags & SHADE_DIFFUSE)
		diffuse = shade_diffuse(desc->light, hit);
	if (desc->flags & SHADE_SHADOWS)
	{
		if (is_in_shadow(hit, desc))
			diffuse = (t_v3){0, 0, 0};
	}
	return (clamp_blend(ambient, diffuse, shadows));
}
