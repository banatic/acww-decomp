/* The main program's static initialisers (static_init.h). */
#include "static_init.h"

#include "a_mes_obj.h"
#include "ab_all_obj.h"
#include "actor_palettes.h"
#include "anim_slots.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/links.h"
#include "autoload_2/vector.h"
#include "backup_card.h"
#include "bg_models.h"
#include "block_02034858.h"
#include "body_anim_heaps.h"
#include "body_look.h"
#include "calendar.h"
#include "camera_view.h"
#include "caution_window.h"
#include "clean.h"
#include "cloth_slots.h"
#include "collision_area.h"
#include "collision_box.h"
#include "collision_segment.h"
#include "event_announce.h"
#include "event_calendar.h"
#include "event_entries.h"
#include "event_queue.h"
#include "face_anim_heaps.h"
#include "face_anim_slots.h"
#include "face_texture.h"
#include "field_collision.h"
#include "fishing_float.h"
#include "furniture_info.h"
#include "glasses_look.h"
#include "globe.h"
#include "head_look.h"
#include "held_item_pool.h"
#include "item_info.h"
#include "mail_text.h"
#include "obj_020dd33c.h"
#include "ov004/member_pointer.h"
#include "place_claim.h"
#include "player_options.h"
#include "room_cells.h"
#include "room_interior.h"
#include "screen_icon.h"
#include "scene_look.h"
#include "text_font.h"
#include "tile_requests.h"
#include "trivial_object.h"
#include "wireless_icon.h"

/* ---- What the initialisers share */

/* The record __register_global_object links an object into, so that its destructor runs at
 * exit (one per object, in the program's .bss). */
typedef struct StaticInitRecord {
    struct StaticInitRecord *next;
    void *destruct;
    void *object;
} StaticInitRecord;

/* A destructor or constructor as the game is handed it: always the game's function, never a
 * Clean one. */
typedef void StaticInitFn(void *object);

extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MIi_CpuClearFast(u32 data, void *dst, u32 size);

/* The null pointer to member function. */
extern const MemberPointer __ptmf_null;

/* `object` (null for an array the destructor finds itself) destructed by `destruct` at exit. */
static void static_init_register(void *object, StaticInitFn *destruct, StaticInitRecord *record)
{
    __register_global_object(object, (void *) (uintptr_t) destruct, record);
}

/* `count` member pointers copied from the program's constants, in order. */
static void static_init_copy(MemberPointer *table, const MemberPointer *const *constants, int count)
{
    for (int i = 0; i < count; i++) {
        table[i] = *constants[i];
    }
}

/* Six colours of four 5-bit components (the fourth always 31), which several source files
 * define for themselves. */
typedef struct StaticInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} StaticInitColour;

