#include "minirt.h"

int	main(int argc, char const **argv)
{
	t_app	app;

	app_init(&app, argc, argv);
	app_run(&app);
	app_destroy(&app);
	return (0);
}
