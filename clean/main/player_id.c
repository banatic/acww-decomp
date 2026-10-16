/* A player's id and the two text classes of a player's name (player_id.h). */
#include "player_id.h"

#include <string.h>

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "main_random.h"
#include "player_records.h"

static_assert(sizeof(DesignCreator) == 0x1e, "DesignCreator size");
static_assert(offsetof(DesignCreator, player_id) == 0x0e, "DesignCreator.player_id");
static_assert(offsetof(DesignCreator, player_name) == 0x10, "DesignCreator.player_name");
static_assert(offsetof(DesignCreator, unk_1c) == 0x1c, "DesignCreator.unk_1c");
static_assert(sizeof(PlayerIdWideText) == 0x1c && offsetof(PlayerIdWideText, chars) == 0x0e, "PlayerIdWideText layout");
static_assert(sizeof(PlayerIdText) == 0x20 && offsetof(PlayerIdText, chars) == 0x12, "PlayerIdText layout");

extern const u8 data_020e2f54[]; /* the wide text's vtable */
extern const u8 data_020e2f6c[]; /* the 8-bit text's vtable */

extern u8 data_021dc7bc[];           /* the town's four players' records */
extern const TownName data_021dc7aa; /* this town (number and name) */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* A new player's number is a random number below 0x7ffc with bit 15 set. */
#define PLAYER_ID_NUMBER_RANGE 0x7ffc
#define PLAYER_ID_NUMBER_MADE 0x8000
/* The byte at 0x1c of a cleared id. */
#define PLAYER_ID_BYTE_1C_CLEARED 2

/* PlayerId_WhichTown */
#define PLAYER_ID_THIS_TOWN 0
#define PLAYER_ID_OTHER_TOWN 1
#define PLAYER_ID_NO_TOWN 2

/* An id's town, at its start. */
static TownName *player_id_town(DesignCreator *player)
{
    return (TownName *) (void *) player;
}

/* ---- the wide text */

/* func_02094f30 (vtable slot 3): the address of the characters. */
int PlayerIdWideText_Chars(int text)
{
    return text + (int) offsetof(PlayerIdWideText, chars);
}
CLEAN_AS(func_02094f30, PlayerIdWideText_Chars)

/* func_02094f34: the first `count` characters copied to `out`. */
void PlayerIdWideText_CopyOut(PlayerIdWideText *text, u16 *out, int count)
{
    MI_CpuCopy8(text->chars, out, (u32) count << 1);
}
CLEAN_AS(func_02094f34, PlayerIdWideText_CopyOut)

/* func_02094f40 (vtable slot 2): the capacity. */
int PlayerIdWideText_Capacity(void *text)
{
    (void) text;
    return PLAYER_ID_NAME_LENGTH;
}
CLEAN_AS(func_02094f40, PlayerIdWideText_Capacity)

/* func_02094f44 (vtable slot 1): destructs and frees. */
PlayerIdWideText *PlayerIdWideText_Delete(PlayerIdWideText *text)
{
    text->vtable = (const TextVtable *) data_020e2f54;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02094f44, PlayerIdWideText_Delete)

/* func_02094f64 (vtable slot 0): the destructor. */
PlayerIdWideText *PlayerIdWideText_Destruct(PlayerIdWideText *text)
{
    text->vtable = (const TextVtable *) data_020e2f54;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_02094f64, PlayerIdWideText_Destruct)

/* func_02094f7c: the constructor. */
PlayerIdWideText *PlayerIdWideText_Construct(PlayerIdWideText *text)
{
    TextBase_WideConstruct(text);
    text->vtable = (const TextVtable *) data_020e2f54;
    return text;
}
CLEAN_AS(func_02094f7c, PlayerIdWideText_Construct)

/* ---- the 8-bit text */

/* func_02094f94 (vtable slot 3): the address of the characters. */
int PlayerIdText_Chars(int text)
{
    return text + (int) offsetof(PlayerIdText, chars);
}
CLEAN_AS(func_02094f94, PlayerIdText_Chars)

/* func_02094f98 (vtable slot 2): the capacity. */
int PlayerIdText_Capacity(void *text)
{
    (void) text;
    return PLAYER_ID_TEXT_CAPACITY;
}
CLEAN_AS(func_02094f98, PlayerIdText_Capacity)

/* func_02094f9c (vtable slot 1): destructs and frees. */
PlayerIdText *PlayerIdText_Delete(PlayerIdText *text)
{
    text->vtable = (const TextVtable *) data_020e2f6c;
    TextBase_Destruct((TextBase *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02094f9c, PlayerIdText_Delete)

/* func_02094fbc (vtable slot 0): the destructor. */
PlayerIdText *PlayerIdText_Destruct(PlayerIdText *text)
{
    text->vtable = (const TextVtable *) data_020e2f6c;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_02094fbc, PlayerIdText_Destruct)

/* func_02094fd4: the constructor. */
PlayerIdText *PlayerIdText_Construct(PlayerIdText *text)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) data_020e2f6c;
    return text;
}
CLEAN_AS(func_02094fd4, PlayerIdText_Construct)

