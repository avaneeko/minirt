#include "minirt.h"
#include "world_def.h"
#include "sphere_def.h"

/* test */
#pragma region test
#include <stdio.h>
#include <time.h>
#include "mlx.h"
#include "config.h"
#include "hit_def.h"
#include "sphere_intersection.h"
#include "plane_intersection.h"

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

	intersect_planes(
		&(t_plane_intersection_desc const){
		.planes = world->objs.planes,
		.plane_len = world->objs.plane_len,
		.ray = *ray,
		.dist_min = 0.f,
		.dist_max = hit.dist,
		.hit = &hit,
	});

	/* UNDONE: */
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

struct s_move_input
{
	/* Keys. */
	int	w : 1;
	int a : 1;
	int s : 1;
	int d : 1;
	int q : 1;
	int e : 1;
	/* Mouse delta. */
	int	mx : 12;
	int	my : 12;
};
typedef struct s_move_input move_input;
static move_input move;

static
void cam_move(t_cam *cam, t_f32 step)
{
    t_v3 delta;

    delta = (t_v3){0,0,0};

    if (move.w) v3_muladds(&delta, &cam->fwd,  step, &delta);
    if (move.s) v3_muladds(&delta, &cam->fwd, -step, &delta);
    if (move.d) v3_muladds(&delta, &cam->right,  step, &delta);
    if (move.a) v3_muladds(&delta, &cam->right, -step, &delta);

    /* world up for Z-up */
    if (move.e) delta.z += step;
    if (move.q) delta.z -= step;

    cam->pos.x += delta.x;
    cam->pos.y += delta.y;
    cam->pos.z += delta.z;
}

static int last_x = -1;
static int last_y = -1;
int on_mouse_move(int x, int y, void *param)
{
    (void)param;

    if (last_x >= 0 and not (move.e == move.q and move.q != 0))
    {
        move.mx += (x - last_x);
        move.my += (y - last_y);
    }
    last_x = x;
    last_y = y;
    return 0;
}

static t_v3 v3_rot_axis(t_v3 v, t_v3 axis, t_f32 ang)
{
    t_f32 c = cosf(ang);
    t_f32 s = sinf(ang);

    /* axis must be normalized */
    t_v3 axv;
    t_v3 a_cross_v;

    axv.x = axis.x * v3_dot(&axis, &v);
    axv.y = axis.y * v3_dot(&axis, &v);
    axv.z = axis.z * v3_dot(&axis, &v);

    v3_cross(&axis, &v, &a_cross_v);

    /* v*c + (axis×v)*s + axis*(axis·v)*(1-c) */
    v.x = v.x * c + a_cross_v.x * s + axv.x * (1.0f - c);
    v.y = v.y * c + a_cross_v.y * s + axv.y * (1.0f - c);
    v.z = v.z * c + a_cross_v.z * s + axv.z * (1.0f - c);
    return v;
}

static void cam_rotate_mouse(t_cam *cam, t_f32 sens)
{
    t_f32 yaw = (t_f32)move.mx * sens;
    t_f32 pitch = (t_f32)move.my * sens;

    t_v3 world_up = (t_v3){0, 0, 1};

    /* yaw around world up */
    cam->fwd = v3_rot_axis(cam->fwd, world_up, -yaw);

    /* rebuild right/up from new forward (your existing cam_init logic), OR: */
    /* pitch around camera right (after yaw) */
    v3_normalize_safe(&cam->fwd);
    cam_init(cam); /* rebuild basis first so cam->right is correct */
    cam->fwd = v3_rot_axis(cam->fwd, cam->right, -pitch);

    v3_normalize_safe(&cam->fwd);
    cam_init(cam);

    move.mx = move.my = 0;
}

// 119 W
// 97 A
// 115 S
// 100 D
// 113 Q
// 101 E
static void
set_move_input(int key, int state)
{
	if (key == 119)
		move.w = state;
	else if (key == 97)
		move.a = state;
	else if (key == 115)
		move.s = state;
	else if (key == 100)
		move.d = state;
	else if (key == 113)
		move.q = state;
	else if (key == 101)
		move.e = state;
	if (key == 0x0020)
		move.mx = move.my = state;
}

// static
// void	process_move_input(int key)
// {

// }

// struct timespec start, end;
// clock_gettime(CLOCK_MONOTONIC_RAW, &start);
// //do stuff
// clock_gettime(CLOCK_MONOTONIC_RAW, &end);

// uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
static float ft; // frametime;
void think(void *param)
{
	draw(((data*)param)->a, ((data*)param)->w);
	try_present(((data*)param)->a);
	ft = 1.f;
	cam_move(&((data*)param)->w->cam, ft);
	cam_rotate_mouse(&((data*)param)->w->cam, .01f);
	// *(int*)&move = 0;
	return;
}

void key_down(int key, void *param)
{
	if (/*key == 113 or */key == 65307)
		mlx_loop_end(((data *)param)->a->mlx);
	set_move_input(key, -1);
}

void key_up(int key, void *param)
{
	if (/*key == 113 or */key == 65307)
		mlx_loop_end(((data *)param)->a->mlx);
	set_move_input(key, 0);
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
		{APP_HOOK_KEY_DOWN, &key_down, &d},
		{APP_HOOK_KEY_UP, &key_up, &d},
		{APP_HOOK_MOUSE_MOVE, &on_mouse_move, &d},
		{APP_HOOK_END_SENTINEL, NULL, NULL}
	});
	app_run(&app);
	app_destroy(&app);
	return (0);
}
