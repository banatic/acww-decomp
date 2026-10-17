/* Overlay 3's static initialisers (ov003_static_init.h). */
#include "ov003_static_init.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "fish_shadow.h"
#include "house_files.h"
#include "main/acre_map.h"
#include "main/scene_exit.h"
#include "ov004/member_pointer.h"
#include "thrown_bottle.h"
#include "tile_event.h"
#include "town_insect.h"

/* ---- What the initialisers share */

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov003InitRecord {
    struct Ov003InitRecord *next;
    void *destruct;
    void *object;
} Ov003InitRecord;

/* A constructor or destructor as the game is handed it: always the game's function, never a
 * Clean one. */
typedef void Ov003InitFn(void *object);

extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* `object` (NULL for an array its destructor finds itself) destructed by `destruct`. */
static void ov003_init_register(void *object, Ov003InitFn *destruct, Ov003InitRecord *record)
{
    __register_global_object(object, (void *) (uintptr_t) destruct, record);
}

/* `count` member pointers copied from the overlay's constants, in order. */
static void ov003_init_copy(MemberPointer *table, const MemberPointer *const *constants, int count)
{
    for (int i = 0; i < count; i++) {
        table[i] = *constants[i];
    }
}

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct Ov003InitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} Ov003InitColour;