/* ---- the id */

/* func_02094fec: the player's index among the town's four players' records, or -1. */
int PlayerId_IndexInTown(DesignCreator *player)
{
    return PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (const void *) player);
}
CLEAN_AS(func_02094fec, PlayerId_IndexInTown)

/* func_02094ffc: whose town the player is of: 0 this town (the same number and name), 1
 * another town, 2 none (the town has no number). */
int PlayerId_WhichTown(DesignCreator *player)
{
    if (TownName_IsSet(&player->town_id) == 0) {
        return PLAYER_ID_NO_TOWN;
    }
    if (player->town_id == data_021dc7aa.number &&
        memcmp(player->town_name, data_021dc7aa.name, sizeof(player->town_name)) == 0) {
        return PLAYER_ID_THIS_TOWN;
    }
    return PLAYER_ID_OTHER_TOWN;
}
CLEAN_AS(func_02094ffc, PlayerId_WhichTown)

/* func_02095038: the player's town set to `town`. */
void PlayerId_SetTown(DesignCreator *player, const TownName *town)
{
    TownName_Copy(player_id_town(player), town);
}
CLEAN_AS(func_02095038, PlayerId_SetTown)

/* func_02095040: the player's town (at the start of the id). */
TownName *PlayerId_Town(DesignCreator *player)
{
    return player_id_town(player);
}
CLEAN_AS(func_02095040, PlayerId_Town)

/* func_02095044: the player's name set from an 8-bit text, through a wide text. */
void PlayerId_SetNameFromText(DesignCreator *player, TextBase *text)
{
    PlayerIdWideText wide;
    PlayerIdWideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) &wide, text);
    PlayerIdWideText_CopyOut(&wide, player->player_name, PLAYER_ID_NAME_LENGTH);
    PlayerIdWideText_Destruct(&wide);
}
CLEAN_AS(func_02095044, PlayerId_SetNameFromText)

/* func_02095074: the player's name written into an 8-bit text, through a wide text.
 * QUIRK: the original returns what the wide text's destructor does, the address of the wide
 * text on its own stack, gone by then, which no caller uses. Clean returns NULL in its place,
 * as an address of its own stack would mean nothing to the caller either. */
void *PlayerId_NameToText(DesignCreator *player, TextBase *text)
{
    PlayerIdWideText wide;
    PlayerIdWideText_Construct(&wide);
    TextBase_SetWide(&wide, player->player_name, PLAYER_ID_NAME_LENGTH);
    TextBase_WideToBytes(text, (WideTextBase *) &wide, 0, 0);
    PlayerIdWideText_Destruct(&wide);
    return NULL;
}
CLEAN_AS(func_02095074, PlayerId_NameToText)

/* func_020950a8: the address of the player's name. */
int PlayerId_Name(int player)
{
    return player + (int) offsetof(DesignCreator, player_name);
}
CLEAN_AS(func_020950a8, PlayerId_Name)

/* func_020950ac: the player's name set to the six characters at `name`. */
void PlayerId_SetName(DesignCreator *player, const u16 *name)
{
    MI_CpuCopy8(name, player->player_name, sizeof(player->player_name));
}
CLEAN_AS(func_020950ac, PlayerId_SetName)

/* func_020950c0: the id's byte at 0x1c, signed. */
int PlayerId_Byte1c(const s8 *player)
{
    return ((const DesignCreator *) (const void *) player)->unk_1c;
}
CLEAN_AS(func_020950c0, PlayerId_Byte1c)

/* func_020950c8: the id's byte at 0x1c set (its low 8 bits). */
void PlayerId_SetByte1c(u8 *player, int value)
{
    ((DesignCreator *) (void *) player)->unk_1c = (s8) (u8) value;
}
CLEAN_AS(func_020950c8, PlayerId_SetByte1c)

/* func_020950cc: the player's number set (its low 16 bits). */
void PlayerId_SetNumber(u16 *player, int number)
{
    ((DesignCreator *) (void *) player)->player_id = (u16) number;
}
CLEAN_AS(func_020950cc, PlayerId_SetNumber)

/* func_020950d0: the player's number. */
int PlayerId_Number(const u16 *player)
{
    return ((const DesignCreator *) (const void *) player)->player_id;
}
CLEAN_AS(func_020950d0, PlayerId_Number)

/* func_020950d4: a new player's number at random. */
u16 PlayerId_NewNumber(void)
{
    return (u16) (MainRandom_Below(PLAYER_ID_NUMBER_RANGE) | PLAYER_ID_NUMBER_MADE);
}
CLEAN_AS(func_020950d4, PlayerId_NewNumber)

