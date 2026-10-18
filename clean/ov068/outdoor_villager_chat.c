/* Behaviour 9 of a villager out walking in the town: the chat of a pair of villagers and its
 * exchanges (outdoor_villager_chat.h). */
#include "outdoor_villager_chat.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor_table.h"
#include "main/design.h"
#include "main/design_info.h"
#include "main/insect_draw.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/npc_lookup.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/session_players.h"
#include "main/small_texts.h"
#include "main/text_base.h"
#include "main/town_villager.h"
#include "main/villager_catchphrase.h"
#include "main/villager_data.h"
#include "main/villager_memories.h"
#include "main/villager_mode.h"
#include "main/villager_mood.h"
#include "main/villager_pairs.h"
#include "main/villager_roster.h"
#include "main/villager_scene_object.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_town.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_watch.h"
#include "outdoor_villager_bonds.h"
#include "outdoor_villager_walks.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The town's villagers. */
extern VillagerTown data_021e5a2c;

/* The chat's wait by the pair's tier (0 to 4). */
extern const s32 data_ov068_022767b8[5];
/* The acts the two play now and then while they chat (eight). */
extern const u8 data_ov068_0227679c[8];
/* The weights of the seven exchanges. */
extern const u8 data_ov068_02276794[7];
/* The moods asked for (func_ov068_0226ad44 draws one) and the records kept (func_ov068_0226ada8
 * and func_ov068_0226ae00) by the ends of the chat. */
extern const u8 data_ov068_02276740[4];
extern const u8 data_ov068_02276738[4];
extern const u8 data_ov068_02276730[4];
extern const u8 data_ov068_02276784[];
extern const u8 data_ov068_0227676c[];
extern const u8 data_ov068_02276744[];
extern const u8 data_ov068_02276754[];
extern const u8 data_ov068_0227678c[];

/* The behaviour member's and the villager's functions used here (outdoor_villager.h has more). */

/* The update's step table and the exchanges' table (each filled once, bit 0 of its guard), and
 * the member pointers they are filled from. */
extern u32 data_ov068_022782b8;
extern MemberPointer data_ov068_022783dc[4];
extern const MemberPointer data_ov068_02277048, data_ov068_02277060, data_ov068_02277068, data_ov068_02277078;
extern u32 data_ov068_0227827c;
extern MemberPointer data_ov068_0227844c[7];
extern const MemberPointer data_ov068_02276fb0, data_ov068_02276fc0, data_ov068_02276fd8, data_ov068_02276fe8,
    data_ov068_02276ff0, data_ov068_02277000, data_ov068_02277018;

#define CHAT_EXCHANGES 7
#define CHAT_TIERS 5
#define CHAT_WAIT_PAST_TABLE 100
#define CHAT_STRANGER_NEAR 0x6000 /* how near the player breaks up a chat */
#define CHAT_POOR_TIER 4
#define CHAT_CLOSE 0x3c00  /* how near the two must stay */
#define CHAT_ACT_FRAMES 20 /* the wait left at least for an act */
#define CHAT_ACT_ONE_IN 32
#define CHAT_DO_19 19
#define CHAT_MOTION_TURN 3
#define CHAT_MOTION_ACT 8
#define CHAT_MOTION_SHOW 20
#define CHAT_PRIORITY 1
#define CHAT_ANIM_FLAGS 0x19c /* u8: the body animation's FrameCtrl flags */
#define CHAT_SPEAKER 0x28     /* u8 *: the villager who shows its new item, in the behaviour */
/* Clothes of codes 0x12a8 to 0x12af are a design. */
#define CHAT_DESIGN_CLOTHES_FIRST 0x12a8
#define CHAT_DESIGN_CLOTHES_LAST 0x12af
#define CHAT_ITEM_1380_FIRST 0x1380
#define CHAT_ITEM_1380_LAST 0x139f
#define CHAT_TOWN_PLACES 8

static u8 *chat_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

/* The scene motion of a villager (0x564), also of a null one (as the game computes it). */
static SceneMotion *chat_motion(u8 *villager)
{
    return (SceneMotion *) (uintptr_t) ((uintptr_t) villager + OUTDOOR_VILLAGER_MOTION);
}

