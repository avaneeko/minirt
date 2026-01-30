#include "adapter.h"

static t_v3 pvec3_to_v3(t_pvec3 v)
{
	t_v3 out;

	out.x = v.x;
	out.y = v.y;
	out.z = v.z;
	return (out);
}
static void adapt_light(t_pworld *pworld, t_world *world)
{
	if (!pworld->L.is_set)
		return ;
	world->light.point = pvec3_to_v3(pworld->L.lpoint);
	world->light.color.r = pworld->L.lcolor.r / 255.0f;
	world->light.color.g = pworld->L.lcolor.g / 255.0f;
	world->light.color.b = pworld->L.lcolor.b / 255.0f;
	world->light.brightness = pworld->L.brightness;
}

static void adapt_camera(t_pworld *pworld, t_world *world)
{
	if (!pworld->C.is_set)
		return ;
	world->cam.pos = pvec3_to_v3(pworld->C.vpoint);
	world->cam.dir = pvec3_to_v3(pworld->C.orien);
	world->cam.fov = pworld->C.fov; //degree
}

static void adapt_ambient(t_pworld *pworld, t_world *world)
{
	if (!pworld->A.is_set)
		return ;
	world->amb.color.r = pworld->A.a_color.r / 255.0f;
	world->amb.color.g = pworld->A.a_color.g / 255.0f;
	world->amb.color.b = pworld->A.a_color.b / 255.0f;
	world->amb.ratio = pworld->A.ratio ;
}

void adapt_pworld_to_world(t_pworld *pworld, t_world *world)
{
	adapt_ambient(pworld, world);
	adapt_camera(pworld, world);
	adapt_light(pworld, world);
	//adapt_sphere()
	//adapt_planes()
	//adapt_cylinder()
}
