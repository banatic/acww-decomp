/* How a chat between two villagers out walking in the town changes bonds and moods
 * (outdoor_villager_bonds.h). */
#include "outdoor_villager_bonds.h"

#include <stdint.h>

#include "clean.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_mode.h"
#include "main/villager_mood.h"
#include "main/villager_pairs.h"
#include "main/villager_roster.h"
#include "main/villager_scene_object.h"
#include "main/villager_town.h"
#include "outdoor_villager.h"

/* The town's villagers. */
extern VillagerTown data_021e5a2c;
/* The shop's eight designs (main's design_sets.h). */
extern u8 data_021ed278[];

/* Clears `size` bytes at `dst`. */
extern void *func_02137550(void *dst, u32 size);

/* The bond changes of the two exchanges, by tier, and the moods of a pair that gets on badly. */
extern const s8 data_ov068_02276764[OUTDOOR_VILLAGER_BONDS_TIERS];
extern const s8 data_ov068_0227674c[OUTDOOR_VILLAGER_BONDS_TIERS];
extern const u8 data_ov068_02276728[2];

#define BONDS_SHOP_DESIGNS 8
#define BONDS_NO_FONDNESS (-128) /* the fondness of a villager without a memory of the player */
#define BONDS_UNKNOWN_TIER 2     /* the tier given for a tier out of range */
#define BONDS_DONE_STEP 3        /* behaviour 9's step that ends the chat */
#define BONDS_GOOD_MOOD 1
#define BONDS_GOOD_MOOD_UNITS 2
#define BONDS_BAD_MOOD_UNITS 2

/* Its town record (vtable slot 0x64), or null. */
static u8 *bonds_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager);
}

/* The villager it is paired with (the word at 0x644). */
static u8 *bonds_partner(u8 *villager)
{
    return (u8 *) (uintptr_t) VillagerSceneObject_Word644((u32 *) (void *) villager);
}

/* The second of a sorted pair learns from the first: their modes and the nickname the first
 * gives the player. */
static void bonds_learn(u8 *first, u8 *second)
{
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);
}

/* func_ov068_0226aad4: the exchange that only learns. The pair sorted, the second learns from
 * the first, gossip lowers the bond of two others, and both moods are asked for (0, 0) and
 * applied; the chat ends (step 3). Always 1. */
int OutdoorVillagerBonds_Learn(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = bonds_partner(villager);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *mine = bonds_record(villager);
    u8 *theirs = bonds_record(partner);
    OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs);
    bonds_learn(first, second);
    OutdoorVillagerBonds_ChangeOthers(self, villager, data_ov068_02276764);
    OutdoorVillagerBonds_AskMood(self, villager, 0, 0, 1);
    OutdoorVillagerBonds_AskMood(self, partner, 0, 0, 1);
    self->step = BONDS_DONE_STEP;
    return 1;
}
CLEAN_AS(func_ov068_0226aad4, OutdoorVillagerBonds_Learn)

/* func_ov068_0226ab58: the exchange where the pair talks about how it gets on. The pair sorted,
 * the second learns from the first, their own bond raised; then by their tier (taken from the
 * records read first): 0 or 1 both moods asked for (1, 2) and applied, 3 or 4 one of the moods
 * 2 and 3 for each (2 units, applied), 2 nothing. The chat ends (step 3). Always 1. */
int OutdoorVillagerBonds_TalkOfBond(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = bonds_partner(villager);
    u8 *mine = bonds_record(villager);
    u8 *theirs = bonds_record(partner);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *a = bonds_record(villager);
    u8 *b = bonds_record(partner);
    OutdoorVillagerBonds_Sort(self, &first, &second, a, b);
    bonds_learn(first, second);
    OutdoorVillagerBonds_ChangeOthers(self, villager, data_ov068_0227674c);
    switch (VillagerPair_TierOf(&data_021e5a2c, mine, theirs)) {
        case 0:
        case 1:
            OutdoorVillagerBonds_AskMood(self, villager, BONDS_GOOD_MOOD, BONDS_GOOD_MOOD_UNITS, 1);
            OutdoorVillagerBonds_AskMood(self, partner, BONDS_GOOD_MOOD, BONDS_GOOD_MOOD_UNITS, 1);
            break;
        case 3:
        case 4:
            OutdoorVillagerBonds_AskMoodOf(self, villager, data_ov068_02276728, 2, BONDS_BAD_MOOD_UNITS, 1);
            OutdoorVillagerBonds_AskMoodOf(self, partner, data_ov068_02276728, 2, BONDS_BAD_MOOD_UNITS, 1);
            break;
        default:
            break;
    }
    self->step = BONDS_DONE_STEP;
    return 1;
}
CLEAN_AS(func_ov068_0226ab58, OutdoorVillagerBonds_TalkOfBond)

