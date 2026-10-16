/* The record of a villager's plan to move away (villager_move_record.h). */
#include "villager_move_record.h"

#include <string.h>

#include "clean.h"

static_assert(sizeof(DesignCreator) == VILLAGER_MOVE_PLAYER_ID_SIZE, "player id");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */
/* The player ids: whether one is set (a town and a player), whether two name the same player
 * (number and name), copied, emptied, destroyed and constructed. */
extern int func_020951bc(const DesignCreator *player);
extern int func_0209518c(const DesignCreator *a, const DesignCreator *b);
extern void func_0209525c(DesignCreator *dst, const DesignCreator *src);
extern void func_02095238(DesignCreator *player);
extern void func_0209526c(void *player);
extern void func_0209529c(void *player);
/* The plan's object: set to a type and item, emptied (type 22, no item), destroyed and
 * constructed. */
extern void func_0209bd30(u8 *object, u8 type, const u16 *item, u8 low_bits);
extern void func_0209bd5c(u8 *object);
extern void func_0209bd7c(u8 *object);
extern void func_0209bd80(u8 *object);

static DesignCreator *stage_player(VillagerMove *move, int stage)
{
    return (DesignCreator *) move->players[stage];
}

/* Whether the two ids are of the same town (its id and name). */
static int same_town(const DesignCreator *a, const DesignCreator *b)
{
    return a->town_id == b->town_id && memcmp(a->town_name, b->town_name, sizeof(a->town_name)) == 0;
}

/* func_0209a4b8: of the stages' set player ids, the one named by the most stages (the same
 * town and player); on a tie the last stage's. NULL while a plan runs (stage below 5) or when
 * no stage names a player. */
DesignCreator *VillagerMoveRecord_MostNamedPlayer(VillagerMove *move)
{
    if (VillagerMoveRecord_IsIdle(move) == 0) {
        return NULL;
    }

    u8 counted = 0;
    u8 counts[VILLAGER_MOVE_STAGES];
    MI_CpuFill8(counts, 0, VILLAGER_MOVE_STAGES);
    for (int i = 0; i < VILLAGER_MOVE_STAGES; i++) {
        if ((counted >> i) & 1) {
            continue;
        }
        DesignCreator *player = stage_player(move, i);
        if (func_020951bc(player) == 0) {
            continue;
        }
        /* The later stages naming the same player share stage i's count. */
        u8 same = 0;
        counted |= (u8) (1u << i);
        counts[i] = 1;
        for (int j = i + 1; j < VILLAGER_MOVE_STAGES; j++) {
            DesignCreator *other = stage_player(move, j);
            if (same_town(player, other) && func_0209518c(player, other) != 0) {
                same |= (u8) (1u << j);
                counted |= (u8) (1u << j);
                counts[i]++;
            }
        }
        for (int k = i + 1; k < VILLAGER_MOVE_STAGES; k++) {
            if ((same >> k) & 1) {
                counts[k] = counts[i];
            }
        }
    }
    if (counted == 0) {
        return NULL;
    }

    int best = 0;
    int best_stage = -1;
    for (int j = 0; j < VILLAGER_MOVE_STAGES; j++) {
        int count = counts[j];
        if (count > best) {
            best = count;
            best_stage = j;
        } else if (count != 0 && count == best) {
            best_stage = j;
        }
    }
    if (best_stage < 0) {
        return NULL;
    }
    return stage_player(move, best_stage);
}
CLEAN_AS(func_0209a4b8, VillagerMoveRecord_MostNamedPlayer)

/* func_0209a610: whether there is no plan (stage 5) and `today` (the clock's date when NULL)
 * is 0-2 days after the last step. */
int VillagerMoveRecord_IsRecentlyDone(VillagerMove *move, const Date *today)
{
    Date clock;
    if (today == NULL) {
        Calendar_Today(&clock);
        today = &clock;
    }
    if (VillagerMoveRecord_IsIdle(move) == 0) {
        return 0;
    }
    int days = Calendar_DaysFrom(today, &move->last_step);
    return days >= 0 && days < VILLAGER_MOVE_RECORD_RECENT_DAYS;
}
CLEAN_AS(func_0209a610, VillagerMoveRecord_IsRecentlyDone)

/* func_0209a654: whether the stage is 5: no plan. */
int VillagerMoveRecord_IsIdle(const VillagerMove *move)
{
    return move->stage == VILLAGER_MOVE_STAGE_NONE;
}
CLEAN_AS(func_0209a654, VillagerMoveRecord_IsIdle)

/* func_0209a664: the current stage's player id set to a copy of `player`; nothing at stage 5. */
void VillagerMoveRecord_SetStagePlayer(VillagerMove *move, const DesignCreator *player)
{
    DesignCreator *stage = VillagerMoveRecord_StagePlayer(move);
    if (stage != NULL) {
        func_0209525c(stage, player);
    }
}
CLEAN_AS(func_0209a664, VillagerMoveRecord_SetStagePlayer)