static VillagerMood *chat_mood(u8 *villager)
{
    return (VillagerMood *) (uintptr_t) ((uintptr_t) villager + OUTDOOR_VILLAGER_MOOD);
}

static u8 *chat_partner(u8 *villager)
{
    return (u8 *) (uintptr_t) VillagerSceneObject_Word644((u32 *) (void *) villager);
}

static u8 **chat_speaker(OutdoorVillagerBehaviour *self)
{
    return (u8 **) (void *) chat_at(self, CHAT_SPEAKER);
}

/* The code at vtable slot `slot` of `object`. */
static uintptr_t chat_slot(u8 *object, u32 slot)
{
    u32 vtable = *(const u32 *) (const void *) object;
    return *(const u32 *) (uintptr_t) (vtable + slot);
}

/* Its town record (vtable slot 0x64). */
static u8 *chat_record(u8 *villager)
{
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) chat_slot(villager, OUTDOOR_VILLAGER_SLOT_RECORD))(villager);
}

/* The partner told the pairing ends (vtable slot 0xbc, OutdoorVillager_Unpair); whether it was
 * paired. */
static int chat_unpair(u8 *partner)
{
    return ((int (*)(u8 *)) chat_slot(partner, 0xbc))(partner);
}

/* This one unpaired after its partner was: behaviour 19 and the pairing's cooldown. */
static void chat_part_for_19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    VillagerSceneObject_SetWord644((u32 *) (void *) villager, 0);
    VillagerSceneObject_SetByte648(villager, 0);
    OutdoorVillagerBehaviour_Start(self, villager, CHAT_DO_19);
    OutdoorVillagerWalks_StartCooldown(self);
}

/* The chat stopped: the byte at 0x838 set for both; step 3. */
static void chat_stop(OutdoorVillagerBehaviour *self, u8 *villager, u8 *partner)
{
    VillagerSceneObject_SetByte838(villager);
    if (partner != NULL) {
        VillagerSceneObject_SetByte838(partner);
    }
    self->step = 3;
}

/* Whether a town record wears a design (clothes 0x12a8 to 0x12af). */
static int chat_wears_design(u8 *record)
{
    u16 clothes = *TownVillager_Clothes(record);
    return clothes >= CHAT_DESIGN_CLOTHES_FIRST && clothes <= CHAT_DESIGN_CLOTHES_LAST;
}

/* A design copied field by field (the byte of padding at its end is left). */
static void chat_copy_design(u8 *dst, const u8 *src)
{
    Design *to = (Design *) (void *) dst;
    const Design *from = (const Design *) (const void *) src;
    memcpy(to->pixels, from->pixels, DESIGN_PIXELS_SIZE);
    to->info.creator = from->info.creator;
    memcpy(to->info.title, from->info.title, sizeof(to->info.title));
    to->info.palette_and_kind = from->info.palette_and_kind;
}

/* Whether two NpcIds are the same villager: the first halfword, the 12 bytes after it and
 * the number (the personality is not compared). */
static int chat_same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* While an act (kind 8) other than 0 plays: with the body animation's flags set, once the
 * motion is done; without them, at the animation's first frame or once it is done: act 0. */
static void chat_end_act(u8 *villager)
{
    SceneMotion *motion = chat_motion(villager);
    if (SceneMotion_Kind(motion) != CHAT_MOTION_ACT) {
        return;
    }
    if (SceneMotion_ActNumber(motion) == 0) {
        return;
    }
    int ends;
    if (*chat_at(villager, CHAT_ANIM_FLAGS) != 0) {
        ends = SceneMotion_IsDone(motion) != 0;
    } else {
        u32 frame = *(const u32 *) (const void *) chat_at(villager, OUTDOOR_VILLAGER_ANIM_FRAME);
        ends = ((frame << 4) >> 16) == 0 || SceneMotion_IsDone(motion) != 0;
    }
    if (ends) {
        SceneMotion_RequestAct(motion, CHAT_PRIORITY, 0, data_020c80f8);
    }
}