/* func_ov068_0226ac40: one of the shop's eight designs drawn at random among those that are not
 * `design` (all of them when `design` is null); null when none is left. */
u8 *OutdoorVillagerBonds_DrawShopDesign(OutdoorVillagerBehaviour *self, u8 *design)
{
    (void) self;
    unsigned int designs = (unsigned int) (uintptr_t) data_021ed278;
    u16 mask = 0;
    int count = 0;
    for (unsigned int i = 0; i < BONDS_SHOP_DESIGNS; i++) {
        if (design != NULL) {
            char *shop = (char *) (uintptr_t) ShopDesigns_At(designs, (u8) i);
            if (Design_Equals(shop, (char *) design) != 0) {
                continue;
            }
        }
        mask = (u16) (mask | (1u << i));
        count++;
    }
    unsigned int drawn = (unsigned int) VillagerRoster_PickBit(mask, count, BONDS_SHOP_DESIGNS);
    if (drawn < BONDS_SHOP_DESIGNS) {
        return (u8 *) (uintptr_t) ShopDesigns_At(designs, (u8) drawn);
    }
    return NULL;
}
CLEAN_AS(func_ov068_0226ac40, OutdoorVillagerBonds_DrawShopDesign)

/* func_ov068_0226aca8: the town records `a` and `b` sorted into `first` and `second`: the one
 * fonder of the current player first (VillagerMemoryEntry_Fondness of its memory of the
 * player, -128 without one), when they are as fond the order drawn at random (one time in two
 * swapped). Without a current player (or one not set) they stay in order. Whether they were
 * swapped. */
int OutdoorVillagerBonds_Sort(OutdoorVillagerBehaviour *self, u8 **first, u8 **second, u8 *a, u8 *b)
{
    (void) self;
    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    if (player == NULL || PlayerId_IsSet(player) == 0) {
        *first = a;
        *second = b;
        return 0;
    }
    int fond_a = BONDS_NO_FONDNESS;
    int fond_b = BONDS_NO_FONDNESS;
    VillagerMemory *memory_a = VillagerMemory_Of(a, player);
    VillagerMemory *memory_b = VillagerMemory_Of(b, player);
    if (memory_a != NULL) {
        fond_a = VillagerMemoryEntry_Fondness(memory_a);
    }
    if (memory_b != NULL) {
        fond_b = VillagerMemoryEntry_Fondness(memory_b);
    }
    int swap = fond_a < fond_b || (fond_a == fond_b && MainRandom_Below(2) != 0);
    if (swap) {
        *first = b;
        *second = a;
        return 1;
    }
    *first = a;
    *second = b;
    return 0;
}
CLEAN_AS(func_ov068_0226aca8, OutdoorVillagerBonds_Sort)

/* func_ov068_0226ad44: one mood of `moods` drawn (of the first `count`) and asked for with
 * `units` (0 units for mood 0), applied when `apply`. */
void OutdoorVillagerBonds_AskMoodOf(OutdoorVillagerBehaviour *self, u8 *villager, const u8 *moods, int count, u8 units,
                                    u8 apply)
{
    u8 mood = moods[MainRandom_Below(count)];
    if (mood == 0) {
        units = 0;
    }
    OutdoorVillagerBonds_AskMood(self, villager, mood, units, apply);
}
CLEAN_AS(func_ov068_0226ad44, OutdoorVillagerBonds_AskMoodOf)

/* func_ov068_0226ad78: the villager's mood (0x83c) asked for `which` with `units`, then applied
 * when `apply`. */
