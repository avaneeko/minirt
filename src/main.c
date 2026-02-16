/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:22:41 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:22:42 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	draw(t_app *app, t_world const *world);

void	think(void *param)
{
	t_aw_pair *const	aw = param;

	draw(aw->a, aw->w);
	if (!aw->a->fpq)
		return ;
	mlx_put_image_to_window(aw->a->mlx, aw->a->wnd, *aw->a->fb, 0, 0);
	aw->a->fpq = 0;
	return ;
}

void	on_key_up(int key, void *param)
{
	t_aw_pair *const	aw = param;

	if (key == 65307)
		mlx_loop_end(aw->a->mlx);
}

void	trace_intersect_shade(t_world const *world, t_u32 x, t_u32 y, t_u32 *px)
{
	t_ray const	ray = ray_from_pixel(&world->cam, x, y);
	t_hit const	hit = intersect(world, &ray);
	t_v3		c;

	if (hit.dist != __FLT_MAX__)
	{
		c = shade(&hit, &(t_shading_desc const){
				.light = &world->light, .ambient = &world->ambient,
				.world = world,
				.flags = SHADE_AMBIENT | SHADE_DIFFUSE | SHADE_SHADOWS,
			});
		px[y * WINDOW_WIDTH + x] = v3_rgb_to_u32(c);
	}
}

void	draw(t_app *app, t_world const *world)
{
	t_u32 *const	px = (t_u32 *)mlx_get_data_addr(
			*app->fb, &(int){0}, &(int){0}, &(int){0});
	t_u32			y;
	t_u32			x;

	if (!px)
		return ;
	fill_bg_col(px, world->bg_col);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			trace_intersect_shade(world, x, y, px);
			x++;
		}
		y++;
	}
	app->fpq = 1;
}

int	main(int argc, char const **argv)
{
	t_app			app;
	t_world			world;
	t_aw_pair const	d = {&app, &world};

	world_init(&world);
	parsing(&world, argc, argv[1]);
	cam_init(&world.cam);
	app_init(&app, argc, argv);
	app_hook_add(&app, (t_hook const []){
	{APP_HOOK_THINK, &think, (void *)&d},
	{APP_HOOK_KEY_UP, &on_key_up, (void *)&d},
	{APP_HOOK_END_SENTINEL, NULL, NULL}
	});
	app_run(&app);
	app_destroy(&app);
	return (0);
}
