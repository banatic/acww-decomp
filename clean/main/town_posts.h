/* The town's post sources (field_collision.h: the object a map hands to func_02030ddc, which
 * the collision asks unit by unit whether the unit holds an upright post, and its radius,
 * height and kind):
 *
 * - main's (vtable data_020e50e8, the object at data_021c80c4 every map of acres gets): first
 *   overlay 3's source (data_021f4b3c) is asked; failing that, the object 0x500a and the
 *   snowmen (snowmen.h) on the town's map are posts. Outside the town's case (data_020e54a8
 *   not 0) the one post is unit (3, 4) of scene 0x1d;
 * - overlay 3's source, a global object of main whose vtable (data_ov003_0223a248) and post
 *   function are overlay 3's; only its destructor is main's. */
#ifndef CLEAN_MAIN_TOWN_POSTS_H
#define CLEAN_MAIN_TOWN_POSTS_H

#include "field_collision.h"
#include "types.h"

/* The posts this source makes. */
#define TOWN_POSTS_OBJECT_500A 0x500a
#define TOWN_POSTS_HEIGHT 0x2000
#define TOWN_POSTS_KIND_10 10

int TownPosts_PostAt(CollisionPostSource *source, fx32 *radius, fx32 *height, int *kind, int x, int z);
CollisionPostSource *TownPosts_DeleteSource(CollisionPostSource *source);
CollisionPostSource *TownPosts_DestructSource(CollisionPostSource *source);
CollisionPostSource *TownPosts_ConstructSource(CollisionPostSource *source);
CollisionPostSource *TownPosts_DestructOverlaySource(CollisionPostSource *source);

#endif