/* One time in 32 while at least 20 frames of the chat are left, an act of the table. */
static void chat_maybe_act(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->wait >= CHAT_ACT_FRAMES && MainRandom_Below(CHAT_ACT_ONE_IN) == 0) {
        u8 act = data_ov068_0227679c[MainRandom_Below(8)];
        SceneMotion_RequestAct(chat_motion(villager), CHAT_PRIORITY, act, data_020c80f8);
    }
}

/* func_ov068_02269a54: behaviour 9's update: Turn9, Talk9, Show9, End9. */
int OutdoorVillagerChat_Update9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[4] = {
        &data_ov068_02277048, /* OutdoorVillagerChat_Turn9 */
        &data_ov068_02277060, /* OutdoorVillagerChat_Talk9 */
        &data_ov068_02277068, /* OutdoorVillagerChat_Show9 */
        &data_ov068_02277078, /* OutdoorVillagerChat_End9 */
    };
    MemberTable_InitOnce(&data_ov068_022782b8, data_ov068_022783dc, steps, 4);
    if (self->step < 4) {
        const MemberPointer *member = &data_ov068_022783dc[self->step];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
    }
    return 0;
}
CLEAN_AS(func_ov068_02269a54, OutdoorVillagerChat_Update9)

/* func_ov068_02269ae4: the partner told the pairing ends; when it was paired, this one is
 * unpaired, resumes its saved behaviour (else 0) and its pairing's cooldown starts. */
void OutdoorVillagerChat_End9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    if (partner == NULL || chat_unpair(partner) == 0) {
        return;
    }
    VillagerSceneObject_SetWord644((u32 *) (void *) villager, 0);
    VillagerSceneObject_SetByte648(villager, 0);
    if (OutdoorVillagerBehaviour_Resume(self, villager) == 0) {
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
    }
    OutdoorVillagerWalks_StartCooldown(self);
}
CLEAN_AS(func_ov068_02269ae4, OutdoorVillagerChat_End9)

/* func_ov068_02269b38: once the speaker's motion of kind 20 is done, the moods of the villager
 * and its partner applied; step 3. */
void OutdoorVillagerChat_Show9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *speaker = *chat_speaker(self);
    if (SceneMotion_Kind(chat_motion(speaker)) != CHAT_MOTION_SHOW) {
        return;
    }
    if (SceneMotion_IsDone(chat_motion(speaker)) == 0) {
        return;
    }
    VillagerMood_Apply(chat_mood(villager));
    VillagerMood_Apply(chat_mood(chat_partner(villager)));
    self->step = 3;
}
CLEAN_AS(func_ov068_02269b38, OutdoorVillagerChat_Show9)

/* _ZN18Obj_ov068_022771c019func_ov068_02269b88Ei: the chat's exchange: the byte at 0x838 set
 * for both, then the exchanges drawn by weight (InsectDraw_PickByWeights on a copy of
 * data_ov068_02276794) and tried, each one's weight cleared once it was tried and did not
 * happen, until one happens; after seven draws without one, step 3. */
