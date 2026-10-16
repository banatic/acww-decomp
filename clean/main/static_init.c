/* The main program's static initialisers (static_init.h). */
#include "static_init.h"

#include "a_mes_obj.h"
#include "ab_all_obj.h"
#include "actor_palettes.h"
#include "actor_table.h"
#include "anim_slots.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/links.h"
#include "autoload_2/process.h"
#include "autoload_2/sound_position.h"
#include "autoload_2/sound_system.h"
#include "autoload_2/vector.h"
#include "backup_card.h"
#include "bbs.h"
#include "bg_models.h"
#include "block_02034858.h"
#include "block_021d27ac.h"
#include "body_anim_heaps.h"
#include "body_look.h"
#include "bottle_mail.h"
#include "calendar.h"
#include "camera_view.h"
#include "caution_window.h"
#include "clean.h"
#include "cloth_slots.h"
#include "collision_area.h"
#include "collision_box.h"
#include "collision_post_source.h"
#include "collision_segment.h"
#include "constellations.h"
#include "control_mode_icon.h"
#include "date_random.h"
#include "day_plan.h"
#include "design_assets.h"
#include "design_sets.h"
#include "display_frame.h"
#include "event_announce.h"
#include "event_calendar.h"
#include "event_entries.h"
#include "event_queue.h"
#include "event_schedule.h"
#include "event_winner.h"
#include "exchange_block.h"
#include "face_anim_heaps.h"
#include "face_anim_slots.h"
#include "face_texture.h"
#include "field_collision.h"
#include "field_label.h"
#include "fishing_float.h"
#include "fox_shop.h"
#include "furniture_info.h"
#include "glasses_look.h"
#include "global_021dc5b0.h"
#include "globe.h"
#include "head_look.h"
#include "held_item_pool.h"
#include "house_looks.h"
#include "house_record.h"
#include "item_1568_count.h"
#include "item_group_order.h"
#include "item_info.h"
#include "last_sale.h"
#include "library_overlay.h"
#include "link_state.h"
#include "mail.h"
#include "mail_text.h"
#include "message_query.h"
#include "message_reader.h"
#include "missing_npc1.h"
#include "missing_npc2.h"
#include "model_object.h"
#include "museum_record.h"
#include "nook_store.h"
#include "npc_plc.h"
#include "obj_020dd33c.h"
#include "ov004/member_pointer.h"
#include "paired_town.h"
#include "place_claim.h"
#include "player_options.h"
#include "player_records.h"
#include "resource_pools.h"
#include "room_cells.h"
#include "room_interior.h"
#include "room_score_state.h"
#include "save_stamp.h"
#include "scene_claim.h"
#include "scene_exit.h"
#include "scene_look.h"
#include "scene_place.h"
#include "screen_icon.h"
#include "screen_mark.h"
#include "screen_panels.h"
#include "select_bmg.h"
#include "session_link.h"
#include "shadow.h"
#include "shop_answers.h"
#include "shop_list_a.h"
#include "sky.h"
#include "sky_objects.h"
#include "sky_weather_day.h"
#include "slot_pool.h"
#include "snowmen.h"
#include "spawner.h"
#include "star_palette.h"
#include "state_block.h"
#include "text_font.h"
#include "text_walker.h"
#include "tile_requests.h"
#include "touch_pick_shapes.h"
#include "town_item_lists.h"
#include "town_layout.h"
#include "town_name.h"
#include "town_record.h"
#include "town_start_day.h"
#include "town_villager.h"
#include "transition_mark.h"
#include "trivial_object.h"
#include "turnip_prices.h"
#include "view_frustum.h"
#include "villager_part_block.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "waiting_letter.h"
#include "wfc_delivery.h"
#include "wfc_stats.h"
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

/* The design sample (design_sets.h), the designs' manager and their information file
 * (design_assets.h), with their records and destructors. */
extern Design data_021d0800;
extern DesignManager data_021d0504;
extern RecordFile data_021d04c8;
extern StaticInitRecord data_021d04bc, data_021d04a4, data_021d04b0;
extern void func_020728d8(void *sample);  /* the sample's destructor */
extern void func_020727d4(void *manager); /* the manager's destructor */
extern void func_02072350(void *archive); /* the file's destructor */

/* __sinit_020c5c94: the design sample, the designs' manager and their information file. */
void StaticInit_Designs(void)
{
    DesignSample_Construct(&data_021d0800);
    static_init_register(&data_021d0800, func_020728d8, &data_021d04bc);
    DesignManager_Construct((char *) &data_021d0504);
    static_init_register(&data_021d0504, func_020727d4, &data_021d04a4);
    DesignArchive_Construct(&data_021d04c8);
    static_init_register(&data_021d04c8, func_02072350, &data_021d04b0);
}
CLEAN_AS(__sinit_020c5c94, StaticInit_Designs)

extern NetSession data_021d0a44;
extern StaticInitRecord data_021d0a38;
extern void func_02073fc8(void *session); /* the session's destructor */

/* __sinit_020c5cf4: the wireless session (session_link.h). */
void StaticInit_Session(void)
{
    Session_Construct(&data_021d0a44);
    static_init_register(&data_021d0a44, func_02073fc8, &data_021d0a38);
}
CLEAN_AS(__sinit_020c5cf4, StaticInit_Session)

extern LibraryOverlaySlot data_021d11c4;
extern StaticInitRecord data_021d11b8;
extern void func_02077bb4(void *slot); /* LibraryOverlay_Destroy: nothing to do */

/* __sinit_020c5d1c: the library overlay's slot (library_overlay.h), holding no overlay. */
void StaticInit_LibraryOverlay(void)
{
    data_021d11c4.overlay = -1;
    static_init_register(&data_021d11c4, func_02077bb4, &data_021d11b8);
}
CLEAN_AS(__sinit_020c5d1c, StaticInit_LibraryOverlay)

/* The town villager being set up (town_villager.h), the filters of the villagers' house items
 * (villager_house_items.c), the villagers' states (villager_state.h) and the resource pools of
 * blocks, 8-byte heaps and 4-byte heaps (resource_pools.h). */
#define STATIC_INIT_HOUSE_FILTERS 5
extern u8 data_021d1554[];
extern MemberPointer data_021d1330[STATIC_INIT_HOUSE_FILTERS];
extern const MemberPointer data_020e18b8, data_020e18a8, data_020e1898, data_020e18b0, data_020e18a0;
extern VillagerStates data_021d13e4;
extern u8 *data_021d12dc[];
extern Heap *data_021d1310[];
extern Heap *data_021d12a4[];
extern StaticInitRecord data_021d1280, data_021d1274, data_021d128c, data_021d1250, data_021d1268;
extern void func_02081710(void *villager); /* the town villager's destructor */
extern void func_020795c8(void *entry);    /* a villager state's constructor */
extern void func_020795a8(void *entry);    /* a villager state's destructor */
extern void func_02082528(void *states);   /* the states' destructor */
extern void func_02078d64(void *pool);     /* the block pool's destructor */
extern void func_02078c74(void *pool);     /* the 8-byte heap pool's destructor */
extern void func_02078bac(void *pool);     /* the 4-byte heap pool's destructor */

static_assert(sizeof(VillagerState) == 44, "VillagerState");

