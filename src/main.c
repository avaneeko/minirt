#include "aw_pair_def.h"
#include "minirt.h"
#include "math.h"

/* test */
#pragma region test
#include <stdio.h>
#include <time.h>
#include "mlx.h"
#include "config.h"
#include "hit_def.h"
#include "shading.h"

void draw(t_app *app, t_world const *world);
void try_present(t_app *app);
t_ray ray_from_pixel(t_cam const *cam, int x, int y);

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

    if (last_x >= 0 && !(move.e == move.q && move.q != 0))
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

void	think(void *param)
{
	t_aw_pair *const	aw = param;

	draw(aw->a, aw->w);
	try_present(aw->a);
	cam_move(&aw->w->cam, 1.f);
	cam_rotate_mouse(&aw->w->cam, .01f);
	return;
}

void	key_down(int key, void *param)
{
	t_aw_pair *const	aw = param;

	if (/*key == 113 or */key == 65307)
		mlx_loop_end(aw->a->mlx);
	set_move_input(key, -1);
}

void key_up(int key, void *param)
{
	t_aw_pair *const	aw = param;

	if (/*key == 113 or */key == 65307)
		mlx_loop_end(aw->a->mlx);
	set_move_input(key, 0);
}

void try_present(t_app *app)
{
	/* Try to present the frame if it's queued/ready. */

	if (!app->fpq)
		return ; /* nothing to present */

	mlx_put_image_to_window(app->mlx, app->wnd, *app->fb, 0, 0);
	app->fpq = 0; /* reset frame queue status */
}

static
void	fill_bg_col(t_u32 *px, t_u32 bg_col)
{
	for (t_u32 y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (t_u32 x = 0; x < WINDOW_WIDTH; x++)
		{
			px[y*WINDOW_WIDTH + x] = bg_col;
		}
	}
}

void draw(t_app *app, t_world const *world)
{
	t_u32 *const px = (t_u32 *)mlx_get_data_addr(*app->fb, &(int){0}, &(int){0}, &(int){0});

	if (!px)
		return ;
	fill_bg_col(px, world->bg_col);
	for (t_u32 y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (t_u32 x = 0; x < WINDOW_WIDTH; x++)
		{
			t_ray const ray = ray_from_pixel(&world->cam, x, y);
			t_hit const hit = intersect(world, &ray);
			if (hit.dist != __FLT_MAX__)
			{
				t_v3 c = shade(&hit, &(t_shading_desc const){
					.light = &world->light,
					.ambient = &world->ambient,
					.world = world,
					.flags = SHADE_AMBIENT | SHADE_DIFFUSE | SHADE_SHADOWS,
				});
				px[y*WINDOW_WIDTH + x] = rgb_to_u32(c);
			}
		}
	}
	app->fpq = 1;
}

#pragma endregion
/* end of test */

int	main(int argc, char const **argv)
{
	t_app	app;
	t_world world;
	t_aw_pair d = {&app, &world};

	world_init(&world);
	parsing(&world, argc, argv[1]);
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
