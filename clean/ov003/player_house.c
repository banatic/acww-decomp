/* The player's house seen from outside: its texture and its mailbox (player_house.h). */
#include "player_house.h"

#include "autoload_2/heap.h"   /* Heap, Heap_FreeAux, Heap_AllocAuxZeroed, Heap_FreeCurrent */
#include "autoload_2/vector.h" /* Vec3 */
#include "clean.h"
#include "main/actor.h" /* Actor_Spawn */

static_assert(offsetof(PlayerHouse, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(PlayerHouse, model) == 0x198, "model");
static_assert(offsetof(PlayerHouse, texture) == 0x2b4, "texture");
static_assert(offsetof(PlayerHouse, texture_2) == 0x2b8, "second texture");
static_assert(sizeof(PlayerHouse) == 0x2bc, "the size PlayerHouse_New allocates");

#define PLAYER_HOUSE_RECEIVER_OFFSET 0xec
#define PLAYER_HOUSE_MAILBOX_PROFILE 0x24
#define PLAYER_HOUSE_MAILBOX_CODE 0x501d
#define PLAYER_HOUSE_LOOKS 16      /* the look is one hexadecimal digit */
#define PLAYER_HOUSE_FILE_ALIGN -4 /* the texture file is loaded from the heap's end */

/* The house's records (five rooms of 0x450 bytes, then the word whose bits give the look). */
extern u8 data_021ebcd4[];
/* "0123456789ABCDEF": the look's digit. */
extern const signed char data_ov003_02236654[PLAYER_HOUSE_LOOKS];
/* "/str/plHsTex/home%c%c.nsbtx", and overlay 3's buffer for the path. */
extern const char data_ov003_02239390[];
extern char data_ov003_0223c998[];
/* The heap files are loaded on, and main's heap the texture is copied to. */
extern Heap *data_021fbe94;
extern Heap *data_021c9b1c;
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02239254[];
extern const u8 data_ov003_02239318[];

extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */
/* The letter overlay 3 picks for the files' names. */
extern signed char func_ov003_022203dc(void);
/* Bits 18 to 23, whether they are nonzero, and bits 6 to 9 of the house's word at 0x15a0. */
extern int func_02060be0(u8 *house);
extern unsigned int func_02060e10(u8 *house);
/* The player's index, and whether it is one of the four (below 4). */
extern int func_020984d4(void);
extern int func_020988d8(unsigned int index);
/* A file loaded whole from `heap`, the texture in a model file, whether that texture still has
 * to be copied, and its copy on `heap`. */
extern void *func_02064b2c(const char *path, Heap *heap, int align, u32 *size);
extern void *func_021077e8(void *file);
extern int func_020560e0(void *texture, int arg);
extern void *func_020561cc(void *texture, Heap *heap);
extern int NNS_G3dBindMdlTex(void *model, void *texture);
extern int NNS_G3dBindMdlPltt(void *model, void *texture);
/* The scene actor of overlay 3 with the special character code `code`, NULL for none. */
extern void *func_ov003_02220174(u16 code);
/* Overlay 9's scene actor: the drawing of an actor's model, the point it gives (whether it
 * has one), its destructor and its constructor. */
extern void func_ov009_022632c8(void *actor);
extern int func_ov009_0226321c(PlayerHouse *house, Vec3 *point, s16 *angle);
extern void *func_ov009_0226539c(PlayerHouse *house);
extern void *func_ov009_0226552c(PlayerHouse *house);

/* func_ov003_0221dc04 (vtable slot 0x98): always 1. */
int PlayerHouse_Slot98(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221dc04, PlayerHouse_Slot98)

/* func_ov003_0221dc08 (vtable slot 0x8c): always 1. */
int PlayerHouse_Slot8C(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221dc08, PlayerHouse_Slot8C)

/* func_ov003_0221dc0c (vtable slot 0x9c): whether bits 18 to 23 of the house's word at 0x15a0
 * are nonzero.
 * QUIRK: declared without a result; in the ROM the answer is still in r0 when it returns, so
 * the caller of the slot gets it. */
void PlayerHouse_Slot9C(void)
{
    func_02060be0(data_021ebcd4);
}
CLEAN_AS(func_ov003_0221dc0c, PlayerHouse_Slot9C)

/* func_ov003_0221dc1c (vtable slot 0x90): 1 when the player's index is not one of the four,
 * else 0. */
int PlayerHouse_Slot90(void)
{
    return func_020988d8((unsigned int) func_020984d4()) ? 0 : 1;
}
CLEAN_AS(func_ov003_0221dc1c, PlayerHouse_Slot90)

/* func_ov003_0221dc38: binds the house's texture to its model, and the second texture with its
 * palettes, each when it is there. */
void PlayerHouse_BindTextures(PlayerHouse *house)
{
    if (house->texture != NULL) {
        NNS_G3dBindMdlTex(house->model, house->texture);
    }
    if (house->texture_2 != NULL) {
        NNS_G3dBindMdlTex(house->model, house->texture_2);
        NNS_G3dBindMdlPltt(house->model, house->texture_2);
    }
}
CLEAN_AS(func_ov003_0221dc38, PlayerHouse_BindTextures)

/* func_ov003_0221dc7c: loads the file PlayerHouse_TexturePath names from the end of the current
 * heap and takes its texture, copied to main's heap when func_020560e0 says so; the file is
 * freed. */
void PlayerHouse_LoadTexture(PlayerHouse *house)
{
    void *file = func_02064b2c(PlayerHouse_TexturePath(), data_021fbe94, PLAYER_HOUSE_FILE_ALIGN, NULL);
    house->texture = func_021077e8(file);
    if (func_020560e0(house->texture, 0) != 0) {
        house->texture = func_020561cc(house->texture, data_021c9b1c);
    }
    Heap_FreeCurrent(file);
}
CLEAN_AS(func_ov003_0221dc7c, PlayerHouse_LoadTexture)

/* func_ov003_0221dcd8: the path of the house's texture, "/str/plHsTex/home<look><letter>.nsbtx",
 * in overlay 3's buffer. */
char *PlayerHouse_TexturePath(void)
{
    int look = PlayerHouse_Look();
    int letter = func_ov003_022203dc();
    func_02064328(data_ov003_0223c998, data_ov003_02239390, data_ov003_02236654[look & (PLAYER_HOUSE_LOOKS - 1)], letter);
    return data_ov003_0223c998;
}
CLEAN_AS(func_ov003_0221dcd8, PlayerHouse_TexturePath)

/* func_ov003_0221dd0c: the house's look (0 to 15): bits 6 to 9 of its word at 0x15a0. */
int PlayerHouse_Look(void)
{
    return (int) func_02060e10(data_021ebcd4);
}
CLEAN_AS(func_ov003_0221dd0c, PlayerHouse_Look)

/* func_ov003_0221dd1c (vtable slot 0x24): draws the model of the mailbox (code 0x501d) when the
 * scene has one; always 1. */
int PlayerHouse_Draw(void)
{
    void *mailbox = func_ov003_02220174(PLAYER_HOUSE_MAILBOX_CODE);
    if (mailbox != NULL) {
        func_ov009_022632c8(mailbox);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221dd1c, PlayerHouse_Draw)

/* func_ov003_0221dd3c (vtable slot 0x70, setting it up): loads and binds its texture; when
 * overlay 9 gives a point, makes the mailbox (profile 0x24, code 0x501d) two units along -x and
 * one along z from it; always 1. */
int PlayerHouse_Init(PlayerHouse *house)
{
    PlayerHouse_LoadTexture(house);
    PlayerHouse_BindTextures(house);
    Vec3 point;
    s16 angle;
    if (func_ov009_0226321c(house, &point, &angle)) {
        point.x -= 0x2000;
        point.z += 0x1000;
        Actor_Spawn(PLAYER_HOUSE_MAILBOX_PROFILE, PLAYER_HOUSE_MAILBOX_CODE, &point, NULL, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221dd3c, PlayerHouse_Init)

/* The vtables set back, then overlay 9's destructor. */
static void player_house_destroy_parts(PlayerHouse *house)
{
    house->vtable = data_ov003_02239254;
    house->receiver_vtable = data_ov003_02239318;
    func_ov009_0226539c(house);
}

/* func_ov003_0221dd90 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
PlayerHouse *PlayerHouse_DestroyAndFree(PlayerHouse *house)
{
    player_house_destroy_parts(house);
    Heap_FreeAux(house);
    return house;
}
CLEAN_AS(func_ov003_0221dd90, PlayerHouse_DestroyAndFree)

/* func_ov003_0221ddbc (vtable slot 0x40): the destructor. */
PlayerHouse *PlayerHouse_Destroy(PlayerHouse *house)
{
    player_house_destroy_parts(house);
    return house;
}
CLEAN_AS(func_ov003_0221ddbc, PlayerHouse_Destroy)

/* func_ov003_0221dde0: the constructor: overlay 9's, then the vtables. */
PlayerHouse *PlayerHouse_Construct(PlayerHouse *house)
{
    func_ov009_0226552c(house);
    house->vtable = data_ov003_02239254;
    house->receiver_vtable = data_ov003_02239318;
    return house;
}
CLEAN_AS(func_ov003_0221dde0, PlayerHouse_Construct)

/* func_ov003_0221de04 (the house's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void PlayerHouse_New(void)
{
    PlayerHouse *house = Heap_AllocAuxZeroed(sizeof(PlayerHouse));
    if (house != NULL) {
        PlayerHouse_Construct(house);
    }
}
CLEAN_AS(func_ov003_0221de04, PlayerHouse_New)

/* ---- The receiver vtable's thunks: each finds the house around `receiver`. */

static PlayerHouse *player_house_from_receiver(void *receiver)
{
    return (PlayerHouse *) (void *) ((u8 *) receiver - PLAYER_HOUSE_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02239254D0Ev: PlayerHouse_DestroyAndFree. */
PlayerHouse *PlayerHouse_ReceiverDestroyAndFree(void *receiver)
{
    return PlayerHouse_DestroyAndFree(player_house_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02239254D0Ev, PlayerHouse_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02239254D1Ev: PlayerHouse_Destroy. */
PlayerHouse *PlayerHouse_ReceiverDestroy(void *receiver)
{
    return PlayerHouse_Destroy(player_house_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02239254D1Ev, PlayerHouse_ReceiverDestroy)
