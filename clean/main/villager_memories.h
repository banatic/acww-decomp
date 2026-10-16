/* What one of the town's villagers remembers of the players it has met: eight memories of
 * 0x80 bytes at the start of the villager (villager_entry.h), each kept by the game's own
 * functions (func_02081xxx):
 *
 *   0x00  the player (its town and its own number and name, as a design's creator)
 *   0x1e  what the villager calls the player (6 characters; the player's name at first)
 *   0x2a  a text of 10 characters, set when bit 1 of the flags is
 *   0x3e  a text of 10 characters, set when bit 3 of the flags is
 *   0x54  a date and time (func_02081e10)
 *   0x5c  a town (func_02081d64)
 *   0x6a  an item; 0x6c (signed) how fond the villager is of the player; 0x6d a byte
 *   0x7c  flags
 *
 * A memory is in use when its player is set (func_02081edc). When the villager meets a new
 * player and all eight are in use, a memory is taken over: one of a player who has left this
 * town, else one of a player of another town (VillagerMemory_PickToReplace). */
#ifndef CLEAN_MAIN_VILLAGER_MEMORIES_H
#define CLEAN_MAIN_VILLAGER_MEMORIES_H

#include "calendar.h"
#include "clean.h"
#include "design.h"
#include "npc_id.h"
#include "types.h"

#define VILLAGER_MEMORIES 8
#define VILLAGER_MEMORY_NONE (-1)
/* VillagerMemory_ListOthers: which players. */
#define VILLAGER_MEMORY_LIST_THIS_TOWN 0
#define VILLAGER_MEMORY_LIST_OTHER_TOWNS 1

typedef struct VillagerMemory {
    DesignCreator player; /* 0x00 */
    u16 nickname[6];      /* 0x1e */
    u16 text_2a[10];      /* 0x2a */
    u16 text_3e[10];      /* 0x3e */
    u8 unknown_52[2];
    DateTime when;     /* 0x54 */
    NpcIdHead town;    /* 0x5c */
    u16 item;          /* 0x6a */
    s8 fondness;       /* 0x6c */
    u8 byte_6d;        /* 0x6d */
    u8 unknown_6e[14]; /* 0x6e */
    u16 flags;         /* 0x7c */
    u8 unknown_7e[2];
} VillagerMemory;

static_assert(sizeof(DesignCreator) == 0x1e, "a player is 0x1e bytes");
static_assert(offsetof(VillagerMemory, when) == 0x54, "the date of a memory");
static_assert(offsetof(VillagerMemory, town) == 0x5c, "the town of a memory");
static_assert(offsetof(VillagerMemory, fondness) == 0x6c, "how fond the villager is");
static_assert(offsetof(VillagerMemory, flags) == 0x7c, "the flags of a memory");
static_assert(sizeof(VillagerMemory) == 0x80, "a memory is 0x80 bytes");

/* What the game's tests of a memory's player look like: the player, this town, the town's
 * players (data_021dc7bc). */
typedef int (*VillagerMemoryTest)(void *player, void *town, void *players);

void VillagerMemory_SetText3E(u8 *villager, const u16 *text, int length, const DesignCreator *player);
int VillagerMemory_GetText3E(u8 *villager, void *text, const DesignCreator *player);
void VillagerMemory_SetText2A(u8 *villager, const u16 *text, int length, const DesignCreator *player);
int VillagerMemory_GetText2A(u8 *villager, void *text, const DesignCreator *player);
void VillagerMemory_ShareNickname(u8 *villager_a, u8 *villager_b, u8 *record);
VillagerMemory *VillagerMemory_SetNicknameChars(u8 *villager, const u16 *chars, int length, const DesignCreator *player);
VillagerMemory *VillagerMemory_SetNickname(u8 *villager, void *text, const DesignCreator *player);
void VillagerMemory_NameFor(u8 *villager, void *text, DesignCreator *player);
int VillagerMemory_RanksAbove(u8 *villager_a, u8 *villager_b, const DateTime *now);
int VillagerMemory_CountKnown(u8 *villager);
int VillagerMemory_ListOthers(u8 *villager, VillagerMemory **out, const DesignCreator *player, int which);
VillagerMemory *VillagerMemory_Meet(u8 *villager, DesignCreator *player);
VillagerMemory *VillagerMemory_Reusable(u8 *villager);
int VillagerMemory_ReusableIndex(u8 *villager);
int VillagerMemory_OtherTownIndex(u8 *villager);
int VillagerMemory_IsOtherTown(void *player, void *town, void *players);
int VillagerMemory_FormerPlayerIndex(u8 *villager);
int VillagerMemory_IsFormerPlayer(u16 *player, u16 *town, void *players);
int VillagerMemory_PickToReplace(VillagerMemory *memories, VillagerMemoryTest test);
int VillagerMemory_NearestMinutes(u8 *villager, const DateTime *now);
int VillagerMemory_MostFond(u8 *villager);
int VillagerMemory_IndexOfPlayer(u8 *villager, const DesignCreator *player);
int VillagerMemory_FreeIndex(u8 *villager);
VillagerMemory *VillagerMemory_Of(u8 *villager, const DesignCreator *player);
VillagerMemory *VillagerMemory_At(u8 *villager, int index);
int VillagerMemory_IndexOf(u8 *villager, const DesignCreator *player);

#endif
