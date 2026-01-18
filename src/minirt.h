#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <iso646.h>
# include "minitypes.h"
# include "utils.h"
# include "error_messages.h"
# include "app_def.h"

/**
 * App initialization.
 */
void
app_init(t_app *app, int argc, char const **argv);

void
app_destroy(t_app const *app);

/**
 * Starts the event polling of the app.
 */
void
app_run(t_app const *app);

/*																			*/
/*	Display the error, clean up and exit.									*/
/*																			*/
void
fatal_error(t_app *app, char const *msg);

#endif
