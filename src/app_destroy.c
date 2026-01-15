#include "minirt.h"
#include "mlx.h"

void	app_destroy(t_app const *app)
{
	t_s32 i;
	if (app->mlx)
	{
		if (app->wnd)
			mlx_destroy_window(app->mlx, app->wnd);
		if (app->fb_cnt)
		{
			i = 0;
			while (i < app->fb_cnt)
				mlx_destroy_image(app->mlx, app->fb[app->fb_cnt - 1 - i++]);
			free(app->fb);
		}
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