void OutdoorVillagerChat_Exchange(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const exchanges[CHAT_EXCHANGES] = {
        &data_ov068_02276fb0, /* func_ov068_0226ab58: how the pair gets on */
        &data_ov068_02276fc0, /* func_ov068_0226aad4: learning only */
        &data_ov068_02276fd8, /* OutdoorVillagerChat_PassCatchphrase */
        &data_ov068_02276fe8, /* OutdoorVillagerChat_PassDesign */
        &data_ov068_02276ff0, /* OutdoorVillagerChat_DefaultClothes */
        &data_ov068_02277000, /* OutdoorVillagerChat_DefaultCatchphrase */
        &data_ov068_02277018, /* OutdoorVillagerChat_NewDesign */
    };
    MemberTable_InitOnce(&data_ov068_0227827c, data_ov068_0227844c, exchanges, CHAT_EXCHANGES);

    u8 *partner = chat_partner(villager);
    VillagerSceneObject_SetByte838(villager);
    VillagerSceneObject_SetByte838(partner);
    u8 weights[CHAT_EXCHANGES];
    MI_CpuCopy8(data_ov068_02276794, weights, CHAT_EXCHANGES);
    int tries;
    for (tries = 0; tries < CHAT_EXCHANGES; tries++) {
        int index = InsectDraw_PickByWeights(weights, CHAT_EXCHANGES);
        if ((unsigned int) index >= CHAT_EXCHANGES) {
            continue;
        }
        const MemberPointer *member = &data_ov068_0227844c[index];
        void *object = MemberPointer_Object(member, self);
        if (((int (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager) != 0) {
            break;
        }
        weights[index] = 0;
    }
    if (tries == CHAT_EXCHANGES) {
        self->step = 3;
    }
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02269b88Ei, OutdoorVillagerChat_Exchange)

/* _ZN18Obj_ov068_022771c019func_ov068_02269c88Ei: the chat (step 1), as
 * outdoor_villager_chat.h says. With the byte at 0x648 set (it was asked to pair, not the
 * one asking) it only ends its acts.
 * QUIRK: whether the partner is ready (its motion done) is judged with this villager's act,
 * not the partner's. */
void OutdoorVillagerChat_Talk9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    if (OutdoorVillagerWalks_HasByteA05(self, villager) != 0 && VillagerSceneObject_HasByte838(villager) == 0 &&
        partner != NULL && chat_unpair(partner) != 0) {
        chat_part_for_19(self, villager);
        return;
    }
    if (VillagerSceneObject_Byte648(villager) != 0) {
        chat_end_act(villager);
        return;
    }

    int distance = OutdoorVillagerChat_PlayerDistance(self, villager);
    if (OutdoorVillagerChat_StrangerNear(self, villager, distance) != 0) {
        chat_stop(self, villager, partner);
        return;
    }
    if (OutdoorVillagerChat_BadPairNear(self, villager, distance) != 0) {
        chat_stop(self, villager, partner);
        OutdoorVillagerBonds_AskMood(self, villager, 2, 1, 1);
        if (partner != NULL) {
            OutdoorVillagerBonds_AskMood(self, partner, 2, 1, 1);
        }
        return;
    }
    if (OutdoorVillagerChat_PartnerClose(self, villager) == 0) {
        chat_stop(self, villager, partner);
        return;
    }

    SceneMotion *motion = chat_motion(villager);
    int ready = 0;
    if (SceneMotion_IsDone(motion) != 0 &&
        (SceneMotion_Kind(motion) != CHAT_MOTION_ACT || SceneMotion_ActNumber(motion) == 0)) {
        ready = 1;
    }
    int partner_ready = 0;
    if (SceneMotion_IsDone(chat_motion(partner)) != 0 &&
        (SceneMotion_Kind(motion) != CHAT_MOTION_ACT || SceneMotion_ActNumber(motion) == 0)) {
        partner_ready = 1;
    }

    if (self->wait == 0) {
        if (!ready) {
            chat_end_act(villager);
            return;
        }
        if (!partner_ready) {
            return;
        }
        if (PlayerRecords_Current() != NULL) {
            OutdoorVillagerChat_Exchange(self, villager);
            return;
        }
        if (MainRandom_Below(2) == 0) {
            OutdoorVillagerBonds_AskMoodOf(self, villager, data_ov068_02276740, 4, 2, 1);
            OutdoorVillagerBonds_AskMoodOf(self, partner, data_ov068_02276740, 4, 2, 1);
        }
        self->step = 3;
        return;
    }

    if (ready) {
        chat_maybe_act(self, villager);
    } else {
        chat_end_act(villager);
    }
    if (partner_ready) {
        chat_maybe_act(self, partner);
    }
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02269c88Ei, OutdoorVillagerChat_Talk9)

/* func_ov068_02269fd4: whether the pair gets on badly (VillagerPair_TierOf of their records,
 * 4: no tier or not both of the town) and `distance` (to the player) is under 0x6000. */
int OutdoorVillagerChat_BadPairNear(OutdoorVillagerBehaviour *self, u8 *villager, int distance)
{
    (void) self;
    u8 *partner = chat_partner(villager);
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    if (VillagerPair_TierOf(&data_021e5a2c, mine, theirs) >= CHAT_POOR_TIER) {
        return distance < CHAT_STRANGER_NEAR;
    }
    return 0;
}
CLEAN_AS(func_ov068_02269fd4, OutdoorVillagerChat_BadPairNear)

/* func_ov068_0226a020: whether a current player is set (PlayerId_IsSet), one of the pair has no
 * memory of it, and `distance` is under 0x6000.
 * QUIRK: the current player record is asked for twice. */
int OutdoorVillagerChat_StrangerNear(OutdoorVillagerBehaviour *self, u8 *villager, int distance)
{
    (void) self;
    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    if (player == NULL || PlayerId_IsSet(player) == 0) {
        return 0;
    }
    u8 *partner = chat_partner(villager);
    VillagerMemory *mine = VillagerMemory_Of(chat_record(villager), player);
    VillagerMemory *theirs = VillagerMemory_Of(chat_record(partner), player);
    if (mine != NULL && theirs != NULL) {
        return 0;
    }
    return distance < CHAT_STRANGER_NEAR;
}
CLEAN_AS(func_ov068_0226a020, OutdoorVillagerChat_StrangerNear)

/* func_ov068_0226a098: the distance from this console's player's object to the nearer of the
 * pair; 0 without the player or a partner. */
int OutdoorVillagerChat_PlayerDistance(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    u8 *partner = chat_partner(villager);
    if (player == 0 || partner == NULL) {
        return 0;
    }
    u8 *object = (u8 *) (uintptr_t) (u32) player;
    int mine = SceneObject_DistanceTo(villager, object);
    int theirs = SceneObject_DistanceTo(partner, object);
    return mine >= theirs ? theirs : mine;
}
CLEAN_AS(func_ov068_0226a098, OutdoorVillagerChat_PlayerDistance)

/* func_ov068_0226a0dc: whether the partner is within 0x3c00 of the villager on the ground
 * plane (and not at its very place). */
int OutdoorVillagerChat_PartnerClose(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    u8 *partner = chat_partner(villager);
    fx32 distance = 0;
    if (partner != NULL) {
        distance = Vec_DistanceXZ((const Vec3 *) (const void *) chat_at(villager, OUTDOOR_VILLAGER_POSITION),
                                  (const Vec3 *) (const void *) chat_at(partner, OUTDOOR_VILLAGER_POSITION));
    }
    return distance > 0 && distance < CHAT_CLOSE;
}
CLEAN_AS(func_ov068_0226a0dc, OutdoorVillagerChat_PartnerClose)

/* func_ov068_0226a114: once the turn (kind 3) is done, it stands and the chat's wait is set by
 * the pair's tier; step 1. Until then, with the byte at 0xa05 set, the partner told the
 * pairing ends and, when it was paired, this one goes to behaviour 19. */
void OutdoorVillagerChat_Turn9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    SceneMotion *motion = chat_motion(villager);
    if (SceneMotion_Kind(motion) == CHAT_MOTION_TURN && SceneMotion_IsDone(motion) != 0) {
        SceneMotion_RequestStand(motion, CHAT_PRIORITY, data_020c80f8);
        self->step = 1;
        int tier = OutdoorVillagerBonds_PairTier(self, villager);
        self->wait = tier < CHAT_TIERS ? data_ov068_022767b8[tier] : CHAT_WAIT_PAST_TABLE;
        return;
    }
    if (OutdoorVillagerWalks_HasByteA05(self, villager) != 0) {
        u8 *partner = chat_partner(villager);
        if (partner != NULL && chat_unpair(partner) != 0) {
            chat_part_for_19(self, villager);
        }
    }
}
CLEAN_AS(func_ov068_0226a114, OutdoorVillagerChat_Turn9)

