/* The eight places of the town's villagers (villager_roster.h). */
#include "villager_roster.h"

#include <string.h>

#include "calendar.h"
#include "clean.h"
#include "villager_bonds.h"
#include "villager_outdoors.h"
#include "villager_state.h"
#include "actor_table.h"
#include "date_time.h"
#include "main_random.h"
#include "npc_lookup.h"
#include "player_id.h"
#include "scene_query.h"
#include "text_base.h"
#include "town_villager.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_move_record.h"
#include "villager_status.h"

static_assert(sizeof(NpcIdHead) == 14, "NpcId head");
static_assert(offsetof(NpcId, number) == 0x0f, "NpcId number");

/* What a draw gives for no candidate. */
#define VILLAGER_ROSTER_NONE (-1)
/* The chance in VillagerRoster_FondestOrAny that a villager as fond as the best so far takes
 * its place: an odd draw below 10. */
#define VILLAGER_ROSTER_TIE_DRAW 10

/* A text object of the game (0x20 bytes) with a vtable; slot 3 gives its characters. The one
 * func_02094fd4 builds (vtable data_020e2f6c) holds a name as the game formats it; the one
 * func_02094f7c builds (vtable data_020e2f54) holds six wide characters at 0x0e. */
typedef struct VillagerRosterText VillagerRosterText;

typedef struct VillagerRosterTextVtable {
    void *slots_00[3];
    u16 *(*chars)(VillagerRosterText *text); /* 0x0c */
} VillagerRosterTextVtable;

struct VillagerRosterText {
    const VillagerRosterTextVtable *vtable;
    u8 rest[0x1c];
};

static_assert(offsetof(VillagerRosterTextVtable, chars) == 0x0c, "vtable slot 3");
static_assert(sizeof(VillagerRosterText) == 0x20, "text object");

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void *func_02081710(void *villager); /* a villager's destructor */
extern void *func_020817a8(void *villager); /* a villager's constructor */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

/* Whether two NpcIds name the same villager: the head and the number, not the personality. */
static int same_villager(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* ---- Finding a villager */

/* func_0207c4a4: the villager whose number is `number`, or NULL. */
u8 *VillagerRoster_FindNumber(VillagerTown *town, int number)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        const NpcId *npc = TownVillager_NpcId(villager);
        if (NpcId_IsValid(npc) && number == NpcId_Number(npc)) {
            return villager;
        }
    }
    return NULL;
}
CLEAN_AS(func_0207c4a4, VillagerRoster_FindNumber)

/* func_0207cd4c: the villager a code 17-24 stands for (places 0-7), or NULL. */
u8 *VillagerRoster_ForCode(VillagerTown *town, int code)
{
    if (SceneQuery_In11((u8) code) == 0) {
        return NULL;
    }
    int index = SceneQuery_IndexIn11((u8) code);
    if (!ActorTable_IsKindESlot((u32) index)) {
        return NULL;
    }
    return VillagerRoster_At(town, index);
}
CLEAN_AS(func_0207cd4c, VillagerRoster_ForCode)

/* func_0207ce98: the villager `npc` names, or NULL. */
u8 *VillagerRoster_Find(VillagerTown *town, const NpcId *npc)
{
    int index = VillagerRoster_IndexOf(town, npc);
    if (!ActorTable_IsKindESlot((u32) index)) {
        return NULL;
    }
    return town->villagers[index];
}
CLEAN_AS(func_0207ce98, VillagerRoster_Find)

/* func_0207cec0: the villager at place `index`, or NULL outside 0-7. */
u8 *VillagerRoster_At(VillagerTown *town, int index)
{
    if (!ActorTable_IsKindESlot((u32) index)) {
        return NULL;
    }
    return town->villagers[index];
}
CLEAN_AS(func_0207cec0, VillagerRoster_At)

/* func_0207cee4: whether place `index` (0-7) holds a villager; 0 outside 0-7. */
int VillagerRoster_IsFilled(VillagerTown *town, int index)
{
    if (!ActorTable_IsKindESlot((u32) index)) {
        return 0;
    }
    return NpcId_IsValid(TownVillager_NpcId(town->villagers[index]));
}
CLEAN_AS(func_0207cee4, VillagerRoster_IsFilled)

/* func_0207cf14: the place of the villager `npc` names, or -1 (also for an invalid `npc`). The
 * places are compared whether they hold a villager or not. */
