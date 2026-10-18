/* The spheres the net is tested against (catch_sphere.h). */
#include "catch_sphere.h"

#include "clean.h"
#include "itcm/vector.h"
#include "main/scene_query.h"
#include "globe.h"

static_assert(offsetof(CatchSphere, next) == 0x1c && offsetof(CatchSphere, reach) == 0x24, "CatchSphere");

#define SWEEP_STEPS 0x6000 /* 6.0: the sweep is cut into six steps */

extern CatchSphere *data_021d3124; /* the list */

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* func_020899a8: whether a sphere of the list lies along the sweep from map point `from` to map
 * point `to`: six points from `from` in sixths of the way are each tested against every
 * sphere, within `radius` plus the sphere's reach. Each sphere's in_reach says whether it was
 * reached; `index`, when not NULL, gets the index of the last one reached in the list.
 * QUIRK: the sixth point is five sixths of the way, so the end `to` itself is never tested. */
int CatchSphere_FindAlong(const Vec3 *from, const Vec3 *to, fx32 radius, u8 *index, int unused)
{
    (void) unused;
    int found = 0;
    CatchSphere *sphere = data_021d3124;
    Vec3 start;
    Vec3 end;
    Vec3 step;
    Vec3 points[CATCH_SPHERE_SWEEP_POINTS];

    Globe_Bend(&start, from);
    Globe_Bend(&end, to);
    Vec_Subtract(&step, &end, &start);
    step.x = FX_Div(step.x, SWEEP_STEPS);
    step.y = FX_Div(step.y, SWEEP_STEPS);
    step.z = FX_Div(step.z, SWEEP_STEPS);
    for (int i = 0; i < CATCH_SPHERE_SWEEP_POINTS; i++) {
        points[i].x = start.x + i * step.x;
        points[i].y = start.y + i * step.y;
        points[i].z = start.z + i * step.z;
    }

    for (; sphere != NULL; sphere = sphere->next) {
        sphere->in_reach = 0;
        fx32 limit = FX_MulFunc(radius + sphere->reach, radius + sphere->reach);
        for (int i = 0; i < CATCH_SPHERE_SWEEP_POINTS; i++) {
            if ((s64) limit >= Vec_DistanceSquared(&points[i], &sphere->sphere.centre)) {
                sphere->in_reach = 1;
                found = 1;
                if (index != NULL) {
                    *index = sphere->sphere.index;
                }
                break;
            }
        }
    }
    return found;
}
CLEAN_AS(func_020899a8, CatchSphere_FindAlong)

/* func_02089aa8: the sphere put at the head of the list, not reached, with its reach, and
 * registered with the pen's pick round map point `centre`, of `radius`, kind 4 and `index`. */
void CatchSphere_Add(CatchSphere *sphere, Vec3 *centre, fx32 reach, fx32 radius, u8 index)
{
    sphere->next = data_021d3124;
    data_021d3124 = sphere;
    sphere->in_reach = 0;
    sphere->reach = reach;
    TouchPick_SetSphereAndAdd((TouchPick *) (intptr_t) SceneQuery_FieldObject(), &sphere->sphere, centre, radius,
                              CATCH_SPHERE_PICK_KIND, index);
}
CLEAN_AS(func_02089aa8, CatchSphere_Add)

/* func_02089af4: the destructor (the pick sphere's); the sphere's address. */
int CatchSphere_Destruct(CatchSphere *sphere)
{
    TouchPickSphere_Destruct(&sphere->sphere);
    return (int) (intptr_t) sphere;
}
CLEAN_AS(func_02089af4, CatchSphere_Destruct)

/* func_02089b04: the constructor: a pick sphere, in no list and not reached. */
CatchSphere *CatchSphere_Construct(CatchSphere *sphere)
{
    TouchPickSphere_Construct2(&sphere->sphere);
    sphere->next = NULL;
    sphere->in_reach = 0;
    return sphere;
}
CLEAN_AS(func_02089b04, CatchSphere_Construct)
