/* Overlay 3's post source (town_post_source.h). */
#include "town_post_source.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "main/collision_post_source.h"
#include "main/acre_tile.h" /* AcreTile_ItemInAcre */

/* The source's vtable. */
extern const CollisionPostSourceVtable data_ov003_0223a248;

/* func_ov003_022208cc (vtable slot 1): the source's vtable, the base class's destructor, and
 * the source is freed (operator delete); returns `source`. */
CollisionPostSource *TownPostSource_Delete(CollisionPostSource *source)
{
    source->vtable = &data_ov003_0223a248;
    CollisionPostSource_DestructBase(source);
    Heap_OperatorDeleteB(source);
    return source;
}
CLEAN_AS(func_ov003_022208cc, TownPostSource_Delete)

/* The posts of a family of item codes (the code's top nibble): one record of three bytes per
 * code of the family, from code 0 of the family on. The table data_ov003_02236b0c ends with a
 * NULL `posts`; it lists the family 0 (0x103 codes). */
typedef struct TownPostSourceFamily {
    const u8 *posts; /* `count` records: radius, height (both in 1/16 units) and kind */
    u8 family;       /* the code's top nibble */
    u8 pad_05;
    u16 count;
} TownPostSourceFamily;

/* A post record's bytes. */
#define TOWN_POST_SOURCE_RADIUS 0
#define TOWN_POST_SOURCE_HEIGHT 1
#define TOWN_POST_SOURCE_KIND 2
#define TOWN_POST_SOURCE_RECORD 3

extern const TownPostSourceFamily data_ov003_02236b0c[];
/* The town's map. */
extern AcreMap *data_021c80bc;

/* A unit's acre (16 units to an acre), rounded down as the ARM's arithmetic shift does. */
static int town_post_source_acre(int unit)
{
    return unit >= 0 ? unit >> 4 : ~(~unit >> 4);
}

/* func_ov003_022273f8: the post record of item `item` (NULL for none): the family of its top
 * nibble, the record of its low twelve bits when the family lists that many; NULL also when
 * the record's radius is 0. */
const u8 *TownPostSource_PostOfItem(const u16 *item)
{
    const u8 *post = NULL;
    if (item == NULL) {
        return NULL;
    }
    u16 code = *item;
    int family = (code & 0xf000) >> 12;
    int index = code & 0xfff;
    for (const TownPostSourceFamily *entry = data_ov003_02236b0c; entry->posts != NULL; entry++) {
        if (family == entry->family) {
            if (entry->count > index) {
                post = entry->posts + TOWN_POST_SOURCE_RECORD * index;
            }
            break;
        }
    }
    if (post != NULL && post[TOWN_POST_SOURCE_RADIUS] == 0) {
        post = NULL;
    }
    return post;
}
CLEAN_AS(func_ov003_022273f8, TownPostSource_PostOfItem)

/* func_ov003_02227394 (vtable slot 2): whether unit (x, z) of the town's map holds a post, by
 * the item on layer 0 there (TownPostSource_PostOfItem): its radius and height (the record's
 * 1/16 units in fx32) and kind. A record of kind 0 is no post. 0 while there is no map. */
int TownPostSource_PostAt(CollisionPostSource *source, fx32 *radius, fx32 *height, int *kind, int x, int z)
{
    (void) source;
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int acre_x = town_post_source_acre(x);
    int acre_z = town_post_source_acre(z);
    const u8 *post =
        TownPostSource_PostOfItem(AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0));
    if (post == NULL || post[TOWN_POST_SOURCE_KIND] == 0) {
        return 0;
    }
    *radius = post[TOWN_POST_SOURCE_RADIUS] << 8;
    *height = post[TOWN_POST_SOURCE_HEIGHT] << 8;
    *kind = post[TOWN_POST_SOURCE_KIND];
    return 1;
}
CLEAN_AS(func_ov003_02227394, TownPostSource_PostAt)
