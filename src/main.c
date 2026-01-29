#include "minirt.h"
#include "world_def.h"
#include "sphere_def.h"

/* test */
#pragma region test
#include <stdio.h>
#include "mlx.h"
#include "config.h"
#include "hit_def.h"
#include "sphere_intersection.h"

typedef struct{t_app *a; t_world *w;} data;

void
InitDebugWorld(t_world *world);
void
WorldDump(t_world const *w);

void draw(t_app *app, t_world const *world);
void try_present(t_app *app);
t_ray ray_from_pixel(t_cam const *cam, int x, int y);

//copypasted into sphere_intersection.c :)
//int	ray_intersect_sphere(t_sphere const *sp, t_ray const *r) {
//	t_v3 oc;
//	t_f32 a;
//	t_f32 b;
//	t_f32 c;
//	t_f32 discriminant;
//
//	v3_sub(&sp->pos, &r->pos, &oc);
//	a = v3_dot(&r->dir, &r->dir);
//	b = -2.0 * v3_dot(&r->dir, &oc);
//	c = v3_dot(&oc, &oc) - sp->r*sp->r;
//	discriminant = b*b - 4*a*c;
//
//	if (discriminant < 0.0f)
//		return 0;
//	discriminant = sqrtf(discriminant);
//
//	return (((-b - discriminant) / (2.0f * a)) > 1e-4f
//		or ((-b + discriminant) / (2.0f * a)) > 1e-4f);
//}
// we replace this with intersect, which then becomes the "shading function"

static t_f32 clamp01(t_f32 x)
{
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

static t_v3 normal_to_rgb(t_v3 n)
{
    t_v3 c;

    c.x = (n.x + 1.0f) * 0.5f;
    c.y = (n.y + 1.0f) * 0.5f;
    c.z = (n.z + 1.0f) * 0.5f;

    c.x = clamp01(c.x);
    c.y = clamp01(c.y);
    c.z = clamp01(c.z);

    return c;
}

t_hit
intersect(t_world const *world, t_ray const *ray)
{
	t_hit	hit;
	hit.dist = __FLT_MAX__;

	intersect_spheres(
		&(t_sphere_intersection_desc const){
		.spheres = world->objs.spheres,
		.sphere_len = world->objs.sphere_len,
		.ray = *ray,
		.dist_min = 0.f,
		.dist_max = hit.dist,
		.hit = &hit,
	});

	/* UNDONE: */
	/* Intersect planes. */
	/* Intersect cylinder. */

	return hit;
}

static t_u32 rgb_to_u32(t_v3 c)
{
    t_u32 r = (t_u32)(c.x * 255.0f + 0.5f);
    t_u32 g = (t_u32)(c.y * 255.0f + 0.5f);
    t_u32 b = (t_u32)(c.z * 255.0f + 0.5f);

    return (r << 16) | (g << 8) | b;
}

void think(void *param)
{
	draw(((data*)param)->a, ((data*)param)->w);
	try_present(((data*)param)->a);
	return;
}

void key(int key, void *param)
{
	if (key == 113 or key == 65307)
		mlx_loop_end(((data *)param)->a->mlx);
}

void try_present(t_app *app)
{
	/* Try to present the frame if it's queued/ready. */

	if (not app->fpq)
		return ; /* nothing to present */

	mlx_put_image_to_window(app->mlx, app->wnd, *app->fb, 0, 0);
	app->fpq = 0; /* reset frame queue status */
}

t_u32	mk_col_xrgb(t_u8 r, t_u8 g, t_u8 b)
{
	return (((t_u32)b & 0xFFu)
		| (((t_u32)g << 8) & 0xFF00u)
		| (((t_u32)r << 16) & 0xFF0000u));
}

void draw(t_app *app, t_world const *world)
{
	t_u32 *const px = (t_u32 *)mlx_get_data_addr(*app->fb, &(int){0}, &(int){0}, &(int){0});
	if (not px)
		return ;

	for (t_u32 y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (t_u32 x = 0; x < WINDOW_WIDTH; x++)
		{
			px[y*WINDOW_WIDTH + x] = world->bg_col;
		}
	}

	for (t_u32 y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (t_u32 x = 0; x < WINDOW_WIDTH; x++)
		{
			t_ray const ray = ray_from_pixel(&world->cam, x, y);
			t_hit const hit = intersect(world, &ray);
			if (hit.dist != __FLT_MAX__)
			{
				t_v3 c = normal_to_rgb(hit.norm);
				px[y*WINDOW_WIDTH + x] = rgb_to_u32(c);
				// px[y*WINDOW_WIDTH + x] = mk_col_xrgb(255 * ((float)x / (WINDOW_WIDTH-1)), 0, 255 * ((float)y / (WINDOW_HEIGHT-1)));
			}
		}
	}
	app->fpq = 1;
}

t_ray ray_from_pixel(t_cam const *cam, int x, int y)
{
	t_f32   u;
	t_f32   v;
	t_f32   sx;
	t_f32   sy;
	t_v3    dir;

	u = ((t_f32)x + 0.5f) / (t_f32)WINDOW_WIDTH;
	v = ((t_f32)y + 0.5f) / (t_f32)WINDOW_HEIGHT;

	sx = (2.0f * u - 1.0f) * cam->half_w;
	sy = (1.0f - 2.0f * v) * cam->half_h;

	/* dir = forward + right*sx + up*sy */
	dir = cam->fwd;
	dir.x += cam->right.x * sx + cam->up.x * sy;
	dir.y += cam->right.y * sx + cam->up.y * sy;
	dir.z += cam->right.z * sx + cam->up.z * sy;

	v3_normalize(&dir);

	return (t_ray){cam->pos, dir};
}

#pragma endregion
/* end of test */

int	main(int argc, char const **argv)
{
	t_app	app;
	t_world world;
	data d = (data){&app, &world};
	InitDebugWorld(&world);

	app_init(&app, argc, argv);
	app_hook_add(&app, (t_hook const[]){
		{APP_HOOK_THINK, &think, &d},
		{APP_HOOK_KEY_UP, &key, &d},
		{APP_HOOK_END_SENTINEL, NULL, NULL}
	});
	app_run(&app);
	app_destroy(&app);
	return (0);
}
