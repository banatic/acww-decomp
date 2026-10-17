/* Overlay 4's static initialisers (ov004_static_init.h). */
#include "ov004_static_init.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "dropped_items.h"
#include "main/camera_control.h" /* CameraView */
#include "main/item_texture.h"   /* ClothTexture_Construct */
#include "main/model_pool.h"     /* ModelPool_Init */
#include "main/scene_exit.h"     /* SceneExit_Init */
#include "member_pointer.h"
#include "museum_insects.h"
#include "museum_room_setup.h"
#include "room_objects.h"
#include "room_pushes.h"

/* ---- What the initialisers share */

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov004InitRecord {
    struct Ov004InitRecord *next;
    void *destruct;
    void *object;
} Ov004InitRecord;

/* A constructor or destructor as the game is handed it: always the game's function, never a
 * Clean one. */
typedef void Ov004InitFn(void *object);

extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* The destructors of objects with nothing to destruct (TrivialObject_Destruct) and of an item
 * code (TrivialObject_DestructItemCode); and the item code that is no item. */
extern void func_020012dc(void *object);
extern void func_020051b0(void *item);
#define OV004_INIT_NO_ITEM 0xfff1

/* The game's empty member pointer. */
extern const MemberPointer __ptmf_null;

/* `object` (NULL for an array its destructor finds itself) destructed by `destruct`. */
static void ov004_init_register(void *object, Ov004InitFn *destruct, Ov004InitRecord *record)
{
    __register_global_object(object, (void *) (uintptr_t) destruct, record);
}

/* `count` member pointers copied from the overlay's constants, in order. */
static void ov004_init_copy(MemberPointer *table, const MemberPointer *const *constants, int count)
{
    for (int i = 0; i < count; i++) {
        table[i] = *constants[i];
    }
}

/* An entry of a talk's steps (cafe_master.h's CafeMasterTalkStep, flea_market_buyer.h's
 * FleaMarketBuyerTalkStep): a member pointer and a flag of its own, which the initialiser
 * leaves as it is. */
typedef struct Ov004InitTalkStep {
    MemberPointer run;
    u8 flag;
    u8 unk_09[3];
} Ov004InitTalkStep;

/* The member pointers of `count` talk steps copied from the overlay's constants, in order. */
static void ov004_init_copy_talk(Ov004InitTalkStep *table, const MemberPointer *const *constants, int count)
{
    for (int i = 0; i < count; i++) {
        table[i].run = *constants[i];
    }
}

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct Ov004InitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} Ov004InitColour;

