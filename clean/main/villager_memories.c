/* What one of the town's villagers remembers of the players it has met (villager_memories.h). */
#include "villager_memories.h"

#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "player_record.h"
#include "player_records.h"

/* VillagerMemory_NameFor: the villager's own name for the player is used only above this. */
#define VILLAGER_MEMORY_NAME_FONDNESS (-10)
/* The lowest fondness, where VillagerMemory_MostFond starts. */
#define VILLAGER_MEMORY_FONDNESS_MIN (-128)

/* A text object (constructed by func_02094fd4, destroyed by func_02094fbc), as big as the game
 * keeps it on its stack. */
typedef struct VillagerMemoryText {
    u32 words[8];
} VillagerMemoryText;
typedef struct VillagerMemoryWideText {
    u32 words[9];
} VillagerMemoryWideText;

extern const NpcIdHead data_021dc7aa; /* this town (number and name) */
extern u8 data_021dc7bc[];            /* the town's four players' records */
/* An empty player, constructed the first time VillagerMemory_FreeIndex runs (bit 0 of its
 * guard) and destroyed with the program through its node. */
extern u32 data_021d1240;
extern DesignCreator data_021d12f0;
extern u8 data_021d125c[];

extern void __register_global_object(void *object, void *destruct, void *node);
extern DesignCreator *func_0209529c(DesignCreator *player);               /* a player's constructor */
extern int func_0209526c(DesignCreator *player);                          /* a player's destructor */
extern void func_02095238(DesignCreator *player);                         /* a player emptied */
extern int func_020951bc(const DesignCreator *player);                    /* whether the player is set */
extern int func_0209518c(const DesignCreator *a, const DesignCreator *b); /* the same player number and name */
extern const NpcIdHead *func_02095040(const void *player);                /* the player's town, at its start */
extern int func_0209871c(void *players, void *player);                    /* the player's index among the town's, or -1 */
extern void *func_02095074(const DesignCreator *player, void *text);      /* the player's name copied to a text */
extern u32 func_02064294(const NpcIdHead *head);                          /* whether the head is set */
extern NpcId *func_0208150c(const void *villager);                        /* the villager's NpcId, at 0x7a0 */
extern int func_02080cf0(u8 *villager);
extern int func_02080808(u8 *villager, u32 index); /* whether the index is 0-7 */

/* A memory's parts (villager_memories.h). */
extern int func_02081d28(const VillagerMemory *memory, const DesignCreator *player); /* the same player */
extern int func_02081edc(const VillagerMemory *memory);                              /* whether it is in use */
extern DesignCreator *func_02081d60(VillagerMemory *memory);                         /* its player */
extern int func_02081cd8(const VillagerMemory *memory);                              /* bit 0 of its flags */
extern int func_02081c00(const VillagerMemory *memory);                              /* bit 1 */
extern int func_02081b54(const VillagerMemory *memory);                              /* bit 3 */
extern int func_02081d20(const VillagerMemory *memory);                              /* how fond the villager is */
extern DateTime *func_02081e10(VillagerMemory *memory);                              /* its date, at 0x54 */
extern NpcIdHead *func_02081d64(VillagerMemory *memory);                             /* its town, at 0x5c */
/* The texts at 0x3e and 0x2a set from up to 10 characters (and bits 3 and 1 of the flags), and
 * copied out to a text object. */
extern void func_02081ac8(VillagerMemory *memory, const u16 *text, int length);
extern void func_02081b24(VillagerMemory *memory, void *text);
extern void func_02081b68(VillagerMemory *memory, const u16 *text, int length);
extern int func_02081bc4(VillagerMemory *memory, void *text);
/* What the villager calls the player (0x1e): set from up to 6 characters or from a text
 * object, and copied out to a text object. */
extern void func_02081c14(VillagerMemory *memory, const u16 *chars, int length);
extern void *func_02081c40(VillagerMemory *memory, void *text);
extern void func_02081c94(VillagerMemory *memory, void *text);
/* The memory taken for the player: emptied, then the player, two values and the player's name
 * as what the villager calls it. 0 when the player is not set. */