/* __sinit_020c5d3c: the town villager, the house items' filters, the villagers' states (their
 * entries constructed by __cxa_vec_ctor, then the whole registered) and the three resource
 * pools. */
void StaticInit_Villagers(void)
{
    static const MemberPointer *const filter_fns[STATIC_INIT_HOUSE_FILTERS] = {
        &data_020e18b8, &data_020e18a8, &data_020e1898, &data_020e18b0, &data_020e18a0,
    };
    TownVillager_Construct(data_021d1554);
    static_init_register(data_021d1554, func_02081710, &data_021d1280);
    static_init_copy(data_021d1330, filter_fns, STATIC_INIT_HOUSE_FILTERS);
    __cxa_vec_ctor(data_021d13e4.entries, VILLAGER_STATE_ENTRIES, sizeof(VillagerState), func_020795c8, func_020795a8);
    static_init_register(&data_021d13e4, func_02082528, &data_021d1274);
    ResourcePools_BlockConstruct(data_021d12dc);
    static_init_register(data_021d12dc, func_02078d64, &data_021d128c);
    ResourcePools_Heap8Construct(data_021d1310);
    static_init_register(data_021d1310, func_02078c74, &data_021d1250);
    ResourcePools_Heap4Construct(data_021d12a4);
    static_init_register(data_021d12a4, func_02078bac, &data_021d1268);
}
CLEAN_AS(__sinit_020c5d3c, StaticInit_Villagers)

/* The actors' table (actor_table.h): its entries' constructors set their code to none, their
 * destructors do nothing. */
extern ActorTable data_021d1d4c;
extern StaticInitRecord data_021d1d40;
extern void func_02082c00(void *entry); /* a kind 0xe entry's constructor */
extern void func_02082bfc(void *entry); /* its destructor */
extern void func_02082bf0(void *entry); /* a kind 0xd entry's constructor */
extern void func_02082bec(void *entry); /* its destructor */
extern void func_02082bc0(void *table); /* ActorEntries_DestructTable */

static_assert(sizeof(ActorEntry) == 8, "ActorEntry");

/* __sinit___sinit_020c5e30.cpp (the initialiser of a C++ source file): the actors' table,
 * both arrays of entries constructed by __cxa_vec_ctor, then the table registered.
 * Not registered: CLEAN_AS takes a C name, and this function's symbol has a '.' in it. */
void StaticInit_ActorTable(void)
{
    __cxa_vec_ctor(data_021d1d4c.kind_e, ACTOR_TABLE_KIND_E_ENTRIES, sizeof(ActorEntry), func_02082c00, func_02082bfc);
    __cxa_vec_ctor(data_021d1d4c.kind_d, ACTOR_TABLE_KIND_D_ENTRIES, sizeof(ActorEntry), func_02082bf0, func_02082bec);
    static_init_register(&data_021d1d4c, func_02082bc0, &data_021d1d40);
}

/* The slot pools (slot_pool.h): speakers, 8-byte heaps, 4-byte heaps, clothes, blocks,
 * animation sets, parts and held items. */
extern SlotPoolSpeakers data_021d1e48;
extern SlotPoolHeap8 data_021d1ebc;
extern SlotPoolHeap4 data_021d1e64;
extern SlotPoolBytes data_021d1e20;
extern SlotPoolBlocks data_021d1e8c;
extern SlotPoolBytes data_021d1e0c;
extern SlotPoolBytes data_021d1e34;
extern SlotPoolItems data_021d1f04;
extern StaticInitRecord data_021d1dac, data_021d1db8, data_021d1dc4, data_021d1dd0, data_021d1de8, data_021d1ddc,
    data_021d1e00, data_021d1df4;
extern void func_02083b3c(void *pool);
extern void func_020839d8(void *pool);
extern void func_02083898(void *pool);
extern void func_02083744(void *pool);
extern void func_020835dc(void *pool);
extern void func_0208349c(void *pool);
extern void func_0208335c(void *pool);
extern void func_020831fc(void *pool);

/* __sinit_020c5e84: the eight slot pools, each constructed and registered. */
void StaticInit_SlotPools(void)
{
    SlotPool_SpeakersConstruct(&data_021d1e48);
    static_init_register(&data_021d1e48, func_02083b3c, &data_021d1dac);
    SlotPool_Heap8Construct(&data_021d1ebc);
    static_init_register(&data_021d1ebc, func_020839d8, &data_021d1db8);
    SlotPool_Heap4Construct(&data_021d1e64);
    static_init_register(&data_021d1e64, func_02083898, &data_021d1dc4);
    SlotPool_ClothesConstruct(&data_021d1e20);
    static_init_register(&data_021d1e20, func_02083744, &data_021d1dd0);
    SlotPool_BlocksConstruct(&data_021d1e8c);
    static_init_register(&data_021d1e8c, func_020835dc, &data_021d1de8);
    SlotPool_AnimSetsConstruct(&data_021d1e0c);
    static_init_register(&data_021d1e0c, func_0208349c, &data_021d1ddc);
    SlotPool_PartsConstruct(&data_021d1e34);
    static_init_register(&data_021d1e34, func_0208335c, &data_021d1e00);
    SlotPool_ItemsConstruct(&data_021d1f04);
    static_init_register(&data_021d1f04, func_020831fc, &data_021d1df4);
}
CLEAN_AS(__sinit_020c5e84, StaticInit_SlotPools)

/* The spawner's request, its checks and its spawn table (spawner.h): the checks' member
 * functions and the placers of the table's 23 entries come from the program's constants. */
#define STATIC_INIT_SPAWN_ENTRIES 23
extern SpawnerRequest data_020e1ca8;
extern SpawnerCheck data_020e1d08[SPAWNER_CHECKS];
extern SpawnerEntry data_020e1d8c[STATIC_INIT_SPAWN_ENTRIES];
extern StaticInitRecord data_021d2130;
extern void func_02085f04(void *request); /* Spawner_RequestDestruct */
extern const MemberFn data_020e1bb8, data_020e1c90, data_020e1c00, data_020e1ba0, data_020e1be8, data_020e1bc0, data_020e1ca0,
    data_020e1c98, data_020e1bd8, data_020e1c88, data_020e1c80;
extern const MemberFn data_020e1c68, data_020e1c60, data_020e1c18, data_020e1c20, data_020e1c48, data_020e1c28, data_020e1c30,
    data_020e1c38, data_020e1c50, data_020e1c58, data_020e1c70, data_020e1c78, data_020e1c10, data_020e1c08, data_020e1b90,
    data_020e1b98, data_020e1bf0, data_020e1ba8, data_020e1be0, data_020e1bb0, data_020e1bc8, data_020e1bd0, data_020e1bf8;

/* __sinit_020c5f70: the spawner's request registered and its position cleared, then each
 * check's member function and each spawn table entry's placer filled in. The ROM names the
 * table's later entries by the symbols data_020e1e0c, data_020e1e8c and data_020e1f0c; they
 * are the same table.
 * QUIRK: the request is registered before its position is cleared. */
