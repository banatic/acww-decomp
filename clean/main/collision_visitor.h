/* The visitors a gathering of the field's collision hands its lists to (CollisionVisitor of
 * collision_query.h): the base class (vtable 0x020da1c0, whose three methods do nothing), the
 * segment test's methods (vtable 0x020da1d4: the first wall, floor or post the path from its
 * start to its end meets moves the end there and is recorded) and the push-out visitor's
 * methods for floors and posts (vtable 0x020da1e8; its walls method is CollisionPushOut_Walls of
 * field_collision.h). */
#ifndef CLEAN_MAIN_COLLISION_VISITOR_H
#define CLEAN_MAIN_COLLISION_VISITOR_H

#include "collision_query.h"
#include "field_collision.h"
#include "types.h"

void CollisionVisitor_NoPosts(void);
void CollisionVisitor_NoFloors(void);
void CollisionVisitor_NoWalls(void);
void CollisionVisitor_Destruct(CollisionVisitor *visitor);
void CollisionVisitor_Construct(CollisionVisitor *visitor);
void CollisionVisitor_TestPosts(CollisionSegmentTest *test, CollisionPostList *posts);
void CollisionVisitor_TestFloors(CollisionSegmentTest *test, CollisionFloorList *floors);
void CollisionVisitor_TestWalls(CollisionSegmentTest *test, CollisionWallList *walls);
void CollisionVisitor_PushOutPosts(CollisionPushOut *visitor, CollisionPostList *posts);
void CollisionVisitor_PushOutFloors(CollisionPushOut *visitor, CollisionFloorList *floors);

#endif