extern int func_02081e94(VillagerMemory *memory, DesignCreator *player, int a, int b);
/* Text objects. */
extern void *func_02094fd4(void *text);                 /* constructor */
extern void *func_02094fbc(void *text);                 /* destructor */
extern void func_020a8c1c(void *text);                  /* emptied */
extern int func_020a89ac(const void *a, const void *b); /* whether both hold the same string */
/* The game's tests of a memory's player, handed to VillagerMemory_PickToReplace. */
extern int func_0208053c(void *player, void *town, void *players);
extern int func_02080578(void *player, void *town, void *players);

static VillagerMemory *memory_at(u8 *villager, int index)
{
    return (VillagerMemory *) (void *) (villager + index * (int) sizeof(VillagerMemory));
}

static int same_town(const NpcIdHead *a, const NpcIdHead *b)
{
    return a->id == b->id && memcmp(a->data, b->data, sizeof(a->data)) == 0;
}

/* func_02080108: the text at 0x3e of the villager's memory of the player set from `length`
 * characters, when it knows the player. */
void VillagerMemory_SetText3E(u8 *villager, const u16 *text, int length, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        func_02081ac8(memory, text, length);
    }
}
CLEAN_AS(func_02080108, VillagerMemory_SetText3E)

/* func_0208012c: the text at 0x3e of the villager's memory of the player copied to `text`, when
 * it knows the player, the player is set and the text has been; non-zero when it was. */
int VillagerMemory_GetText3E(u8 *villager, void *text, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL && func_020951bc(player) && func_02081b54(memory)) {
        func_02081b24(memory, text);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0208012c, VillagerMemory_GetText3E)

/* func_0208016c: the text at 0x2a of the villager's memory of the player set from `length`
 * characters, when it knows the player. */
void VillagerMemory_SetText2A(u8 *villager, const u16 *text, int length, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        func_02081b68(memory, text, length);
    }
}
CLEAN_AS(func_0208016c, VillagerMemory_SetText2A)

/* func_02080190: the text at 0x2a of the villager's memory of the player copied to `text`, when
 * it knows the player, the player is set and the text has been; what func_02081bc4 returns
 * then, else 0. */
int VillagerMemory_GetText2A(u8 *villager, void *text, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory == NULL) {
        return 0;
    }
    int result = func_020951bc(player);
    if (result == 0) {
        return 0;
    }
    result = func_02081c00(memory);
    if (result == 0) {
        return 0;
    }
    return func_02081bc4(memory, text);
}
CLEAN_AS(func_02080190, VillagerMemory_GetText2A)

/* func_020801c4: when two villagers both know the player of `record` (the current player's
 * record when NULL), and one of them calls the player something other than the player's name
 * (villager B first), the other takes up that name. */
void VillagerMemory_ShareNickname(u8 *villager_a, u8 *villager_b, u8 *record)
{
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL) {
        return;
    }
    DesignCreator *player = PlayerRecord_Player(record);
    if (!func_020951bc(player)) {
        return;
    }
    if (!NpcId_IsValid(func_0208150c(villager_a)) || !NpcId_IsValid(func_0208150c(villager_b))) {
        return;
    }
    VillagerMemory *memory_b = VillagerMemory_Of(villager_b, player);
    VillagerMemory *memory_a = VillagerMemory_Of(villager_a, player);
    VillagerMemoryText nickname;
    VillagerMemoryWideText name;
    func_02094fd4(&nickname);
    func_02094fd4(&name);
    if (memory_b != NULL && memory_a != NULL) {
        VillagerMemory *from = NULL;
        VillagerMemory *to = NULL;
        func_02095074(player, &name);
        func_02081c94(memory_b, &nickname);
        if (!func_020a89ac(&name, &nickname)) {
            from = memory_b;
            to = memory_a;
        } else {
            func_020a8c1c(&nickname);
            func_02081c94(memory_a, &nickname);
            if (!func_020a89ac(&name, &nickname)) {
                from = memory_a;
                to = memory_b;
            }
        }
        if (from != NULL && to != NULL) {
            func_020a8c1c(&nickname);
            func_02081c94(from, &nickname);
            func_02081c40(to, &nickname);
        }
    }
    func_02094fbc(&name);
    func_02094fbc(&nickname);
}
CLEAN_AS(func_020801c4, VillagerMemory_ShareNickname)

