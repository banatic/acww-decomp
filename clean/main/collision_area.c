/* Collision areas (collision_area.h). */
#include "collision_area.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "collision_box.h"
#include "collision_triangle.h"
#include "itcm/vector.h"

static_assert(sizeof(CollisionArea) == 0x4c, "collision area");
static_assert(offsetof(CollisionArea, next) == 0x38 && offsetof(CollisionArea, reach_squared) == 0x48,
              "collision area fields");

/* The areas in the world, the last one added first. */
extern CollisionArea *data_021c30e0;
/* The class vtable of an area. */
extern const u8 data_020da234[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* func_02032610: tells each area of the list whose reach covers `position` (the squared
 * distance from its centre at most its reach_squared) that `owner` of `radius` is there. */
void CollisionArea_TellNear(const Vec3 *position, fx32 radius, void *owner)
{
    for (CollisionArea *area = data_021c30e0; area != NULL; area = area->next) {
        s64 distance_squared = Vec_DistanceSquared(&area->centre, position);
        if ((s64) area->reach_squared >= distance_squared) {
            const CollisionAreaVtable *vtable = (const CollisionAreaVtable *) area->triangle.vtable;
            vtable->touch(area, position, owner, radius);
        }
    }
}
CLEAN_AS(func_02032610, CollisionArea_TellNear)

/* func_02032658: takes `area` out of the list and resets it; whether it was in the list. */
int CollisionArea_Remove(CollisionArea *area)
{
    CollisionArea *previous = NULL;
    for (CollisionArea *current = data_021c30e0; current != NULL; current = current->next) {
        if (current == area) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                data_021c30e0 = current->next;
            }
            CollisionArea_Reset(area);
            return 1;
        }
        previous = current;
    }
    return 0;
}
CLEAN_AS(func_02032658, CollisionArea_Remove)

/* func_02032694: puts `area` at the head of the list unless it has a next area; whether it did.
 * QUIRK: the last area of the list has none, so adding it again links the list into a loop. */
int CollisionArea_Add(CollisionArea *area)
{
    if (area->next != NULL) {
        return 0;
    }
    area->next = data_021c30e0;
    data_021c30e0 = area;
    return 1;
}
CLEAN_AS(func_02032694, CollisionArea_Add)

/* func_020326b0: empties the list. `list` (the world's byte at 0x1a91) is not read. */
void CollisionArea_ClearList(void *list)
{
    (void) list;
    data_021c30e0 = NULL;
}
CLEAN_AS(func_020326b0, CollisionArea_ClearList)

/* func_020326bc: the list object's destructor; nothing to do. */
void CollisionArea_ListDestruct(void *list)
{
    (void) list;
}
CLEAN_AS(func_020326bc, CollisionArea_ListDestruct)

/* func_020326c0: the list object's constructor; nothing to do. */
void CollisionArea_ListConstruct(void *list)
{
    (void) list;
}
CLEAN_AS(func_020326c0, CollisionArea_ListConstruct)

/* func_020326c4: makes `area` the triangle `a`, `b`, `c` with its normal from its corners
 * (CollisionTriangle_CornerNormal), its centre the middle of the corners' bounds and its reach
 * `reach`. */
void CollisionArea_Set(CollisionArea *area, const Vec3 *a, const Vec3 *b, const Vec3 *c, fx32 reach)
{
    area->reach_squared = FX_MulFunc(reach, reach);

    Vec3 max = *a;
    Vec3 min = *a;
    CollisionBox_KeepMax(&max, b);
    CollisionBox_KeepMin(&min, b);
    CollisionBox_KeepMax(&max, c);
    CollisionBox_KeepMin(&min, c);
    area->centre.x = (min.x + max.x) >> 1;
    area->centre.y = (min.y + max.y) >> 1;
    area->centre.z = (min.z + max.z) >> 1;

    Vec3 normal;
    CollisionTriangle_CornerNormal(&normal, a, b, c);
    CollisionTriangle_Set(&area->triangle, a, b, c, &normal);
}
CLEAN_AS(func_020326c4, CollisionArea_Set)

/* func_02032754: the area's centre. */
Vec3 *CollisionArea_GetCentre(CollisionArea *area)
{
    return &area->centre;
}
CLEAN_AS(func_02032754, CollisionArea_GetCentre)

/* func_02032758: out of any list, no reach, centred at 0. */
void CollisionArea_Reset(CollisionArea *area)
{
    area->next = NULL;
    area->reach_squared = 0;
    area->centre.x = 0;
    area->centre.y = 0;
    area->centre.z = 0;
}
CLEAN_AS(func_02032758, CollisionArea_Reset)

/* func_02032768: an area's constructor: the triangle's, then the area's vtable, reset. */
CollisionArea *CollisionArea_Construct(CollisionArea *area)
{
    CollisionTriangle_ConstructBase(&area->triangle);
    area->triangle.vtable = data_020da234;
    CollisionArea_Reset(area);
    return area;
}
CLEAN_AS(func_02032768, CollisionArea_Construct)