void StaticInit_Spawner(void)
{
    static const MemberFn *const check_fns[SPAWNER_CHECKS] = {
        &data_020e1bb8, &data_020e1c90, &data_020e1c00, &data_020e1ba0, &data_020e1be8, &data_020e1bc0,
        &data_020e1ca0, &data_020e1c98, &data_020e1bd8, &data_020e1c88, &data_020e1c80,
    };
    static const MemberFn *const place_fns[STATIC_INIT_SPAWN_ENTRIES] = {
        &data_020e1c68, &data_020e1c60, &data_020e1c18, &data_020e1c20, &data_020e1c48, &data_020e1c28,
        &data_020e1c30, &data_020e1c38, &data_020e1c50, &data_020e1c58, &data_020e1c70, &data_020e1c78,
        &data_020e1c10, &data_020e1c08, &data_020e1b90, &data_020e1b98, &data_020e1bf0, &data_020e1ba8,
        &data_020e1be0, &data_020e1bb0, &data_020e1bc8, &data_020e1bd0, &data_020e1bf8,
    };
    static_init_register(&data_020e1ca8, func_02085f04, &data_021d2130);
    static_init_vec(&data_020e1ca8.position, 0, 0, 0);
    for (int i = 0; i < SPAWNER_CHECKS; i++) {
        data_020e1d08[i].check = *check_fns[i];
    }
    for (int i = 0; i < STATIC_INIT_SPAWN_ENTRIES; i++) {
        data_020e1d8c[i].place = *place_fns[i];
    }
}
CLEAN_AS(__sinit_020c5f70, StaticInit_Spawner)

/* The tiles around a tile the event winners' code checks (event_winner.c): the eight next to
 * it, and the fourteen around a house (columns -3 and 2 and row 2), and the object of
 * block_021d27ac.h. */
#define STATIC_INIT_NEIGHBOURS 8
#define STATIC_INIT_HOUSE_RING 14
extern EventWinnerTile data_021d27e0[STATIC_INIT_NEIGHBOURS];
extern EventWinnerTile data_021d2820[STATIC_INIT_HOUSE_RING];
extern Block021d27ac data_021d27ac;
extern StaticInitRecord data_021d27a0;
extern void func_02086158(void *block); /* the object's destructor */

static void static_init_tile(EventWinnerTile *tile, int x, int z)
{
    tile->x = x;
    tile->z = z;
}

/* __sinit_020c6194: the fourteen tiles around a house, the eight next to a tile, and the
 * object at data_021d27ac.
 * The start-up code constructs that object with func_02086198 and registers func_02086158 as
 * its destructor: of the two names block_021d27ac.c gives them, Block021d27ac_Destruct is the
 * constructor. */
void StaticInit_EventWinnerTiles(void)
{
    static_init_tile(&data_021d2820[0], -3, -2);
    static_init_tile(&data_021d2820[1], 2, -2);
    static_init_tile(&data_021d2820[2], -3, -1);
    static_init_tile(&data_021d2820[3], 2, -1);
    static_init_tile(&data_021d2820[4], -3, 0);
    static_init_tile(&data_021d2820[5], 2, 0);
    static_init_tile(&data_021d2820[6], -3, 1);
    static_init_tile(&data_021d2820[7], 2, 1);
    static_init_tile(&data_021d2820[8], -3, 2);
    static_init_tile(&data_021d2820[9], -2, 2);
    static_init_tile(&data_021d2820[10], -1, 2);
    static_init_tile(&data_021d2820[11], 0, 2);
    static_init_tile(&data_021d2820[12], 1, 2);
    static_init_tile(&data_021d2820[13], 2, 2);
    static_init_tile(&data_021d27e0[0], 0, 1);
    static_init_tile(&data_021d27e0[1], 0, -1);
    static_init_tile(&data_021d27e0[2], -1, 0);
    static_init_tile(&data_021d27e0[3], 1, 0);
    static_init_tile(&data_021d27e0[4], -1, -1);
    static_init_tile(&data_021d27e0[5], 1, -1);
    static_init_tile(&data_021d27e0[6], -1, 1);
    static_init_tile(&data_021d27e0[7], 1, 1);
    Block021d27ac_Destruct(&data_021d27ac);
    static_init_register(&data_021d27ac, func_02086158, &data_021d27a0);
}
CLEAN_AS(__sinit_020c6194, StaticInit_EventWinnerTiles)

/* __sinit_020c62a0: nothing. */
void StaticInit_Nothing62a0(void) {}
CLEAN_AS(__sinit_020c62a0, StaticInit_Nothing62a0)

extern ScreenPanels data_021d3258;
extern StaticInitRecord data_021d3164;
extern void func_0208b5b0(void *panels); /* the panels' destructor */

/* __sinit_020c62a4: the screen panels (screen_panels.h). */
void StaticInit_ScreenPanels(void)
{
    ScreenPanels_Construct(&data_021d3258);
    static_init_register(&data_021d3258, func_0208b5b0, &data_021d3164);
}
CLEAN_AS(__sinit_020c62a4, StaticInit_ScreenPanels)

extern ScreenMark data_021d35f8;
extern StaticInitRecord data_021d35cc;
extern void func_0208ef34(void *mark); /* the mark's destructor */

/* __sinit_020c62cc: the screen mark (screen_mark.h). */
void StaticInit_ScreenMark(void)
{
    ScreenMark_Construct(&data_021d35f8);
    static_init_register(&data_021d35f8, func_0208ef34, &data_021d35cc);
}
CLEAN_AS(__sinit_020c62cc, StaticInit_ScreenMark)

extern TransitionMark data_021d3654;
extern StaticInitRecord data_021d3628;
extern void func_0208fac4(void *mark); /* the mark's destructor */

/* __sinit_020c62f4: the transition mark (transition_mark.h). */
void StaticInit_TransitionMark(void)
{
    TransitionMark_Construct(&data_021d3654);
    static_init_register(&data_021d3654, func_0208fac4, &data_021d3628);
}
CLEAN_AS(__sinit_020c62f4, StaticInit_TransitionMark)

extern ControlModeIcon data_021d369c;
extern StaticInitRecord data_021d3690;
extern void func_0208fe5c(void *icon); /* the icon's destructor */

/* __sinit_020c631c: the control mode's icon (control_mode_icon.h). */
void StaticInit_ControlModeIcon(void)
{
    ControlModeIcon_Construct(&data_021d369c);
    static_init_register(&data_021d369c, func_0208fe5c, &data_021d3690);
}
CLEAN_AS(__sinit_020c631c, StaticInit_ControlModeIcon)

extern ExchangeBlock data_021d36d4[EXCHANGE_BLOCK_VISITORS];
extern StaticInitRecord data_021d36c8;
extern void func_0209008c(void *blocks); /* the visitors' blocks' destructor */

/* __sinit_020c6344: the exchange blocks kept for the visitors (exchange_block.h). */
void StaticInit_ExchangeBlocks(void)
{
    ExchangeBlock_ConstructVisitors(data_021d36d4);
    static_init_register(data_021d36d4, func_0209008c, &data_021d36c8);
}
CLEAN_AS(__sinit_020c6344, StaticInit_ExchangeBlocks)

/* An object of four slots (func_020962f8 builds it: four points, and for each slot two calls
 * on the object itself), with its record and destructor. */
extern u8 data_021d5684[];
extern StaticInitRecord data_021d5678;
extern void *func_020962f8(void *object);
extern void func_020962dc(void *object);

