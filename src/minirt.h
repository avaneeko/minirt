#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <iso646.h>
# include "minitypes.h"
# include "utils.h"
# include "error_messages.h"

struct s_app
{
	void	*mlx;	/* MLX ptr. */
	void	*wnd;	/* MLX Window. */
	void	**fb;	/* Frame buffer ptr array. */
	t_u8	fb_cnt;	/* Frame buffer count. */
};
typedef struct s_app	t_app;

/**
 * App initialization.
 */
void
app_init(t_app *app, int argc, char const **argv);

void
app_destroy(t_app const *app);

/*																			*/
/*	Display the error, clean up and exit.									*/
/*																			*/
void
fatal_error(t_app *app, char const *msg);

#endif
