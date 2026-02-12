#include "cylinder_intersection.h"

void	intersect_cylinder_side(t_cylinder_intersection_desc const *desc);
void	intersect_cylinder_cap(t_cylinder_intersection_desc const *desc);

void	intersect_cylinders(t_cylinder_intersection_desc const *desc)
{
	intersect_cylinder_side(desc);
	intersect_cylinder_cap(desc);
}