/* __sinit_020c636c: the object at data_021d5684. */
void StaticInit_Object5684(void)
{
    func_020962f8(data_021d5684);
    static_init_register(data_021d5684, func_020962dc, &data_021d5678);
}
CLEAN_AS(__sinit_020c636c, StaticInit_Object5684)

extern u8 data_021d5738[];
extern StaticInitRecord data_021d56fc;
extern void func_02098580(void *guests); /* the guests' records' destructor */

/* __sinit_020c6394: the three guests' records (player_records.h). */
void StaticInit_GuestRecords(void)
{
    PlayerRecords_ConstructGuests(data_021d5738);
    static_init_register(data_021d5738, func_02098580, &data_021d56fc);
}
CLEAN_AS(__sinit_020c6394, StaticInit_GuestRecords)

/* The step types' entries of the villagers' part blocks (villager_part_block.h). */
extern VillagerPartTypeEntry data_020e3504[VILLAGER_PART_BLOCK_STEPS];
extern const MemberPointer data_020e3498, data_020e34a0, data_020e34a8, data_020e34c0, data_020e34b0;

/* __sinit_020c63bc: each step type's two member functions: the set-ups of types 10, 14, 16,
 * 17 and 19 from the program's constants, every other one null. */
void StaticInit_VillagerPartTypes(void)
{
    static const MemberPointer *const setup_fns[VILLAGER_PART_BLOCK_STEPS] = {
        &data_020e3498, &__ptmf_null,   &__ptmf_null,   &__ptmf_null, &data_020e34a0,
        &__ptmf_null,   &data_020e34a8, &data_020e34c0, &__ptmf_null, &data_020e34b0,
    };
    for (int i = 0; i < VILLAGER_PART_BLOCK_STEPS; i++) {
        data_020e3504[i].setup = *setup_fns[i];
        data_020e3504[i].unknown = __ptmf_null;
    }
}
CLEAN_AS(__sinit_020c63bc, StaticInit_VillagerPartTypes)

extern u8 data_021dc5b0;
extern StaticInitRecord data_021dc5b4;
extern void func_0209d080(void *object); /* Global021dc5b0_Destruct */

/* __sinit_020c6464: the byte of global_021dc5b0.h. */
void StaticInit_Global021dc5b0(void)
{
    Global021dc5b0_Construct(&data_021dc5b0);
    static_init_register(&data_021dc5b0, func_0209d080, &data_021dc5b4);
}
CLEAN_AS(__sinit_020c6464, StaticInit_Global021dc5b0)

/* The scene claims (scene_claim.h): the exit and the scenes' masks. */
extern SceneClaimExit data_021dc6e8;
extern SceneClaimMask data_021dc70c[SCENE_CLAIM_SCENES];
extern StaticInitRecord data_021dc6dc, data_021dc6d0;
extern void func_0209d89c(void *exit);  /* the exit's destructor */
extern void func_0209d9c4(void *mask);  /* a mask's constructor */
extern void func_0209d934(void *mask);  /* a mask's destructor */
extern void func_0209d9a8(void *masks); /* SceneClaimMasks_Destruct */

static_assert(sizeof(SceneClaimMask) == 1, "SceneClaimMask");

/* __sinit_020c648c: the scene claims' exit, and their masks constructed by __cxa_vec_ctor,
 * cleared and registered as a whole. */
void StaticInit_SceneClaims(void)
{
    SceneClaimExit_Construct(&data_021dc6e8);
    static_init_register(&data_021dc6e8, func_0209d89c, &data_021dc6dc);
    __cxa_vec_ctor(data_021dc70c, SCENE_CLAIM_SCENES, sizeof(SceneClaimMask), func_0209d9c4, func_0209d934);
    SceneClaimMasks_Clear((char *) data_021dc70c);
    static_init_register(data_021dc70c, func_0209d9a8, &data_021dc6d0);
}
CLEAN_AS(__sinit_020c648c, StaticInit_SceneClaims)

/* The state block (state_block.h), its record, and the constructors and destructors of its
 * parts that the game is handed: the mailboxes' and the parts at 0x16800's. */
extern StateBlock data_021dc7a8;
extern StaticInitRecord data_021dc764;
extern void func_020980c4(void *box);   /* a mailbox's constructor */
extern void func_020980a4(void *box);   /* a mailbox's destructor */
extern void func_0203a690(void *part);  /* a part at 0x16800's constructor */
extern void func_0203a68c(void *part);  /* its destructor */
extern void func_0209f1a8(void *block); /* StateBlock_Destruct */
extern void *func_020901d8(void *part); /* the part at 0x11c70's constructor */

/* __sinit_020c64e8: the state block's parts constructed from the first to the last (the
 * mailboxes and the parts at 0x16800 as arrays, by __cxa_vec_ctor), then the block registered
 * whole. */
void StaticInit_StateBlock(void)
{
    StateBlock *block = &data_021dc7a8;
    TownName_Construct(&block->town);
    PlayerRecords_ConstructTown(block->players);
    VillagerRoster_Construct((VillagerTown *) block->villagers);
    TownLayout_Construct(block->layout);
    Item1568Count_Construct(&block->part_0f52a);
    DayPlan_Construct(&block->part_0f52b);
    HouseRecord_Construct((HouseRecord *) block->part_0f52c);
    ShopDesigns_Construct((ShopDesigns *) block->shop_designs);
    func_020901d8(block->part_11c70);
    Bbs_Construct((Bbs *) block->bbs);
    __cxa_vec_ctor(block->mailboxes, STATE_BLOCK_PLAYERS, sizeof(block->mailboxes[0]), func_020980c4, func_020980a4);
    MailPostOffice_Construct((MailPostOffice *) block->post_office);
    Constellations_ConstructList((int) (uintptr_t) block->constellations);
    __cxa_vec_ctor(block->part_16800, STATE_BLOCK_PLAYERS, sizeof(block->part_16800[0]), func_0203a690, func_0203a68c);
    WfcStats_Construct((WfcStats *) block->part_16ad0);
    HouseLooks_Construct((HouseLooksRecord *) block->house_looks);
    BottleMail_ConstructState((BottleState *) block->bottle);
    WaitingLetter_Construct((WaitingLetter *) block->part_1704c);
    MuseumRecord_Construct((MuseumRecord *) block->museum);
    NookStore_Construct((NookStore *) block->nook_store);
    EventSchedule_ClearWeek((EventSchedule *) block->part_17218);
    TownRecord_Construct(block->part_17254);
    TownItemLists_ConstructListA(block->part_172c0);
    TownItemLists_ConstructListB(block->part_172de);
    EventWinner_Construct((EventWinner *) block->part_172fc);
    LastSale_Construct((LastSale *) block->part_17344);
    TurnipPrices_Construct((TurnipPrices *) block->part_17364);
    SkyWeatherDay_Construct((SkyWeatherDay *) block->part_1737e);
    FoxShop_Construct((FoxShop *) block->fox_shop);
    ShopListA_Construct((ShopListA *) block->shop_list_a);
    Snowmen_ConstructRecords((SnowmenRecord *) block->snowmen);
    RoomScoreState_ConstructJudgeDate(block->part_173c8);
    ItemGroupOrder_ConstructAll(block->part_173d4);
    TownStartDay_Construct((TownStartDay *) block->part_173dd);
    PairedTown_Construct(block->part_173e2);
    SaveStamp_Construct((SaveStamp *) block->part_173f8);
    static_init_register(block, func_0209f1a8, &data_021dc764);
}
CLEAN_AS(__sinit_020c64e8, StaticInit_StateBlock)