int VillagerRoster_IndexOf(VillagerTown *town, const NpcId *npc)
{
    if (!NpcId_IsValid(npc)) {
        return VILLAGER_ROSTER_NONE;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (same_villager(npc, TownVillager_NpcId(town->villagers[i]))) {
            return i;
        }
    }
    return VILLAGER_ROSTER_NONE;
}
CLEAN_AS(func_0207cf14, VillagerRoster_IndexOf)

/* ---- Names */

/* func_0207ce48: whether the first `length` wide characters of `a` and `b` are the same. */
int VillagerRoster_NameEquals(const u16 *a, const u16 *b, int length)
{
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0207ce48, VillagerRoster_NameEquals)

/* func_0207ce70: the length of the name in the `length` wide characters of `name`, leaving
 * off the zeros and wide spaces (0x3000) at its end. */
int VillagerRoster_NameLength(const u16 *name, int length)
{
    for (; length > 0; length--) {
        u16 c = name[length - 1];
        if (c != VILLAGER_ROSTER_NUL && c != VILLAGER_ROSTER_WIDE_SPACE) {
            return length;
        }
    }
    return 0;
}
CLEAN_AS(func_0207ce70, VillagerRoster_NameLength)

/* func_0207cd84: the first villager whose name is the `length` wide characters of `name` (their
 * trailing blanks left off; 1-6 of them), among those that know `player` when it is not NULL;
 * else NULL. Each villager's name is formatted into a text object and copied into one of six
 * wide characters to be compared. */
u8 *VillagerRoster_FindByName(VillagerTown *town, const u16 *name, int length, const void *player)
{
    u8 *villager = VillagerRoster_At(town, 0);
    VillagerRosterText formatted;
    VillagerRosterText wide;
    PlayerIdText_Construct((PlayerIdText *) &formatted);
    PlayerIdWideText_Construct((PlayerIdWideText *) &wide);

    u8 *found = NULL;
    int wanted = VillagerRoster_NameLength(name, length);
    if (wanted > 0 && wanted <= VILLAGER_ROSTER_NAME_CHARS) {
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++, villager += VILLAGER_TOWN_VILLAGER_SIZE) {
            if (!has_villager(villager)) {
                continue;
            }
            if (player != NULL && VillagerMemory_Of(villager, player) == NULL) {
                continue;
            }
            TextBase_Clear(&formatted);
            NpcId_FormatName(TownVillager_NpcId(villager), (char *) &formatted);
            TextBase_BytesToWide((WideTextBase *) &wide, (TextBase *) &formatted);
            u16 *chars = wide.vtable->chars(&wide);
            int chars_length = VillagerRoster_NameLength(chars, PlayerIdWideText_Capacity(&wide));
            if (chars_length == wanted && VillagerRoster_NameEquals(chars, name, chars_length)) {
                found = villager;
                break;
            }
        }
    }
    PlayerIdWideText_Destruct((PlayerIdWideText *) &wide);
    PlayerIdText_Destruct((PlayerIdText *) &formatted);
    return found;
}
CLEAN_AS(func_0207cd84, VillagerRoster_FindByName)

/* ---- Counting and drawing */

/* func_0207cad4: the number of villagers in the town. */
int VillagerRoster_Count(VillagerTown *town)
{
    return VillagerRoster_CountFilled(town->villagers[0]);
}
CLEAN_AS(func_0207cad4, VillagerRoster_Count)

/* func_0207cadc: how many of the eight places from `villagers` hold a villager. */
int VillagerRoster_CountFilled(u8 *villagers)
{
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(villagers + i * VILLAGER_TOWN_VILLAGER_SIZE)) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0207cadc, VillagerRoster_CountFilled)

