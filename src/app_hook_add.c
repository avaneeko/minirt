#include "app.h"
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "error_messages.h"

/**
 * Registers a specified fnptr to the event of `hook_id`
 */
static
void	register_hook(t_app const *app, t_s8 hook_id, void *fnptr, void *param)
{
	if (hook_id == APP_HOOK_THINK)
		mlx_loop_hook(app->mlx, fnptr, param);
	else if (hook_id == APP_HOOK_KEY_UP)
		mlx_key_hook(app->wnd, fnptr, param);
	else if (hook_id == APP_HOOK_MOUSE)
		mlx_mouse_hook(app->wnd, fnptr, param);
	else
	{
		write(2, ERR_FATAL_APP_HOOK_INVALID, sizeof(ERR_FATAL_APP_HOOK_INVALID)
			- 1);
		app_destroy(app);
		exit(1);
	}
}

void	app_hook_add(t_app const *app, t_hook const *hooks)
{
	while (hooks->id != APP_HOOK_END_SENTINEL)
	{
		register_hook(app, hooks->id, hooks->fnptr, hooks->param);
		hooks++;
	}
}
