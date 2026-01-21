#include "app.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * Fatal error defines an application termination point that conveys the error
 * occurred to the user, performs a complete clean up of all resources held by
 * the application and gracefully exits the program.
 */

void	app_fatal_error(t_app *app, char const *msg)
{
	if (msg)
		(void)write_exact(2, msg, slen(msg));
	app_destroy(app);
	exit(1);
}