/* The start menu's states' entries and updates (start_menu.c). */
#define STATIC_INIT_START_MENU_FNS 12
extern MemberPointer data_021f3ba4[STATIC_INIT_START_MENU_FNS];
extern const MemberPointer data_020e3698, data_020e36f8, data_020e36f0, data_020e36e8, data_020e36e0, data_020e36d8,
    data_020e36d0, data_020e36a8, data_020e36c0, data_020e36b8, data_020e36b0, data_020e36c8;

/* __sinit_020c66e0: the start menu's states' member functions. Their table's address. */
int StaticInit_StartMenu(void)
{
    static const MemberPointer *const menu_fns[STATIC_INIT_START_MENU_FNS] = {
        &data_020e3698, &data_020e36f8, &data_020e36f0, &data_020e36e8, &data_020e36e0, &data_020e36d8,
        &data_020e36d0, &data_020e36a8, &data_020e36c0, &data_020e36b8, &data_020e36b0, &data_020e36c8,
    };
    static_init_copy(data_021f3ba4, menu_fns, STATIC_INIT_START_MENU_FNS);
    return (int) (uintptr_t) data_021f3ba4;
}
CLEAN_AS(__sinit_020c66e0, StaticInit_StartMenu)

/* The Wi-Fi session's letter, notice and statistics (wfc_session.c) and the activity's jobs'
 * starts and steps (activity_process.c). */
#define STATIC_INIT_ACTIVITY_FNS 64
extern WfcLetter data_021f3d90;
extern WfcNotice data_021f3cbc;
extern WfcStats data_021f40a4;
extern StaticInitRecord data_021f3c40, data_021f3c4c, data_021f3c58;
extern void func_0203f664(void *letter); /* the letter's destructor */
extern void func_0203f5dc(void *notice); /* the notice's destructor */
extern void func_02088264(void *stats);  /* the statistics' destructor */
extern MemberPointer data_021f3ea4[STATIC_INIT_ACTIVITY_FNS];
extern const MemberPointer data_020e3a48, data_020e3a40, data_020e38c8, data_020e3a30, data_020e3a28, data_020e38b8,
    data_020e3888, data_020e3a10, data_020e3a08, data_020e3a00, data_020e39f8, data_020e39f0, data_020e39e8, data_020e38d8,
    data_020e38e0, data_020e39d0, data_020e39c8, data_020e39c0, data_020e39b8, data_020e39b0, data_020e39a8, data_020e39a0,
    data_020e3958, data_020e3970, data_020e3978, data_020e3988, data_020e3990, data_020e39e0, data_020e3a18, data_020e3a38,
    data_020e3a50, data_020e3950, data_020e3948, data_020e3940, data_020e3848, data_020e3840, data_020e3810, data_020e3818,
    data_020e3820, data_020e3910, data_020e3908, data_020e3900, data_020e3830, data_020e3878, data_020e38e8, data_020e3860,
    data_020e3870, data_020e38d0, data_020e3880, data_020e38c0, data_020e3890, data_020e3898, data_020e38a0, data_020e38b0,
    data_020e38f8, data_020e3920, data_020e3928, data_020e3938, data_020e3960, data_020e3980, data_020e3998, data_020e3a20,
    data_020e3a58, data_020e3850;

/* __sinit_020c6790: the Wi-Fi letter, notice and statistics, and the activity's jobs' member
 * functions. */
void StaticInit_Activity(void)
{
    static const MemberPointer *const job_fns[STATIC_INIT_ACTIVITY_FNS] = {
        &data_020e3a48, &data_020e3a40, &data_020e38c8, &data_020e3a30, &data_020e3a28, &data_020e38b8, &data_020e3888,
        &data_020e3a10, &data_020e3a08, &data_020e3a00, &data_020e39f8, &data_020e39f0, &data_020e39e8, &data_020e38d8,
        &data_020e38e0, &data_020e39d0, &data_020e39c8, &data_020e39c0, &data_020e39b8, &data_020e39b0, &data_020e39a8,
        &data_020e39a0, &data_020e3958, &data_020e3970, &data_020e3978, &data_020e3988, &data_020e3990, &data_020e39e0,
        &data_020e3a18, &data_020e3a38, &data_020e3a50, &data_020e3950, &data_020e3948, &data_020e3940, &data_020e3848,
        &data_020e3840, &data_020e3810, &data_020e3818, &data_020e3820, &data_020e3910, &data_020e3908, &data_020e3900,
        &data_020e3830, &data_020e3878, &data_020e38e8, &data_020e3860, &data_020e3870, &data_020e38d0, &data_020e3880,
        &data_020e38c0, &data_020e3890, &data_020e3898, &data_020e38a0, &data_020e38b0, &data_020e38f8, &data_020e3920,
        &data_020e3928, &data_020e3938, &data_020e3960, &data_020e3980, &data_020e3998, &data_020e3a20, &data_020e3a58,
        &data_020e3850,
    };
    WfcDelivery_ConstructLetter(&data_021f3d90);
    static_init_register(&data_021f3d90, func_0203f664, &data_021f3c40);
    WfcDelivery_ConstructNotice(&data_021f3cbc);
    static_init_register(&data_021f3cbc, func_0203f5dc, &data_021f3c4c);
    WfcStats_Construct(&data_021f40a4);
    static_init_register(&data_021f40a4, func_02088264, &data_021f3c58);
    static_init_copy(data_021f3ea4, job_fns, STATIC_INIT_ACTIVITY_FNS);
}
CLEAN_AS(__sinit_020c6790, StaticInit_Activity)

extern LinkState data_021f4320;
extern StaticInitRecord data_021f42fc;
extern void func_020a6b38(void *state); /* the link state's destructor */

/* __sinit_020c6b88: the link state (link_state.h). */
void StaticInit_LinkState(void)
{
    LinkState_Construct(&data_021f4320);
    static_init_register(&data_021f4320, func_020a6b38, &data_021f42fc);
}
CLEAN_AS(__sinit_020c6b88, StaticInit_LinkState)

/* Three message numbers of the talk code, with an empty destructor
 * (TrivialObject_DestructByte); the box walker and the text copier (text_walker.h) and the
 * message query (message_query.h). */
#define STATIC_INIT_NO_MESSAGE 0xff
#define STATIC_INIT_MESSAGE_FE 0xfe
extern u8 data_021f43ec, data_021f43f8, data_021f43e8;
extern BoxWalker data_021f44dc;
extern TextCopier data_021f450c;
extern MessageQuery data_021f4548;
extern StaticInitRecord data_021f4410, data_021f4434, data_021f441c, data_021f4440, data_021f444c, data_021f4404;
extern void func_020088f8(void *byte);   /* TrivialObject_DestructByte */
extern void func_020a91d8(void *walker); /* the box walker's destructor */
extern void func_020a8d78(void *copier); /* the text copier's destructor */
extern void func_020a7d48(void *query);  /* the message query's destructor */

/* __sinit_020c6bb0: the three message numbers (0xff, 0xff and 0xfe), the box walker, the text
 * copier and the message query. */
