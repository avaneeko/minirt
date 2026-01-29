#ifndef MINITYPES_H
# define MINITYPES_H

/**
 * This file defines types that are used throughout the minirt.
 *
 * Please use these types instead of hardcoding int, long etc. unless the
 * program behavior is not dependent on the variables' underlying type.
 *
 * Because of the norm, they have to be prepended with the `t_`.
 */

# include <stdint.h>
# include <stddef.h>

typedef int8_t		t_s8;
typedef uint8_t		t_u8;
typedef int16_t		t_s16;
typedef uint16_t	t_u16;
typedef int32_t		t_s32;
typedef uint32_t	t_u32;
typedef int64_t		t_s64;
typedef uint64_t	t_u64;
typedef float		t_f32;
typedef double		t_f64;

typedef size_t		t_usize;
typedef ptrdiff_t	t_ssize;

typedef uintptr_t	t_uptr;
typedef intptr_t	t_sptr;
typedef ptrdiff_t	t_ptrdiff;

#endif