static void static_init_colour(StaticInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* Red, blue, yellow, green, cyan and grey, in that order. */
static void static_init_colours(StaticInitColour *red, StaticInitColour *blue, StaticInitColour *yellow,
                                StaticInitColour *green, StaticInitColour *cyan, StaticInitColour *grey)
{
    static_init_colour(red, 31, 20, 20, 31);
    static_init_colour(blue, 20, 20, 31, 31);
    static_init_colour(yellow, 31, 31, 20, 31);
    static_init_colour(green, 20, 31, 20, 31);
    static_init_colour(cyan, 20, 31, 31, 31);
    static_init_colour(grey, 20, 24, 24, 31);
}

static void static_init_vec(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* The destructor of a Vec3 and of other objects with nothing to destruct (TrivialObject_Destruct),
 * and of an item code (TrivialObject_DestructItemCode). */
extern void func_020012dc(void *object);
extern void func_020051b0(void *item);

/* ---- The initialisers, in address order */

extern AbAllObj data_0213ff20;
extern StaticInitRecord data_0213ff14;
extern void func_0200314c(void *obj); /* AbAllObj_Destruct */

/* __sinit_020c41cc: the "ab_all" object (ab_all_obj.h). */
void StaticInit_AbAllObj(void)
{
    AbAllObj_Init(&data_0213ff20);
    static_init_register(&data_0213ff20, func_0200314c, &data_0213ff14);
}
CLEAN_AS(__sinit_020c41cc, StaticInit_AbAllObj)

/* Every actor (actor.h). */
extern List data_0213ff78;

/* __sinit_020c41f4: the list of actors, empty. Its address. */
int StaticInit_ActorList(void)
{
    data_0213ff78.first = NULL;
    data_0213ff78.last = NULL;
    return (int) (uintptr_t) &data_0213ff78;
}
CLEAN_AS(__sinit_020c41f4, StaticInit_ActorList)

extern WirelessIcon data_0213ff98;
extern ScreenIcon data_0213ffb0;
extern StaticInitRecord data_0213ff8c;
extern StaticInitRecord data_0213ff80;
extern void func_02003da8(void *icon); /* WirelessIcon_Destruct */
extern void func_02003b50(void *icon); /* ScreenIcon_Destruct */

/* __sinit_020c4204: the wireless icon (wireless_icon.h) and the screen icon (screen_icon.h). */
void StaticInit_StatusIcons(void)
{
    WirelessIcon_Construct(&data_0213ff98);
    static_init_register(&data_0213ff98, func_02003da8, &data_0213ff8c);
    ScreenIcon_Construct(&data_0213ffb0);
    static_init_register(&data_0213ffb0, func_02003b50, &data_0213ff80);
}
CLEAN_AS(__sinit_020c4204, StaticInit_StatusIcons)

extern AMesObj data_021c1284;
extern StaticInitRecord data_021c1278;
extern void func_02011fc0(void *obj); /* AMesObj_Destruct */

/* __sinit_020c4248: the message object (a_mes_obj.h). */
void StaticInit_AMesObj(void)
{
    AMesObj_Construct(&data_021c1284);
    static_init_register(&data_021c1284, func_02011fc0, &data_021c1278);
}
CLEAN_AS(__sinit_020c4248, StaticInit_AMesObj)

/* The scene objects' side points (scene_object.c) and probe points (scene_probe.c), and their
 * records. */
extern Vec3 data_021c16b4[2];
extern Vec3 data_021c16e4[2];
extern StaticInitRecord data_021c157c[4];
/* The tables of member pointers the scene objects dispatch through: the look's kinds
 * (scene_look.c), the motions' rows of three (scene_motion_request.c), the actions' pairs
 * (scene_action.c) and the path walker's tables of eight (path_walker.c). */
#define STATIC_INIT_LOOK_FNS 6
#define STATIC_INIT_MOTION_FNS 66
#define STATIC_INIT_ACTION_FNS 10
#define STATIC_INIT_WALKER_FNS 56
extern MemberPointer data_021c1794[STATIC_INIT_LOOK_FNS];
extern MemberPointer data_021c1ad4[STATIC_INIT_MOTION_FNS];
extern MemberPointer data_021c17c4[STATIC_INIT_ACTION_FNS];
extern MemberPointer data_021c1914[STATIC_INIT_WALKER_FNS];
/* The path walker's step of one tile in each of four directions (path_walker.c). */
typedef struct StaticInitStep {
    s32 x;
    s32 z;
} StaticInitStep;
extern StaticInitStep data_021c172c[4];

extern const MemberPointer data_020d85cc, data_020d87fc, data_020d8b74, data_020d87bc, data_020d878c, data_020d879c;
extern const MemberPointer data_020d86bc, data_020d8534, data_020d8544, data_020d855c, data_020d8564, data_020d8924,
    data_020d87c4, data_020d87cc, data_020d87d4, data_020d8b94, data_020d86d4;
extern const MemberPointer data_020d8bc4, data_020d8bbc, data_020d8bb4, data_020d8bac, data_020d8ba4, data_020d8b9c,
    data_020d898c, data_020d8b8c, data_020d8b84, data_020d8b7c, data_020d89bc, data_020d8b6c;
extern const MemberPointer data_020d8b64, data_020d89d4, data_020d89dc, data_020d8b4c, data_020d8b44, data_020d8b3c,
    data_020d8b34, data_020d8b2c, data_020d8a04, data_020d8b1c, data_020d8b14, data_020d8b0c, data_020d8b04, data_020d8afc;
extern const MemberPointer data_020d8a2c, data_020d8aec, data_020d8a3c, data_020d8adc, data_020d8ad4, data_020d8acc,
    data_020d8ac4, data_020d8a9c, data_020d8aa4, data_020d8ab4, data_020d8abc, data_020d8ae4, data_020d8af4;
extern const MemberPointer data_020d86e4, data_020d86f4, data_020d86fc, data_020d8714, data_020d871c, data_020d872c,
    data_020d8734, data_020d8754, data_020d8824, data_020d876c;
extern const MemberPointer data_020d86c4, data_020d86ac, data_020d86a4, data_020d8554, data_020d8684, data_020d857c,
    data_020d8664, data_020d8594, data_020d864c, data_020d85b4, data_020d894c, data_020d85c4, data_020d85d4, data_020d8614,
    data_020d85ec, data_020d8674;
extern const MemberPointer data_020d86ec, data_020d8704, data_020d8724, data_020d873c, data_020d875c, data_020d877c,
    data_020d8794, data_020d87a4, data_020d87ec, data_020d88b4, data_020d8964, data_020d89a4, data_020d89b4, data_020d89fc,
    data_020d8a34, data_020d8aac;
extern const MemberPointer data_020d8a7c, data_020d869c, data_020d856c, data_020d8584, data_020d85a4, data_020d8634,
    data_020d85e4, data_020d85fc, data_020d870c, data_020d8744, data_020d8784, data_020d8b5c, data_020d88cc, data_020d89ac,
    data_020d89c4, data_020d8b54;
extern const MemberPointer data_020d853c, data_020d859c, data_020d85bc, data_020d867c, data_020d874c, data_020d87f4,
    data_020d880c, data_020d8a14;

/* __sinit_020c4270: the scene objects' constants: their two side points (+-0.5, 0, 1.0) and
 * two probe points (+-0.4375, 0, 0.9375), each registered with an empty destructor; the tables
 * of member pointers filled from the program's constants; and the path walker's four steps
 * (0, -1), (-1, 0), (0, 1) and (1, 0). */
void StaticInit_SceneObjectTables(void)
{
    static const MemberPointer *const look_fns[STATIC_INIT_LOOK_FNS] = {
        &data_020d85cc, &data_020d87fc, &data_020d8b74, &data_020d87bc, &data_020d878c, &data_020d879c,
    };
    static const MemberPointer *const motion_fns[STATIC_INIT_MOTION_FNS] = {
        &data_020d86bc, &data_020d8534, &__ptmf_null,   &data_020d8544, &data_020d855c, &__ptmf_null,   &data_020d8564,
        &data_020d8924, &__ptmf_null,   &data_020d87c4, &data_020d87cc, &__ptmf_null,   &data_020d87d4, &data_020d8b94,
        &__ptmf_null,   &data_020d86d4, &data_020d8bc4, &__ptmf_null,   &data_020d8bbc, &data_020d8bb4, &__ptmf_null,
        &data_020d8bac, &data_020d8ba4, &data_020d8b9c, &data_020d898c, &data_020d8b8c, &__ptmf_null,   &data_020d8b84,
        &data_020d8b7c, &__ptmf_null,   &data_020d89bc, &data_020d8b6c, &data_020d8b64, &data_020d89d4, &data_020d89dc,
        &data_020d8b4c, &data_020d8b44, &__ptmf_null,   &data_020d8b3c, &data_020d8b34, &data_020d8b2c, &data_020d8a04,
        &data_020d8b1c, &data_020d8b14, &data_020d8b0c, &data_020d8b04, &__ptmf_null,   &data_020d8afc, &data_020d8a2c,
        &__ptmf_null,   &data_020d8aec, &data_020d8a3c, &data_020d8adc, &__ptmf_null,   &data_020d8ad4, &data_020d8acc,
        &__ptmf_null,   &data_020d8ac4, &data_020d8a9c, &data_020d8aa4, &data_020d8ab4, &__ptmf_null,   &data_020d8abc,
        &data_020d8ae4, &data_020d8af4, &__ptmf_null,
    };
    static const MemberPointer *const action_fns[STATIC_INIT_ACTION_FNS] = {
        &data_020d86e4, &data_020d86f4, &data_020d86fc, &data_020d8714, &data_020d871c,
        &data_020d872c, &data_020d8734, &data_020d8754, &data_020d8824, &data_020d876c,
    };
    static const MemberPointer *const walker_fns[STATIC_INIT_WALKER_FNS] = {
        &data_020d86c4, &data_020d86ac, &data_020d86a4, &data_020d8554, &data_020d8684, &data_020d857c, &data_020d8664,
        &data_020d8594, &data_020d864c, &data_020d85b4, &data_020d894c, &data_020d85c4, &data_020d85d4, &data_020d8614,
        &data_020d85ec, &data_020d8674, &data_020d86ec, &data_020d8704, &data_020d8724, &data_020d873c, &data_020d875c,
        &data_020d877c, &data_020d8794, &data_020d87a4, &data_020d87ec, &data_020d88b4, &data_020d8964, &data_020d89a4,
        &data_020d89b4, &data_020d89fc, &data_020d8a34, &data_020d8aac, &data_020d8a7c, &data_020d869c, &data_020d856c,
        &data_020d8584, &data_020d85a4, &data_020d8634, &data_020d85e4, &data_020d85fc, &data_020d870c, &data_020d8744,
        &data_020d8784, &data_020d8b5c, &data_020d88cc, &data_020d89ac, &data_020d89c4, &data_020d8b54, &data_020d853c,
        &data_020d859c, &data_020d85bc, &data_020d867c, &data_020d874c, &data_020d87f4, &data_020d880c, &data_020d8a14,
    };

    static_init_vec(&data_021c16b4[0], 0x800, 0, 0x1000);
    static_init_register(&data_021c16b4[0], func_020012dc, &data_021c157c[0]);
    static_init_vec(&data_021c16b4[1], -0x800, 0, 0x1000);
    static_init_register(&data_021c16b4[1], func_020012dc, &data_021c157c[1]);
    static_init_vec(&data_021c16e4[0], 0x700, 0, 0xf00);
    static_init_register(&data_021c16e4[0], func_020012dc, &data_021c157c[2]);
    static_init_vec(&data_021c16e4[1], -0x700, 0, 0xf00);
    static_init_register(&data_021c16e4[1], func_020012dc, &data_021c157c[3]);

    static_init_copy(data_021c1794, look_fns, STATIC_INIT_LOOK_FNS);
    static_init_copy(data_021c1ad4, motion_fns, STATIC_INIT_MOTION_FNS);
    static_init_copy(data_021c17c4, action_fns, STATIC_INIT_ACTION_FNS);
    static_init_copy(data_021c1914, walker_fns, STATIC_INIT_WALKER_FNS);

    data_021c172c[0] = (StaticInitStep){0, -1};
    data_021c172c[1] = (StaticInitStep){-1, 0};
    data_021c172c[2] = (StaticInitStep){0, 1};
    data_021c172c[3] = (StaticInitStep){1, 0};
}
CLEAN_AS(__sinit_020c4270, StaticInit_SceneObjectTables)

/* A letter the villagers' talk writes (villager_talk.c), its record, and the letter's
 * constructor and destructor (they set its vtable word). */
extern u8 data_021c2604[];
extern StaticInitRecord data_021c1d28;
extern void func_02066694(void *letter);
extern void func_02066688(void *letter);

/* __sinit_020c4a80: the villagers' talk's letter. */
void StaticInit_TalkLetter(void)
{
    func_02066694(data_021c2604);
    static_init_register(data_021c2604, func_02066688, &data_021c1d28);
}
CLEAN_AS(__sinit_020c4a80, StaticInit_TalkLetter)

/* The speed scale of the special scene objects' animation players (special_scene_object.c),
 * from the standard one. */
extern s32 data_021c30ac;
extern s32 data_020c8120;

/* __sinit_020c4aa8: the special scene objects' animation speed, the standard one less 0x8000
 * (0.5 in 16.16). */
void StaticInit_SpecialSceneAnimSpeed(void)
{
    data_021c30ac = data_020c8120 - 0x8000;
}
CLEAN_AS(__sinit_020c4aa8, StaticInit_SpecialSceneAnimSpeed)

extern CollisionPoint data_021c30b8;
extern StaticInitRecord data_021c30c0;
extern void func_0202f2f0(void *point); /* CollisionPoint_Destruct */

/* __sinit_020c4ac4: the collision code's point (0, 0) (collision_segment.h). */
void StaticInit_CollisionOrigin(void)
{
    CollisionPoint_Set(&data_021c30b8, 0, 0);
    static_init_register(&data_021c30b8, func_0202f2f0, &data_021c30c0);
}
CLEAN_AS(__sinit_020c4ac4, StaticInit_CollisionOrigin)

/* 16.0 times 0.5, and the up vector and unit scale of the collision code (collision_box.c,
 * collision_query.c). */
extern fx32 data_021c30d0;
extern Vec3 data_021c317c;
extern Vec3 data_021c31a0;
extern StaticInitRecord data_021c3170;
extern StaticInitRecord data_021c3194;
/* The collision world (field_collision.h), its record, and the constructor and destructor of
 * its block maps and its own destructor. */
extern CollisionWorld data_021c31e8;
extern StaticInitRecord data_021c31b8;
extern void func_02034824(void *map);   /* CollisionBlockMap_Construct */
extern void func_02034804(void *map);   /* CollisionBlockMap_Destroy */
extern void func_02034790(void *world); /* CollisionWorld_Destroy */

static_assert(sizeof(FieldBlockMap) == 0x138, "FieldBlockMap");

/* __sinit_020c4af0: the collision code's constants and its world: the block maps (an array
 * constructed by __cxa_vec_ctor), the walls, floors and posts, the box and area lists, the
 * cell grid and the extra posts, then the world registered whole. */
void StaticInit_CollisionWorld(void)
{
    data_021c30d0 = FX_MulFunc(0x20000, 0x800);
    static_init_vec(&data_021c317c, 0, 0x1000, 0);
    static_init_register(&data_021c317c, func_020012dc, &data_021c3170);
    static_init_vec(&data_021c31a0, 0x1000, 0x1000, 0x1000);
    static_init_register(&data_021c31a0, func_020012dc, &data_021c3194);

    CollisionWorld *world = &data_021c31e8;
    __cxa_vec_ctor(world->maps, COLLISION_BLOCK_MAPS, sizeof(FieldBlockMap), func_02034824, func_02034804);
    CollisionWalls_Construct(&world->walls);
    CollisionFloors_Construct(&world->floors);
    CollisionPosts_Construct(&world->posts);
    CollisionBox_ListConstruct(&world->unk_1a90);
    CollisionArea_ListConstruct(&world->unk_1a91);
    CollisionCellGrid_Construct(&world->grid);
    CollisionExtraPosts_Clear(&world->extra_posts);
    static_init_register(world, func_02034790, &data_021c31b8);
}
CLEAN_AS(__sinit_020c4af0, StaticInit_CollisionWorld)

extern StaticInitColour data_021c513c, data_021c5134, data_021c5138, data_021c5150, data_021c514c, data_021c5148;
extern Block021c5160 data_021c5160;
extern StaticInitRecord data_021c5154;
extern void func_020348c4(void *block); /* Block021c5160_Destroy */

/* __sinit_020c4bdc: the six colours of its source file and the object of block_02034858.h. */
void StaticInit_Block021c5160(void)
{
    static_init_colours(&data_021c513c, &data_021c5134, &data_021c5138, &data_021c5150, &data_021c514c, &data_021c5148);
    Block021c5160_Construct(&data_021c5160);
    static_init_register(&data_021c5160, func_020348c4, &data_021c5154);
}
CLEAN_AS(__sinit_020c4bdc, StaticInit_Block021c5160)

/* An item code (room_interior.c) and the codes of the scenes' wallpapers and carpets, with
 * their records. */
extern u16 data_021c5174;
extern u16 data_021c519c[ROOM_INTERIOR_SCENES];
extern u16 data_021c5204[ROOM_INTERIOR_SCENES];
extern StaticInitRecord data_021c5178;
extern StaticInitRecord data_021c5184;
extern StaticInitRecord data_021c5190;
extern void func_02034ce0(void *code); /* RoomInterior_ConstructCode */
extern void func_02034cc0(void *none); /* RoomInterior_DestroySceneWallpapers */
extern void func_02034ca0(void *none); /* RoomInterior_DestroySceneCarpets */

#define STATIC_INIT_NO_ITEM 0xfff1

/* __sinit_020c4c5c: the room interiors' item code (none) and the scenes' two arrays of codes,
 * each constructed by __cxa_vec_ctor and registered as a whole (a null object: the destructor
 * knows its array). */
void StaticInit_RoomInterior(void)
{
    data_021c5174 = STATIC_INIT_NO_ITEM;
    static_init_register(&data_021c5174, func_020051b0, &data_021c5178);
    __cxa_vec_ctor(data_021c519c, ROOM_INTERIOR_SCENES, sizeof(u16), func_02034ce0, func_020051b0);
    static_init_register(NULL, func_02034cc0, &data_021c5184);
    __cxa_vec_ctor(data_021c5204, ROOM_INTERIOR_SCENES, sizeof(u16), func_02034ce0, func_020051b0);
    static_init_register(NULL, func_02034ca0, &data_021c5190);
}
CLEAN_AS(__sinit_020c4c5c, StaticInit_RoomInterior)

extern BgModels data_021c52c0;
extern StaticInitRecord data_021c52b4;
extern void func_02037ae4(void *models); /* BgModels_Destruct */

/* __sinit_020c4cd4: the background models (bg_models.h). */
void StaticInit_BgModels(void)
{
    BgModels_Construct(&data_021c52c0);
    static_init_register(&data_021c52c0, func_02037ae4, &data_021c52b4);
}
CLEAN_AS(__sinit_020c4cd4, StaticInit_BgModels)

extern CautionWindow data_021c5c4c;
extern u8 data_021c5a24[];
extern CautionWindowLabel data_021c59d0;
extern u8 data_021c5b38[];
extern StaticInitRecord data_021c5940, data_021c594c, data_021c5958, data_021c5964;
extern void func_02038a90(void *window);  /* CautionWindow_Destruct */
extern void func_02038d18(void *message); /* CautionWindowMessage_Destruct */
extern void func_02038cb4(void *label);   /* CautionWindowUnit_Destruct */

/* __sinit_020c4cfc: the caution window (caution_window.h), its two messages and its label. */
void StaticInit_CautionWindow(void)
{
    CautionWindow_Construct(&data_021c5c4c);
    static_init_register(&data_021c5c4c, func_02038a90, &data_021c5940);
    CautionWindowMessage_Construct((int) (uintptr_t) data_021c5a24);
    static_init_register(data_021c5a24, func_02038d18, &data_021c594c);
    CautionWindowUnit_Construct(&data_021c59d0);
    static_init_register(&data_021c59d0, func_02038cb4, &data_021c5958);
    CautionWindowMessage_Construct((int) (uintptr_t) data_021c5b38);
    static_init_register(data_021c5b38, func_02038d18, &data_021c5964);
}
CLEAN_AS(__sinit_020c4cfc, StaticInit_CautionWindow)

extern StaticInitColour data_021c6794, data_021c67a8, data_021c6798, data_021c6790, data_021c678c, data_021c67a0;
/* The camera's eye, point looked at, goal view and a point (camera_view.c, camera_control.c). */
extern Vec3 data_021c67b8;
extern Vec3 data_021c67d0;
extern u8 data_021c6800[];
extern Vec3 data_021c67f4;
extern StaticInitRecord data_021c67ac, data_021c67c4, data_021c67dc, data_021c67e8;
extern void func_0203cb30(void *view); /* CarpetTexture_Destruct: an empty destructor */
/* The camera modes' start and frame functions (camera_view.c). */
#define STATIC_INIT_CAMERA_FNS (CAMERA_MODES * 2)
extern MemberPointer data_021c6820[STATIC_INIT_CAMERA_FNS];
extern const MemberPointer data_020da744, data_020da82c, data_020da824, data_020da81c, data_020da814, data_020da80c,
    data_020da804, data_020da7fc, data_020da774, data_020da7ec, data_020da7e4, data_020da7c4, data_020da7cc, data_020da7f4,
    data_020da834, data_020da844, data_020da854, data_020da7ac, data_020da7a4, data_020da79c, data_020da794, data_020da864,
    data_020da734, data_020da84c, data_020da73c, data_020da76c, data_020da754, data_020da764, data_020da784, data_020da7bc,
    data_020da7d4, data_020da83c, data_020da85c, data_020da72c, data_020da724, data_020da78c, data_020da77c, data_020da75c,
    data_020da7b4, data_020da7dc, data_020da86c, data_020da71c;

/* __sinit_020c4d74: the six colours of its source file, the camera's vectors and view (with
 * empty destructors) and its modes' member functions. */
void StaticInit_CameraView(void)
{
    static const MemberPointer *const camera_fns[STATIC_INIT_CAMERA_FNS] = {
        &data_020da744, &data_020da82c, &data_020da824, &data_020da81c, &data_020da814, &data_020da80c, &data_020da804,
        &data_020da7fc, &data_020da774, &data_020da7ec, &data_020da7e4, &data_020da7c4, &data_020da7cc, &data_020da7f4,
        &data_020da834, &data_020da844, &data_020da854, &data_020da7ac, &data_020da7a4, &data_020da79c, &data_020da794,
        &data_020da864, &data_020da734, &data_020da84c, &data_020da73c, &data_020da76c, &data_020da754, &data_020da764,
        &data_020da784, &data_020da7bc, &data_020da7d4, &data_020da83c, &data_020da85c, &data_020da72c, &data_020da724,
        &data_020da78c, &data_020da77c, &data_020da75c, &data_020da7b4, &data_020da7dc, &data_020da86c, &data_020da71c,
    };
    static_init_colours(&data_021c6794, &data_021c67a8, &data_021c6798, &data_021c6790, &data_021c678c, &data_021c67a0);
    static_init_register(&data_021c67b8, func_020012dc, &data_021c67ac);
    static_init_register(&data_021c67d0, func_020012dc, &data_021c67c4);
    static_init_register(data_021c6800, func_0203cb30, &data_021c67dc);
    static_init_register(&data_021c67f4, func_020012dc, &data_021c67e8);
    static_init_copy(data_021c6820, camera_fns, STATIC_INIT_CAMERA_FNS);
}
CLEAN_AS(__sinit_020c4d74, StaticInit_CameraView)

extern PlayerOptions data_021c6998;
extern StaticInitRecord data_021c699c;
extern void func_0203d2b4(void *options); /* PlayerOptions_Empty2B4 */

/* __sinit_020c5088: the player's options (player_options.h), whose constructor and destructor
 * do nothing. */
void StaticInit_PlayerOptions(void)
{
    PlayerOptions_Empty2C4((int) (uintptr_t) &data_021c6998);
    static_init_register(&data_021c6998, func_0203d2b4, &data_021c699c);
}
CLEAN_AS(__sinit_020c5088, StaticInit_PlayerOptions)

extern MailText data_021c69b4;
extern StaticInitRecord data_021c69a8;
extern void func_0203d698(void *writer); /* MailText_Destruct */

/* __sinit_020c50b0: the mail's text writer (mail_text.h). */
void StaticInit_MailText(void)
{
    MailText_Construct(&data_021c69b4);
    static_init_register(&data_021c69b4, func_0203d698, &data_021c69a8);
}
CLEAN_AS(__sinit_020c50b0, StaticInit_MailText)

/* The events waiting (event_queue.c) and the registered scene objects (scene_object_base.c). */
extern List data_021c72c4;
extern List data_021c72cc;

/* __sinit_020c50d8: the list of events waiting, empty. Its address. */
int StaticInit_EventQueueList(void)
{
    data_021c72c4.first = NULL;
    data_021c72c4.last = NULL;
    return (int) (uintptr_t) &data_021c72c4;
}
CLEAN_AS(__sinit_020c50d8, StaticInit_EventQueueList)

/* __sinit_020c50e8: the list of registered scene objects, empty. Its address. */
int StaticInit_SceneObjectBaseList(void)
{
    data_021c72cc.first = NULL;
    data_021c72cc.last = NULL;
    return (int) (uintptr_t) &data_021c72cc;
}
CLEAN_AS(__sinit_020c50e8, StaticInit_SceneObjectBaseList)

extern EventQueueEntry data_021c72e8[EVENT_ENTRIES];
extern void func_0203f598(void *entry); /* EventEntries_Construct */

static_assert(sizeof(EventQueueEntry) == 28, "EventQueueEntry");

/* __sinit_020c50f8: the event entries (event_entries.h), constructed by __cxa_vec_ctor; they
 * have no destructor. */
void StaticInit_EventEntries(void)
{
    __cxa_vec_ctor(data_021c72e8, EVENT_ENTRIES, sizeof(EventQueueEntry), func_0203f598, NULL);
}
CLEAN_AS(__sinit_020c50f8, StaticInit_EventEntries)

/* The globe's depth (globe.c), from the world's depth of an acre, and its view. */
extern fx32 data_021c748c;
extern const fx32 data_020ca0e8;
extern GlobeView data_021c749c;
extern StaticInitRecord data_021c7490;
extern void func_0203f724(void *view); /* Globe_DestructView */

/* __sinit_020c511c: the globe's depth and view (globe.h). */
void StaticInit_Globe(void)
{
    data_021c748c = data_020ca0e8;
    Globe_ConstructView(&data_021c749c);
    static_init_register(&data_021c749c, func_0203f724, &data_021c7490);
}
CLEAN_AS(__sinit_020c511c, StaticInit_Globe)

/* The date of today's list of events and a second date (event_calendar.c). */
extern Date data_021c74d0;
extern Date data_021c7528;
extern StaticInitRecord data_021c74b8, data_021c74c4;
extern void func_02040868(void *date); /* EventCalendar_DateDestruct */

/* __sinit_020c5154: the event calendar's two dates (event_calendar.h). */
void StaticInit_EventCalendar(void)
{
    EventCalendar_DateConstruct(&data_021c74d0);
    static_init_register(&data_021c74d0, func_02040868, &data_021c74b8);
    EventCalendar_DateConstruct(&data_021c7528);
    static_init_register(&data_021c7528, func_02040868, &data_021c74c4);
}
CLEAN_AS(__sinit_020c5154, StaticInit_EventCalendar)

extern EventAnnounceState data_021c75a0;
extern StaticInitRecord data_021c7594;
extern void func_020413f4(void *state); /* EventAnnounce_Nothing13f4 */

/* __sinit_020c5194: the event announcement's state (event_announce.h): its step, message and
 * file cleared. */
void StaticInit_EventAnnounce(void)
{
    data_021c75a0.step = 0;
    data_021c75a0.message = 0;
    data_021c75a0.ending = 0;
    static_init_register(&data_021c75a0, func_020413f4, &data_021c7594);
}
CLEAN_AS(__sinit_020c5194, StaticInit_EventAnnounce)

/* The object at data_021c79c4 (block_02042200.c reads its first 0x34 bytes): three words at
 * 0x18 (cleared, then set to -1 by func_0204b160), four words, and sixteen entries of 0x20
 * bytes. */
typedef struct StaticInitEntry79c4 {
    u8 unk_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 unk_18[8];
} StaticInitEntry79c4;
typedef struct StaticInitObject79c4 {
    u8 unk_00[0x18];
    u32 unk_18[3];                   /* 0x18 */
    u8 unk_24[0x10];                 /* 0x24 */
    s32 unk_34[4];                   /* 0x34 */
    StaticInitEntry79c4 entries[16]; /* 0x44 */
} StaticInitObject79c4;
static_assert(offsetof(StaticInitObject79c4, entries) == 0x44 && sizeof(StaticInitEntry79c4) == 0x20, "StaticInitObject79c4");

/* The town's object (town_day.h) and its code-0x6d tiles, the object at data_021c79c4, and the
 * tile requests (tile_requests.h). */
extern u8 data_021c779c[];
extern s32 data_021c77c0[];
extern StaticInitObject79c4 data_021c79c4;
extern TileRequests data_021c7c48;
extern StaticInitRecord data_021c777c, data_021c7770;
extern void func_0204b184(void *town);   /* an empty destructor */
extern void func_0204b160(void *words);  /* clears three words and sets them to -1 */
extern void func_0204b170(void *object); /* the object's destructor */
extern void func_020012e0(void *pair);   /* WordPair_Construct: both words -1 */

#define STATIC_INIT_TOWN_TILES 0x18
#define STATIC_INIT_TILE_REQUESTS 3

/* __sinit_020c51b8: the town's object registered (it has no constructor); the object at
 * data_021c79c4 built (its words at 0x18, the four words and its entries' two words cleared)
 * and registered; the tile requests' tiles cleared; and the town's 0x18 code-0x6d tiles set to
 * (-1, -1) by __cxa_vec_ctor. */
void StaticInit_TownObjects(void)
{
    static_init_register(data_021c779c, func_0204b184, &data_021c777c);

    StaticInitObject79c4 *object = &data_021c79c4;
    func_0204b160(object->unk_18);
    for (int i = 0; i < 4; i++) {
        object->unk_34[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        object->entries[i].unk_10 = 0;
        object->entries[i].unk_14 = 0;
    }
    static_init_register(object, func_0204b170, &data_021c7770);

    for (int i = 0; i < STATIC_INIT_TILE_REQUESTS; i++) {
        data_021c7c48.requests[i].tile.x = 0;
        data_021c7c48.requests[i].tile.z = 0;
    }
    __cxa_vec_ctor(data_021c77c0, STATIC_INIT_TOWN_TILES, 2 * sizeof(s32), func_020012e0, NULL);
}
CLEAN_AS(__sinit_020c51b8, StaticInit_TownObjects)

/* __sinit_020c5250: nothing. */
void StaticInit_Nothing5250(void) {}
CLEAN_AS(__sinit_020c5250, StaticInit_Nothing5250)

extern BackupCard data_021c8188;

/* __sinit_020c5254: the save memory's record (backup_card.h): no size, no lock held. Its lock
 * (BACKUP_CARD_NO_LOCK). */
int StaticInit_BackupCard(void)
{
    data_021c8188.size = 0;
    data_021c8188.lock = BACKUP_CARD_NO_LOCK;
    return BACKUP_CARD_NO_LOCK;
}
CLEAN_AS(__sinit_020c5254, StaticInit_BackupCard)

extern TextFont data_021c8230, data_021c828c, data_021c82e8, data_021c81d4;
extern StaticInitRecord data_021c8198, data_021c81a4, data_021c81b0, data_021c81c8;
extern void func_02051810(void *font); /* TextFont_Destruct */

/* __sinit_020c5268: the four fonts (text_font.h). */
void StaticInit_TextFonts(void)
{
    TextFont_Construct(&data_021c8230);
    static_init_register(&data_021c8230, func_02051810, &data_021c8198);
    TextFont_Construct(&data_021c828c);
    static_init_register(&data_021c828c, func_02051810, &data_021c81a4);
    TextFont_Construct(&data_021c82e8);
    static_init_register(&data_021c82e8, func_02051810, &data_021c81b0);
    TextFont_Construct(&data_021c81d4);
    static_init_register(&data_021c81d4, func_02051810, &data_021c81c8);
}
CLEAN_AS(__sinit_020c5268, StaticInit_TextFonts)

/* The rooms' cells: scenes 17-24, Nook's scenes 26-31 and scene 10 (room_cells.c), and the
 * place claims (place_claim.h). */
#define STATIC_INIT_CELLS_17_TO_24 8
#define STATIC_INIT_CELLS_NOOK 6
extern RoomCells data_021c89fc[STATIC_INIT_CELLS_17_TO_24];
extern RoomCells data_021c884c[STATIC_INIT_CELLS_NOOK];
extern RoomCells data_021c87b4;
extern PlaceClaim data_021c87fc[PLACE_CLAIM_SLOTS];
extern StaticInitRecord data_021c8780, data_021c8798, data_021c878c, data_021c8774;
extern void func_020530d4(void *cells);  /* RoomCells_Construct */
extern void func_020530b0(void *cells);  /* RoomCells_Destruct */
extern void func_020534cc(void *none);   /* RoomCells_Destruct17To24Records */
extern void func_020534ac(void *none);   /* RoomCells_DestructNookRecords */
extern void func_0205349c(void *claim);  /* PlaceClaim_Construct */
extern void func_02053498(void *claim);  /* PlaceClaim_Destruct */
extern void func_0205347c(void *claims); /* PlaceClaim_DestructAll */

/* Thirteen pairs of 16-bit values (x, z offsets of one tile and none), next to each other. */
typedef struct StaticInitPair16 {
    s16 x;
    s16 z;
} StaticInitPair16;
extern StaticInitPair16 data_021c874c, data_021c8754, data_021c8758, data_021c875c, data_021c8760, data_021c876c,
    data_021c8770, data_021c8764, data_021c8768, data_021c87a4, data_021c87a8, data_021c87ac, data_021c87b0;

static_assert(sizeof(RoomCells) == 72 && sizeof(PlaceClaim) == 20, "RoomCells, PlaceClaim");
static_assert(PLACE_CLAIM_SLOTS == 4, "PLACE_CLAIM_SLOTS");

static void static_init_pair(StaticInitPair16 *pair, s16 x, s16 z)
{
    pair->x = x;
    pair->z = z;
}

/* __sinit_020c52d8: the rooms' cells (two arrays constructed by __cxa_vec_ctor and registered
 * as a whole, and scene 10's), the place claims, and the thirteen pairs. */
void StaticInit_RoomCells(void)
{
    __cxa_vec_ctor(data_021c89fc, STATIC_INIT_CELLS_17_TO_24, sizeof(RoomCells), func_020530d4, func_020530b0);
    static_init_register(NULL, func_020534cc, &data_021c8780);
    __cxa_vec_ctor(data_021c884c, STATIC_INIT_CELLS_NOOK, sizeof(RoomCells), func_020530d4, func_020530b0);
    static_init_register(NULL, func_020534ac, &data_021c8798);
    RoomCells_Construct(&data_021c87b4);
    static_init_register(&data_021c87b4, func_020530b0, &data_021c878c);
    __cxa_vec_ctor(data_021c87fc, PLACE_CLAIM_SLOTS, sizeof(PlaceClaim), func_0205349c, func_02053498);
    static_init_register(data_021c87fc, func_0205347c, &data_021c8774);

    static_init_pair(&data_021c874c, 0, 0);
    static_init_pair(&data_021c8754, 0, 0);
    static_init_pair(&data_021c8758, 1, 0);
    static_init_pair(&data_021c875c, 0, 0);
    static_init_pair(&data_021c8760, 0, -1);
    static_init_pair(&data_021c876c, 0, 0);
    static_init_pair(&data_021c8770, -1, 0);
    static_init_pair(&data_021c8764, 0, 0);
    static_init_pair(&data_021c8768, 0, 1);
    static_init_pair(&data_021c87a4, 0, 0);
    static_init_pair(&data_021c87a8, 1, 0);
    static_init_pair(&data_021c87ac, 0, 1);
    static_init_pair(&data_021c87b0, 1, 1);
}
CLEAN_AS(__sinit_020c52d8, StaticInit_RoomCells)

extern FurnitureRecordFiles data_021c8c48;
extern StaticInitRecord data_021c8c3c;
extern void func_02053ed8(void *files); /* FurnitureFiles_Destruct */

/* __sinit_020c5404: the furniture's record files (furniture_info.h). */
void StaticInit_FurnitureFiles(void)
{
    FurnitureFiles_Construct(&data_021c8c48);
    static_init_register(&data_021c8c48, func_02053ed8, &data_021c8c3c);
}
CLEAN_AS(__sinit_020c5404, StaticInit_FurnitureFiles)

/* __sinit_020c542c: nothing. */
void StaticInit_Nothing542c(void) {}
CLEAN_AS(__sinit_020c542c, StaticInit_Nothing542c)

/* The modes' handlers of the object of obj_020dd33c.h, by mode, kind and handler. */
#define STATIC_INIT_MODE_FNS (OBJ_020DD33C_MODE_COUNT * 4)
extern MemberPointer data_021c9460[STATIC_INIT_MODE_FNS];
extern const MemberPointer data_020dd1e4, data_020dd28c, data_020dd224, data_020dd26c, data_020dd21c, data_020dd30c,
    data_020dd1fc, data_020dd204, data_020dd20c, data_020dd1cc, data_020dd214, data_020dd22c, data_020dd234, data_020dd23c,
    data_020dd244, data_020dd24c, data_020dd254, data_020dd1c4, data_020dd25c, data_020dd314, data_020dd264, data_020dd304,
    data_020dd274, data_020dd2f4, data_020dd27c, data_020dd2e4, data_020dd294, data_020dd2d4, data_020dd2cc, data_020dd2ac,
    data_020dd2b4, data_020dd2c4, data_020dd2dc;
/* Its tables of steps (obj_020dd33c_modes.c): the bytes they are made from, the gaps between
 * them, three points with empty destructors, and the speeds made from the gaps. */
extern const u8 data_020cbb00[4];
extern const u8 data_020cbaf0[3];
extern const u8 data_020cbaf4[3];
extern const u8 data_020cbaec[2];
extern u8 data_021c9348[3];
extern u8 data_021c9344[2];
extern u8 data_021c9340[2];
extern u8 data_021c933c[1];
extern Vec3 data_021c9390, data_021c93e4, data_021c939c;
extern StaticInitRecord data_021c9384, data_021c93d8, data_021c9378;
extern const fx32 data_020cbb34[4];
extern fx32 data_021c9400[4];

/* |a / b|. */
static fx32 static_init_abs_quotient(fx32 a, int b)
{
    fx32 v = a / b;
    return v < 0 ? -v : v;
}

/* __sinit_020c5430: the modes' handlers of the object of obj_020dd33c.h; the gaps between the
 * bytes of four tables (each truncated to a byte), three points, and the speeds 1 to 3 of
 * data_021c9400: data_020cbb34's value over the gap of data_021c9348, made positive.
 * REQUIRES: the gaps of data_020cbb00 are not 0 (they are 9, 2 and 2). */
void StaticInit_Obj020dd33cModes(void)
{
    static const MemberPointer *const mode_fns[STATIC_INIT_MODE_FNS] = {
        &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020dd1e4, &data_020dd28c, &data_020dd224,
        &data_020dd26c, &data_020dd21c, &__ptmf_null,   &data_020dd30c, &data_020dd1fc, &data_020dd204, &data_020dd20c,
        &data_020dd1cc, &data_020dd214, &data_020dd22c, &data_020dd234, &data_020dd23c, &data_020dd244, &data_020dd24c,
        &data_020dd254, &data_020dd1c4, &data_020dd25c, &data_020dd314, &data_020dd264, &__ptmf_null,   &__ptmf_null,
        &data_020dd304, &data_020dd274, &data_020dd2f4, &data_020dd27c, &data_020dd2e4, &data_020dd294, &__ptmf_null,
        &__ptmf_null,   &__ptmf_null,   &__ptmf_null,   &data_020dd2d4, &data_020dd2cc, &data_020dd2ac, &data_020dd2b4,
        &__ptmf_null,   &__ptmf_null,   &data_020dd2c4, &data_020dd2dc, &__ptmf_null,   &__ptmf_null,
    };
    static_init_copy(data_021c9460, mode_fns, STATIC_INIT_MODE_FNS);

    for (int i = 0; i < 3; i++) {
        data_021c9348[i] = (u8) (data_020cbb00[i + 1] - data_020cbb00[i]);
    }
    static_init_vec(&data_021c9390, -0x400, -0x300, 0x1100);
    static_init_register(&data_021c9390, func_020012dc, &data_021c9384);
    for (int i = 0; i < 2; i++) {
        data_021c9344[i] = (u8) (data_020cbaf0[i + 1] - data_020cbaf0[i]);
    }
    for (int i = 0; i < 2; i++) {
        data_021c9340[i] = (u8) (data_020cbaf4[i + 1] - data_020cbaf4[i]);
    }
    data_021c933c[0] = (u8) (data_020cbaec[1] - data_020cbaec[0]);
    static_init_vec(&data_021c93e4, 0, 0, 0xd00);
    static_init_register(&data_021c93e4, func_020012dc, &data_021c93d8);
    for (int i = 0; i < 3; i++) {
        data_021c9400[i + 1] = static_init_abs_quotient(data_020cbb34[i + 1], data_021c9348[i]);
    }
    static_init_vec(&data_021c939c, 0, 0, 0x1300);
    static_init_register(&data_021c939c, func_020012dc, &data_021c9378);
}
CLEAN_AS(__sinit_020c5430, StaticInit_Obj020dd33cModes)

/* The room scores' state (room_score.c): each group's best score, the special items' marks,
 * and each group's categories followed by the word of all the categories. */
#define STATIC_INIT_SCORE_GROUPS 0x4a
#define STATIC_INIT_SCORE_MARK_BYTES 0xe0
extern u32 data_021c9854[STATIC_INIT_SCORE_GROUPS];
extern u32 data_021c9774[STATIC_INIT_SCORE_MARK_BYTES / 4];
extern u32 data_021c997c[STATIC_INIT_SCORE_GROUPS];
extern u32 data_021c9a7c[];
extern StaticInitRecord data_021c968c, data_021c96c8, data_021c96a4;
extern void func_0205bfcc(void *best);       /* RoomScoreState_DestructBest */
extern void func_0205bfc8(void *marks);      /* RoomScoreState_DestructMarks */
extern void func_0205bfc4(void *categories); /* RoomScoreState_DestructCategories */

/* __sinit_020c5788: the room scores' state, cleared: the best scores by MI_CpuFill8, the marks
 * by MIi_CpuClearFast, the categories one word at a time and the word of all the categories
 * (word 10 of data_021c9a7c). */
void StaticInit_RoomScore(void)
{
    MI_CpuFill8(data_021c9854, 0, sizeof(data_021c9854));
    static_init_register(data_021c9854, func_0205bfcc, &data_021c968c);
    MIi_CpuClearFast(0, data_021c9774, STATIC_INIT_SCORE_MARK_BYTES);
    static_init_register(data_021c9774, func_0205bfc8, &data_021c96c8);
    for (int i = 0; i < STATIC_INIT_SCORE_GROUPS; i++) {
        data_021c997c[i] = 0;
    }
    data_021c9a7c[10] = 0;
    static_init_register(data_021c997c, func_0205bfc4, &data_021c96a4);
}
CLEAN_AS(__sinit_020c5788, StaticInit_RoomScore)

extern AnimSlots data_021c9b58;
extern StaticInitRecord data_021c9b38;
extern void func_0205ce94(void *slots); /* AnimSlots_Destruct */

/* __sinit_020c5808: the animation slots (anim_slots.h). */
void StaticInit_AnimSlots(void)
{
    AnimSlots_Construct(&data_021c9b58);
    static_init_register(&data_021c9b58, func_0205ce94, &data_021c9b38);
}
CLEAN_AS(__sinit_020c5808, StaticInit_AnimSlots)

extern BodyLookTable data_021c9c2c;
extern StaticInitRecord data_021c9c20;
extern void func_0205d19c(void *table); /* BodyLook_DestructTable */

/* __sinit_020c5830: the bodies' looks (body_look.h). */
void StaticInit_BodyLook(void)
{
    BodyLook_ConstructTable(&data_021c9c2c);
    static_init_register(&data_021c9c2c, func_0205d19c, &data_021c9c20);
}
CLEAN_AS(__sinit_020c5830, StaticInit_BodyLook)

extern ClothSlots data_021c9d1c;
extern StaticInitRecord data_021c9d10;
extern void func_0205d690(void *slots); /* ClothSlots_Destruct */

/* __sinit_020c5858: the cloth slots (cloth_slots.h). */
void StaticInit_ClothSlots(void)
{
    ClothSlots_Construct(&data_021c9d1c);
    static_init_register(&data_021c9d1c, func_0205d690, &data_021c9d10);
}
CLEAN_AS(__sinit_020c5858, StaticInit_ClothSlots)

extern FaceAnimSlots data_021c9d7c;
extern StaticInitRecord data_021c9d5c;
extern void func_0205da74(void *slots); /* FaceAnimSlots_Destruct */

/* __sinit_020c5880: the face animation slots (face_anim_slots.h). */
void StaticInit_FaceAnimSlots(void)
{
    FaceAnimSlots_Construct(&data_021c9d7c);
    static_init_register(&data_021c9d7c, func_0205da74, &data_021c9d5c);
}
CLEAN_AS(__sinit_020c5880, StaticInit_FaceAnimSlots)

extern u8 data_021c9df4[];
extern StaticInitRecord data_021c9de8;
extern void func_0205dc34(void *heaps); /* FaceAnimHeaps_Destruct */

/* __sinit_020c58a8: the face animation heaps (face_anim_heaps.h). */
void StaticInit_FaceAnimHeaps(void)
{
    FaceAnimHeaps_Construct(data_021c9df4);
    static_init_register(data_021c9df4, func_0205dc34, &data_021c9de8);
}
CLEAN_AS(__sinit_020c58a8, StaticInit_FaceAnimHeaps)

extern u8 data_021c9e24[];
extern StaticInitRecord data_021c9e18;
extern void func_0205dd50(void *textures); /* FaceTexture_Destruct */

/* __sinit_020c58d0: the face texture buffers (face_texture.h). */
void StaticInit_FaceTexture(void)
{
    FaceTexture_Construct(data_021c9e24);
    static_init_register(data_021c9e24, func_0205dd50, &data_021c9e18);
}
CLEAN_AS(__sinit_020c58d0, StaticInit_FaceTexture)

extern GlassesLookTable data_021c9e68;
extern StaticInitRecord data_021c9e48;
extern void func_0205e018(void *table); /* GlassesLook_DestructTable */

/* __sinit_020c58f8: the glasses' looks (glasses_look.h). */
void StaticInit_GlassesLook(void)
{
    GlassesLook_ConstructTable(&data_021c9e68);
    static_init_register(&data_021c9e68, func_0205e018, &data_021c9e48);
}
CLEAN_AS(__sinit_020c58f8, StaticInit_GlassesLook)

extern HeadLookTable data_021c9f5c;
extern StaticInitRecord data_021c9f3c;
extern void func_0205e65c(void *table); /* HeadLook_DestructTable */

/* __sinit_020c5920: the heads' looks (head_look.h). */
void StaticInit_HeadLook(void)
{
    HeadLook_ConstructTable(&data_021c9f5c);
    static_init_register(&data_021c9f5c, func_0205e65c, &data_021c9f3c);
}
CLEAN_AS(__sinit_020c5920, StaticInit_HeadLook)

extern HeldItemPool data_021ca16c;
extern StaticInitRecord data_021ca114;
extern void func_0205f524(void *pool); /* HeldItemPool_Destruct */

/* __sinit_020c5948: the held items' pool (held_item_pool.h). */
void StaticInit_HeldItemPool(void)
{
    HeldItemPool_Construct(&data_021ca16c);
    static_init_register(&data_021ca16c, func_0205f524, &data_021ca114);
}
CLEAN_AS(__sinit_020c5948, StaticInit_HeldItemPool)

extern u8 data_021cacd0[];
extern StaticInitRecord data_021cacc4;
extern void func_0205f7f8(void *heaps); /* BodyAnimHeaps_Destruct */

/* __sinit_020c5970: the body animation heaps (body_anim_heaps.h). */
void StaticInit_BodyAnimHeaps(void)
{
    BodyAnimHeaps_Construct(data_021cacd0);
    static_init_register(data_021cacd0, func_0205f7f8, &data_021cacc4);
}
CLEAN_AS(__sinit_020c5970, StaticInit_BodyAnimHeaps)

extern u8 data_021cacec[];
extern StaticInitRecord data_021cace0;
extern void func_0205f950(void *table); /* ActorPalettes_Destruct */

/* __sinit_020c5998: the actors' palette buffers (actor_palettes.h). */
void StaticInit_ActorPalettes(void)
{
    ActorPalettes_Construct(data_021cacec);
    static_init_register(data_021cacec, func_0205f950, &data_021cace0);
}
CLEAN_AS(__sinit_020c5998, StaticInit_ActorPalettes)

extern FishingFloatPool data_021cad80;
extern StaticInitRecord data_021cad10;
extern void func_02060844(void *pool); /* FishingFloatPool_Destruct */
/* The fishing float's states' step functions (fishing_float.c). */
extern MemberPointer data_021cad30[FISHING_FLOAT_STATES];
extern const MemberPointer data_020dd80c, data_020dd804, data_020dd7fc, data_020dd7f4, data_020dd7e4, data_020dd7ec,
    data_020dd7dc, data_020dd7d4, data_020dd7cc, data_020dd7c4;

/* __sinit_020c59c0: the fishing floats' pool (fishing_float.h) and their states' step
 * functions. */
void StaticInit_FishingFloat(void)
{
    static const MemberPointer *const float_fns[FISHING_FLOAT_STATES] = {
        &data_020dd80c, &data_020dd804, &data_020dd7fc, &data_020dd7f4, &data_020dd7e4,
        &data_020dd7ec, &data_020dd7dc, &data_020dd7d4, &data_020dd7cc, &data_020dd7c4,
    };
    FishingFloatPool_Construct(&data_021cad80);
    static_init_register(&data_021cad80, func_02060844, &data_021cad10);
    static_init_copy(data_021cad30, float_fns, FISHING_FLOAT_STATES);
}
CLEAN_AS(__sinit_020c59c0, StaticInit_FishingFloat)

/* The main program's random numbers (main_random.h), seeded with 1. */
extern Random data_021cb5a0;
extern StaticInitRecord data_021cb5a4;
extern void func_0206154c(void *random); /* MainRandom_Destruct */

/* __sinit_020c5a78: the main random numbers, seeded with 1. */
void StaticInit_MainRandom(void)
{
    Random_Init(&data_021cb5a0, 1);
    static_init_register(&data_021cb5a0, func_0206154c, &data_021cb5a4);
}
CLEAN_AS(__sinit_020c5a78, StaticInit_MainRandom)

/* The items' info files and an item code (item_info.c). */
extern ItemInfoFiles data_021cb5e0;
extern u16 data_021cb5b0;
extern StaticInitRecord data_021cb5c8, data_021cb5d4;
extern void *func_02062d7c(void *files); /* the files' constructor */
extern void func_02062d44(void *files);  /* the files' destructor */

/* __sinit_020c5aa0: the items' info files, and the item code (none). */
void StaticInit_ItemInfo(void)
{
    func_02062d7c(&data_021cb5e0);
    static_init_register(&data_021cb5e0, func_02062d44, &data_021cb5c8);
    data_021cb5b0 = STATIC_INIT_NO_ITEM;
    static_init_register(&data_021cb5b0, func_020051b0, &data_021cb5d4);
}
CLEAN_AS(__sinit_020c5aa0, StaticInit_ItemInfo)

extern StaticInitColour data_021cd878, data_021cd874, data_021cd870, data_021cd868, data_021cd86c, data_021cd860;

/* __sinit_020c5ae4: the six colours of its source file. */
void StaticInit_Colours5ae4(void)
{
    static_init_colours(&data_021cd878, &data_021cd874, &data_021cd870, &data_021cd868, &data_021cd86c, &data_021cd860);
}
CLEAN_AS(__sinit_020c5ae4, StaticInit_Colours5ae4)

/* Three text objects, each a text base (text_base.c) given its class's vtable, with their
 * records, constructors and destructors. */
extern u8 data_021cd8c4[], data_021cd9b0[], data_021cd8ec[];
extern StaticInitRecord data_021cd8a0, data_021cd8b8, data_021cd894;
extern void *func_0206daf8(void *text);
extern void *func_0206da98(void *text);
extern void *func_0206da38(void *text);
extern void func_0206dae0(void *text);
extern void func_0206da80(void *text);
extern void func_0206da20(void *text);

/* __sinit_020c5b40: three text objects (vtables data_020df240, data_020df210 and
 * data_020df228). */
void StaticInit_Texts5b40(void)
{
    func_0206daf8(data_021cd8c4);
    static_init_register(data_021cd8c4, func_0206dae0, &data_021cd8a0);
    func_0206da98(data_021cd9b0);
    static_init_register(data_021cd9b0, func_0206da80, &data_021cd8b8);
    func_0206da38(data_021cd8ec);
    static_init_register(data_021cd8ec, func_0206da20, &data_021cd894);
}
CLEAN_AS(__sinit_020c5b40, StaticInit_Texts5b40)

extern StaticInitColour data_021cfb84, data_021cfb8c, data_021cfb74, data_021cfb70, data_021cfb78, data_021cfb7c;
extern Random data_021cfb80;
extern StaticInitRecord data_021cfba0;

/* __sinit_020c5ba0: the six colours of its source file, and its random numbers seeded with 1
 * (MainRandom_Destruct as their destructor). */
void StaticInit_Colours5ba0(void)
{
    static_init_colours(&data_021cfb84, &data_021cfb8c, &data_021cfb74, &data_021cfb70, &data_021cfb78, &data_021cfb7c);
    Random_Init(&data_021cfb80, 1);
    static_init_register(&data_021cfb80, func_0206154c, &data_021cfba0);
}
CLEAN_AS(__sinit_020c5ba0, StaticInit_Colours5ba0)

/* The sound set (sound.h); it has no constructor. */
extern u8 data_021cfbcc[];
extern StaticInitRecord data_021cfbb0;
extern void func_0206eac0(void *set); /* its destructor (its two melody players') */

/* __sinit_020c5c24: the sound set registered. */
void StaticInit_SoundSet(void)
{
    static_init_register(data_021cfbcc, func_0206eac0, &data_021cfbb0);
}
CLEAN_AS(__sinit_020c5c24, StaticInit_SoundSet)

/* The owners the overlay groups are loaded for (overlay_groups.c), a letter like
 * data_021c2604, and the object of global_021cfc98.h. */
extern List data_021cfca0;
extern u8 data_021cfd68[];
extern u32 data_021cfc98[2];
extern StaticInitRecord data_021cfcc0, data_021cfca8;
extern void func_02004b2c(void *object); /* Global021cfc98_Destruct */

/* __sinit_020c5c40: the overlay groups' owners empty, a letter, and the object at
 * data_021cfc98 cleared. */
void StaticInit_OverlayGroups(void)
{
    data_021cfca0.first = NULL;
    data_021cfca0.last = NULL;
    func_02066694(data_021cfd68);
    static_init_register(data_021cfd68, func_02066688, &data_021cfcc0);
    data_021cfc98[0] = 0;
    data_021cfc98[1] = 0;
    static_init_register(data_021cfc98, func_02004b2c, &data_021cfca8);
}
CLEAN_AS(__sinit_020c5c40, StaticInit_OverlayGroups)

/* __sinit_020c5c90: nothing. */
void StaticInit_Nothing5c90(void) {}
CLEAN_AS(__sinit_020c5c90, StaticInit_Nothing5c90)
