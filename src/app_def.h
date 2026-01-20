#ifndef APP_DEF_H
# define APP_DEF_H

/**
 * This file defines the data structure of the app.
 */

# include "minitypes.h"

struct s_app
{
	void	*mlx;	/* MLX ptr. */
	void	*wnd;	/* MLX Window. */
	void	**fb;	/* Frame buffer ptr array. */
	t_u8	fb_cnt;	/* Frame buffer count. */
};
typedef struct s_app	t_app;

#endif
