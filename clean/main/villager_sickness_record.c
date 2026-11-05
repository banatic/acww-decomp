/* The record of a villager sick in bed (villager_sickness_record.h). */
#include "villager_sickness_record.h"

#include <string.h>

#include "clean.h"
#include "villager_errand.h"
#include "main_random.h"
#include "player_id.h"

static_assert(sizeof(DesignCreator) == VILLAGER_SICKNESS_PLAYER_ID_SIZE, "player id");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_0209526c(void *player);
extern void func_0209529c(void *player);

static DesignCreator *stage_player(VillagerSickness *sickness, int stage)
{
    return (DesignCreator *) sickness->players[stage];
}

/* Whether the two ids are of the same town (its id and name). */
static int same_town(const DesignCreator *a, const DesignCreator *b)
{
    return a->town_id == b->town_id && memcmp(a->town_name, b->town_name, sizeof(a->town_name)) == 0;
}

/* func_0209a4b8: of the stages' set player ids, the one named by the most stages (the same
 * town and player); on a tie the last stage's. NULL while the villager is sick (stage below 5) or when
 * no stage names a player. */
DesignCreator *VillagerSicknessRecord_MostNamedPlayer(VillagerSickness *sickness)
{
    if (VillagerSicknessRecord_IsWell(sickness) == 0) {
        return NULL;
    }

    u8 counted = 0;
    u8 counts[VILLAGER_SICKNESS_STAGES];
    MI_CpuFill8(counts, 0, VILLAGER_SICKNESS_STAGES);
    for (int i = 0; i < VILLAGER_SICKNESS_STAGES; i++) {
        if ((counted >> i) & 1) {
            continue;
        }
        DesignCreator *player = stage_player(sickness, i);
        if (PlayerId_IsSet(player) == 0) {
            continue;
        }
        /* The later stages naming the same player share stage i's count. */
        u8 same = 0;
        counted |= (u8) (1u << i);
        counts[i] = 1;
        for (int j = i + 1; j < VILLAGER_SICKNESS_STAGES; j++) {
            DesignCreator *other = stage_player(sickness, j);
            if (same_town(player, other) && PlayerId_SamePlayer(player, other) != 0) {
                same |= (u8) (1u << j);
                counted |= (u8) (1u << j);
                counts[i]++;
            }
        }
        for (int k = i + 1; k < VILLAGER_SICKNESS_STAGES; k++) {
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
    for (int j = 0; j < VILLAGER_SICKNESS_STAGES; j++) {
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
    return stage_player(sickness, best_stage);
}
CLEAN_AS(func_0209a4b8, VillagerSicknessRecord_MostNamedPlayer)

/* func_0209a610: whether the villager is well (stage 5) and `today` (the clock's date when NULL)
 * is 0-2 days after the last step. */
int VillagerSicknessRecord_IsRecentlyCured(VillagerSickness *sickness, const Date *today)
{
    Date clock;
    if (today == NULL) {
        Calendar_Today(&clock);
        today = &clock;
    }
    if (VillagerSicknessRecord_IsWell(sickness) == 0) {
        return 0;
    }
    int days = Calendar_DaysFrom(today, &sickness->last_step);
    return days >= 0 && days < VILLAGER_SICKNESS_RECENT_DAYS;
}
CLEAN_AS(func_0209a610, VillagerSicknessRecord_IsRecentlyCured)

/* func_0209a654: whether the stage is 5: well, or no one sick. */
int VillagerSicknessRecord_IsWell(const VillagerSickness *sickness)
{
    return sickness->stage == VILLAGER_SICKNESS_WELL;
}
CLEAN_AS(func_0209a654, VillagerSicknessRecord_IsWell)

/* func_0209a664: the current stage's player id set to a copy of `player`; nothing at stage 5. */
void VillagerSicknessRecord_SetStagePlayer(VillagerSickness *sickness, const DesignCreator *player)
{
    DesignCreator *stage = VillagerSicknessRecord_StagePlayer(sickness);
    if (stage != NULL) {
        PlayerId_Copy(stage, player);
    }
}
CLEAN_AS(func_0209a664, VillagerSicknessRecord_SetStagePlayer)

/* func_0209a67c: whether the current stage names a player. */
int VillagerSicknessRecord_HasStagePlayer(VillagerSickness *sickness)
{
    DesignCreator *stage = VillagerSicknessRecord_StagePlayer(sickness);
    return stage != NULL && PlayerId_IsSet(stage) != 0;
}
CLEAN_AS(func_0209a67c, VillagerSicknessRecord_HasStagePlayer)

/* func_0209a69c: whether `player`, when set, is the player of one of the stages.
 * BUG: the loop never moves on from stage 0, so only stage 0's player is compared (five
 * times). */
int VillagerSicknessRecord_NamesPlayer(VillagerSickness *sickness, const DesignCreator *player)
{
    if (PlayerId_IsSet((DesignCreator *) player) == 0) {
        return 0;
    }
    const DesignCreator *stage = stage_player(sickness, 0);
    for (int i = 0; i < VILLAGER_SICKNESS_STAGES; i++) {
#ifdef BUGFIX
        stage = stage_player(sickness, i);
#endif
        if (same_town(player, stage) && PlayerId_SamePlayer(player, stage) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0209a69c, VillagerSicknessRecord_NamesPlayer)

/* func_0209a6ec: the current stage's player id; NULL at stage 5. */
DesignCreator *VillagerSicknessRecord_StagePlayer(VillagerSickness *sickness)
{
    return VillagerSicknessRecord_Player(sickness, sickness->stage);
}
CLEAN_AS(func_0209a6ec, VillagerSicknessRecord_StagePlayer)

/* func_0209a6fc: the stage's player id; NULL past 4. */
DesignCreator *VillagerSicknessRecord_Player(VillagerSickness *sickness, u32 stage)
{
    if (stage < VILLAGER_SICKNESS_STAGES) {
        return stage_player(sickness, (int) stage);
    }
    return NULL;
}
CLEAN_AS(func_0209a6fc, VillagerSicknessRecord_Player)

/* func_0209a710: the villager `npc` falls sick `today`: the record cleared, the
 * object of type 9 with item 0x155e, both dates today (the last step's fourth byte 1), and
 * stage 1 or 2 at random. */
void VillagerSicknessRecord_Start(VillagerSickness *sickness, const NpcId *npc, const Date *today)
{
    VillagerSicknessRecord_Clear(sickness);
    NpcId_Copy(&sickness->npc, npc);
    u16 item = VILLAGER_SICKNESS_MEDICINE;
    VillagerErrand_Set((VillagerErrand *) (void *) sickness->object, VILLAGER_SICKNESS_OBJECT_TYPE, &item, 0);
    MI_CpuCopy8(today, &sickness->started, sizeof(Date));
    MI_CpuCopy8(today, &sickness->last_step, sizeof(Date));
    sickness->last_step.unused = 1;
    sickness->stage = (u8) (MainRandom_Below(2) + 1);
}
CLEAN_AS(func_0209a710, VillagerSicknessRecord_Start)

/* func_0209a774 */
NpcId *VillagerSicknessRecord_Npc(VillagerSickness *sickness)
{
    return &sickness->npc;
}
CLEAN_AS(func_0209a774, VillagerSicknessRecord_Npc)

/* func_0209a778 */
u8 *VillagerSicknessRecord_Errand(VillagerSickness *sickness)
{
    return sickness->object;
}
CLEAN_AS(func_0209a778, VillagerSicknessRecord_Errand)

/* func_0209a77c: no one sick: the object emptied, no villager, no stage players, both dates
 * 1/1/2000 and stage 5. */
void VillagerSicknessRecord_Clear(VillagerSickness *sickness)
{
    VillagerErrand_Clear((VillagerErrand *) (void *) sickness->object);
    NpcId_Clear(&sickness->npc);
    for (int i = 0; i < VILLAGER_SICKNESS_STAGES; i++) {
        PlayerId_Clear(stage_player(sickness, i));
    }
    sickness->started.day = 1;
    sickness->started.month = 1;
    sickness->started.year = 0;
    sickness->started.unused = 0;
    sickness->last_step.day = 1;
    sickness->last_step.month = 1;
    sickness->last_step.year = 0;
    sickness->last_step.unused = 0;
    sickness->stage = VILLAGER_SICKNESS_WELL;
}
CLEAN_AS(func_0209a77c, VillagerSicknessRecord_Clear)

/* func_0209a7e8: the destructor. */
VillagerSickness *VillagerSicknessRecord_Destruct(VillagerSickness *sickness)
{
    __cxa_vec_cleanup(sickness->players, VILLAGER_SICKNESS_STAGES, VILLAGER_SICKNESS_PLAYER_ID_SIZE, func_0209526c);
    NpcId_Destruct(&sickness->npc);
    VillagerErrand_Destruct((VillagerErrand *) (void *) sickness->object);
    return sickness;
}
CLEAN_AS(func_0209a7e8, VillagerSicknessRecord_Destruct)

/* func_0209a814: the constructor: the parts constructed, then the record cleared. */
VillagerSickness *VillagerSicknessRecord_Construct(VillagerSickness *sickness)
{
    VillagerErrand_Construct((VillagerErrand *) (void *) sickness->object);
    NpcId_Construct(&sickness->npc);
    __cxa_vec_ctor(sickness->players, VILLAGER_SICKNESS_STAGES, VILLAGER_SICKNESS_PLAYER_ID_SIZE, func_0209529c,
                   func_0209526c);
    VillagerSicknessRecord_Clear(sickness);
    return sickness;
}
CLEAN_AS(func_0209a814, VillagerSicknessRecord_Construct)
