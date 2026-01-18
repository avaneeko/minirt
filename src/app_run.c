#include <mlx.h>
#include "app_def.h"

void app_run(t_app const *app)
{
    mlx_loop(app->mlx);
}