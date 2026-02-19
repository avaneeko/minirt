/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:15:51 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 18:26:26 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_def.h"
#include "shading_desc.h"
#include "shadow.h"
#include "v3.h"

t_hit	intersect(t_world const *world, t_ray const *ray);

int	is_in_shadow(t_hit const *hit, t_shading_desc const *desc)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_v3	dir_to_light;
	t_f32	dist_to_light;

	shadow_ray.pos = hit->pos;
	shadow_ray.pos.x += hit->norm.x * 1e-4f;
	shadow_ray.pos.y += hit->norm.y * 1e-4f;
	shadow_ray.pos.z += hit->norm.z * 1e-4f;
	v3_sub(&desc->light->pos, &shadow_ray.pos, &dir_to_light);
	dist_to_light = v3_len(&dir_to_light);
	v3_normalize(&dir_to_light);
	shadow_ray.dir = dir_to_light;
	shadow_hit = intersect(desc->world, &shadow_ray);
	if (shadow_hit.dist < dist_to_light)
		return (1);
	return (0);
}
