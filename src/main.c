#include "minirt.h"
#include "world_def.h"
#include "sphere_def.h"

int key(int key, void *param)
{
	t_app const *app = param;
	(void)app;
	if (key == 113 or key == 65307)
		write_exact(2, "should quit now :)\r\n", sizeof("should quit now :)\r\n") - 1);
}

int	main(int argc, char const **argv)
{
	t_app	app;

	app_init(&app, argc, argv);
	app_hook_add(&app, (t_hook const[]){
		{APP_HOOK_KEY_UP, &key, &app},
		{APP_HOOK_END_SENTINEL, NULL, NULL}
	});
	app_run(&app);
	app_destroy(&app);
	return (0);
}