/* func_0207cd40: the first place without a villager, or -1 when all eight are filled. */
int VillagerRoster_FirstFree(VillagerTown *town)
{
    return TownVillager_FirstEmpty((u8 *) town, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207cd40, VillagerRoster_FirstFree)

/* func_0207cc54: a random one of the bits set among the low `bits` bits of `mask`, of which
 * `count` are said to be set; -1 for a count of 0 or less, and when fewer bits are set than
 * the draw counts past. */
int VillagerRoster_PickBit(unsigned int mask, int count, int bits)
{
    if (count <= 0) {
        return VILLAGER_ROSTER_NONE;
    }
    int nth = (int) MainRandom_Below(count);
    for (int i = 0; i < bits; i++) {
        if ((mask >> i) & 1) {
            if (nth == 0) {
                return i;
            }
            nth--;
        }
    }
    return VILLAGER_ROSTER_NONE;
}
CLEAN_AS(func_0207cc54, VillagerRoster_PickBit)

/* func_0207cb10: of the villagers that know `player` (a player id), the fondest of it; a tie
 * with the best so far is settled by a draw. When the player id is not set or no villager
 * knows the player, any villager (VillagerRoster_PickAny). */
u8 *VillagerRoster_FondestOrAny(VillagerTown *town, const void *player)
{
    u8 *best = NULL;
    if (PlayerId_IsSet((DesignCreator *) player) != 0) {
        int best_fondness = -128;
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            u8 *villager = town->villagers[i];
            if (!has_villager(villager)) {
                continue;
            }
            const s8 *memory = (const s8 *) VillagerMemory_Of(villager, player);
            if (memory == NULL) {
                continue;
            }
            int fondness = VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) memory);
            if (best == NULL || fondness > best_fondness) {
                best = villager;
                best_fondness = fondness;
            } else if (fondness == best_fondness && (MainRandom_Below(VILLAGER_ROSTER_TIE_DRAW) & 1)) {
                best = villager;
            }
        }
    }
    if (best == NULL) {
        best = VillagerRoster_PickAny(town, NULL, 0);
    }
    return best;
}
CLEAN_AS(func_0207cb10, VillagerRoster_FondestOrAny)

/* func_0207cb9c: a random villager for which func_0207f074 holds (a resident, not away, that
 * the current player's record does not hold), leaving out the `count` villagers of `excluded`
 * (NULL entries skipped) and the one planning to move away; NULL for none. */
u8 *VillagerRoster_PickResident(VillagerTown *town, const NpcId *const *excluded, int count)
{
    u8 left_out = 0;
    for (int i = 0; i < count; i++) {
        if (excluded[i] != NULL) {
            int index = VillagerRoster_IndexOf(town, excluded[i]);
            if (ActorTable_IsKindESlot((u32) index)) {
                left_out |= (u8) (1u << index);
            }
        }
    }
    int moving = VillagerMove_VillagerIndex(town);
    if (ActorTable_IsKindESlot((u32) moving)) {
        left_out |= (u8) (1u << moving);
    }

    u8 candidates = 0;
    int candidate_count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        const NpcId *npc = TownVillager_NpcId(villager);
        if (((left_out >> i) & 1) == 0 && NpcId_IsValid(npc) && VillagerStatus_IsFree(villager)) {
            candidates |= (u8) (1u << i);
            candidate_count++;
        }
    }
    return VillagerRoster_At(town, VillagerRoster_PickBit(candidates, candidate_count, VILLAGER_TOWN_VILLAGERS));
}
CLEAN_AS(func_0207cb9c, VillagerRoster_PickResident)

/* func_0207cc94: a random villager of the town, leaving out the `count` villagers of
 * `excluded` (NULL entries skipped); NULL for none.
 * QUIRK: each valid entry of `excluded` found in the town takes one off the count, so the same
 * villager listed twice takes off two and the draw can come out empty. */