void StaticInit_TextWalkers(void)
{
    data_021f43ec = STATIC_INIT_NO_MESSAGE;
    static_init_register(&data_021f43ec, func_020088f8, &data_021f4410);
    data_021f43f8 = STATIC_INIT_NO_MESSAGE;
    static_init_register(&data_021f43f8, func_020088f8, &data_021f4434);
    data_021f43e8 = STATIC_INIT_MESSAGE_FE;
    static_init_register(&data_021f43e8, func_020088f8, &data_021f441c);
    BoxWalker_Construct(&data_021f44dc);
    static_init_register(&data_021f44dc, func_020a91d8, &data_021f4440);
    TextCopier_Construct(&data_021f450c);
    static_init_register(&data_021f450c, func_020a8d78, &data_021f444c);
    MessageQuery_Construct(&data_021f4548);
    static_init_register(&data_021f4548, func_020a7d48, &data_021f4404);
}
CLEAN_AS(__sinit_020c6bb0, StaticInit_TextWalkers)

extern SelectBmg data_021f4670;
extern StaticInitRecord data_021f45b4;
extern void func_020ab948(void *file); /* the file's destructor */

/* __sinit_020c6c54: the selection message file (select_bmg.h). */
void StaticInit_SelectBmg(void)
{
    SelectBmg_Construct(&data_021f4670);
    static_init_register(&data_021f4670, func_020ab948, &data_021f45b4);
}
CLEAN_AS(__sinit_020c6c54, StaticInit_SelectBmg)

/* The shadows' model (shadow.c), a model object (model_object.h). */
extern ModelObject data_021f472c;
extern StaticInitRecord data_021f4720;
extern void func_02055764(void *object); /* the model object's destructor */

/* __sinit_020c6c7c: the shadows' model. */
void StaticInit_ShadowModel(void)
{
    ModelObject_Construct(&data_021f472c);
    static_init_register(&data_021f472c, func_02055764, &data_021f4720);
}
CLEAN_AS(__sinit_020c6c7c, StaticInit_ShadowModel)

/* The five shadows (shadow.h): trees of sizes 2, 3 and 4, the wide one and the narrow one. */
extern ObjShadow data_021f4904, data_021f4938, data_021f496c, data_021f489c, data_021f48d0;
extern StaticInitRecord data_021f47f4, data_021f480c, data_021f4830, data_021f483c, data_021f47dc;
extern void func_020ad1d8(void *shadow); /* a shadow's destructor */

/* __sinit_020c6ca4: the five shadows. */
void StaticInit_Shadows(void)
{
    ObjShadow_Construct(&data_021f4904);
    static_init_register(&data_021f4904, func_020ad1d8, &data_021f47f4);
    ObjShadow_Construct(&data_021f4938);
    static_init_register(&data_021f4938, func_020ad1d8, &data_021f480c);
    ObjShadow_Construct(&data_021f496c);
    static_init_register(&data_021f496c, func_020ad1d8, &data_021f4830);
    ObjShadow_Construct(&data_021f489c);
    static_init_register(&data_021f489c, func_020ad1d8, &data_021f483c);
    ObjShadow_Construct(&data_021f48d0);
    static_init_register(&data_021f48d0, func_020ad1d8, &data_021f47dc);
}
CLEAN_AS(__sinit_020c6ca4, StaticInit_Shadows)

/* The shops' dated random numbers (date_random.h), two item codes (shop_stock.c: none, and
 * the sold marker 0x1547) and the shops' answers (shop_answers.h). */
#define STATIC_INIT_SOLD_MARKER 0x1547
extern DatedRandom data_021f4a80;
extern u16 data_021f49f0;
extern u16 data_021f49f4;
extern ShopAnswers data_021f49ec;
extern StaticInitRecord data_021f4aa4, data_021f4a44, data_021f4ab0, data_021f4a68;
extern void func_02063ddc(void *random);  /* the dated random numbers' destructor */
extern void func_020b023c(void *answers); /* the answers' destructor */

/* __sinit_020c6d2c: the shops' random numbers, their two item codes and their answers. */
void StaticInit_Shops(void)
{
    DatedRandom_Construct(&data_021f4a80);
    static_init_register(&data_021f4a80, func_02063ddc, &data_021f4aa4);
    data_021f49f0 = STATIC_INIT_NO_ITEM;
    static_init_register(&data_021f49f0, func_020051b0, &data_021f4a44);
    data_021f49f4 = STATIC_INIT_SOLD_MARKER;
    static_init_register(&data_021f49f4, func_020051b0, &data_021f4ab0);
    ShopAnswers_Construct(&data_021f49ec);
    static_init_register(&data_021f49ec, func_020b023c, &data_021f4a68);
}
CLEAN_AS(__sinit_020c6d2c, StaticInit_Shops)

extern SnowmenLooseBall data_021f4ae8[SNOWMEN_LOOSE_BALLS];
extern StaticInitRecord data_021f4adc;
extern void func_020b0aa8(void *ball);  /* a loose ball's constructor */
extern void func_020b0aa4(void *ball);  /* its destructor */
extern void func_020b0a88(void *balls); /* Snowmen_DestructLooseBalls */

static_assert(sizeof(SnowmenLooseBall) == 16, "SnowmenLooseBall");

/* __sinit_020c6da8: the two loose snowballs (snowmen.h), constructed by __cxa_vec_ctor and
 * registered as a whole. */
void StaticInit_SnowmenBalls(void)
{
    __cxa_vec_ctor(data_021f4ae8, SNOWMEN_LOOSE_BALLS, sizeof(SnowmenLooseBall), func_020b0aa8, func_020b0aa4);
    static_init_register(data_021f4ae8, func_020b0a88, &data_021f4adc);
}
CLEAN_AS(__sinit_020c6da8, StaticInit_SnowmenBalls)

/* The town's post source (town_posts.c): a post source with overlay 3's vtable. */
extern CollisionPostSource data_021f4b3c;
extern const CollisionPostSourceVtable data_ov003_0223a248;
extern StaticInitRecord data_021f4b70;
extern void func_020b3fe4(void *source); /* its destructor */

/* __sinit_020c6de0: the town's post source, constructed as a base post source and then given
 * its class's vtable (in overlay 3). */
void StaticInit_TownPostSource(void)
{
    CollisionPostSource_Construct(&data_021f4b3c);
    data_021f4b3c.vtable = &data_ov003_0223a248;
    static_init_register(&data_021f4b3c, func_020b3fe4, &data_021f4b70);
}
CLEAN_AS(__sinit_020c6de0, StaticInit_TownPostSource)

extern MessageReader data_021f4dac;
extern StaticInitRecord data_021f4c80;
extern void func_020b4070(void *reader); /* the reader's destructor */

/* __sinit_020c6e10: the message reader (message_reader.h). */
void StaticInit_MessageReader(void)
{
    MessageReader_Construct(&data_021f4dac);
    static_init_register(&data_021f4dac, func_020b4070, &data_021f4c80);
}
CLEAN_AS(__sinit_020c6e10, StaticInit_MessageReader)

/* The scenes' objects: the display hooks a scene on the field runs with (scene_process.c), the
 * view frustum (view_frustum.h), the touch screen's picks (touch_pick_shapes.h), the scene's
 * exit (scene_exit.h) and the saved and marked places (scene_place.h). */
