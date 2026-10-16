/* Collision areas: triangles that want to be told when an actor moves near them (the areas of
 * overlay 9's scene actors). An area is a C++ object (0x4c bytes, class vtable 0x020da234,
 * derived from CollisionTriangle of field_collision.h, whose four methods it keeps) kept in the
 * list at data_021c30e0. Each move of the field's collision (CollisionQuery_Move) tells every
 * area whose reach covers the actor's position through the area's fifth virtual method, which
 * the derived classes provide.
 *
 * Positions are 20.12 fixed point. */
#ifndef CLEAN_MAIN_COLLISION_AREA_H
#define CLEAN_MAIN_COLLISION_AREA_H

#include "autoload_2/vector.h"
#include "field_collision.h"
#include "types.h"

typedef struct CollisionArea {
    CollisionTriangle triangle;
    struct CollisionArea *next; /* 0x38: the next area of the list */
    Vec3 centre;                /* 0x3c: the middle of the bounds of its corners */
    fx32 reach_squared;         /* 0x48: the square of how far from `centre` it is told of actors */
} CollisionArea;

/* The methods of an area: the triangle's four (collision_triangle.h), then what an actor of
 * `radius` at `position` near the area does to it. */
typedef struct CollisionAreaVtable {
    const void *triangle[4];
    void (*touch)(CollisionArea *area, const Vec3 *position, void *owner, fx32 radius);
} CollisionAreaVtable;

void CollisionArea_TellNear(const Vec3 *position, fx32 radius, void *owner);
int CollisionArea_Remove(CollisionArea *area);
int CollisionArea_Add(CollisionArea *area);
void CollisionArea_ClearList(void *list);
void CollisionArea_ListDestruct(void *list);
void CollisionArea_ListConstruct(void *list);
void CollisionArea_Set(CollisionArea *area, const Vec3 *a, const Vec3 *b, const Vec3 *c, fx32 reach);
Vec3 *CollisionArea_GetCentre(CollisionArea *area);
void CollisionArea_Reset(CollisionArea *area);
CollisionArea *CollisionArea_Construct(CollisionArea *area);

#endif
