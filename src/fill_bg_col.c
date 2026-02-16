#include "fill_bg_col.h"
#include "config.h"

void	fill_bg_col(t_u32 *px, t_u32 bg_col)
{
	t_u32	y;
	t_u32	x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			px[y * WINDOW_WIDTH + x] = bg_col;
			x++;
		}
		y++;
	}
}