extern DisplayFrameHooks data_021f693c;
extern const DisplayFrameHooksVtable data_020e550c;
extern ViewFrustum data_021f6a6c;
extern TouchPick data_021f6a14;
extern SceneExit data_021f69d0;
extern ScenePlace data_021f69a0, data_021f69b8;
extern StaticInitRecord data_021f6964, data_021f6970, data_021f697c, data_021f694c, data_021f6958;
extern void func_0203a9a8(void *frustum); /* the frustum's destructor */
extern void func_020b7e5c(void *pick);    /* the picks' destructor */
extern void func_020b649c(void *exit);    /* the exit's destructor */
extern void func_020b657c(void *place);   /* a place's destructor */

/* __sinit_020c6e38: the field's display hooks given their vtable, then the frustum, the picks,
 * the exit and the two places. */
void StaticInit_SceneObjects(void)
{
    data_021f693c.vtable = &data_020e550c;
    ViewFrustum_Construct(&data_021f6a6c);
    static_init_register(&data_021f6a6c, func_0203a9a8, &data_021f6964);
    TouchPick_Construct(&data_021f6a14);
    static_init_register(&data_021f6a14, func_020b7e5c, &data_021f6970);
    SceneExit_Construct(&data_021f69d0);
    static_init_register(&data_021f69d0, func_020b649c, &data_021f697c);
    ScenePlace_Construct(&data_021f69a0);
    static_init_register(&data_021f69a0, func_020b657c, &data_021f694c);
    ScenePlace_Construct(&data_021f69b8);
    static_init_register(&data_021f69b8, func_020b657c, &data_021f6958);
}
CLEAN_AS(__sinit_020c6e38, StaticInit_SceneObjects)

extern StaticInitColour data_021f6acc, data_021f6aec, data_021f6ae8, data_021f6ae4, data_021f6ae0, data_021f6adc;

/* __sinit_020c6ed8: the six colours of its source file. */
void StaticInit_Colours6ed8(void)
{
    static_init_colours(&data_021f6acc, &data_021f6aec, &data_021f6ae8, &data_021f6ae4, &data_021f6ae0, &data_021f6adc);
}
CLEAN_AS(__sinit_020c6ed8, StaticInit_Colours6ed8)

extern FieldLabel data_021f6b20;
extern StaticInitRecord data_021f6af4;
extern void func_020b8cec(void *label); /* the label's destructor */

/* __sinit_020c6f34: the field's label (field_label.h). */
void StaticInit_FieldLabel(void)
{
    FieldLabel_Construct(&data_021f6b20);
    static_init_register(&data_021f6b20, func_020b8cec, &data_021f6af4);
}
CLEAN_AS(__sinit_020c6f34, StaticInit_FieldLabel)

/* The transfer queues (transfer_queue.c): the VBlank's and the main loop's. */
extern List data_021f6ca0;
extern List data_021f6c98;

/* __sinit_020c6f5c: both transfer queues empty. The main loop's queue's address. */
int StaticInit_TransferQueues(void)
{
    data_021f6ca0.first = NULL;
    data_021f6ca0.last = NULL;
    data_021f6c98.first = NULL;
    data_021f6c98.last = NULL;
    return (int) (uintptr_t) &data_021f6c98;
}
CLEAN_AS(__sinit_020c6f5c, StaticInit_TransferQueues)

/* The sky (sky.h), its stars' palette (star_palette.h) and its objects (sky_objects.h), and
 * the sky objects' path length: six acres' width. */
#define STATIC_INIT_SKY_PATH_ACRES 6
extern StarPalette data_021f7280;
extern SkyObjects data_021f8b48;
extern const fx32 data_020ca0ec;
extern s32 data_021f6cdc;
extern StaticInitRecord data_021f6d20, data_021f6d14, data_021f6d08;
extern void func_020bb998(void *sky);     /* the sky's destructor */
extern void func_020b18a8(void *palette); /* the palette's destructor */
extern void func_020c1574(void *objects); /* the objects' destructor */

/* __sinit_020c6f74: the sky, its stars' palette, its objects and their path's length. */
void StaticInit_Sky(void)
{
    Sky_Construct(&data_021f75b0);
    static_init_register(&data_021f75b0, func_020bb998, &data_021f6d20);
    StarPalette_Construct(&data_021f7280);
    static_init_register(&data_021f7280, func_020b18a8, &data_021f6d14);
    SkyObjects_Construct(&data_021f8b48);
    static_init_register(&data_021f8b48, func_020c1574, &data_021f6d08);
    data_021f6cdc = STATIC_INIT_SKY_PATH_ACRES * data_020ca0ec;
}
CLEAN_AS(__sinit_020c6f74, StaticInit_Sky)

/* The first missing villager's colours and its states' entries and updates (missing_npc1.c). */
#define STATIC_INIT_MISSING1_FNS (MISSING_NPC1_STATES * 2)
extern StaticInitColour data_021fbbf4, data_021fbbe8, data_021fbbec, data_021fbbe4, data_021fbbf8, data_021fbbf0;
extern MemberPointer data_021fbbfc[STATIC_INIT_MISSING1_FNS];
extern const MemberPointer data_020e7b64, data_020e7b5c, data_020e7ae4, data_020e7aec, data_020e7b44, data_020e7b3c,
    data_020e7b34, data_020e7b14, data_020e7b24, data_020e7b2c, data_020e7b4c, data_020e7b54, data_020e7b04, data_020e7adc,
    data_020e7af4, data_020e7afc, data_020e7b0c, data_020e7b1c;

/* __sinit_020c6fe8: the six colours of missing_npc1.c and its states' member functions. */
void StaticInit_MissingNpc1(void)
{
    static const MemberPointer *const state_fns[STATIC_INIT_MISSING1_FNS] = {
        &data_020e7b64, &data_020e7b5c, &data_020e7ae4, &data_020e7aec, &data_020e7b44, &data_020e7b3c,
        &data_020e7b34, &data_020e7b14, &data_020e7b24, &data_020e7b2c, &data_020e7b4c, &data_020e7b54,
        &data_020e7b04, &data_020e7adc, &data_020e7af4, &data_020e7afc, &data_020e7b0c, &data_020e7b1c,
    };
    static_init_colours(&data_021fbbf4, &data_021fbbe8, &data_021fbbec, &data_021fbbe4, &data_021fbbf8, &data_021fbbf0);
    static_init_copy(data_021fbbfc, state_fns, STATIC_INIT_MISSING1_FNS);
}
CLEAN_AS(__sinit_020c6fe8, StaticInit_MissingNpc1)

/* The second missing villager's colours, its states' entries and updates (missing_npc2.c: one
 * table of 20 member pointers whose last four the ROM names data_021fbd58) and its two side
 * points (+-0.5, 0, 1.0). */
