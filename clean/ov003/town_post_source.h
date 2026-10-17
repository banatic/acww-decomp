/* Overlay 3's post source (main/town_posts.h): a global object of main (data_021f4b3c) whose
 * vtable (data_ov003_0223a248) is overlay 3's: slot 0 is main's destructor
 * (TownPosts_DestructOverlaySource), slot 1 the deleting destructor here, slot 2 its post_at
 * (func_ov003_02227394). */
#ifndef CLEAN_OV003_TOWN_POST_SOURCE_H
#define CLEAN_OV003_TOWN_POST_SOURCE_H

#include "main/field_collision.h"
#include "types.h"

CollisionPostSource *TownPostSource_Delete(CollisionPostSource *source);
const u8 *TownPostSource_PostOfItem(const u16 *item);
int TownPostSource_PostAt(CollisionPostSource *source, fx32 *radius, fx32 *height, int *kind, int x, int z);

#endif