/* func_020802a4: what the villager calls the player set from `length` characters, when it knows
 * the player; its memory of the player, or NULL. */
VillagerMemory *VillagerMemory_SetNicknameChars(u8 *villager, const u16 *chars, int length, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        func_02081c14(memory, chars, length);
    }
    return memory;
}
CLEAN_AS(func_020802a4, VillagerMemory_SetNicknameChars)

/* func_020802c8: what the villager calls the player set from a text object, when it knows the
 * player; its memory of the player, or NULL. */
VillagerMemory *VillagerMemory_SetNickname(u8 *villager, void *text, const DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        func_02081c40(memory, text);
    }
    return memory;
}
CLEAN_AS(func_020802c8, VillagerMemory_SetNickname)

/* func_020802ec: the name the villager uses for the player, copied to `text`: what it calls the
 * player when it knows a set player and is fonder of it than -10, else the player's name. */
void VillagerMemory_NameFor(u8 *villager, void *text, DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL && func_020951bc(player) && func_02081d20(memory) > VILLAGER_MEMORY_NAME_FONDNESS) {
        func_02081c94(memory, text);
    } else {
        func_02095074(player, text);
    }
}
CLEAN_AS(func_020802ec, VillagerMemory_NameFor)

/* func_02080330: whether villager A ranks above villager B: A has a valid NpcId and B has not,
 * or by the first of these that differs: A knows more players; A has what func_02080cf0 looks
 * for and B has not; A is fonder of its favourite player; A's nearest memory date is fewer
 * minutes from `now`. 0 on a tie or with A's NpcId not valid. */
int VillagerMemory_RanksAbove(u8 *villager_a, u8 *villager_b, const DateTime *now)
{
    if (!NpcId_IsValid(func_0208150c(villager_a))) {
        return 0;
    }
    if (!NpcId_IsValid(func_0208150c(villager_b))) {
        return 1;
    }
    int known_a = VillagerMemory_CountKnown(villager_a);
    int known_b = VillagerMemory_CountKnown(villager_b);
    if (known_a != known_b) {
        return known_a > known_b;
    }
    int has_a = func_02080cf0(villager_a) != 0;
    int has_b = func_02080cf0(villager_b) != 0;
    if (has_a != has_b) {
        return has_a;
    }
    int fond_a = VillagerMemory_MostFond(villager_a);
    int fond_b = VillagerMemory_MostFond(villager_b);
    if (fond_a != fond_b) {
        return fond_a > fond_b;
    }
    int minutes_a = VillagerMemory_NearestMinutes(villager_a, now);
    int minutes_b = VillagerMemory_NearestMinutes(villager_b, now);
    return minutes_a < minutes_b;
}
CLEAN_AS(func_02080330, VillagerMemory_RanksAbove)

/* func_020803e0: how many of the eight memories are in use. */
int VillagerMemory_CountKnown(u8 *villager)
{
    int count = 0;
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        if (func_02081edc(memory_at(villager, i))) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_020803e0, VillagerMemory_CountKnown)

/* func_02080404: the memories in use of players other than `player` listed in `out`: with
 * `which` 0 those whose town (0x5c) is this town, with 1 those whose town is another, else
 * all; how many. None when `player` is not set.
 * QUIRK: the game also tests that this town's head is not at address 0, which always holds. */
int VillagerMemory_ListOthers(u8 *villager, VillagerMemory **out, const DesignCreator *player, int which)
{
    int count = 0;
    if (!func_020951bc(player)) {
        return 0;
    }
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        VillagerMemory *memory = memory_at(villager, i);
        if (!func_02081edc(memory) || func_02081d28(memory, player)) {
            continue;
        }
        int listed;
        if (which == VILLAGER_MEMORY_LIST_THIS_TOWN) {
            listed = same_town(func_02081d64(memory), &data_021dc7aa);
        } else if (which == VILLAGER_MEMORY_LIST_OTHER_TOWNS) {
            listed = !same_town(func_02081d64(memory), &data_021dc7aa);
        } else {
            listed = 1;
        }
        if (listed) {
            out[count] = memory;
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_02080404, VillagerMemory_ListOthers)

/* func_020804b8: the villager's memory of the player; for a player it does not know, a memory
 * taken for it (VillagerMemory_Reusable, then func_02081e94); NULL when none can be. */
VillagerMemory *VillagerMemory_Meet(u8 *villager, DesignCreator *player)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory != NULL) {
        return memory;
    }
    memory = VillagerMemory_Reusable(villager);
    if (memory == NULL) {
        return NULL;
    }
    func_02081e94(memory, player, 0, 0);
    return memory;
}
CLEAN_AS(func_020804b8, VillagerMemory_Meet)