/* func_ov068_0226a1b8: behaviour 9's start: a turn to the partner (the angle taken before a
 * running act's effects are reset, OutdoorVillagerObject_ResetActEffects), the watch on the partner (kind 2),
 * step 0, the byte at 0x838 cleared, its mood asked for (0, 0, applied) and its mood's sounds
 * on. */
int OutdoorVillagerChat_Start9(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    int angle = SceneObject_YawTo(villager, partner);
    OutdoorVillagerObject_ResetActEffects(villager);
    SceneMotion_Request(chat_motion(villager), CHAT_MOTION_TURN, CHAT_PRIORITY, 0, 0, 0, (s16) angle, 0, 0, data_020c80f8, 0);
    OutdoorVillagerWatch_Hold((OutdoorVillagerWatch *) (void *) chat_at(villager, OUTDOOR_VILLAGER_WATCH), villager, 2, 0,
                              (int) (uintptr_t) partner, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR, data_020c814c, 1);
    self->step = 0;
    VillagerSceneObject_ClearByte838(villager);
    OutdoorVillagerBonds_AskMood(self, villager, 0, 0, 1);
    VillagerMood_SetSoundsOn(chat_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226a1b8, OutdoorVillagerChat_Start9)

/* ---- The exchanges: each answers whether it happened (and so ends the drawing) */

/* func_ov068_0226a260: a new design for the first of the pair (the speaker): one of
 * data_021ed278's eight other than the one it wears (func_ov068_0226ac40); without one,
 * nothing (0). Else the second learns from the first, the pair's record kept, the speaker's
 * mood asked for (1, 2), the design copied onto the first's and its clothes set to it
 * (0x12a8), and the speaker shows it (kind 20); step 2. */
int OutdoorVillagerChat_NewDesign(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    u8 *speaker = OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs) == 0 ? villager : partner;
    *chat_speaker(self) = speaker;

    u8 *worn = NULL;
    if (chat_wears_design(first)) {
        worn = TownVillager_Design(first);
    }
    u8 *design = OutdoorVillagerBonds_DrawShopDesign(self, worn);
    if (design == NULL) {
        return 0;
    }
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);
    OutdoorVillagerBonds_ChangePair(self, villager, (const s8 *) data_ov068_02276784);
    OutdoorVillagerBonds_AskMood(self, speaker, 1, 2, 0);
    chat_copy_design(TownVillager_Design(first), design);
    u16 clothes = CHAT_DESIGN_CLOTHES_FIRST;
    TownVillager_SetClothes(first, &clothes);
    u16 shown = CHAT_DESIGN_CLOTHES_FIRST;
    SceneMotion_RequestKind20(chat_motion(speaker), CHAT_PRIORITY, &shown);
    self->step = 2;
    return 1;
}
CLEAN_AS(func_ov068_0226a260, OutdoorVillagerChat_NewDesign)

