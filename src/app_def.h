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
	t_u8	fpq;	/* Is frame queued for presenting? */
};
typedef struct s_app	t_app;

/**
 * App hook definitions.
 */

# define APP_HOOK_THINK 0
# define APP_HOOK_KEY_UP 1
# define APP_HOOK_MOUSE 2
# define APP_HOOK_END_SENTINEL -1

/* App hook function prototypes:

APP_HOOK_THINK:
void
think(void *param)

APP_HOOK_KEY_UP:
void
key_up(int key, void *param)

APP_HOOK_MOUSE:
void
mouse(int button, int x, int y, void *param)

*/

struct s_hook
{
	t_s8	id;		/* Hook id. */
	void	*fnptr;	/* Function ptr. */
	void	*param;	/* Parameter ptr passed to the function. */
};
typedef struct s_hook t_hook;

#endif
