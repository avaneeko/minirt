#include "world_def.h"
#include "sphere_def.h"
#include "plane_def.h"
#include "cylinder_def.h"
#include "cam.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void
InitCamera(t_cam *cam)
{
	// cam->pos = (t_v3){-50.f, 0.f, 20.f};
	cam->pos = (t_v3){0.f, 0.f, 0.f};
	cam->dir = (t_v3){0.f, 0.f, 1.f};
	cam->fov = 70.f;
}

/**
 * Sphere:
 * sp 0.0,0.0,20.6 12.6 10,0,255
 ∗ identifier: sp
 ∗ x, y, z coordinates of the sphere center: 0.0,0.0,20.6
 ∗ the sphere diameter: 12.6
 ∗ R,G,B colors in the range [0-255]: 10, 0, 255
 */
static void
InitSpheres(t_sphere **spheres, t_u32 *len, t_u32 *cap)
{
	if ((*spheres = malloc(16 * sizeof(t_sphere))) == NULL)
	{
		write(2, "Out of memory\r\n", 15);
		_Exit(-1);
	}
	// spheres[0]->pos = (t_v3){0.f,0.f,20.6f};
	(*spheres)[0].pos = (t_v3){0.f,15.f,0.f};
	(*spheres)[0].r = 12.6f / 2.f;
	(*spheres)[0].col = (t_v3){10 / 255.f, 0 / 255.f, 255 / 255.f};

	(*spheres)[1].pos = (t_v3){10.f,20.f,0.f};
	(*spheres)[1].r = 12.6f / 2.f;
	(*spheres)[1].col = (t_v3){10 / 255.f, 0 / 255.f, 255 / 255.f};

	(*spheres)[2].pos = (t_v3){-20.f,42.f,5.f};
	(*spheres)[2].r = 12.6f / 2.f;
	(*spheres)[2].col = (t_v3){10 / 255.f, 0 / 255.f, 255 / 255.f};

	(*spheres)[3].pos = (t_v3){20.f,42.f,-17.f};
	(*spheres)[3].r = 12.6f / 4.f;
	(*spheres)[3].col = (t_v3){10 / 255.f, 0 / 255.f, 255 / 255.f};

	*len = 4;
	*cap = 16;
}

static void
InitCylinders(t_cylinder **cylinders, t_u32 *len, t_u32 *cap)
{
	if ((*cylinders = malloc(16 * sizeof(t_cylinder))) == NULL)
	{
		write(2, "Out of memory\r\n", 15);
		_Exit(-1);
	}
	(*cylinders)[0].pos = (t_v3){0.f,35.f,0.f};
	(*cylinders)[0].ang = (t_v3){1.0f, 0.0f, 0.0f};
	(*cylinders)[0].r = 12.6f / 2.f;
	(*cylinders)[0].h = 10.0f;
	(*cylinders)[0].col = (t_v3){10 / 255.f, 0 / 255.f, 255 / 255.f};

	*len = 1;
	*cap = 16;
}

/**
 * Plane:
 * pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
 ∗ identifier: pl
 ∗ x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
 ∗ 3D normalized normal vector, in the range [-1,1] for each x, y, z axis:
 * 0.0,1.0,0.0
 ∗ R,G,B colors in the range [0-255]: 0,0,225
 */
static void
InitPlanes(t_plane **planes, t_u32 *len, t_u32 *cap)
{
	if ((*planes = malloc(16 * sizeof(t_plane))) == NULL)
	{
		write(2, "Out of memory\r\n", 15);
		_Exit(-1);
	}

	(*planes)[0].pos = (t_v3){0.0f, 0.0f, -10.0f};
	(*planes)[0].ang = (t_v3){0.0f, 1.0f, 0.0f};
	(*planes)[0].col = (t_v3){0.f, 0.f, 1.f};

	*len = 0;
	*cap = 16;
}

/**
 * Initialize a debug world.
 *
 * Test scene for debugging.
 * Assumes that passed in world is completely uninitialized.
 */
void
InitDebugWorld(t_world *world)
{
	InitCamera(&world->cam);
	InitSpheres(&world->objs.spheres, &world->objs.sphere_len, &world->objs.sphere_cap);
	InitPlanes(&world->objs.planes, &world->objs.plane_len, &world->objs.plane_cap);
	InitCylinders(&world->objs.cylinders, &world->objs.cylinder_len, &world->objs.cylinder_cap);
	world->cam.fwd = (t_v3){0.f, 1.f, 0.f};
	world->cam.fov = 1.22173048f;

	world->bg_col = 0x00112233; /* or 0x0011223344 */

	return;
}

static void DumpV3(char const *label, t_v3 v)
{
	printf("%s{ x=%.6f, y=%.6f, z=%.6f }", label, (double)v.x, (double)v.y, (double)v.z);
}

static void DumpSphere(t_u32 i, t_sphere const *s)
{
	printf("  sphere[%u]: ", (unsigned)i);
	DumpV3("pos=", s->pos);
	printf(", r=%.6f, ", (double)s->r);
	DumpV3("col=", s->col);
	printf("\n");
}

void WorldDump(t_world const *w)
{
	t_u32 i;

	if (!w)
	{
		printf("WorldDump: (null)\n");
		return;
	}

	printf("t_world @ %p\n", (void const *)w);
	printf("  spheres: %p\n", (void const *)w->objs.spheres);
	printf("  sphere_len: %u\n", (unsigned)w->objs.sphere_len);
	printf("  sphere_cap: %u\n", (unsigned)w->objs.sphere_cap);

	printf("  cam:\n");
	printf("    ");
	DumpV3("pos=", w->cam.pos);
	printf("\n");
	printf("    ");
	DumpV3("dir=", w->cam.dir);
	printf("\n");
	printf("    fov=%.6f (rad)\n", (double)w->cam.fov);

	if (!w->objs.spheres)
	{
		printf("  spheres: (null pointer)\n");
		return;
	}

	printf("  spheres (iterating 0..sphere_len-1):\n");
	for (i = 0; i < w->objs.sphere_len; ++i)
		DumpSphere(i, &w->objs.spheres[i]);
}