/* func_ov068_0226a3e0: the second's catchphrase back to its own default (its NpcId's number's,
 * NpcLookup_CatchphraseToWide, when there is one), after it learns from the first and the
 * town's record is kept; both moods asked for from data_ov068_02276738; step 3. */
int OutdoorVillagerChat_DefaultCatchphrase(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs);
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);
    OutdoorVillagerBonds_ChangeOthers(self, villager, (const s8 *) data_ov068_0227676c);

    CatchphraseWide text;
    CatchphraseWide_Construct(&text);
    if (NpcLookup_CatchphraseToWide(&text, NpcId_Number(TownVillager_NpcId(second))) != 0) {
        VillagerCatchphrase_SetFromText(second, (VillagerCatchphraseText *) (void *) &text);
    }
    OutdoorVillagerBonds_AskMoodOf(self, villager, data_ov068_02276738, 4, 2, 1);
    OutdoorVillagerBonds_AskMoodOf(self, partner, data_ov068_02276738, 4, 2, 1);
    self->step = 3;
    CatchphraseWide_Destruct(&text);
    return 1;
}
CLEAN_AS(func_ov068_0226a3e0, OutdoorVillagerChat_DefaultCatchphrase)

/* func_ov068_0226a49c: the first of the pair (the speaker) back to its own defaults: its item
 * of 0x1380 to 0x139f, unless it has one, and its clothes. When the clothes it wears differ
 * from its default (by their variant's item when they have variants), both moods asked for
 * (data_ov068_02276730, not applied), its clothes set and the speaker shows them (kind 20),
 * step 2; else both moods asked for and applied, step 3. */
