/* The town's post sources (town_posts.h). */
#include "town_posts.h"

#include "acre_tile.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "snowmen.h"

/* Main's source's vtable: destructor, deleting destructor, TownPosts_PostAt. */
extern const u8 data_020e50e8[];
/* Overlay 3's source's vtable. */
extern const u8 data_ov003_0223a248[];

extern u8 data_020e54a8;    /* 0 in the town's case, when the town's map is read */
extern u8 data_021f4b3c[];  /* overlay 3's source */
extern void *data_021c80bc; /* the town's map */
extern u8 data_021f3b56[];  /* the snowmen's records (snowmen.h) */

/* Overlay 3's post function, which asks overlay 3's table of the town's objects. */
extern int func_ov003_02227394(void *source, fx32 *radius, fx32 *height, int *kind, int x, int z);
extern int func_0204bb54(u16 *code); /* a snowman's map object */
extern int func_0204bb2c(u16 *code); /* the snowman's number */
extern u8 func_020b65c4(void);       /* the scene */
/* The base class of the post sources (vtable data_020da1fc): its constructor and destructor,
 * each of which puts the base vtable in. */
extern void func_02031ec0(void *source);
extern void func_02031e84(void *source);

/* The post of the object 0x500a, the snowmen's, and the one of scene 0x1d. */
#define TOWN_POSTS_RADIUS_500A 0xb33
#define TOWN_POSTS_RADIUS_SNOWMAN 0x1000
#define TOWN_POSTS_KIND_SNOWMAN 0
#define TOWN_POSTS_SCENE 0x1d
#define TOWN_POSTS_SCENE_X 3
#define TOWN_POSTS_SCENE_Z 4
#define TOWN_POSTS_RADIUS_SCENE 0xe66

/* A unit's acre (16 units to an acre), rounded down as the ARM's arithmetic shift does. */
static int town_posts_acre(int unit)
{
    return unit >= 0 ? unit >> 4 : ~(~unit >> 4);
}

static void town_posts_set(fx32 *radius, fx32 *height, int *kind, fx32 r, int k)
{
    *radius = r;
    *height = TOWN_POSTS_HEIGHT;
    *kind = k;
}

/* func_020b39bc (slot 2 of main's source): whether unit (x, z) holds a post, and its radius,
 * height and kind. In the town's case overlay 3's source is asked first, and what it answers
 * stands; else the item on layer 0 of the town's map at the unit: the object 0x500a is a post
 * of radius 0xb33 and kind 10, a snowman one of radius 1.0 and kind 0. Otherwise only unit
 * (3, 4) of scene 0x1d holds a post, of radius 0xe66 and kind 10. Every post is 2.0 high.
 * QUIRK: for a snowman its sizes are fetched (Snowmen_Get) and not used; its post has the same
 * radius whatever its size. */
int TownPosts_PostAt(CollisionPostSource *source, fx32 *radius, fx32 *height, int *kind, int x, int z)
{
    (void) source;
    if (data_020e54a8 != 0) {
        if (func_020b65c4() != TOWN_POSTS_SCENE || x != TOWN_POSTS_SCENE_X || z != TOWN_POSTS_SCENE_Z) {
            return 0;
        }
        town_posts_set(radius, height, kind, TOWN_POSTS_RADIUS_SCENE, TOWN_POSTS_KIND_10);
        return 1;
    }

    if (func_ov003_02227394(data_021f4b3c, radius, height, kind, x, z) != 0) {
        return 1;
    }
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int acre_x = town_posts_acre(x);
    int acre_z = town_posts_acre(z);
    u16 *item = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
    if (item == NULL) {
        return 0;
    }
    if (*item == TOWN_POSTS_OBJECT_500A) {
        town_posts_set(radius, height, kind, TOWN_POSTS_RADIUS_500A, TOWN_POSTS_KIND_10);
        return 1;
    }
    if (func_0204bb54(item) == 0) {
        return 0;
    }
    int number = func_0204bb2c(item);
    int head_size;
    int body_size;
    Snowmen_Get((SnowmenRecord *) data_021f3b56, (u32) number, &head_size, &body_size, NULL, NULL, NULL, NULL);
    town_posts_set(radius, height, kind, TOWN_POSTS_RADIUS_SNOWMAN, TOWN_POSTS_KIND_SNOWMAN);
    return 1;
}
CLEAN_AS(func_020b39bc, TownPosts_PostAt)

/* func_020b3ac4: main's source destroyed (TownPosts_DestructSource) and its memory freed. */
CollisionPostSource *TownPosts_DeleteSource(CollisionPostSource *source)
{
    source->vtable = (const CollisionPostSourceVtable *) data_020e50e8;
    func_02031e84(source);
    Heap_OperatorDeleteB(source);
    return source;
}
CLEAN_AS(func_020b3ac4, TownPosts_DeleteSource)

/* func_020b3ae4: main's source's destructor: its vtable, then the base class's. */
CollisionPostSource *TownPosts_DestructSource(CollisionPostSource *source)
{
    source->vtable = (const CollisionPostSourceVtable *) data_020e50e8;
    func_02031e84(source);
    return source;
}
CLEAN_AS(func_020b3ae4, TownPosts_DestructSource)

/* func_020b3afc: main's source's constructor: the base class's, then its vtable. */
CollisionPostSource *TownPosts_ConstructSource(CollisionPostSource *source)
{
    func_02031ec0(source);
    source->vtable = (const CollisionPostSourceVtable *) data_020e50e8;
    return source;
}
CLEAN_AS(func_020b3afc, TownPosts_ConstructSource)

/* func_020b3fe4: overlay 3's source's destructor: its vtable (an address in overlay 3, written
 * whether or not the overlay is loaded), then the base class's. */
CollisionPostSource *TownPosts_DestructOverlaySource(CollisionPostSource *source)
{
    source->vtable = (const CollisionPostSourceVtable *) data_ov003_0223a248;
    func_02031e84(source);
    return source;
}
CLEAN_AS(func_020b3fe4, TownPosts_DestructOverlaySource)