/* func_020804e8: the memory to take for a new player, or NULL. */
VillagerMemory *VillagerMemory_Reusable(u8 *villager)
{
    return VillagerMemory_At(villager, VillagerMemory_ReusableIndex(villager));
}
CLEAN_AS(func_020804e8, VillagerMemory_Reusable)

/* func_02080500: which memory to take for a new player: a free one, else one of a player who
 * has left this town, else one of a player of another town; -1 for none. */
int VillagerMemory_ReusableIndex(u8 *villager)
{
    int index = VillagerMemory_FreeIndex(villager);
    if (index == VILLAGER_MEMORY_NONE) {
        index = VillagerMemory_FormerPlayerIndex(villager);
    }
    if (index == VILLAGER_MEMORY_NONE) {
        index = VillagerMemory_OtherTownIndex(villager);
    }
    return index;
}
CLEAN_AS(func_02080500, VillagerMemory_ReusableIndex)

/* func_0208052c: the memory of a player of another town to take over, or -1. */
int VillagerMemory_OtherTownIndex(u8 *villager)
{
    return VillagerMemory_PickToReplace((VillagerMemory *) (void *) villager, func_0208053c);
}
CLEAN_AS(func_0208052c, VillagerMemory_OtherTownIndex)

/* func_0208053c: whether the player's town is not `town`. */
int VillagerMemory_IsOtherTown(void *player, void *town, void *players)
{
    (void) players;
    return !same_town((const NpcIdHead *) town, func_02095040(player));
}
CLEAN_AS(func_0208053c, VillagerMemory_IsOtherTown)

/* func_02080568: the memory of a player who has left this town to take over, or -1. */
int VillagerMemory_FormerPlayerIndex(u8 *villager)
{
    return VillagerMemory_PickToReplace((VillagerMemory *) (void *) villager, func_02080578);
}
CLEAN_AS(func_02080568, VillagerMemory_FormerPlayerIndex)

/* func_02080578: whether the player is of `town` but not among its players. */
int VillagerMemory_IsFormerPlayer(u16 *player, u16 *town, void *players)
{
    const NpcIdHead *own = func_02095040(player);
    if (!same_town((const NpcIdHead *) (void *) town, own)) {
        return 0;
    }
    return func_0209871c(players, player) == -1;
}
CLEAN_AS(func_02080578, VillagerMemory_IsFormerPlayer)

/* func_020805bc: which of the eight memories in use whose player passes `test` (with this town
 * and its players) to take over: one with bit 0 of its flags clear over one with it set, then
 * the one the villager is least fond of, then the one with the earliest date; -1 for none, or
 * when this town is not set. */
int VillagerMemory_PickToReplace(VillagerMemory *memories, VillagerMemoryTest test)
{
    int best = VILLAGER_MEMORY_NONE;
    if (!func_02064294(&data_021dc7aa)) {
        return best;
    }
    VillagerMemory *chosen = NULL;
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        VillagerMemory *memory = &memories[i];
        if (!func_02081edc(memory)) {
            continue;
        }
        if (!test(func_02081d60(memory), (void *) (uintptr_t) &data_021dc7aa, data_021dc7bc)) {
            continue;
        }
        int take;
        if (chosen == NULL) {
            take = 1;
        } else {
            int chosen_bit = func_02081cd8(chosen);
            int memory_bit = func_02081cd8(memory);
            if (chosen_bit == memory_bit) {
                int chosen_fond = func_02081d20(chosen);
                int memory_fond = func_02081d20(memory);
                if (chosen_fond > memory_fond) {
                    take = 1;
                } else {
                    chosen_fond = func_02081d20(chosen);
                    memory_fond = func_02081d20(memory);
                    take = 0;
                    if (chosen_fond == memory_fond) {
                        DateTime *chosen_when = func_02081e10(chosen);
                        DateTime *memory_when = func_02081e10(memory);
                        take = DateTime_Compare(chosen_when, memory_when,
                                                DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR |
                                                    DATE_TIME_MINUTE | DATE_TIME_SECOND) == 1;
                    }
                }
            } else {
                take = func_02081cd8(memory) == 0;
            }
        }
        if (take) {
            chosen = memory;
            best = i;
        }
    }
    return best;
}
CLEAN_AS(func_020805bc, VillagerMemory_PickToReplace)

