#ifndef APP_H
# define APP_H

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
app_fatal_error(t_app *app, char const *msg);

/**
 * Adds an application hook(s) to the specified events.
 * `hooks` has to end with an APP_HOOK_END_SENTINEL hook id hook.
 *
 * See t_hook and APP_HOOK_* definitions.
 */
void
app_hook_add(t_app const *app, t_hook const *hooks);

#endif
