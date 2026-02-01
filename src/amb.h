#ifndef AMB_H
# define AMB_H

# include <stdbool.h>
# include "v3.h"

struct s_amb
{
	bool  is_set;
	float ratio;
	t_v3 color;
};
typedef struct s_amb t_amb;

#endif