/* func_02080684: the fewest minutes between `now` and the date of a memory in use (either way);
 * 0 when one is at `now` to the second, 0x7fffffff when none is in use. */
int VillagerMemory_NearestMinutes(u8 *villager, const DateTime *now)
{
    int nearest = 0x7fffffff;
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        VillagerMemory *memory = memory_at(villager, i);
        if (!func_02081edc(memory)) {
            continue;
        }
        const DateTime *when = func_02081e10(memory);
        int order = DateTime_Compare(now, when,
                                     DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR | DATE_TIME_MINUTE |
                                         DATE_TIME_SECOND);
        int minutes;
        if (order == 1) {
            minutes = DateTime_MinutesBetween(when, now);
        } else if (order == -1) {
            minutes = DateTime_MinutesBetween(now, when);
        } else {
            return 0;
        }
        if (minutes < nearest) {
            nearest = minutes;
        }
    }
    return nearest;
}
CLEAN_AS(func_02080684, VillagerMemory_NearestMinutes)

/* func_020806f8: how fond the villager is of the player it is fondest of; -128 with no memory
 * in use. */
int VillagerMemory_MostFond(u8 *villager)
{
    int most = VILLAGER_MEMORY_FONDNESS_MIN;
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        VillagerMemory *memory = memory_at(villager, i);
        if (func_02081edc(memory)) {
            int fondness = func_02081d20(memory);
            if (fondness > most) {
                most = fondness;
            }
        }
    }
    return most;
}
CLEAN_AS(func_020806f8, VillagerMemory_MostFond)

/* func_02080728: the memory whose player has the player's number and name (its town not
 * compared), in use or not; -1 for none. */
int VillagerMemory_IndexOfPlayer(u8 *villager, const DesignCreator *player)
{
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        if (func_0209518c(func_02081d60(memory_at(villager, i)), player)) {
            return i;
        }
    }
    return VILLAGER_MEMORY_NONE;
}
CLEAN_AS(func_02080728, VillagerMemory_IndexOfPlayer)

/* func_02080758: a free memory (its player empty); -1 for none. */
int VillagerMemory_FreeIndex(u8 *villager)
{
    if ((data_021d1240 & 1) == 0) {
        func_0209529c(&data_021d12f0);
        __register_global_object(&data_021d12f0, (void *) (uintptr_t) func_0209526c, data_021d125c);
        data_021d1240 |= 1;
    }
    func_02095238(&data_021d12f0);
    return VillagerMemory_IndexOf(villager, &data_021d12f0);
}
CLEAN_AS(func_02080758, VillagerMemory_FreeIndex)

/* func_020807a8: the villager's memory of the player, or NULL. */
VillagerMemory *VillagerMemory_Of(u8 *villager, const DesignCreator *player)
{
    return VillagerMemory_At(villager, VillagerMemory_IndexOf(villager, player));
}
CLEAN_AS(func_020807a8, VillagerMemory_Of)

/* func_020807c0: memory `index`, or NULL for an index past 0-7. */
VillagerMemory *VillagerMemory_At(u8 *villager, int index)
{
    if (!func_02080808(villager, (u32) index)) {
        return NULL;
    }
    return memory_at(villager, index);
}
CLEAN_AS(func_020807c0, VillagerMemory_At)

/* func_020807dc: the memory of the player (the same town, number and name), in use or not; -1
 * for none. */
int VillagerMemory_IndexOf(u8 *villager, const DesignCreator *player)
{
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        if (func_02081d28(memory_at(villager, i), player)) {
            return i;
        }
    }
    return VILLAGER_MEMORY_NONE;
}
CLEAN_AS(func_020807dc, VillagerMemory_IndexOf)
