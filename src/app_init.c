#include "minirt.h"
#include "mlx.h"
#include "config.h"

/**
 * Creates frame buffers.
 *
 * Always creates only 1 frame buffer in non-bonus.
 *
 * UNDONE: This glues malloc() and mlx_new_image() failures into
 * one ERR_FATAL_MLX_FB_FAIL. It would be nice if it didn't.
 *
 * Returns 1 on success.
 */
static
int	c_fb(void *mlx, t_u8 *fb_cnt, void ***fb)
{
	*fb = malloc(1 * sizeof(void *));
	if (not *fb)
		return (*fb_cnt = 0);
	**fb = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (not **fb)
	{
		free(*fb);
		return (0);
	}
	return (*fb_cnt = 1);
}

/**
 * This hook is called when `X` (aka 'close') is pressed.
 */
static
void	hk_end(void *param)
{
	mlx_loop_end(param);
}

/**
 * Registers necessary hooks.
 */
static
void	register_hooks(void *mlx, void *wnd)
{
	mlx_hook(wnd, 17, 0, (void *)hk_end, mlx);
}

/**
 * `app` is assumed to be fully uninitialized.
 */
void	app_init(t_app *app, int argc, char const **argv)
{
	(void)argc;
	(void)argv;
	app->fb_cnt = 0;
	app->fpq = 0;
	app->mlx = mlx_init();
	if (not app->mlx)
		app_fatal_error(app, ERR_FATAL_MLX_FAIL);
	app->wnd = mlx_new_window(app->mlx,
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (not app->wnd)
		app_fatal_error(app, ERR_FATAL_MLX_WND_FAIL);
	if (not c_fb(app->mlx, &app->fb_cnt, &app->fb))
		app_fatal_error(app, ERR_FATAL_MLX_FB_FAIL);
	register_hooks(app->mlx, app->wnd);
}
