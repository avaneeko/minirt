#include "minirt.h"
#include "world_def.h"
#include "sphere_def.h"

/* test */
#pragma region test
#include <stdio.h>
#include "mlx.h"
#include "config.h"

typedef struct{t_app *a; t_world *w;} data;

void
InitDebugWorld(t_world *world);
void
WorldDump(t_world const *w);

void draw(t_app *app, t_world const *world);
void try_present(t_app *app);
t_ray ray_from_pixel(t_cam const *cam, int x, int y);

/**
 * This is not correct, since it traces an infinite unbound ray from
 * the camera front and back at the same time.
*/
int hit_sphere(t_sphere const *sp, t_ray const *r) {
	t_v3 oc; v3_sub(&sp->pos, &r->pos, &oc);
	t_f32 a = v3_dot(&r->dir, &r->dir);
	t_f32 b = -2.0 * v3_dot(&r->dir, &oc);
	t_f32 c = v3_dot(&oc, &oc) - sp->r*sp->r;
	t_f32 discriminant = b*b - 4*a*c;
	return (discriminant >= 0);
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
			if (hit_sphere(world->objs.spheres + 0, &ray))
				px[y*WINDOW_WIDTH + x] = mk_col_xrgb(255 * ((float)x / (WINDOW_WIDTH-1)), 0, 255 * ((float)y / (WINDOW_HEIGHT-1)));
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
