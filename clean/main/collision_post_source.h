/* The base class of the post sources (CollisionPostSource of field_collision.h, class vtable
 * 0x020da1fc: destructor, deleting destructor, post_at), which tell the field's collision which
 * units hold a post: its constructors and destructors, its post_at (no unit holds a post) and
 * the source the collision asks, the current map's (word 0x120 of the map) or, when it has
 * none, a default one of the base class, built on first use. */
#ifndef CLEAN_MAIN_COLLISION_POST_SOURCE_H
#define CLEAN_MAIN_COLLISION_POST_SOURCE_H

#include "field_collision.h"
#include "types.h"

CollisionPostSource *CollisionPostSource_Current(void);
int CollisionPostSource_NoPost(void);
void CollisionPostSource_DestructBase(CollisionPostSource *source);
CollisionPostSource *CollisionPostSource_Delete(CollisionPostSource *source);
void CollisionPostSource_Destruct(CollisionPostSource *source);
void CollisionPostSource_ConstructDefault(CollisionPostSource *source);
void CollisionPostSource_Construct(CollisionPostSource *source);

#endif