u8 *VillagerRoster_PickAny(VillagerTown *town, const NpcId *const *excluded, int count)
{
    u8 filled[VILLAGER_TOWN_VILLAGERS];
    int filled_count = 0;
    MI_CpuFill8(filled, 0, sizeof(filled));
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (VillagerRoster_IsFilled(town, i)) {
            filled[i] = 1;
            filled_count++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (excluded[i] == NULL) {
            continue;
        }
        int index = VillagerRoster_IndexOf(town, excluded[i]);
        if (ActorTable_IsKindESlot((u32) index)) {
            filled[index] = 0;
            if (NpcId_IsValid(excluded[i])) {
                filled_count--;
            }
        }
    }
    if (filled_count > 0) {
        int nth = (int) MainRandom_Below(filled_count);
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            if (filled[i] == 1) {
                if (nth == 0) {
                    return town->villagers[i];
                }
                nth--;
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_0207cc94, VillagerRoster_PickAny)

/* ---- Where the villagers are */

/* func_0207c6a4: every villager asleep at home (place VILLAGER_PLACE_ASLEEP, state 0) that is
 * not out walking is woken up (VILLAGER_PLACE_HOME) once the clock is past the hours its
 * personality sleeps. */
void VillagerRoster_WakeUp(VillagerTown *town)
{
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        const NpcId *npc = TownVillager_NpcId(villager);
        if (!NpcId_IsValid(npc)) {
            continue;
        }
        VillagerState *state = VillagerStatus_StateEntry(villager);
        if (VillagerState_LinkedByte01(state) != VILLAGER_PLACE_ASLEEP || VillagerState_LinkedState(state) != 0) {
            continue;
        }
        if (VillagerOutdoors_OutsideSlot(&town->outdoors, i) != VILLAGER_OUTDOORS_NONE) {
            continue;
        }
        if (NpcLookup_IsInNightWindow(NpcId_Personality(npc), &now) != 0) {
            continue;
        }
        VillagerState_SetByte01(state, VILLAGER_PLACE_HOME);
    }
}
CLEAN_AS(func_0207c6a4, VillagerRoster_WakeUp)

/* func_0207c72c: whether the villager `npc` names is out walking. */
int VillagerRoster_IsOutside(VillagerTown *town, const NpcId *npc)
{
    int index = VillagerRoster_IndexOf(town, npc);
    return VillagerOutdoors_OutsideSlot(&town->outdoors, index) != VILLAGER_OUTDOORS_NONE;
}
CLEAN_AS(func_0207c72c, VillagerRoster_IsOutside)

/* func_0207c754: the villagers out walking brought up to date (VillagerOutdoors_Update). */
void VillagerRoster_UpdateOutdoors(VillagerTown *town, int keep_time)
{
    VillagerOutdoors_Update(&town->outdoors, town->villagers[0], keep_time);
}
CLEAN_AS(func_0207c754, VillagerRoster_UpdateOutdoors)

/* ---- The block as a whole */

/* func_0207cf80: every place emptied, the bonds, the walkers and the moving plan reset; the date
 * at 0x404c to day 1 of month 1 of year 0, not set; no time seen; no newcomer and no villager
 * gone; no mark and no number met. */
void VillagerRoster_Init(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        TownVillager_Reset(town->villagers[i]);
    }
    VillagerBond_Clear(town->bonds);
    VillagerOutdoors_Init(&town->outdoors);
    VillagerMoveRecord_Clear(&town->move);

    town->date_404c.day = 1;
    town->date_404c.month = 1;
    town->date_404c.year = 0;
    town->date_404c.unused = 0;
    memset(&town->latest, 0, sizeof(town->latest));
    memset(&town->time_4058, 0, sizeof(town->time_4058));
    town->index_4075 = VILLAGER_TOWN_NONE;
    town->unknown_4060[0x14] = (u8) VILLAGER_TOWN_NONE; /* 0x4074: the number of the villager gone */

    MI_CpuFill8(&town->mark, 0, sizeof(town->mark));
    MI_CpuFill8(town->unknown_4060, 0, 0x14); /* 0x4060: the numbers met */
}
CLEAN_AS(func_0207cf80, VillagerRoster_Init)

/* func_0207d03c: the destructor: the moving plan, the walkers, the bonds, then the eight
 * villagers. */
VillagerTown *VillagerRoster_Destruct(VillagerTown *town)
{
    VillagerMoveRecord_Destruct(&town->move);
    VillagerOutdoors_Destruct(&town->outdoors);
    VillagerBond_Destruct(town->bonds);
    __cxa_vec_cleanup(town->villagers, VILLAGER_TOWN_VILLAGERS, VILLAGER_TOWN_VILLAGER_SIZE,
                      (void (*)(void *))(uintptr_t) func_02081710);
    return town;
}
CLEAN_AS(func_0207d03c, VillagerRoster_Destruct)

/* func_0207d080: the constructor: the eight villagers, the bonds, the walkers, the moving plan;
 * no time seen. */
VillagerTown *VillagerRoster_Construct(VillagerTown *town)
{
    __cxa_vec_ctor(town->villagers, VILLAGER_TOWN_VILLAGERS, VILLAGER_TOWN_VILLAGER_SIZE,
                   (void (*)(void *))(uintptr_t) func_020817a8, (void (*)(void *))(uintptr_t) func_02081710);
    VillagerBond_Construct(town->bonds);
    VillagerOutdoors_Construct(&town->outdoors);
    VillagerMoveRecord_Construct(&town->move);
    memset(&town->latest, 0, sizeof(town->latest));
    memset(&town->time_4058, 0, sizeof(town->time_4058));
    return town;
}
CLEAN_AS(func_0207d080, VillagerRoster_Construct)