#define STATIC_INIT_MISSING2_FNS (MISSING_NPC2_STATES * 2)
#define STATIC_INIT_MISSING2_FIRST 16
#define STATIC_INIT_MISSING2_LAST (STATIC_INIT_MISSING2_FNS - STATIC_INIT_MISSING2_FIRST)
extern StaticInitColour data_021fbc98, data_021fbca4, data_021fbc9c, data_021fbc8c, data_021fbc90, data_021fbc94;
extern MemberPointer data_021fbcd8[STATIC_INIT_MISSING2_FIRST];
extern MemberPointer data_021fbd58[STATIC_INIT_MISSING2_LAST];
extern Vec3 data_021fbcc0[2];
extern StaticInitRecord data_021fbca8, data_021fbcb4;
extern const MemberPointer data_020e7d78, data_020e7d80, data_020e7da8, data_020e7da0, data_020e7d98, data_020e7d20,
    data_020e7d88, data_020e7d18, data_020e7d30, data_020e7d38, data_020e7d68, data_020e7d40, data_020e7d48, data_020e7d50,
    data_020e7d58, data_020e7d60, data_020e7d70, data_020e7d90, data_020e7d28, data_020e7d10;

/* __sinit_020c714c: the six colours of missing_npc2.c, its states' member functions, and its
 * two side points, each registered with an empty destructor. */
void StaticInit_MissingNpc2(void)
{
    static const MemberPointer *const first_fns[STATIC_INIT_MISSING2_FIRST] = {
        &data_020e7d78, &data_020e7d80, &data_020e7da8, &data_020e7da0, &data_020e7d98, &data_020e7d20,
        &data_020e7d88, &data_020e7d18, &data_020e7d30, &data_020e7d38, &data_020e7d68, &data_020e7d40,
        &data_020e7d48, &data_020e7d50, &data_020e7d58, &data_020e7d60,
    };
    static const MemberPointer *const last_fns[STATIC_INIT_MISSING2_LAST] = {
        &data_020e7d70,
        &data_020e7d90,
        &data_020e7d28,
        &data_020e7d10,
    };
    static_init_colours(&data_021fbc98, &data_021fbca4, &data_021fbc9c, &data_021fbc8c, &data_021fbc90, &data_021fbc94);
    static_init_copy(data_021fbcd8, first_fns, STATIC_INIT_MISSING2_FIRST);
    static_init_copy(data_021fbd58, last_fns, STATIC_INIT_MISSING2_LAST);
    static_init_vec(&data_021fbcc0[0], 0x800, 0, 0x1000);
    static_init_register(&data_021fbcc0[0], func_020012dc, &data_021fbca8);
    static_init_vec(&data_021fbcc0[1], -0x800, 0, 0x1000);
    static_init_register(&data_021fbcc0[1], func_020012dc, &data_021fbcb4);
}
CLEAN_AS(__sinit_020c714c, StaticInit_MissingNpc2)

/* The placing villager's states' entries and updates (npc_plc.c). */
#define STATIC_INIT_NPC_PLC_FNS (NPC_PLC_STATES * 2)
extern MemberPointer data_021fbd90[STATIC_INIT_NPC_PLC_FNS];
extern const MemberPointer data_020e7f78, data_020e7f90, data_020e7f50, data_020e7f58, data_020e7f70, data_020e7f60,
    data_020e7f80;

/* __sinit_020c7320: the placing villager's states' member functions (state 2 has no entry).
 * Their table's address. */
int StaticInit_NpcPlc(void)
{
    static const MemberPointer *const state_fns[STATIC_INIT_NPC_PLC_FNS] = {
        &data_020e7f78, &data_020e7f90, &data_020e7f50, &data_020e7f58,
        &__ptmf_null,   &data_020e7f70, &data_020e7f60, &data_020e7f80,
    };
    static_init_copy(data_021fbd90, state_fns, STATIC_INIT_NPC_PLC_FNS);
    return (int) (uintptr_t) data_021fbd90;
}
CLEAN_AS(__sinit_020c7320, StaticInit_NpcPlc)

/* __sinit_020c7398: nothing. */
void StaticInit_Nothing7398(void) {}
CLEAN_AS(__sinit_020c7398, StaticInit_Nothing7398)

/* A point at the origin that several objects use (camera_modes.c, caution_window.c, the
 * missing villagers). */
extern Vec3 data_021fbee8;
extern StaticInitRecord data_021fbedc;

/* __sinit_020c739c: the origin, registered with an empty destructor. */
void StaticInit_Origin(void)
{
    static_init_vec(&data_021fbee8, 0, 0, 0);
    static_init_register(&data_021fbee8, func_020012dc, &data_021fbedc);
}
CLEAN_AS(__sinit_020c739c, StaticInit_Origin)

/* __sinit_020c73d0: nothing. */
void StaticInit_Nothing73d0(void) {}
CLEAN_AS(__sinit_020c73d0, StaticInit_Nothing73d0)

/* The processes' tree and lists (autoload_2/process.c) and the member function each phase
 * calls on them: CONNECT on the tree, CREATE, EXECUTE, DRAW and DELETE on the lists. */
extern ProcessTree data_021fcff8;
extern ProcessList data_021fd014, data_021fd004, data_021fd024, data_021fd034;
extern const MemberFn data_0213e838, data_0213e848, data_0213e820, data_0213e840, data_0213e828;

static void static_init_process_list(ProcessList *list, const MemberFn *each)
{
    list->list.first = NULL;
    list->list.last = NULL;
    list->each = *each;
}

/* __sinit_020c73d4: the processes' tree and four lists empty, each with its phase's member
 * function. */
void StaticInit_Processes(void)
{
    data_021fcff8.each = data_0213e838;
    data_021fcff8.tree.top = NULL;
    static_init_process_list(&data_021fd014, &data_0213e848);
    static_init_process_list(&data_021fd004, &data_0213e820);
    static_init_process_list(&data_021fd024, &data_0213e840);
    static_init_process_list(&data_021fd034, &data_0213e828);
}
CLEAN_AS(__sinit_020c73d4, StaticInit_Processes)

extern SoundSystem data_021fd1bc;

/* __sinit_020c74b0: the sound system (autoload_2/sound_system.h); it is never destructed. */
void StaticInit_SoundSystem(void)
{
    SoundSystem_Construct(&data_021fd1bc);
}
CLEAN_AS(__sinit_020c74b0, StaticInit_SoundSystem)

/* The sounds' distance curve and the slopes of two speakers' volumes
 * (autoload_2/sound_position.c): the full volume, 127.0, over 0.6, 0.4 and 0.2. */
#define STATIC_INIT_FULL_VOLUME 0x7f000
#define STATIC_INIT_SPLIT 0x99a      /* 0.6 */
#define STATIC_INIT_SPLIT_REST 0x666 /* 0.4 */
#define STATIC_INIT_SPLIT_LOW 0x333  /* 0.2 */
extern SoundDistanceCurve data_021fd248;
extern fx32 data_021fd23c, data_021fd244, data_021fd240;
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* __sinit_020c74c4: the distance curve cleared, and the three slopes. */
void StaticInit_SoundPosition(void)
{
    SoundPosition_ClearCurve(&data_021fd248);
    data_021fd23c = FX_Div(STATIC_INIT_FULL_VOLUME, STATIC_INIT_SPLIT);
    data_021fd244 = FX_Div(STATIC_INIT_FULL_VOLUME, STATIC_INIT_SPLIT_REST);
    data_021fd240 = FX_Div(STATIC_INIT_FULL_VOLUME, STATIC_INIT_SPLIT_LOW);
}
CLEAN_AS(__sinit_020c74c4, StaticInit_SoundPosition)
