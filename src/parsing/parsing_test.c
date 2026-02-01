
#include "minirt.h"
#include "world_def.h"
#include "sphere_def.h"
#include "plane_def.h"
#include "cylinder_def.h"
#include <stdio.h>

static void dump_spheres(t_world *w)
{
	t_u32 i;

	printf("Spheres (%u):\n", w->objs.sphere_len);
	i = 0;
	while (i < w->objs.sphere_len)
	{
		t_sphere *s = &w->objs.spheres[i];

		printf("  [%u]\n", i);
		printf("    position = (%f, %f, %f)\n",
			s->pos.x, s->pos.y, s->pos.z);
		printf("    radius = %f\n", s->r);
		printf("    color  = %f,%f,%f\n",
			s->col.x, s->col.y, s->col.z);
		i++;
	}
}

static void dump_planes(t_world *w)
{
	t_u32 i;

	printf("Planes (%u):\n", w->objs.plane_len);
	i = 0;
	while (i < w->objs.plane_len)
	{
		t_plane *p = &w->objs.planes[i];

		printf("  [%u]\n", i);
		printf("    position  = (%f, %f, %f)\n",
			p->pos.x, p->pos.y, p->pos.z);
		printf("    angle = (%f, %f, %f)\n",
			p->ang.x, p->ang.y, p->ang.z);
		printf("    color  = %f,%f,%f\n",
			p->col.x, p->col.y, p->col.z);
		i++;
	}
}

static void dump_cylinders(t_world *w)
{
	t_u32 i;

	printf("Cylinders (%u):\n", w->objs.cylinder_len);
	i = 0;
	while (i < w->objs.cylinder_len)
	{
		t_cylinder *c = &w->objs.cylinders[i];

		printf("  [%u]\n", i);
		printf("    pos    = (%f, %f, %f)\n",
			c->pos.x, c->pos.y, c->pos.z);
		printf("    axis   = (%f, %f, %f)\n",
			c->ang.x, c->ang.y, c->ang.z);
		printf("    radius = %f\n", c->r);
		printf("    height = %f\n", c->h);
		printf("    color  = %f,%f,%f\n",
			c->col.x, c->col.y, c->col.z);
		i++;
	}
}

static void dump_world(t_world *w)
{
	printf("Ambient:\n");
	printf("  ratio = %f\n", w->amb.ratio);
	printf("  color = %f,%f,%f\n",
		w->amb.color.x,
		w->amb.color.y,
		w->amb.color.z);

	printf("Camera:\n");
	printf("  pos = (%f, %f, %f)\n",
		w->cam.pos.x,
		w->cam.pos.y,
		w->cam.pos.z);
	printf("  dir = (%f, %f, %f)\n",
		w->cam.dir.x,
		w->cam.dir.y,
		w->cam.dir.z);
	printf("  fov = %f\n", w->cam.fov);

	printf("Light:\n");
	printf("  point = (%f, %f, %f)\n",
		w->light.point.x,
		w->light.point.y,
		w->light.point.z);
	printf("  brightness = %f\n", w->light.brightness);
	printf("  color = %f,%f,%f\n",
		w->light.color.x,
		w->light.color.y,
		w->light.color.z);

	dump_spheres(w);
	dump_planes(w);
	dump_cylinders(w);
	printf("================================\n");
}
