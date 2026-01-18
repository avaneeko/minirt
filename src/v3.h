#ifndef V3_H
# define V3_H

/**
 * This file defines vector3 math.
 */

# include "v3_def.h"

void
v3_add(t_v3 const *a, t_v3 const *b, t_v3 *dst);

void
v3_sub(t_v3 const *a, t_v3 const *b, t_v3 *dst);

void
v3_mul(t_v3 const *a, t_v3 const *b, t_v3 *dst);

void
v3_div(t_v3 const *a, t_v3 const *b, t_v3 *dst);

void
v3_scalar_add(t_v3 const *a, t_f32 b, t_v3 *dst);

void
v3_scalar_sub(t_v3 const *a, t_f32 b, t_v3 *dst);

void
v3_scalar_mul(t_v3 const *a, t_f32 b, t_v3 *dst);

void
v3_scalar_div(t_v3 const *a, t_f32 b, t_v3 *dst);

t_f32
v3_len(t_v3 const *a);

t_f32
v3_len2(t_v3 const *a);

void
v3_normalize(t_v3 *a);

void
v3_normalize_to(t_v3 const *a, t_v3 *dst);

t_f32
v3_dot(t_v3 const *a, t_v3 const *b);

void
v3_cross(t_v3 const *a, t_v3 const *b, t_v3 *dst);

#endif
