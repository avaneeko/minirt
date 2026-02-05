#include "cylinder_intersection.h"
#include <math.h>
#include "../src/cylinder_intersection_side~.c"
#include "../src/cylinder_intersection_cap~.c"

void	intersect_cylinders(t_cylinder_intersection_desc const *desc)
{
	intersect_cylinder_side(desc);
	intersect_cylinder_cap(desc);
}