static void ov003_init_colour(Ov003InitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* The six colours several source files define for themselves: red, blue, yellow, green, cyan
 * and grey, in that order. */
static void ov003_init_colours(Ov003InitColour *red, Ov003InitColour *blue, Ov003InitColour *yellow, Ov003InitColour *green,
                               Ov003InitColour *cyan, Ov003InitColour *grey)
{
    ov003_init_colour(red, 31, 20, 20, 31);
    ov003_init_colour(blue, 20, 20, 31, 31);
    ov003_init_colour(yellow, 31, 31, 20, 31);
    ov003_init_colour(green, 20, 31, 20, 31);
    ov003_init_colour(cyan, 20, 31, 31, 31);
    ov003_init_colour(grey, 20, 24, 24, 31);
}

/* The destructor of objects with nothing to destruct (TrivialObject_Destruct) and of a scene
 * exit (SceneExit_Destruct). */
extern void func_020012dc(void *object);
extern void func_020b649c(void *object);

/* ---- The initialisers, in address order */

extern Ov003InitColour data_ov003_0223c5c0, data_ov003_0223c5a4, data_ov003_0223c5a8, data_ov003_0223c5b0, data_ov003_0223c5ac,
    data_ov003_0223c5b4;

/* __sinit_ov003_0223728c: the six colours of its source file. */
void Ov003Init_Colours0223c5a4(void)
{
    ov003_init_colours(&data_ov003_0223c5c0, &data_ov003_0223c5a4, &data_ov003_0223c5a8, &data_ov003_0223c5b0,
                       &data_ov003_0223c5ac, &data_ov003_0223c5b4);
}
CLEAN_AS(__sinit_ov003_0223728c, Ov003Init_Colours0223c5a4)

extern Ov003InitColour data_ov003_0223c750, data_ov003_0223c740, data_ov003_0223c744, data_ov003_0223c73c, data_ov003_0223c738,
    data_ov003_0223c734;

/* __sinit_ov003_022372e8: the six colours of its source file. */
void Ov003Init_Colours0223c734(void)
{
    ov003_init_colours(&data_ov003_0223c750, &data_ov003_0223c740, &data_ov003_0223c744, &data_ov003_0223c73c,
                       &data_ov003_0223c738, &data_ov003_0223c734);
}
CLEAN_AS(__sinit_ov003_022372e8, Ov003Init_Colours0223c734)

extern Ov003InitColour data_ov003_0223c784, data_ov003_0223c7a0, data_ov003_0223c78c, data_ov003_0223c798, data_ov003_0223c79c,
    data_ov003_0223c788;

/* __sinit_ov003_02237344: the six colours of its source file. */
void Ov003Init_Colours0223c784(void)
{
    ov003_init_colours(&data_ov003_0223c784, &data_ov003_0223c7a0, &data_ov003_0223c78c, &data_ov003_0223c798,
                       &data_ov003_0223c79c, &data_ov003_0223c788);
}
CLEAN_AS(__sinit_ov003_02237344, Ov003Init_Colours0223c784)

extern Ov003InitColour data_ov003_0223c9c0, data_ov003_0223c9bc, data_ov003_0223c9d0, data_ov003_0223c9d4, data_ov003_0223c9cc,
    data_ov003_0223c9c8;

/* __sinit_ov003_022373a0: the six colours of its source file. */
void Ov003Init_Colours0223c9bc(void)
{
    ov003_init_colours(&data_ov003_0223c9c0, &data_ov003_0223c9bc, &data_ov003_0223c9d0, &data_ov003_0223c9d4,
                       &data_ov003_0223c9cc, &data_ov003_0223c9c8);
}
CLEAN_AS(__sinit_ov003_022373a0, Ov003Init_Colours0223c9bc)

extern Ov003InitColour data_ov003_0223caa0, data_ov003_0223cab4, data_ov003_0223cab0, data_ov003_0223caac, data_ov003_0223caa8,
    data_ov003_0223caa4;

/* __sinit_ov003_022373fc: the six colours of its source file. */
void Ov003Init_Colours0223caa0(void)
{
    ov003_init_colours(&data_ov003_0223caa0, &data_ov003_0223cab4, &data_ov003_0223cab0, &data_ov003_0223caac,
                       &data_ov003_0223caa8, &data_ov003_0223caa4);
}
CLEAN_AS(__sinit_ov003_022373fc, Ov003Init_Colours0223caa0)

extern Ov003InitColour data_ov003_0223cab8, data_ov003_0223cabc, data_ov003_0223cac8, data_ov003_0223cac4, data_ov003_0223cac0,
    data_ov003_0223cacc;

/* __sinit_ov003_02237458: the six colours of its source file. */
void Ov003Init_Colours0223cab8(void)
{
    ov003_init_colours(&data_ov003_0223cab8, &data_ov003_0223cabc, &data_ov003_0223cac8, &data_ov003_0223cac4,
                       &data_ov003_0223cac0, &data_ov003_0223cacc);
}
CLEAN_AS(__sinit_ov003_02237458, Ov003Init_Colours0223cab8)

extern Ov003InitColour data_ov003_0223cae4, data_ov003_0223cae8, data_ov003_0223cad8, data_ov003_0223cae0, data_ov003_0223cadc,
    data_ov003_0223caec;

/* __sinit_ov003_022374b4: the six colours of its source file. */
void Ov003Init_Colours0223cad8(void)
{
    ov003_init_colours(&data_ov003_0223cae4, &data_ov003_0223cae8, &data_ov003_0223cad8, &data_ov003_0223cae0,
                       &data_ov003_0223cadc, &data_ov003_0223caec);
}
CLEAN_AS(__sinit_ov003_022374b4, Ov003Init_Colours0223cad8)

/* The ways out of the town (21 SceneExits) and the point (16.0, 0.125, 29.0) all but the last
 * put the player at, with their records. */
#define OV003_INIT_EXITS 21
#define OV003_INIT_EXIT_PLAYER_PARAM 0x22c00000
#define OV003_INIT_EXIT_ANGLE (-0x8000)
#define OV003_INIT_EXIT_CHANGE_ARG 2
#define OV003_INIT_EXIT_NEXT_ARG 2
extern Vec3 data_ov003_0223cbe0;
extern Ov003InitRecord data_ov003_0223cbec;
extern SceneExit data_ov003_0223cc04[OV003_INIT_EXITS];
extern Ov003InitRecord data_ov003_0223cbd4, data_ov003_0223cbc8, data_ov003_0223cbbc, data_ov003_0223cbb0, data_ov003_0223cba4,
    data_ov003_0223cb98, data_ov003_0223cb2c, data_ov003_0223cb80, data_ov003_0223cb74, data_ov003_0223cb68,
    data_ov003_0223caf0, data_ov003_0223cb50, data_ov003_0223cb44, data_ov003_0223cb38, data_ov003_0223cb20,
    data_ov003_0223cb8c, data_ov003_0223cb14, data_ov003_0223cb5c, data_ov003_0223cafc, data_ov003_0223cbf8,
    data_ov003_0223cb08;

/* __sinit_ov003_02237510: the point, registered with an empty destructor, then the exits, each
 * made by SceneExit_Init and registered with SceneExit_Destruct. The first twenty lead to the
 * scenes below, at the point (a copy of it is handed on), facing angle -0x8000, with the
 * player's parameter 0x22c00000; the last leads to the player's saved place (scene 0x3f) with
 * all of them zero. All have change and next arguments 2 and a door of kind 0 facing 0. */
void Ov003Init_TownExits(void)
{
    static const struct {
        u8 scene;
        Ov003InitRecord *record;
    } exits[OV003_INIT_EXITS - 1] = {
        {0x11, &data_ov003_0223cbd4}, {0x12, &data_ov003_0223cbc8}, {0x13, &data_ov003_0223cbbc}, {0x14, &data_ov003_0223cbb0},
        {0x15, &data_ov003_0223cba4}, {0x16, &data_ov003_0223cb98}, {0x17, &data_ov003_0223cb2c}, {0x18, &data_ov003_0223cb80},
        {0x19, &data_ov003_0223cb74}, {0x09, &data_ov003_0223cb68}, {0x0a, &data_ov003_0223caf0}, {0x1a, &data_ov003_0223cb50},
        {0x1b, &data_ov003_0223cb44}, {0x1c, &data_ov003_0223cb38}, {0x1d, &data_ov003_0223cb20}, {0x20, &data_ov003_0223cb8c},
        {0x0f, &data_ov003_0223cb14}, {0x10, &data_ov003_0223cb5c}, {0x01, &data_ov003_0223cafc}, {0x0b, &data_ov003_0223cbf8},
    };

    data_ov003_0223cbe0.x = 0x10000;
    data_ov003_0223cbe0.y = 0x200;
    data_ov003_0223cbe0.z = 0x1d000;
    ov003_init_register(&data_ov003_0223cbe0, func_020012dc, &data_ov003_0223cbec);

    for (int i = 0; i < OV003_INIT_EXITS - 1; i++) {
        Vec3 point = data_ov003_0223cbe0;
        SceneExit_Init(&data_ov003_0223cc04[i], exits[i].scene, &point, OV003_INIT_EXIT_PLAYER_PARAM, OV003_INIT_EXIT_ANGLE,
                       OV003_INIT_EXIT_CHANGE_ARG, OV003_INIT_EXIT_NEXT_ARG, 0, 0);
        ov003_init_register(&data_ov003_0223cc04[i], func_020b649c, exits[i].record);
    }

    Vec3 origin = {0, 0, 0};
    SceneExit_Init(&data_ov003_0223cc04[OV003_INIT_EXITS - 1], SCENE_EXIT_TO_SAVED_PLACE, &origin, 0, 0,
                   OV003_INIT_EXIT_CHANGE_ARG, OV003_INIT_EXIT_NEXT_ARG, 0, 0);
    ov003_init_register(&data_ov003_0223cc04[OV003_INIT_EXITS - 1], func_020b649c, &data_ov003_0223cb08);
}
CLEAN_AS(__sinit_ov003_02237510, Ov003Init_TownExits)

/* The houses' palettes, textures and X files (house_files.h), their records and destructors. */
extern HousePalette data_ov003_0223ce58;
extern HouseTextures data_ov003_0223cea0;
extern HouseXFiles data_ov003_0223ce80;
extern Ov003InitRecord data_ov003_0223ce5c, data_ov003_0223ce68, data_ov003_0223ce74;
extern void func_ov003_0221fe90(void *object); /* HousePalette_Destruct */
extern void func_ov003_0222010c(void *object); /* HouseTextures_Destruct */
extern void func_ov003_0221ff98(void *object); /* HouseXFiles_Destruct */

/* __sinit_ov003_02237a44: the houses' palettes, textures and X files. */
void Ov003Init_HouseFiles(void)
{
    HousePalette_Construct(&data_ov003_0223ce58);
    ov003_init_register(&data_ov003_0223ce58, func_ov003_0221fe90, &data_ov003_0223ce5c);
    HouseTextures_Construct(&data_ov003_0223cea0);
    ov003_init_register(&data_ov003_0223cea0, func_ov003_0222010c, &data_ov003_0223ce68);
    HouseXFiles_Construct(&data_ov003_0223ce80);
    ov003_init_register(&data_ov003_0223ce80, func_ov003_0221ff98, &data_ov003_0223ce74);
}
CLEAN_AS(__sinit_ov003_02237a44, Ov003Init_HouseFiles)

/* The tile events' table (tile_event.h: four entries per player, 0xa4 bytes each), an object of
 * the same source file with nothing to destruct, their records, and the table's entry
 * constructor and destructor and its own destructor. */
#define OV003_INIT_TILE_EVENTS 20
extern TileEventEntry data_ov003_0223cfe4[OV003_INIT_TILE_EVENTS];
extern u8 data_ov003_0223cf88[];
extern Ov003InitRecord data_ov003_0223cf7c, data_ov003_0223cf94;
extern void func_ov003_022275ec(void *entry);
extern void func_ov003_022275d8(void *entry);
extern void func_ov003_022275bc(void *table);

static_assert(sizeof(TileEventEntry) == 0xa4, "a tile event entry");
static_assert(sizeof(SceneExit) == 0x1c, "a scene exit");
static_assert(sizeof(FishShadow) == 0x24c && sizeof(PlayerFish) == 0xa4, "the fish");
static_assert(sizeof(ThrownBottle) == 0x60, "a thrown bottle");
static_assert(sizeof(TownInsect) == 0x25c, "an insect");

/* __sinit_ov003_02237aa4: the tile events' table, each entry constructed, and the object at
 * data_ov003_0223cf88. */
void Ov003Init_TileEvents(void)
{
    __cxa_vec_ctor(data_ov003_0223cfe4, OV003_INIT_TILE_EVENTS, sizeof(TileEventEntry), func_ov003_022275ec,
                   func_ov003_022275d8);
    ov003_init_register(data_ov003_0223cfe4, func_ov003_022275bc, &data_ov003_0223cf7c);
    ov003_init_register(data_ov003_0223cf88, func_020012dc, &data_ov003_0223cf94);
}
CLEAN_AS(__sinit_ov003_02237aa4, Ov003Init_TileEvents)

/* The fish of the town's water (fish_shadow.h): the shadows, the fin, the players' fish, the
 * object at data_ov003_0225f0b4 with its copy of the scene's map, and the thrown bottles
 * (thrown_bottle.h); their records and the game's constructors and destructors. */
#define OV003_INIT_FISH_SIZES 8
#define OV003_INIT_BOTTLE_STATES 3
#define OV003_INIT_PLAYER_FISH_STATES 5
#define OV003_INIT_SWIM_PAIRS 4
#define OV003_INIT_SWIM_BEHAVIOURS 6
#define OV003_INIT_HOOK_STATES 7
#define OV003_INIT_SHADOW_STATE_FNS 10
extern AcreMap *data_021c80bc;
extern FishShadow data_ov003_0225f76c[FISH_SHADOW_COUNT];
extern FishFin data_ov003_0225f220;
extern PlayerFish data_ov003_0225f4dc[PLAYER_FISH_COUNT];
extern u8 data_ov003_0225f0b4[];
extern AcreMap *data_ov003_0225f0bc;
extern ThrownBottle data_ov003_0225f35c[THROWN_BOTTLE_COUNT];
extern Ov003InitRecord data_ov003_0225f0c4, data_ov003_0225f0d0, data_ov003_0225f0dc, data_ov003_0225f0e8, data_ov003_0225f0f4;
extern void func_ov003_0222902c(void *fish);   /* FishShadow_ConstructRecord */
extern void func_ov003_02228fe8(void *fish);   /* FishShadow_DestructRecord */
extern void func_ov003_0222c494(void *object); /* FishShadow_DestroyAll */
extern void func_ov003_02228f54(void *fin);    /* FishFin_Destruct */
extern void func_ov003_02228ed4(void *fish);   /* PlayerFish_Construct */
extern void func_ov003_02228ec4(void *fish);   /* PlayerFish_Destruct */
extern void func_ov003_0222c474(void *object); /* PlayerFish_DestroyAll */
extern void func_ov003_0222c414(void *object); /* FishShadowGlobal0225f0b4_Destruct */
extern void func_ov003_0222c3e0(void *bottle); /* ThrownBottle_Construct */
extern void func_ov003_0222c3d0(void *bottle); /* ThrownBottle_Destruct */
extern void func_ov003_0222c454(void *object); /* ThrownBottle_DestroyAll */

/* The member functions of the bottles' states (thrown_bottle.c), the players' fish's states
 * (player_fish.c), the swim and hook updates' pairs, the swim behaviours and the hook states
 * (fish_shadow_swim.c) and the shadows' states' entries and updates (fish_shadow.c). */
extern MemberPointer data_ov003_0225f100[OV003_INIT_BOTTLE_STATES];
extern MemberPointer data_ov003_0225f138[OV003_INIT_PLAYER_FISH_STATES];
extern MemberPointer data_ov003_0225f118[OV003_INIT_SWIM_PAIRS];
extern MemberPointer data_ov003_0225f160[OV003_INIT_SWIM_BEHAVIOURS];
extern MemberPointer data_ov003_0225f190[OV003_INIT_HOOK_STATES];
extern MemberPointer data_ov003_0225f1d0[OV003_INIT_SHADOW_STATE_FNS];
extern const MemberPointer data_ov003_0223bee0, data_ov003_0223bea8, data_ov003_0223bee8;
extern const MemberPointer data_ov003_0223bdf0, data_ov003_0223bed0, data_ov003_0223bec8, data_ov003_0223bec0,
    data_ov003_0223beb8;
extern const MemberPointer data_ov003_0223be78, data_ov003_0223be80, data_ov003_0223be48, data_ov003_0223be40;
extern const MemberPointer data_ov003_0223be30, data_ov003_0223be28, data_ov003_0223be20, data_ov003_0223bdf8,
    data_ov003_0223be08, data_ov003_0223be10;
extern const MemberPointer data_ov003_0223be60, data_ov003_0223be70, data_ov003_0223be98, data_ov003_0223bde0,
    data_ov003_0223bed8, data_ov003_0223be50, data_ov003_0223be38;
extern const MemberPointer data_ov003_0223be00, data_ov003_0223be18, data_ov003_0223beb0, data_ov003_0223bde8,
    data_ov003_0223be68, data_ov003_0223bdd0, data_ov003_0223be90, data_ov003_0223be58, data_ov003_0223be88,
    data_ov003_0223bdd8;

/* The shadows' size classes (fish_shadow.c's FishShadowSize): their two scales are filled from
 * a table of pairs. */
typedef struct Ov003InitFishSize {
    u8 unk_00[0x0e];
    u8 scale_x; /* 0x0e: in percent */
    u8 scale_z; /* 0x0f */
    u8 unk_10[4];
} Ov003InitFishSize;
typedef struct Ov003InitFishScale {
    u8 x;
    u8 z;
} Ov003InitFishScale;
static_assert(sizeof(Ov003InitFishSize) == 0x14, "a size class");
extern Ov003InitFishSize data_ov003_0223c014[OV003_INIT_FISH_SIZES];
extern const Ov003InitFishScale data_ov003_0223bef0[OV003_INIT_FISH_SIZES];

/* __sinit_ov003_02237af4: the fish: the six shadows constructed, the fin, the four players'
 * fish, the object at data_ov003_0225f0b4 handed the scene's map (kept first in
 * data_ov003_0225f0bc) and the four thrown bottles, each registered; then the tables of member
 * pointers filled, and between the first two the size classes' scales. */
void Ov003Init_Fish(void)
{
    static const MemberPointer *const bottle_fns[OV003_INIT_BOTTLE_STATES] = {
        &data_ov003_0223bee0,
        &data_ov003_0223bea8,
        &data_ov003_0223bee8,
    };
    static const MemberPointer *const player_fish_fns[OV003_INIT_PLAYER_FISH_STATES] = {
        &data_ov003_0223bdf0, &data_ov003_0223bed0, &data_ov003_0223bec8, &data_ov003_0223bec0, &data_ov003_0223beb8,
    };
    static const MemberPointer *const swim_pairs[OV003_INIT_SWIM_PAIRS] = {
        &data_ov003_0223be78,
        &data_ov003_0223be80,
        &data_ov003_0223be48,
        &data_ov003_0223be40,
    };
    static const MemberPointer *const swim_fns[OV003_INIT_SWIM_BEHAVIOURS] = {
        &data_ov003_0223be30, &data_ov003_0223be28, &data_ov003_0223be20,
        &data_ov003_0223bdf8, &data_ov003_0223be08, &data_ov003_0223be10,
    };
    static const MemberPointer *const hook_fns[OV003_INIT_HOOK_STATES] = {
        &data_ov003_0223be60, &data_ov003_0223be70, &data_ov003_0223be98, &data_ov003_0223bde0,
        &data_ov003_0223bed8, &data_ov003_0223be50, &data_ov003_0223be38,
    };
    static const MemberPointer *const shadow_fns[OV003_INIT_SHADOW_STATE_FNS] = {
        &data_ov003_0223be00, &data_ov003_0223be18, &data_ov003_0223beb0, &data_ov003_0223bde8, &data_ov003_0223be68,
        &data_ov003_0223bdd0, &data_ov003_0223be90, &data_ov003_0223be58, &data_ov003_0223be88, &data_ov003_0223bdd8,
    };

    __cxa_vec_ctor(data_ov003_0225f76c, FISH_SHADOW_COUNT, sizeof(FishShadow), func_ov003_0222902c, func_ov003_02228fe8);
    ov003_init_register(NULL, func_ov003_0222c494, &data_ov003_0225f0c4);
    FishFin_Construct(&data_ov003_0225f220);
    ov003_init_register(&data_ov003_0225f220, func_ov003_02228f54, &data_ov003_0225f0d0);
    __cxa_vec_ctor(data_ov003_0225f4dc, PLAYER_FISH_COUNT, sizeof(PlayerFish), func_ov003_02228ed4, func_ov003_02228ec4);
    ov003_init_register(NULL, func_ov003_0222c474, &data_ov003_0225f0dc);
    AcreMap *map = data_021c80bc;
    data_ov003_0225f0bc = map;
    FishShadowGlobal0225f0b4_Construct(data_ov003_0225f0b4, (int) (uintptr_t) map);
    ov003_init_register(data_ov003_0225f0b4, func_ov003_0222c414, &data_ov003_0225f0e8);
    __cxa_vec_ctor(data_ov003_0225f35c, THROWN_BOTTLE_COUNT, sizeof(ThrownBottle), func_ov003_0222c3e0, func_ov003_0222c3d0);
    ov003_init_register(NULL, func_ov003_0222c454, &data_ov003_0225f0f4);

    ov003_init_copy(data_ov003_0225f100, bottle_fns, OV003_INIT_BOTTLE_STATES);
    for (int i = 0; i < OV003_INIT_FISH_SIZES; i++) {
        data_ov003_0223c014[i].scale_x = data_ov003_0223bef0[i].x;
        data_ov003_0223c014[i].scale_z = data_ov003_0223bef0[i].z;
    }
    ov003_init_copy(data_ov003_0225f138, player_fish_fns, OV003_INIT_PLAYER_FISH_STATES);
    ov003_init_copy(data_ov003_0225f118, swim_pairs, OV003_INIT_SWIM_PAIRS);
    ov003_init_copy(data_ov003_0225f160, swim_fns, OV003_INIT_SWIM_BEHAVIOURS);
    ov003_init_copy(data_ov003_0225f190, hook_fns, OV003_INIT_HOOK_STATES);
    ov003_init_copy(data_ov003_0225f1d0, shadow_fns, OV003_INIT_SHADOW_STATE_FNS);
}
CLEAN_AS(__sinit_ov003_02237af4, Ov003Init_Fish)

/* The town's insects (town_insect.h): the town's eight, the two of the events and the four
 * held, each array with its destructor and record; and the point ahead of an actor
 * (field_actor.c), with nothing to destruct. */
extern TownInsect data_ov003_022617bc[TOWN_INSECT_TOWN_COUNT];
extern TownInsect data_ov003_02260994[TOWN_INSECT_EVENT_COUNT];
extern TownInsect data_ov003_02260e4c[TOWN_INSECT_HELD_COUNT];
extern Vec3 data_ov003_02260558;
extern Ov003InitRecord data_ov003_02260564, data_ov003_02260570, data_ov003_0226057c, data_ov003_02260588;
extern void func_ov003_0222d57c(void *insect); /* TownInsect_Construct */
extern void func_ov003_0222d520(void *insect); /* TownInsect_Destruct */
extern void func_ov003_02235c10(void *object);
extern void func_ov003_02235bec(void *object);
extern void func_ov003_02235bc8(void *object);

/* __sinit_ov003_02237e48: the three arrays of insects, each record constructed, and the point
 * ahead of an actor. */
void Ov003Init_TownInsects(void)
{
    __cxa_vec_ctor(data_ov003_022617bc, TOWN_INSECT_TOWN_COUNT, sizeof(TownInsect), func_ov003_0222d57c, func_ov003_0222d520);
    ov003_init_register(NULL, func_ov003_02235c10, &data_ov003_02260564);
    __cxa_vec_ctor(data_ov003_02260994, TOWN_INSECT_EVENT_COUNT, sizeof(TownInsect), func_ov003_0222d57c, func_ov003_0222d520);
    ov003_init_register(NULL, func_ov003_02235bec, &data_ov003_02260570);
    __cxa_vec_ctor(data_ov003_02260e4c, TOWN_INSECT_HELD_COUNT, sizeof(TownInsect), func_ov003_0222d57c, func_ov003_0222d520);
    ov003_init_register(NULL, func_ov003_02235bc8, &data_ov003_0226057c);
    ov003_init_register(&data_ov003_02260558, func_020012dc, &data_ov003_02260588);
}
CLEAN_AS(__sinit_ov003_02237e48, Ov003Init_TownInsects)

/* The objects behind the session's shared records 24-31 (eight of 0x10 bytes, main's
 * session_record.c), their record, and their constructor and destructor (both do nothing) and
 * the array's destructor. */
#define OV003_INIT_SESSION_OBJECTS 8
#define OV003_INIT_SESSION_OBJECT_SIZE 0x10
extern u8 data_ov003_02262aa8[OV003_INIT_SESSION_OBJECTS * OV003_INIT_SESSION_OBJECT_SIZE];
extern Ov003InitRecord data_ov003_02262a9c;
extern void func_ov003_02235d84(void *object);
extern void func_ov003_02235d80(void *object);
extern void func_ov003_02235d60(void *object);

/* __sinit_ov003_02237ee8: the session's objects constructed. */
void Ov003Init_SessionObjects(void)
{
    __cxa_vec_ctor(data_ov003_02262aa8, OV003_INIT_SESSION_OBJECTS, OV003_INIT_SESSION_OBJECT_SIZE, func_ov003_02235d84,
                   func_ov003_02235d80);
    ov003_init_register(NULL, func_ov003_02235d60, &data_ov003_02262a9c);
}
CLEAN_AS(__sinit_ov003_02237ee8, Ov003Init_SessionObjects)

extern Ov003InitColour data_ov003_02262d88, data_ov003_02262d84, data_ov003_02262d80, data_ov003_02262d7c, data_ov003_02262d78,
    data_ov003_02262d8c;

/* __sinit_ov003_02237f20: the six colours of its source file. */
void Ov003Init_Colours02262d78(void)
{
    ov003_init_colours(&data_ov003_02262d88, &data_ov003_02262d84, &data_ov003_02262d80, &data_ov003_02262d7c,
                       &data_ov003_02262d78, &data_ov003_02262d8c);
}
CLEAN_AS(__sinit_ov003_02237f20, Ov003Init_Colours02262d78)