int OutdoorVillagerChat_DefaultClothes(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *partner = chat_partner(villager);
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    int swapped = OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs);
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);
    *chat_speaker(self) = swapped == 0 ? villager : partner;
    OutdoorVillagerBonds_ChangeOthers(self, villager, (const s8 *) data_ov068_02276744);

    u16 item = *VillagerState_Item(VillagerStatus_StateEntry(first));
    u16 wanted;
    if (item < CHAT_ITEM_1380_FIRST || item > CHAT_ITEM_1380_LAST) {
        u16 default_item;
        VillagerData_DefaultItem1380(&default_item, first);
        wanted = default_item;
        TownVillager_SetItem1380(first, &wanted);
    }
    u16 default_clothes;
    VillagerData_DefaultClothes(&default_clothes, first);
    wanted = default_clothes;

    const u16 *clothes = TownVillager_Clothes(first);
    int same;
    if (ItemCode_HasVariant(clothes)) {
        int worn = ItemCode_VariantItem(clothes);
        same = worn == ItemCode_VariantItem(&wanted);
    } else {
        same = *clothes == wanted;
    }

    if (!same) {
        OutdoorVillagerBonds_AskMoodOf(self, villager, data_ov068_02276730, 4, 2, 0);
        OutdoorVillagerBonds_AskMoodOf(self, partner, data_ov068_02276730, 4, 2, 0);
        TownVillager_SetClothes(first, &wanted);
        SceneMotion_RequestKind20(chat_motion(*chat_speaker(self)), CHAT_PRIORITY, &wanted);
        self->step = 2;
    } else {
        OutdoorVillagerBonds_AskMoodOf(self, villager, data_ov068_02276730, 4, 2, 1);
        OutdoorVillagerBonds_AskMoodOf(self, partner, data_ov068_02276730, 4, 2, 1);
        self->step = 3;
    }
    return 1;
}
CLEAN_AS(func_ov068_0226a49c, OutdoorVillagerChat_DefaultClothes)

/* func_ov068_0226a618: the first's design passed on, when it wears one (else nothing, 0). The
 * second learns from the first. When the second already wears the same design, another
 * villager of the town is drawn instead (neither of the pair, one not wearing that design and
 * with a status, VillagerStatus_Get), or nobody. The design is copied onto the receiver's and
 * its clothes set to it (0x12a8); the pair's record is kept. Given to the second: both moods
 * asked for (1, 2), the speaker (here the second) shows it (kind 20), step 2; else both moods
 * asked for and applied, step 3. */
int OutdoorVillagerChat_PassDesign(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    *chat_speaker(self) = OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs) == 0 ? partner : villager;

    if (!chat_wears_design(first)) {
        return 0;
    }
    u8 *design = TownVillager_Design(first);
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);

    int to_second = 1;
    if (chat_wears_design(second) && Design_Equals((char *) TownVillager_Design(second), (char *) design) != 0) {
        const NpcId *giver = TownVillager_NpcId(first);
        const NpcId *other = TownVillager_NpcId(second);
        to_second = 0;
        second = NULL;
        unsigned int mask = 0;
        int count = 0;
        for (int i = 0; i < CHAT_TOWN_PLACES; i++) {
            u8 *entry = VillagerRoster_At(&data_021e5a2c, i);
            if (entry == NULL) {
                continue;
            }
            const NpcId *npc = TownVillager_NpcId(entry);
            if (NpcId_IsValid(npc) == 0 || chat_same_npc(npc, giver) || chat_same_npc(npc, other)) {
                continue;
            }
            if (chat_wears_design(entry) && Design_Equals((char *) TownVillager_Design(entry), (char *) design) != 0) {
                continue;
            }
            if (VillagerStatus_Get(entry) != 0) {
                mask = (u8) (mask | (1u << i));
                count++;
            }
        }
        int place = VillagerRoster_PickBit(mask, count, CHAT_TOWN_PLACES);
        if (ActorTable_IsKindESlot((u32) place)) {
            second = VillagerRoster_At(&data_021e5a2c, place);
        }
    }

    if (second != NULL) {
        chat_copy_design(TownVillager_Design(second), design);
        u16 clothes = CHAT_DESIGN_CLOTHES_FIRST;
        TownVillager_SetClothes(second, &clothes);
    }
    OutdoorVillagerBonds_ChangePair(self, villager, (const s8 *) data_ov068_02276754);
    if (to_second && second != NULL) {
        OutdoorVillagerBonds_AskMood(self, villager, 1, 2, 0);
        OutdoorVillagerBonds_AskMood(self, partner, 1, 2, 0);
        u16 shown = CHAT_DESIGN_CLOTHES_FIRST;
        SceneMotion_RequestKind20(chat_motion(*chat_speaker(self)), CHAT_PRIORITY, &shown);
        self->step = 2;
    } else {
        OutdoorVillagerBonds_AskMood(self, villager, 1, 2, 1);
        OutdoorVillagerBonds_AskMood(self, partner, 1, 2, 1);
        self->step = 3;
    }
    return 1;
}
CLEAN_AS(func_ov068_0226a618, OutdoorVillagerChat_PassDesign)