static void ov004_init_colour(Ov004InitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* The six colours several source files define for themselves: red, blue, yellow, green, cyan
 * and grey, in that order. */
static void ov004_init_colours(Ov004InitColour *red, Ov004InitColour *blue, Ov004InitColour *yellow, Ov004InitColour *green,
                               Ov004InitColour *cyan, Ov004InitColour *grey)
{
    ov004_init_colour(red, 31, 20, 20, 31);
    ov004_init_colour(blue, 20, 20, 31, 31);
    ov004_init_colour(yellow, 31, 31, 20, 31);
    ov004_init_colour(green, 20, 31, 20, 31);
    ov004_init_colour(cyan, 20, 31, 31, 31);
    ov004_init_colour(grey, 20, 24, 24, 31);
}

/* A point set and registered with an empty destructor. */
static void ov004_init_vec(Vec3 *point, fx32 x, fx32 y, fx32 z, Ov004InitRecord *record)
{
    point->x = x;
    point->y = y;
    point->z = z;
    ov004_init_register(point, func_020012dc, record);
}

/* A point of the ground plane, (x, 0, z), with its record. */
typedef struct Ov004InitPoint {
    Vec3 *point;
    fx32 x;
    fx32 z;
    Ov004InitRecord *record;
} Ov004InitPoint;

static void ov004_init_points(const Ov004InitPoint *points, int count)
{
    for (int i = 0; i < count; i++) {
        ov004_init_vec(points[i].point, points[i].x, 0, points[i].z, points[i].record);
    }
}

/* ---- The initialisers, in address order */

extern Ov004InitColour data_ov004_02256c4c, data_ov004_02256c6c, data_ov004_02256c7c, data_ov004_02256c48, data_ov004_02256c5c,
    data_ov004_02256c58;
extern Vec3 data_ov004_02256ecc, data_ov004_02256ed8, data_ov004_02256ee4, data_ov004_02256ef0, data_ov004_02256efc,
    data_ov004_02256f08, data_ov004_02256f14, data_ov004_02256f20, data_ov004_02256f2c, data_ov004_02256f38,
    data_ov004_02256f44, data_ov004_02256f50;
extern Ov004InitRecord data_ov004_02256cfc, data_ov004_02256d20, data_ov004_02256d50, data_ov004_02256d2c, data_ov004_02256d38,
    data_ov004_02256d44, data_ov004_02256ce4, data_ov004_02256cf0, data_ov004_02256d74, data_ov004_02256d80,
    data_ov004_02256d8c, data_ov004_02256d98;

/* __sinit_ov004_0224de7c: the six colours of its source file and twelve points of the ground
 * plane, each registered with an empty destructor: the corners of the square of side 2.0
 * about the origin (twice), two more at x 3.0, and the corners of the square of side 4.0. */
void Ov004Init_Corners(void)
{
    static const Ov004InitPoint points[12] = {
        {&data_ov004_02256ecc, -0x1000, -0x1000, &data_ov004_02256cfc},
        {&data_ov004_02256ed8, -0x1000, 0x1000, &data_ov004_02256d20},
        {&data_ov004_02256ee4, 0x1000, 0x1000, &data_ov004_02256d50},
        {&data_ov004_02256ef0, 0x1000, -0x1000, &data_ov004_02256d2c},
        {&data_ov004_02256efc, -0x1000, -0x1000, &data_ov004_02256d38},
        {&data_ov004_02256f08, -0x1000, 0x1000, &data_ov004_02256d44},
        {&data_ov004_02256f14, 0x3000, 0x1000, &data_ov004_02256ce4},
        {&data_ov004_02256f20, 0x3000, -0x1000, &data_ov004_02256cf0},
        {&data_ov004_02256f2c, -0x2000, -0x2000, &data_ov004_02256d74},
        {&data_ov004_02256f38, -0x2000, 0x2000, &data_ov004_02256d80},
        {&data_ov004_02256f44, 0x2000, 0x2000, &data_ov004_02256d8c},
        {&data_ov004_02256f50, 0x2000, -0x2000, &data_ov004_02256d98},
    };
    ov004_init_colours(&data_ov004_02256c4c, &data_ov004_02256c6c, &data_ov004_02256c7c, &data_ov004_02256c48,
                       &data_ov004_02256c5c, &data_ov004_02256c58);
    ov004_init_points(points, 12);
}
CLEAN_AS(__sinit_ov004_0224de7c, Ov004Init_Corners)

extern Vec3 data_ov004_022572c4, data_ov004_022572d0, data_ov004_022572dc, data_ov004_022572e8, data_ov004_02257100,
    data_ov004_022572f4, data_ov004_02257300;
extern Ov004InitRecord data_ov004_022570c4, data_ov004_022570d0, data_ov004_022570dc, data_ov004_022570e8, data_ov004_022570f4,
    data_ov004_0225710c, data_ov004_02257118, data_ov004_022570b8;
/* The music item a player started in a villager's house (music_player.c). */
extern u16 data_ov004_02256fec;

/* __sinit_ov004_0224e058: seven points of the ground plane, each registered with an empty
 * destructor, then the music player's started item set to none and registered with the item
 * code's destructor. */
void Ov004Init_MusicPlayer(void)
{
    static const Ov004InitPoint points[7] = {
        {&data_ov004_022572c4, 0x2000, 0x2000, &data_ov004_022570c4},
        {&data_ov004_022572d0, 0x2000, -0x2000, &data_ov004_022570d0},
        {&data_ov004_022572dc, 0x1000, 0x3000, &data_ov004_022570dc},
        {&data_ov004_022572e8, 0x1000, -0x3000, &data_ov004_022570e8},
        {&data_ov004_02257100, 0, 0, &data_ov004_022570f4},
        {&data_ov004_022572f4, -0x1000, -0x1000, &data_ov004_0225710c},
        {&data_ov004_02257300, -0x1000, 0x1000, &data_ov004_02257118},
    };
    ov004_init_points(points, 7);
    data_ov004_02256fec = OV004_INIT_NO_ITEM;
    ov004_init_register(&data_ov004_02256fec, func_020051b0, &data_ov004_022570b8);
}
CLEAN_AS(__sinit_ov004_0224e058, Ov004Init_MusicPlayer)

extern Ov004InitColour data_ov004_022577bc, data_ov004_022577c4, data_ov004_022577c8, data_ov004_022577b0, data_ov004_022577c0,
    data_ov004_022577b4;

/* __sinit_ov004_0224e168: the six colours of its source file. */
void Ov004Init_Colours022577b0(void)
{
    ov004_init_colours(&data_ov004_022577bc, &data_ov004_022577c4, &data_ov004_022577c8, &data_ov004_022577b0,
                       &data_ov004_022577c0, &data_ov004_022577b4);
}
CLEAN_AS(__sinit_ov004_0224e168, Ov004Init_Colours022577b0)

extern Ov004InitColour data_ov004_02257934, data_ov004_02257924, data_ov004_0225792c, data_ov004_0225791c, data_ov004_02257910,
    data_ov004_02257920;

/* __sinit_ov004_0224e1c4: the six colours of its source file. */
void Ov004Init_Colours02257910(void)
{
    ov004_init_colours(&data_ov004_02257934, &data_ov004_02257924, &data_ov004_0225792c, &data_ov004_0225791c,
                       &data_ov004_02257910, &data_ov004_02257920);
}
CLEAN_AS(__sinit_ov004_0224e1c4, Ov004Init_Colours02257910)

extern Ov004InitColour data_ov004_02257a00, data_ov004_02257a1c, data_ov004_02257a04, data_ov004_022579fc, data_ov004_02257a0c,
    data_ov004_02257a10;

/* __sinit_ov004_0224e220: the six colours of its source file. */
void Ov004Init_Colours022579fc(void)
{
    ov004_init_colours(&data_ov004_02257a00, &data_ov004_02257a1c, &data_ov004_02257a04, &data_ov004_022579fc,
                       &data_ov004_02257a0c, &data_ov004_02257a10);
}
CLEAN_AS(__sinit_ov004_0224e220, Ov004Init_Colours022579fc)

extern Ov004InitColour data_ov004_02257bc8, data_ov004_02257bd8, data_ov004_02257bbc, data_ov004_02257bc0, data_ov004_02257bcc,
    data_ov004_02257bd4;

/* __sinit_ov004_0224e27c: the six colours of its source file. */
void Ov004Init_Colours02257bbc(void)
{
    ov004_init_colours(&data_ov004_02257bc8, &data_ov004_02257bd8, &data_ov004_02257bbc, &data_ov004_02257bc0,
                       &data_ov004_02257bcc, &data_ov004_02257bd4);
}
CLEAN_AS(__sinit_ov004_0224e27c, Ov004Init_Colours02257bbc)

/* The room villager's member functions (room_villager.c) and the tiles a quarter turn moves it
 * by. */
#define OV004_INIT_ROOM_VILLAGER_FNS 10
extern MemberPointer data_ov004_02257cb8[OV004_INIT_ROOM_VILLAGER_FNS];
extern const MemberPointer data_ov004_022539a4, data_ov004_02253944, data_ov004_02253994, data_ov004_0225398c,
    data_ov004_02253964, data_ov004_0225397c, data_ov004_02253974, data_ov004_0225396c, data_ov004_02253934,
    data_ov004_0225394c;
typedef struct Ov004InitTileStep {
    s32 x;
    s32 z;
} Ov004InitTileStep;
extern Ov004InitTileStep data_ov004_02257c98[4];

/* __sinit_ov004_0224e2d8: the room villager's member functions, and the tile steps of its four
 * quarter turns: (0, 1), (1, 0), (0, -1), (-1, 0).
 * QUIRK: it answers the address of the last step (left in the result register). */
int Ov004Init_RoomVillager(void)
{
    static const MemberPointer *const fns[OV004_INIT_ROOM_VILLAGER_FNS] = {
        &data_ov004_022539a4, &data_ov004_02253944, &data_ov004_02253994, &data_ov004_0225398c, &data_ov004_02253964,
        &data_ov004_0225397c, &data_ov004_02253974, &data_ov004_0225396c, &data_ov004_02253934, &data_ov004_0225394c};
    ov004_init_copy(data_ov004_02257cb8, fns, OV004_INIT_ROOM_VILLAGER_FNS);
    data_ov004_02257c98[0].x = 0;
    data_ov004_02257c98[0].z = 1;
    data_ov004_02257c98[1].x = 1;
    data_ov004_02257c98[1].z = 0;
    data_ov004_02257c98[2].x = 0;
    data_ov004_02257c98[2].z = -1;
    data_ov004_02257c98[3].x = -1;
    data_ov004_02257c98[3].z = 0;
    return (int) (uintptr_t) &data_ov004_02257c98[3];
}
CLEAN_AS(__sinit_ov004_0224e2d8, Ov004Init_RoomVillager)

/* The flea market villager's member functions (flea_market_villager.c). */
#define OV004_INIT_FLEA_MARKET_VILLAGER_FNS 16
extern MemberPointer data_ov004_02257d58[OV004_INIT_FLEA_MARKET_VILLAGER_FNS];
extern const MemberPointer data_ov004_02253a8c, data_ov004_02253afc, data_ov004_02253af4, data_ov004_02253ac4,
    data_ov004_02253ae4, data_ov004_02253adc, data_ov004_02253ad4, data_ov004_02253acc, data_ov004_02253aa4,
    data_ov004_02253abc, data_ov004_02253ab4, data_ov004_02253aac, data_ov004_02253aec, data_ov004_02253a9c,
    data_ov004_02253a94;

/* __sinit_ov004_0224e39c: the flea market villager's member functions (flea_market_villager.c).
 * QUIRK: it answers the table's address (left in the result register). */
int Ov004Init_FleaMarketVillager(void)
{
    static const MemberPointer *const fns[OV004_INIT_FLEA_MARKET_VILLAGER_FNS] = {
        &data_ov004_02253a8c, &data_ov004_02253afc, &data_ov004_02253af4, &data_ov004_02253ac4,
        &__ptmf_null,         &data_ov004_02253ae4, &data_ov004_02253adc, &data_ov004_02253ad4,
        &data_ov004_02253acc, &data_ov004_02253aa4, &data_ov004_02253abc, &data_ov004_02253ab4,
        &data_ov004_02253aac, &data_ov004_02253aec, &data_ov004_02253a9c, &data_ov004_02253a94};
    ov004_init_copy(data_ov004_02257d58, fns, OV004_INIT_FLEA_MARKET_VILLAGER_FNS);
    return (int) (uintptr_t) data_ov004_02257d58;
}
CLEAN_AS(__sinit_ov004_0224e39c, Ov004Init_FleaMarketVillager)

/* The flea market buyer's talk steps, its member functions and the two of data_ov004_02257f10
 * (flea_market_buyer.c). */
extern Ov004InitTalkStep data_ov004_02257dd8[2];
extern MemberPointer data_ov004_02257e90[16];
extern MemberPointer data_ov004_02257f10[2];
extern const MemberPointer data_ov004_02253ce0, data_ov004_02253cd0, data_ov004_02253d18, data_ov004_02253cd8,
    data_ov004_02253cc8, data_ov004_02253d58, data_ov004_02253d50, data_ov004_02253d48, data_ov004_02253d40,
    data_ov004_02253d38, data_ov004_02253d30, data_ov004_02253d20, data_ov004_02253d28, data_ov004_02253ce8,
    data_ov004_02253d10, data_ov004_02253d08, data_ov004_02253d00, data_ov004_02253cf8, data_ov004_02253cf0;

/* __sinit_ov004_0224e484: the flea market buyer's talk steps (none, then the offer), its
 * member functions and the two of data_ov004_02257f10. */
void Ov004Init_FleaMarketBuyer(void)
{
    static const MemberPointer *const talk[2] = {&__ptmf_null, &data_ov004_02253ce0};
    static const MemberPointer *const fns[16] = {
        &data_ov004_02253cd0, &data_ov004_02253d18, &data_ov004_02253cd8, &data_ov004_02253cc8,
        &data_ov004_02253d58, &data_ov004_02253d50, &data_ov004_02253d48, &data_ov004_02253d40,
        &data_ov004_02253d38, &data_ov004_02253d30, &data_ov004_02253d20, &data_ov004_02253d28,
        &data_ov004_02253ce8, &data_ov004_02253d10, &data_ov004_02253d08, &data_ov004_02253d00};
    static const MemberPointer *const more[2] = {&data_ov004_02253cf8, &data_ov004_02253cf0};
    ov004_init_copy_talk(data_ov004_02257dd8, talk, 2);
    ov004_init_copy(data_ov004_02257e90, fns, 16);
    ov004_init_copy(data_ov004_02257f10, more, 2);
}
CLEAN_AS(__sinit_ov004_0224e484, Ov004Init_FleaMarketBuyer)

/* The third shop villager's member functions (shop3_villager.c). */
#define OV004_INIT_SHOP3VILLAGER_FNS 6
extern MemberPointer data_ov004_02257f48[OV004_INIT_SHOP3VILLAGER_FNS];
extern const MemberPointer data_ov004_02253efc, data_ov004_02253f0c, data_ov004_02253f1c, data_ov004_02253f14,
    data_ov004_02253f04;

/* __sinit_ov004_0224e5b0: the third shop villager's member functions (shop3_villager.c).
 * QUIRK: it answers the table's address (left in the result register). */
int Ov004Init_Shop3Villager(void)
{
    static const MemberPointer *const fns[OV004_INIT_SHOP3VILLAGER_FNS] = {&data_ov004_02253efc, &data_ov004_02253f0c,
                                                                           &__ptmf_null,         &data_ov004_02253f1c,
                                                                           &data_ov004_02253f14, &data_ov004_02253f04};
    ov004_init_copy(data_ov004_02257f48, fns, OV004_INIT_SHOP3VILLAGER_FNS);
    return (int) (uintptr_t) data_ov004_02257f48;
}
CLEAN_AS(__sinit_ov004_0224e5b0, Ov004Init_Shop3Villager)

extern Ov004InitColour data_ov004_02257f78, data_ov004_02257f80, data_ov004_02257f88, data_ov004_02257f84, data_ov004_02257f94,
    data_ov004_02257f98;

/* __sinit_ov004_0224e60c: the six colours of its source file. */
void Ov004Init_Colours02257f78(void)
{
    ov004_init_colours(&data_ov004_02257f78, &data_ov004_02257f80, &data_ov004_02257f88, &data_ov004_02257f84,
                       &data_ov004_02257f94, &data_ov004_02257f98);
}
CLEAN_AS(__sinit_ov004_0224e60c, Ov004Init_Colours02257f78)

/* The tailor sister's member functions (tailor_sister.c). */
#define OV004_INIT_TAILOR_SISTER_FNS 14
extern MemberPointer data_ov004_0225806c[OV004_INIT_TAILOR_SISTER_FNS];
extern const MemberPointer data_ov004_022542f8, data_ov004_022542d8, data_ov004_022542f0, data_ov004_02254320,
    data_ov004_02254330, data_ov004_02254328, data_ov004_02254300, data_ov004_02254318, data_ov004_02254308,
    data_ov004_02254310, data_ov004_022542c8, data_ov004_022542d0, data_ov004_022542e0, data_ov004_022542e8;

/* __sinit_ov004_0224e668: the tailor sister's member functions (tailor_sister.c).
 * QUIRK: it answers the table's address (left in the result register). */
int Ov004Init_TailorSister(void)
{
    static const MemberPointer *const fns[OV004_INIT_TAILOR_SISTER_FNS] = {
        &data_ov004_022542f8, &data_ov004_022542d8, &data_ov004_022542f0, &data_ov004_02254320, &data_ov004_02254330,
        &data_ov004_02254328, &data_ov004_02254300, &data_ov004_02254318, &data_ov004_02254308, &data_ov004_02254310,
        &data_ov004_022542c8, &data_ov004_022542d0, &data_ov004_022542e0, &data_ov004_022542e8};
    ov004_init_copy(data_ov004_0225806c, fns, OV004_INIT_TAILOR_SISTER_FNS);
    return (int) (uintptr_t) data_ov004_0225806c;
}
CLEAN_AS(__sinit_ov004_0224e668, Ov004Init_TailorSister)

/* The cafe master's talk sequences and member functions (cafe_master.c). */
extern Ov004InitTalkStep data_ov004_02254618[4];
extern MemberPointer data_ov004_022580e0[16];
extern const MemberPointer data_ov004_022545a4, data_ov004_02254544, data_ov004_0225451c, data_ov004_0225459c,
    data_ov004_02254534, data_ov004_0225458c, data_ov004_02254584, data_ov004_0225457c, data_ov004_0225452c,
    data_ov004_0225455c, data_ov004_02254564, data_ov004_02254574, data_ov004_0225456c, data_ov004_0225454c,
    data_ov004_0225450c, data_ov004_0225453c, data_ov004_02254514, data_ov004_02254524, data_ov004_02254554;

/* __sinit_ov004_0224e734: the cafe master's talk steps (the first none) and member functions.
 * QUIRK: it answers the member functions' table's address (left in the result register). */
int Ov004Init_CafeMaster(void)
{
    static const MemberPointer *const talk[4] = {&__ptmf_null, &data_ov004_022545a4, &data_ov004_02254544,
                                                 &data_ov004_0225451c};
    static const MemberPointer *const fns[16] = {
        &data_ov004_0225459c, &data_ov004_02254534, &data_ov004_0225458c, &data_ov004_02254584,
        &data_ov004_0225457c, &data_ov004_0225452c, &data_ov004_0225455c, &data_ov004_02254564,
        &data_ov004_02254574, &data_ov004_0225456c, &data_ov004_0225454c, &data_ov004_0225450c,
        &data_ov004_0225453c, &data_ov004_02254514, &data_ov004_02254524, &data_ov004_02254554};
    ov004_init_copy_talk(data_ov004_02254618, talk, 4);
    ov004_init_copy(data_ov004_022580e0, fns, 16);
    return (int) (uintptr_t) data_ov004_022580e0;
}
CLEAN_AS(__sinit_ov004_0224e734, Ov004Init_CafeMaster)

/* The second gatekeeper's talk steps and member functions (gatekeeper2.c). */
extern Ov004InitTalkStep data_ov004_02258160[4];
extern MemberPointer data_ov004_02258190[14];
extern const MemberPointer data_ov004_022547a0, data_ov004_022547c8, data_ov004_022547a8, data_ov004_02254810,
    data_ov004_02254808, data_ov004_02254800, data_ov004_022547f8, data_ov004_022547e8, data_ov004_022547f0,
    data_ov004_022547e0, data_ov004_022547b8, data_ov004_022547d0, data_ov004_02254798, data_ov004_022547c0,
    data_ov004_022547b0, data_ov004_022547d8, data_ov004_02254818;

/* __sinit_ov004_0224e85c: the second gatekeeper's talk steps (the first none) and member functions.
 * QUIRK: it answers the member functions' table's address (left in the result register). */
int Ov004Init_Gatekeeper2(void)
{
    static const MemberPointer *const talk[4] = {&__ptmf_null, &data_ov004_022547a0, &data_ov004_022547c8,
                                                 &data_ov004_022547a8};
    static const MemberPointer *const fns[14] = {
        &data_ov004_02254810, &data_ov004_02254808, &data_ov004_02254800, &data_ov004_022547f8, &data_ov004_022547e8,
        &data_ov004_022547f0, &data_ov004_022547e0, &data_ov004_022547b8, &data_ov004_022547d0, &data_ov004_02254798,
        &data_ov004_022547c0, &data_ov004_022547b0, &data_ov004_022547d8, &data_ov004_02254818};
    ov004_init_copy_talk(data_ov004_02258160, talk, 4);
    ov004_init_copy(data_ov004_02258190, fns, 14);
    return (int) (uintptr_t) data_ov004_02258190;
}
CLEAN_AS(__sinit_ov004_0224e85c, Ov004Init_Gatekeeper2)

/* The TTI villager's member functions (tti_npc.c). */
#define OV004_INIT_TTI_NPC_FNS 4
extern MemberPointer data_ov004_02258204[OV004_INIT_TTI_NPC_FNS];
extern const MemberPointer data_ov004_022549c4, data_ov004_022549cc, data_ov004_022549d4, data_ov004_022549dc;

/* __sinit_ov004_0224e968: the TTI villager's member functions (tti_npc.c).
 * QUIRK: it answers the table's address (left in the result register). */
int Ov004Init_TtiNpc(void)
{
    static const MemberPointer *const fns[OV004_INIT_TTI_NPC_FNS] = {&data_ov004_022549c4, &data_ov004_022549cc,
                                                                     &data_ov004_022549d4, &data_ov004_022549dc};
    ov004_init_copy(data_ov004_02258204, fns, OV004_INIT_TTI_NPC_FNS);
    return (int) (uintptr_t) data_ov004_02258204;
}
CLEAN_AS(__sinit_ov004_0224e968, Ov004Init_TtiNpc)

extern Ov004InitColour data_ov004_02258288, data_ov004_0225828c, data_ov004_02258280, data_ov004_02258284, data_ov004_02258290,
    data_ov004_02258278;

/* __sinit_ov004_0224e9a8: the six colours of its source file. */
void Ov004Init_Colours02258278(void)
{
    ov004_init_colours(&data_ov004_02258288, &data_ov004_0225828c, &data_ov004_02258280, &data_ov004_02258284,
                       &data_ov004_02258290, &data_ov004_02258278);
}
CLEAN_AS(__sinit_ov004_0224e9a8, Ov004Init_Colours02258278)

/* The cafe's points (cafe_props.c). */
extern Vec3 data_ov004_0225836c, data_ov004_02258384, data_ov004_0225839c, data_ov004_02258318, data_ov004_02258330,
    data_ov004_02258348;
extern Ov004InitRecord data_ov004_02258354, data_ov004_02258378, data_ov004_02258390, data_ov004_02258360, data_ov004_02258324,
    data_ov004_0225833c;

/* __sinit_ov004_0224ea04: the cafe's six points, each registered with an empty destructor. */
void Ov004Init_CafePoints(void)
{
    ov004_init_vec(&data_ov004_0225836c, 0, 0, 0, &data_ov004_02258354);
    ov004_init_vec(&data_ov004_02258384, 0x17700, 0x1900, 0x15800, &data_ov004_02258378);
    ov004_init_vec(&data_ov004_0225839c, 0x17800, 0x1a00, 0x13400, &data_ov004_02258390);
    ov004_init_vec(&data_ov004_02258318, 0x10c00, 0x1600, 0x1b000, &data_ov004_02258360);
    ov004_init_vec(&data_ov004_02258330, 0x16a00, 0x1900, 0x13000, &data_ov004_02258324);
    ov004_init_vec(&data_ov004_02258348, 0x16600, 0x1900, 0x11e00, &data_ov004_0225833c);
}
CLEAN_AS(__sinit_ov004_0224ea04, Ov004Init_CafePoints)

extern Ov004InitColour data_ov004_02258448, data_ov004_02258458, data_ov004_02258454, data_ov004_0225845c, data_ov004_02258450,
    data_ov004_0225844c;

/* __sinit_ov004_0224eaf8: the six colours of its source file. */
void Ov004Init_Colours02258448(void)
{
    ov004_init_colours(&data_ov004_02258448, &data_ov004_02258458, &data_ov004_02258454, &data_ov004_0225845c,
                       &data_ov004_02258450, &data_ov004_0225844c);
}
CLEAN_AS(__sinit_ov004_0224eaf8, Ov004Init_Colours02258448)

extern Ov004InitColour data_ov004_022584b0, data_ov004_022584a4, data_ov004_022584a0, data_ov004_022584ac, data_ov004_0225849c,
    data_ov004_0225848c;

/* __sinit_ov004_0224eb54: the six colours of its source file. */
void Ov004Init_Colours0225848c(void)
{
    ov004_init_colours(&data_ov004_022584b0, &data_ov004_022584a4, &data_ov004_022584a0, &data_ov004_022584ac,
                       &data_ov004_0225849c, &data_ov004_0225848c);
}
CLEAN_AS(__sinit_ov004_0224eb54, Ov004Init_Colours0225848c)

/* The tailor's cloth model (tailor_object.c) and the game's destructor of it
 * (ClothTexture_Destruct). */
extern DesignModel data_ov004_022585ac;
extern Ov004InitRecord data_ov004_02258560;
extern void func_0203d224(void *file);

/* __sinit_ov004_0224ebb0: the tailor's cloth model constructed and registered. */
void Ov004Init_TailorCloth(void)
{
    ClothTexture_Construct(&data_ov004_022585ac);
    ov004_init_register(&data_ov004_022585ac, func_0203d224, &data_ov004_02258560);
}
CLEAN_AS(__sinit_ov004_0224ebb0, Ov004Init_TailorCloth)

/* The telephone's states (rmo_telephone.c): a member pointer each. */
#define OV004_INIT_TELEPHONE_FNS 30
extern Ov004InitColour data_ov004_022588d4, data_ov004_022588c4, data_ov004_022588cc, data_ov004_022588c0, data_ov004_022588bc,
    data_ov004_022588d0;
extern MemberPointer data_ov004_022588d8[OV004_INIT_TELEPHONE_FNS];
extern const MemberPointer data_ov004_0225587c, data_ov004_02255874, data_ov004_02255854, data_ov004_0225585c,
    data_ov004_0225586c, data_ov004_02255884, data_ov004_02255894, data_ov004_0225589c, data_ov004_0225583c,
    data_ov004_02255834, data_ov004_0225582c, data_ov004_022557c4, data_ov004_0225581c, data_ov004_02255814,
    data_ov004_022557dc, data_ov004_022557e4, data_ov004_022557f4, data_ov004_022557fc, data_ov004_0225580c,
    data_ov004_02255844, data_ov004_0225584c, data_ov004_02255864, data_ov004_0225588c, data_ov004_022558a4,
    data_ov004_022557bc, data_ov004_022557cc, data_ov004_022557d4, data_ov004_022557ec, data_ov004_02255804,
    data_ov004_02255824;

/* __sinit_ov004_0224ebd8: the six colours of its source file and the telephone's states'
 * member functions. */
void Ov004Init_Telephone(void)
{
    static const MemberPointer *const fns[OV004_INIT_TELEPHONE_FNS] = {
        &data_ov004_0225587c, &data_ov004_02255874, &data_ov004_02255854, &data_ov004_0225585c, &data_ov004_0225586c,
        &data_ov004_02255884, &data_ov004_02255894, &data_ov004_0225589c, &data_ov004_0225583c, &data_ov004_02255834,
        &data_ov004_0225582c, &data_ov004_022557c4, &data_ov004_0225581c, &data_ov004_02255814, &data_ov004_022557dc,
        &data_ov004_022557e4, &data_ov004_022557f4, &data_ov004_022557fc, &data_ov004_0225580c, &data_ov004_02255844,
        &data_ov004_0225584c, &data_ov004_02255864, &data_ov004_0225588c, &data_ov004_022558a4, &data_ov004_022557bc,
        &data_ov004_022557cc, &data_ov004_022557d4, &data_ov004_022557ec, &data_ov004_02255804, &data_ov004_02255824};
    ov004_init_colours(&data_ov004_022588d4, &data_ov004_022588c4, &data_ov004_022588cc, &data_ov004_022588c0,
                       &data_ov004_022588bc, &data_ov004_022588d0);
    ov004_init_copy(data_ov004_022588d8, fns, OV004_INIT_TELEPHONE_FNS);
}
CLEAN_AS(__sinit_ov004_0224ebd8, Ov004Init_Telephone)

/* The room shell's point of node "hasu1" and the code its getters answer while there is none
 * (room_shell.c). */
extern Vec3 data_ov004_02258a30;
extern u16 data_ov004_022589ec;
extern Ov004InitRecord data_ov004_02258ad8, data_ov004_02258a84;

/* __sinit_ov004_0224ede4: the room shell's point at the origin and its code set to no item,
 * each registered. */
void Ov004Init_RoomShell(void)
{
    ov004_init_vec(&data_ov004_02258a30, 0, 0, 0, &data_ov004_02258ad8);
    data_ov004_022589ec = OV004_INIT_NO_ITEM;
    ov004_init_register(&data_ov004_022589ec, func_020051b0, &data_ov004_02258a84);
}
CLEAN_AS(__sinit_ov004_0224ede4, Ov004Init_RoomShell)

/* The dropped items (dropped_items.h), and the game's constructor and destructor of one and of
 * the array. */
extern DroppedItem data_ov004_02258af4[DROPPED_ITEMS];
extern Ov004InitRecord data_ov004_02258ae8;
extern void func_ov004_02234008(void *drop);  /* DroppedItem_Construct */
extern void func_ov004_02233ff4(void *drop);  /* DroppedItem_Destruct */
extern void func_ov004_02233fd8(void *items); /* DroppedItems_Destruct */

/* __sinit_ov004_0224ee2c: the fifteen dropped items constructed and the array registered. */
void Ov004Init_DroppedItems(void)
{
    __cxa_vec_ctor(data_ov004_02258af4, DROPPED_ITEMS, sizeof(DroppedItem), func_ov004_02234008, func_ov004_02233ff4);
    ov004_init_register(data_ov004_02258af4, func_ov004_02233fd8, &data_ov004_02258ae8);
}
CLEAN_AS(__sinit_ov004_0224ee2c, Ov004Init_DroppedItems)

/* The museum's aquarium: its two tanks' points and its fish's tables of member functions. */
extern Vec3 data_ov004_022593dc, data_ov004_022593c4;
extern Ov004InitRecord data_ov004_022593d0, data_ov004_022593e8;
extern MemberPointer data_ov004_02259424[4]; /* aquarium_fish.c */
extern MemberPointer data_ov004_0225949c[7]; /* aquarium_fish.c */
extern MemberPointer data_ov004_0225946c[6]; /* aquarium_fish_classes.c */
extern MemberPointer data_ov004_02259444[5]; /* aquarium_fish_classes.c */
extern MemberPointer data_ov004_022593f4[3]; /* aquarium_fish_kinds.c */
extern MemberPointer data_ov004_0225940c[3]; /* museum_aquarium.c */
extern const MemberPointer data_ov004_02255c50, data_ov004_02255c58, data_ov004_02255c40, data_ov004_02255cc8,
    data_ov004_02255c60, data_ov004_02255c88, data_ov004_02255d10, data_ov004_02255c70, data_ov004_02255d18,
    data_ov004_02255c68, data_ov004_02255ca0, data_ov004_02255d08, data_ov004_02255cd0, data_ov004_02255cf8,
    data_ov004_02255cd8, data_ov004_02255ce8, data_ov004_02255cc0, data_ov004_02255cf0, data_ov004_02255ce0,
    data_ov004_02255c48, data_ov004_02255cb8, data_ov004_02255c38, data_ov004_02255ca8, data_ov004_02255c98,
    data_ov004_02255c90, data_ov004_02255c78, data_ov004_02255c80, data_ov004_02255cb0;

/* __sinit_ov004_0224ee64: the aquarium's two tank points, (17.0, 0, 21.0) and (17.0, 0, 7.0),
 * each registered with an empty destructor, then its fish's member functions. */
void Ov004Init_Aquarium(void)
{
    static const MemberPointer *const fns_9424[4] = {&data_ov004_02255c50, &data_ov004_02255c58, &data_ov004_02255c40,
                                                     &data_ov004_02255cc8};
    static const MemberPointer *const fns_949c[7] = {&data_ov004_02255c60, &data_ov004_02255c88, &data_ov004_02255d10,
                                                     &data_ov004_02255c70, &data_ov004_02255d18, &data_ov004_02255c68,
                                                     &data_ov004_02255ca0};
    static const MemberPointer *const fns_946c[6] = {&data_ov004_02255d08, &data_ov004_02255cd0, &data_ov004_02255cf8,
                                                     &data_ov004_02255cd8, &data_ov004_02255ce8, &data_ov004_02255cc0};
    static const MemberPointer *const fns_9444[5] = {&data_ov004_02255cf0, &data_ov004_02255ce0, &data_ov004_02255c48,
                                                     &data_ov004_02255cb8, &data_ov004_02255c38};
    static const MemberPointer *const fns_93f4[3] = {&data_ov004_02255ca8, &data_ov004_02255c98, &data_ov004_02255c90};
    static const MemberPointer *const fns_940c[3] = {&data_ov004_02255c78, &data_ov004_02255c80, &data_ov004_02255cb0};
    ov004_init_vec(&data_ov004_022593dc, 0x11000, 0, 0x15000, &data_ov004_022593d0);
    ov004_init_vec(&data_ov004_022593c4, 0x11000, 0, 0x7000, &data_ov004_022593e8);
    ov004_init_copy(data_ov004_02259424, fns_9424, 4);
    ov004_init_copy(data_ov004_0225949c, fns_949c, 7);
    ov004_init_copy(data_ov004_0225946c, fns_946c, 6);
    ov004_init_copy(data_ov004_02259444, fns_9444, 5);
    ov004_init_copy(data_ov004_022593f4, fns_93f4, 3);
    ov004_init_copy(data_ov004_0225940c, fns_940c, 3);
}
CLEAN_AS(__sinit_ov004_0224ee64, Ov004Init_Aquarium)

/* The room's objects (room_objects.h): the pool of models, the table of objects, the heap, the
 * object at data_ov004_022596b0, the grid and the pushes, the square of an acre's depth, and
 * where the last object taken away stands; the game's destructors of them. */
extern ModelPool data_ov004_02259698;
extern RoomObject *data_ov004_02259714[];
extern struct Heap *data_ov004_022595c4;
extern u8 data_ov004_022596b0[];
extern u8 data_ov004_02259804[];
extern RoomPush data_ov004_02259784[];
extern s32 data_ov004_022595d8;
extern Vec3 data_ov004_0225967c;
extern int data_020ca0e8; /* an acre's depth */
extern Ov004InitRecord data_ov004_02259634, data_ov004_022595e0, data_ov004_022595ec, data_ov004_022595f8, data_ov004_02259604,
    data_ov004_02259610, data_ov004_02259670;
extern void *func_ov004_0223d2f8(void *object);
extern void func_0209d2b4(void *pool);        /* ModelPool_Destruct */
extern void func_ov004_0223ce70(void *table); /* RoomObjects_TableDestruct */
extern void func_ov004_0223cefc(void *heap);  /* RoomObjects_HeapDestruct */
extern void func_ov004_0223d2d4(void *object);
extern void func_ov004_0223cd3c(void *grid);   /* RoomObjects_GridDestruct */
extern void func_ov004_0223c7d8(void *pushes); /* RoomPushes_Destruct */

/* __sinit_ov004_0224f068: the room's model pool, table of objects, heap, the object at
 * data_ov004_022596b0, grid and pushes constructed and registered; the square of an acre's
 * depth kept (20.12, rounded); the vanish point at the origin, registered with an empty
 * destructor. */
void Ov004Init_RoomObjects(void)
{
    ModelPool_Init(&data_ov004_02259698);
    ov004_init_register(&data_ov004_02259698, func_0209d2b4, &data_ov004_02259634);
    RoomObjects_TableConstruct(data_ov004_02259714);
    ov004_init_register(data_ov004_02259714, func_ov004_0223ce70, &data_ov004_022595e0);
    RoomObjects_HeapConstruct(&data_ov004_022595c4);
    ov004_init_register(&data_ov004_022595c4, func_ov004_0223cefc, &data_ov004_022595ec);
    func_ov004_0223d2f8(data_ov004_022596b0);
    ov004_init_register(data_ov004_022596b0, func_ov004_0223d2d4, &data_ov004_022595f8);
    RoomObjects_GridConstruct(data_ov004_02259804);
    ov004_init_register(data_ov004_02259804, func_ov004_0223cd3c, &data_ov004_02259604);
    RoomPushes_Construct(data_ov004_02259784);
    ov004_init_register(data_ov004_02259784, func_ov004_0223c7d8, &data_ov004_02259610);
    s64 depth = data_020ca0e8;
    data_ov004_022595d8 = (s32) ((depth * depth + 0x800) >> 12);
    ov004_init_vec(&data_ov004_0225967c, 0, 0, 0, &data_ov004_02259670);
}
CLEAN_AS(__sinit_ov004_0224f068, Ov004Init_RoomObjects)

/* The museum's insects (museum_insects.h), and the game's constructor and destructor of one
 * and of the table (InsectRoom_DestructTable). */
extern MuseumInsect data_ov004_02259a34[MUSEUM_INSECT_ENTRIES];
extern Ov004InitRecord data_ov004_02259a28;
extern void func_ov004_0223ed30(void *insect); /* MuseumInsect_Construct */
extern void func_ov004_0223ecc8(void *insect); /* MuseumInsect_Destruct */
extern void func_ov004_0224519c(void *table);  /* InsectRoom_DestructTable */

/* __sinit_ov004_0224f164: the 32 insects constructed and the table's destructor registered
 * (it finds the table itself). */
void Ov004Init_MuseumInsects(void)
{
    __cxa_vec_ctor(data_ov004_02259a34, MUSEUM_INSECT_ENTRIES, sizeof(MuseumInsect), func_ov004_0223ed30, func_ov004_0223ecc8);
    ov004_init_register(NULL, func_ov004_0224519c, &data_ov004_02259a28);
}
CLEAN_AS(__sinit_ov004_0224f164, Ov004Init_MuseumInsects)

/* The museum's obj_etc_museum spots (museum_room_setup.h), the data they are built from (two
 * entries, then the rows' table data_ov004_0224b868, then the other 57) and the game's
 * destructor of one. */
#define OV004_INIT_MUSEUM_SPOTS 59
extern MuseumSetupSpot data_ov004_0225f820[OV004_INIT_MUSEUM_SPOTS];
extern const MuseumSetupSpotSource data_ov004_0224b838[2];
extern const MuseumSetupSpotSource data_ov004_0224b8bc[OV004_INIT_MUSEUM_SPOTS - 2];
extern Ov004InitRecord data_ov004_0225f7a8, data_ov004_0225f658, data_ov004_0225f7f0, data_ov004_0225f7cc, data_ov004_0225f5e0,
    data_ov004_0225f7fc, data_ov004_0225f598, data_ov004_0225f778, data_ov004_0225f76c, data_ov004_0225f5bc,
    data_ov004_0225f5c8, data_ov004_0225f748, data_ov004_0225f5ec, data_ov004_0225f730, data_ov004_0225f5f8,
    data_ov004_0225f718, data_ov004_0225f610, data_ov004_0225f61c, data_ov004_0225f670, data_ov004_0225f688,
    data_ov004_0225f694, data_ov004_0225f6a0, data_ov004_0225f6ac, data_ov004_0225f6b8, data_ov004_0225f6c4,
    data_ov004_0225f6dc, data_ov004_0225f6e8, data_ov004_0225f6f4, data_ov004_0225f700, data_ov004_0225f724,
    data_ov004_0225f760, data_ov004_0225f79c, data_ov004_0225f580, data_ov004_0225f7c0, data_ov004_0225f55c,
    data_ov004_0225f568, data_ov004_0225f58c, data_ov004_0225f790, data_ov004_0225f5b0, data_ov004_0225f7d8,
    data_ov004_0225f7e4, data_ov004_0225f808, data_ov004_0225f544, data_ov004_0225f574, data_ov004_0225f5a4,
    data_ov004_0225f5d4, data_ov004_0225f604, data_ov004_0225f628, data_ov004_0225f640, data_ov004_0225f64c,
    data_ov004_0225f664, data_ov004_0225f67c, data_ov004_0225f6d0, data_ov004_0225f70c, data_ov004_0225f73c,
    data_ov004_0225f784, data_ov004_0225f7b4, data_ov004_0225f814, data_ov004_0225f550;
extern void func_ov004_02245648(void *spot); /* MuseumSetupSpot_Destruct */

/* __sinit_ov004_0224f1a0: each of the 59 spots built from its entry and registered, in the
 * order of the source file. */
void Ov004Init_MuseumSpots(void)
{
    static const struct {
        u8 spot;
        const MuseumSetupSpotSource *source;
        Ov004InitRecord *record;
    } spots[OV004_INIT_MUSEUM_SPOTS] = {
        {2, &data_ov004_0224b8bc[4], &data_ov004_0225f7a8},   {3, &data_ov004_0224b8bc[5], &data_ov004_0225f658},
        {4, &data_ov004_0224b8bc[6], &data_ov004_0225f7f0},   {5, &data_ov004_0224b8bc[7], &data_ov004_0225f7cc},
        {0, &data_ov004_0224b838[0], &data_ov004_0225f5e0},   {1, &data_ov004_0224b838[1], &data_ov004_0225f7fc},
        {15, &data_ov004_0224b8bc[13], &data_ov004_0225f598}, {16, &data_ov004_0224b8bc[14], &data_ov004_0225f778},
        {17, &data_ov004_0224b8bc[15], &data_ov004_0225f76c}, {18, &data_ov004_0224b8bc[16], &data_ov004_0225f5bc},
        {19, &data_ov004_0224b8bc[17], &data_ov004_0225f5c8}, {20, &data_ov004_0224b8bc[18], &data_ov004_0225f748},
        {21, &data_ov004_0224b8bc[19], &data_ov004_0225f5ec}, {22, &data_ov004_0224b8bc[20], &data_ov004_0225f730},
        {23, &data_ov004_0224b8bc[21], &data_ov004_0225f5f8}, {24, &data_ov004_0224b8bc[22], &data_ov004_0225f718},
        {25, &data_ov004_0224b8bc[23], &data_ov004_0225f610}, {26, &data_ov004_0224b8bc[24], &data_ov004_0225f61c},
        {27, &data_ov004_0224b8bc[25], &data_ov004_0225f670}, {28, &data_ov004_0224b8bc[26], &data_ov004_0225f688},
        {29, &data_ov004_0224b8bc[27], &data_ov004_0225f694}, {30, &data_ov004_0224b8bc[28], &data_ov004_0225f6a0},
        {31, &data_ov004_0224b8bc[29], &data_ov004_0225f6ac}, {32, &data_ov004_0224b8bc[30], &data_ov004_0225f6b8},
        {33, &data_ov004_0224b8bc[31], &data_ov004_0225f6c4}, {34, &data_ov004_0224b8bc[32], &data_ov004_0225f6dc},
        {35, &data_ov004_0224b8bc[33], &data_ov004_0225f6e8}, {36, &data_ov004_0224b8bc[34], &data_ov004_0225f6f4},
        {37, &data_ov004_0224b8bc[35], &data_ov004_0225f700}, {38, &data_ov004_0224b8bc[36], &data_ov004_0225f724},
        {6, &data_ov004_0224b8bc[0], &data_ov004_0225f760},   {7, &data_ov004_0224b8bc[1], &data_ov004_0225f79c},
        {8, &data_ov004_0224b8bc[2], &data_ov004_0225f580},   {9, &data_ov004_0224b8bc[3], &data_ov004_0225f7c0},
        {10, &data_ov004_0224b8bc[8], &data_ov004_0225f55c},  {11, &data_ov004_0224b8bc[9], &data_ov004_0225f568},
        {12, &data_ov004_0224b8bc[10], &data_ov004_0225f58c}, {13, &data_ov004_0224b8bc[11], &data_ov004_0225f790},
        {14, &data_ov004_0224b8bc[12], &data_ov004_0225f5b0}, {39, &data_ov004_0224b8bc[37], &data_ov004_0225f7d8},
        {40, &data_ov004_0224b8bc[38], &data_ov004_0225f7e4}, {41, &data_ov004_0224b8bc[39], &data_ov004_0225f808},
        {42, &data_ov004_0224b8bc[40], &data_ov004_0225f544}, {43, &data_ov004_0224b8bc[41], &data_ov004_0225f574},
        {44, &data_ov004_0224b8bc[42], &data_ov004_0225f5a4}, {45, &data_ov004_0224b8bc[43], &data_ov004_0225f5d4},
        {46, &data_ov004_0224b8bc[44], &data_ov004_0225f604}, {47, &data_ov004_0224b8bc[45], &data_ov004_0225f628},
        {48, &data_ov004_0224b8bc[46], &data_ov004_0225f640}, {49, &data_ov004_0224b8bc[47], &data_ov004_0225f64c},
        {50, &data_ov004_0224b8bc[48], &data_ov004_0225f664}, {51, &data_ov004_0224b8bc[49], &data_ov004_0225f67c},
        {52, &data_ov004_0224b8bc[50], &data_ov004_0225f6d0}, {53, &data_ov004_0224b8bc[51], &data_ov004_0225f70c},
        {54, &data_ov004_0224b8bc[52], &data_ov004_0225f73c}, {55, &data_ov004_0224b8bc[53], &data_ov004_0225f784},
        {56, &data_ov004_0224b8bc[54], &data_ov004_0225f7b4}, {57, &data_ov004_0224b8bc[55], &data_ov004_0225f814},
        {58, &data_ov004_0224b8bc[56], &data_ov004_0225f550},
    };
    for (int i = 0; i < OV004_INIT_MUSEUM_SPOTS; i++) {
        MuseumSetupSpot *spot = &data_ov004_0225f820[spots[i].spot];
        MuseumSetupSpot_Construct(spot, spots[i].source);
        ov004_init_register(spot, func_ov004_02245648, spots[i].record);
    }
}
CLEAN_AS(__sinit_ov004_0224f1a0, Ov004Init_MuseumSpots)

/* The player pick's states' member functions (player_pick.c). */
#define OV004_INIT_PLAYER_PICK_FNS 14
extern MemberPointer data_ov004_0225fe94[OV004_INIT_PLAYER_PICK_FNS];
extern const MemberPointer data_ov004_022567dc, data_ov004_022567cc, data_ov004_0225683c, data_ov004_02256834,
    data_ov004_0225682c, data_ov004_02256824, data_ov004_0225681c, data_ov004_02256814, data_ov004_0225680c,
    data_ov004_02256804, data_ov004_022567fc, data_ov004_022567f4, data_ov004_022567ec, data_ov004_022567e4;

/* __sinit_ov004_0224f8a4: the player pick's states' member functions (player_pick.c).
 * QUIRK: it answers the table's address (left in the result register). */
int Ov004Init_PlayerPick(void)
{
    static const MemberPointer *const fns[OV004_INIT_PLAYER_PICK_FNS] = {
        &data_ov004_022567dc, &data_ov004_022567cc, &data_ov004_0225683c, &data_ov004_02256834, &data_ov004_0225682c,
        &data_ov004_02256824, &data_ov004_0225681c, &data_ov004_02256814, &data_ov004_0225680c, &data_ov004_02256804,
        &data_ov004_022567fc, &data_ov004_022567f4, &data_ov004_022567ec, &data_ov004_022567e4};
    ov004_init_copy(data_ov004_0225fe94, fns, OV004_INIT_PLAYER_PICK_FNS);
    return (int) (uintptr_t) data_ov004_0225fe94;
}
CLEAN_AS(__sinit_ov004_0224f8a4, Ov004Init_PlayerPick)

/* Three ways out of a room (scene_exit.h) and the game's destructor of one
 * (SceneExit_Destruct). */
extern SceneExit data_ov004_0225ff7c, data_ov004_0225ff98, data_ov004_0225ffb4;
extern Ov004InitRecord data_ov004_0225ff70, data_ov004_0225ff64, data_ov004_0225ff58;
extern void func_020b649c(void *exit);

/* __sinit_ov004_0224f970: three ways out, each made by SceneExit_Init and registered: to scene
 * 1 at (15.0, 0.125, 29.0) facing 0x4000 with the player's parameter 0x11000000 and a door of
 * kind 2 facing -0x4000; to scene 5 at (17.0, 0.125, 29.0) facing -0x4000 with a door of kind
 * 2 facing 0x4000; to the buildings 0x5014-0x501a at the origin with parameter 0x800000 and
 * no door. All have change and next arguments 2. */
void Ov004Init_RoomExits(void)
{
    Vec3 first = {0xf000, 0x200, 0x1d000};
    SceneExit_Init(&data_ov004_0225ff7c, 1, &first, 0x11000000, 0x4000, 2, 2, -0x4000, 2);
    ov004_init_register(&data_ov004_0225ff7c, func_020b649c, &data_ov004_0225ff70);
    Vec3 second = {0x11000, 0x200, 0x1d000};
    SceneExit_Init(&data_ov004_0225ff98, 5, &second, 0x11000000, -0x4000, 2, 2, 0x4000, 2);
    ov004_init_register(&data_ov004_0225ff98, func_020b649c, &data_ov004_0225ff64);
    Vec3 origin = {0, 0, 0};
    SceneExit_Init(&data_ov004_0225ffb4, SCENE_EXIT_TO_BUILDINGS_5014, &origin, 0x800000, 0, 2, 2, 0, 0);
    ov004_init_register(&data_ov004_0225ffb4, func_020b649c, &data_ov004_0225ff58);
}
CLEAN_AS(__sinit_ov004_0224f970, Ov004Init_RoomExits)

/* The views of the cafe's show (room_camera.c) and the game's empty destructor of a view
 * (CarpetTexture_Destruct). */
extern Ov004InitColour data_ov004_0225ffe4, data_ov004_0225ffd4, data_ov004_0225ffd0, data_ov004_0225ffe0, data_ov004_0225ffd8,
    data_ov004_0225ffdc;
extern CameraView data_ov004_022569ac, data_ov004_022569cc, data_ov004_0225698c;
extern Ov004InitRecord data_ov004_0225fff4, data_ov004_02260000, data_ov004_0225ffe8;
extern void func_0203cb30(void *view);

/* A view registered, then its two offsets set (its angles and distance are the overlay's
 * data). */
static void ov004_init_view(CameraView *view, Ov004InitRecord *record, fx32 second_x, fx32 second_z)
{
    ov004_init_register(view, func_0203cb30, record);
    view->offset.x = 0;
    view->offset.y = 0x1e14;
    view->offset.z = 0xf0a;
    view->second_offset.x = second_x;
    view->second_offset.y = 0x200;
    view->second_offset.z = second_z;
}

/* __sinit_ov004_0224fa44: the six colours of its source file and the show's three views, each
 * with the offset (0, 1.88, 0.94) and the second offset at height 0.125: the wide one at
 * (19.375, 23.375), the close one at (16.25, 18.69) and the show's own at (15.35, 18.46). */
void Ov004Init_RoomCamera(void)
{
    ov004_init_colours(&data_ov004_0225ffe4, &data_ov004_0225ffd4, &data_ov004_0225ffd0, &data_ov004_0225ffe0,
                       &data_ov004_0225ffd8, &data_ov004_0225ffdc);
    ov004_init_view(&data_ov004_022569ac, &data_ov004_0225fff4, 0x13600, 0x17600);
    ov004_init_view(&data_ov004_022569cc, &data_ov004_02260000, 0x10400, 0x12b00);
    ov004_init_view(&data_ov004_0225698c, &data_ov004_0225ffe8, 0xf5ad, 0x12757);
}
CLEAN_AS(__sinit_ov004_0224fa44, Ov004Init_RoomCamera)
