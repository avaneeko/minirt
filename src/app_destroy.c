#include "minirt.h"
#include "mlx.h"

void	app_destroy(t_app const *app)
{
	if (app->mlx)
	{
		if (app->wnd)
			mlx_destroy_window(app->mlx, app->wnd);
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