/* func_020950f8: a new player's number that is none of the `count` numbers at `numbers`.
 * QUIRK: it also draws again on zero, which a new number (bit 15 set) never is. */
int PlayerId_NewNumberNotIn(const u16 *numbers, int count)
{
    int number = PlayerId_NewNumber();
    while (number == 0 || PlayerId_NumberIsIn((u16) number, numbers, count) == 1) {
        number = PlayerId_NewNumber();
    }
    return number;
}
CLEAN_AS(func_020950f8, PlayerId_NewNumberNotIn)

/* func_02095128: whether `number` is one of the `count` numbers at `numbers` (none when NULL or
 * zero of them). */
int PlayerId_NumberIsIn(u16 number, const u16 *numbers, int count)
{
    if (count == 0 || numbers == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (numbers[i] == number) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02095128, PlayerId_NumberIsIn)

/* func_02095158: an id made of the six characters at `name`, the number, the byte at 0x1c and
 * the town `town` (NULL: this town). */
void PlayerId_Make(DesignCreator *player, const u16 *name, u16 number, u8 byte_1c, const TownName *town)
{
    MI_CpuCopy8(name, player->player_name, sizeof(player->player_name));
    player->player_id = number;
    player->unk_1c = (s8) byte_1c;
    if (town == NULL) {
        town = &data_021dc7aa;
    }
    TownName_Copy(player_id_town(player), town);
}
CLEAN_AS(func_02095158, PlayerId_Make)

/* func_0209518c: whether the two ids name the same player: the same number, byte at 0x1c and
 * name (the towns are not compared). */
int PlayerId_SamePlayer(const DesignCreator *a, const DesignCreator *b)
{
    return a->player_id == b->player_id && a->unk_1c == b->unk_1c &&
           memcmp(a->player_name, b->player_name, sizeof(a->player_name)) == 0;
}
CLEAN_AS(func_0209518c, PlayerId_SamePlayer)

/* func_020951bc: whether the id is set: its town has a number, and so has the player. */
int PlayerId_IsSet(DesignCreator *player)
{
    return TownName_IsSet(&player->town_id) == 1 && player->player_id != 0;
}
CLEAN_AS(func_020951bc, PlayerId_IsSet)

/* func_020951dc: `src` copied to `dst`: the name, the number, the byte at 0x1c, then the town. */
void PlayerId_CopyTo(const DesignCreator *src, DesignCreator *dst)
{
    MI_CpuCopy8(src->player_name, dst->player_name, sizeof(dst->player_name));
    dst->player_id = src->player_id;
    dst->unk_1c = src->unk_1c;
    TownName_CopyTo(&src->town_id, &dst->town_id);
}
CLEAN_AS(func_020951dc, PlayerId_CopyTo)

/* func_02095208: `src` assigned to `dst`: the name, the number, the byte at 0x1c, then the
 * town. */
void PlayerId_Assign(DesignCreator *dst, const DesignCreator *src)
{
    MI_CpuCopy8(src->player_name, dst->player_name, sizeof(dst->player_name));
    dst->player_id = src->player_id;
    dst->unk_1c = src->unk_1c;
    TownName_Assign(player_id_town(dst), (const TownName *) (const void *) src);
}
CLEAN_AS(func_02095208, PlayerId_Assign)

/* func_02095238: no name, no number, the byte at 0x1c 2, then no town. */
void PlayerId_Clear(DesignCreator *player)
{
    MI_CpuFill8(player->player_name, 0, sizeof(player->player_name));
    player->player_id = 0;
    player->unk_1c = PLAYER_ID_BYTE_1C_CLEARED;
    TownName_Clear(player_id_town(player));
}
CLEAN_AS(func_02095238, PlayerId_Clear)

/* func_0209525c: `src` copied to `dst` in one copy. */
void PlayerId_Copy(DesignCreator *dst, const DesignCreator *src)
{
    MI_CpuCopy8(src, dst, sizeof(DesignCreator));
}
CLEAN_AS(func_0209525c, PlayerId_Copy)

/* func_0209526c: the destructor (the town's, which does nothing); the id's address. */
int PlayerId_Destruct(DesignCreator *player)
{
    TownName_Destruct(player);
    return (int) (intptr_t) player;
}
CLEAN_AS(func_0209526c, PlayerId_Destruct)

/* func_0209527c: the copy constructor: the town constructed, then `src` assigned; the id's
 * address. */
int PlayerId_CopyConstruct(DesignCreator *dst, DesignCreator *src)
{
    TownName_Construct(dst);
    PlayerId_Assign(dst, src);
    return (int) (intptr_t) dst;
}
CLEAN_AS(func_0209527c, PlayerId_CopyConstruct)

/* func_0209529c: the constructor (the town's, which does nothing). */
DesignCreator *PlayerId_Construct(DesignCreator *player)
{
    TownName_Construct(player);
    return player;
}
CLEAN_AS(func_0209529c, PlayerId_Construct)