/* func_0209a67c: whether the current stage names a player. */
int VillagerMoveRecord_HasStagePlayer(VillagerMove *move)
{
    DesignCreator *stage = VillagerMoveRecord_StagePlayer(move);
    return stage != NULL && func_020951bc(stage) != 0;
}
CLEAN_AS(func_0209a67c, VillagerMoveRecord_HasStagePlayer)

/* func_0209a69c: whether `player`, when set, is the player of one of the stages.
 * BUG: the loop never moves on from stage 0, so only stage 0's player is compared (five
 * times). */
int VillagerMoveRecord_NamesPlayer(VillagerMove *move, const DesignCreator *player)
{
    if (func_020951bc(player) == 0) {
        return 0;
    }
    const DesignCreator *stage = stage_player(move, 0);
    for (int i = 0; i < VILLAGER_MOVE_STAGES; i++) {
#ifdef BUGFIX
        stage = stage_player(move, i);
#endif
        if (same_town(player, stage) && func_0209518c(player, stage) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0209a69c, VillagerMoveRecord_NamesPlayer)

/* func_0209a6ec: the current stage's player id; NULL at stage 5. */
DesignCreator *VillagerMoveRecord_StagePlayer(VillagerMove *move)
{
    return VillagerMoveRecord_Player(move, move->stage);
}
CLEAN_AS(func_0209a6ec, VillagerMoveRecord_StagePlayer)

/* func_0209a6fc: the stage's player id; NULL past 4. */
DesignCreator *VillagerMoveRecord_Player(VillagerMove *move, u32 stage)
{
    if (stage < VILLAGER_MOVE_STAGES) {
        return stage_player(move, (int) stage);
    }
    return NULL;
}
CLEAN_AS(func_0209a6fc, VillagerMoveRecord_Player)

/* func_0209a710: a new plan for the villager `npc` from `today`: the record cleared, the
 * object of type 9 with item 0x155e, both dates today (the last step's fourth byte 1), and
 * stage 1 or 2 at random. */
void VillagerMoveRecord_Start(VillagerMove *move, const NpcId *npc, const Date *today)
{
    VillagerMoveRecord_Clear(move);
    NpcId_Copy(&move->npc, npc);
    u16 item = VILLAGER_MOVE_RECORD_ITEM;
    func_0209bd30(move->object, VILLAGER_MOVE_RECORD_TYPE, &item, 0);
    MI_CpuCopy8(today, &move->started, sizeof(Date));
    MI_CpuCopy8(today, &move->last_step, sizeof(Date));
    move->last_step.unused = 1;
    move->stage = (u8) (func_020644cc(2) + 1);
}
CLEAN_AS(func_0209a710, VillagerMoveRecord_Start)

/* func_0209a774 */
NpcId *VillagerMoveRecord_Npc(VillagerMove *move)
{
    return &move->npc;
}
CLEAN_AS(func_0209a774, VillagerMoveRecord_Npc)

/* func_0209a778 */
u8 *VillagerMoveRecord_Object(VillagerMove *move)
{
    return move->object;
}
CLEAN_AS(func_0209a778, VillagerMoveRecord_Object)

/* func_0209a77c: no plan: the object emptied, no villager, no stage players, both dates
 * 1/1/2000 and stage 5. */
void VillagerMoveRecord_Clear(VillagerMove *move)
{
    func_0209bd5c(move->object);
    NpcId_Clear(&move->npc);
    for (int i = 0; i < VILLAGER_MOVE_STAGES; i++) {
        func_02095238(stage_player(move, i));
    }
    move->started.day = 1;
    move->started.month = 1;
    move->started.year = 0;
    move->started.unused = 0;
    move->last_step.day = 1;
    move->last_step.month = 1;
    move->last_step.year = 0;
    move->last_step.unused = 0;
    move->stage = VILLAGER_MOVE_STAGE_NONE;
}
CLEAN_AS(func_0209a77c, VillagerMoveRecord_Clear)

/* func_0209a7e8: the destructor. */
VillagerMove *VillagerMoveRecord_Destruct(VillagerMove *move)
{
    __cxa_vec_cleanup(move->players, VILLAGER_MOVE_STAGES, VILLAGER_MOVE_PLAYER_ID_SIZE, func_0209526c);
    NpcId_Destruct(&move->npc);
    func_0209bd7c(move->object);
    return move;
}
CLEAN_AS(func_0209a7e8, VillagerMoveRecord_Destruct)

/* func_0209a814: the constructor: the parts constructed, then the record cleared. */
VillagerMove *VillagerMoveRecord_Construct(VillagerMove *move)
{
    func_0209bd80(move->object);
    NpcId_Construct(&move->npc);
    __cxa_vec_ctor(move->players, VILLAGER_MOVE_STAGES, VILLAGER_MOVE_PLAYER_ID_SIZE, func_0209529c, func_0209526c);
    VillagerMoveRecord_Clear(move);
    return move;
}
CLEAN_AS(func_0209a814, VillagerMoveRecord_Construct)