void OutdoorVillagerBonds_AskMood(OutdoorVillagerBehaviour *self, u8 *villager, int which, int units, u8 apply)
{
    (void) self;
    VillagerMood *mood = (VillagerMood *) (void *) (villager + OUTDOOR_VILLAGER_MOOD);
    VillagerMood_Ask(mood, (unsigned int) which, (unsigned int) units);
    if (apply) {
        VillagerMood_Apply(mood);
    }
}
CLEAN_AS(func_ov068_0226ad78, OutdoorVillagerBonds_AskMood)

/* func_ov068_0226ada8: gossip: two villagers of the town drawn at random (the second other
 * than the first) get their bond changed by `amounts` at their tier. Nothing when the town has
 * no villager to draw. */
void OutdoorVillagerBonds_ChangeOthers(OutdoorVillagerBehaviour *self, u8 *villager, const s8 *amounts)
{
    (void) villager;
    VillagerTown *town = &data_021e5a2c;
    u8 *one = VillagerRoster_PickAny(town, NULL, 0);
    if (one == NULL) {
        return;
    }
    const NpcId *first = TownVillager_NpcId(one);
    const NpcId *excluded;
    func_02137550(&excluded, sizeof(excluded));
    excluded = first;
    u8 *other = VillagerRoster_PickAny(town, &excluded, 1);
    if (other != NULL) {
        OutdoorVillagerBonds_Change(self, first, TownVillager_NpcId(other), amounts);
    }
}
CLEAN_AS(func_ov068_0226ada8, OutdoorVillagerBonds_ChangeOthers)

/* func_ov068_0226ae00: the villager and its partner (the word at 0x644) get their bond changed
 * by `amounts` at their tier. */
void OutdoorVillagerBonds_ChangePair(OutdoorVillagerBehaviour *self, u8 *villager, const s8 *amounts)
{
    u8 *partner = bonds_partner(villager);
    u8 *mine = bonds_record(villager);
    u8 *theirs = bonds_record(partner);
    const NpcId *a = TownVillager_NpcId(mine);
    const NpcId *b = TownVillager_NpcId(theirs);
    OutdoorVillagerBonds_Change(self, a, b, amounts);
}
CLEAN_AS(func_ov068_0226ae00, OutdoorVillagerBonds_ChangePair)

/* func_ov068_0226ae48: the bond of villagers `a` and `b` changed by the amount of `amounts` at
 * their tier (none for a tier of 5 or more). */
void OutdoorVillagerBonds_Change(OutdoorVillagerBehaviour *self, const NpcId *a, const NpcId *b, const s8 *amounts)
{
    (void) self;
    int tier = OutdoorVillagerBonds_Tier(a, b);
    if (tier < OUTDOOR_VILLAGER_BONDS_TIERS) {
        VillagerPair_AddBond(&data_021e5a2c, a, b, amounts[tier]);
    }
}
CLEAN_AS(func_ov068_0226ae48, OutdoorVillagerBonds_Change)

/* func_ov068_0226ae80: the tier of the villager and its partner (the word at 0x644). */
int OutdoorVillagerBonds_PairTier(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    u8 *partner = bonds_partner(villager);
    u8 *mine = bonds_record(villager);
    u8 *theirs = bonds_record(partner);
    const NpcId *a = TownVillager_NpcId(mine);
    const NpcId *b = TownVillager_NpcId(theirs);
    return OutdoorVillagerBonds_Tier(a, b);
}
CLEAN_AS(func_ov068_0226ae80, OutdoorVillagerBonds_PairTier)

/* func_ov068_0226aec0: the tier of villagers `a` and `b` (VillagerPair_Tier of their places in
 * the town), 2 when it is out of range. */
int OutdoorVillagerBonds_Tier(const NpcId *a, const NpcId *b)
{
    VillagerTown *town = &data_021e5a2c;
    int index_a = VillagerRoster_IndexOf(town, a);
    int index_b = VillagerRoster_IndexOf(town, b);
    int tier = VillagerPair_Tier(town, index_a, index_b);
    return tier < OUTDOOR_VILLAGER_BONDS_TIERS ? tier : BONDS_UNKNOWN_TIER;
}
CLEAN_AS(func_ov068_0226aec0, OutdoorVillagerBonds_Tier)