/* func_ov068_0226a91c: the first's catchphrase passed on: to the second, or when the second
 * already says it, to another villager of the town drawn (neither of the pair, one not
 * saying it), or nobody. The second learns from the first, the town's record is kept, both
 * moods asked for (1, 2, applied); step 3. */
int OutdoorVillagerChat_PassCatchphrase(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *partner = chat_partner(villager);
    u8 *first = NULL;
    u8 *second = NULL;
    u8 *mine = chat_record(villager);
    u8 *theirs = chat_record(partner);
    OutdoorVillagerBonds_Sort(self, &first, &second, mine, theirs);

    Label10Text said;
    Label10Text other;
    Label10Text_Construct(&said);
    Label10Text_Construct(&other);
    VillagerCatchphrase_ToLabel(first, &said, 0);
    VillagerCatchphrase_ToLabel(second, &other, 0);
    VillagerMode_LearnFrom(second, first);
    VillagerMemory_ShareNickname(second, first, NULL);

    if (TextBase_Equals((TextBase *) (void *) &said, (TextBase *) (void *) &other) != 0) {
        const NpcId *giver = TownVillager_NpcId(first);
        const NpcId *taker = TownVillager_NpcId(second);
        unsigned int mask = 0;
        second = NULL;
        int count = 0;
        for (int i = 0; i < CHAT_TOWN_PLACES; i++) {
            u8 *entry = VillagerRoster_At(&data_021e5a2c, i);
            if (entry == NULL) {
                continue;
            }
            const NpcId *npc = TownVillager_NpcId(entry);
            if (NpcId_IsValid(npc) == 0 || chat_same_npc(npc, giver) || chat_same_npc(npc, taker)) {
                continue;
            }
            VillagerCatchphrase_ToLabel(entry, &other, 0);
            if (TextBase_Equals((TextBase *) (void *) &said, (TextBase *) (void *) &other) == 0) {
                mask = (u8) (mask | (1u << i));
                count++;
            }
        }
        int place = VillagerRoster_PickBit(mask, count, CHAT_TOWN_PLACES);
        if (ActorTable_IsKindESlot((u32) place)) {
            second = VillagerRoster_At(&data_021e5a2c, place);
        }
    }

    if (second != NULL) {
        VillagerCatchphrase_SetFromLabel(second, &said);
    }
    OutdoorVillagerBonds_ChangeOthers(self, villager, (const s8 *) data_ov068_0227678c);
    OutdoorVillagerBonds_AskMood(self, villager, 1, 2, 1);
    OutdoorVillagerBonds_AskMood(self, partner, 1, 2, 1);
    self->step = 3;
    Label10Text_Destruct(&other);
    Label10Text_Destruct(&said);
    return 1;
}
CLEAN_AS(func_ov068_0226a91c, OutdoorVillagerChat_PassCatchphrase)
