/* A villager out walking in the town: its destructors, its own vtable slots and its effect
 * (outdoor_villager.h). */
#include "outdoor_villager.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/held_item_link.h"
#include "main/main_random.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/session_players.h"
#include "main/villager_checks.h"
#include "main/villager_entry.h"
#include "main/villager_home.h"
#include "main/villager_mood.h"
#include "main/villager_scene_object.h"
#include "main/villager_scene_slots.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_talk_scene.h"
#include "outdoor_villager_watch.h"
#include "outdoor_villager_walks.h"

static_assert(offsetof(OutdoorVillagerEffect, countdown) == 0x02, "countdown");
static_assert(sizeof(OutdoorVillagerEffect) == 0x04, "effect size");
static_assert(offsetof(OutdoorVillagerBehaviour, current) == 0x10, "current");
static_assert(offsetof(OutdoorVillagerBehaviour, resume) == 0x18, "resume");
static_assert(offsetof(OutdoorVillagerBehaviour, step) == 0x1c, "step");
static_assert(offsetof(OutdoorVillagerBehaviour, wait) == 0x20, "wait");
static_assert(offsetof(OutdoorVillagerBehaviour, cooldown) == 0x24, "cooldown");
static_assert(offsetof(OutdoorVillagerBehaviour, count_38) == 0x38, "count 0x38");
static_assert(offsetof(OutdoorVillagerBehaviour, hold_3a) == 0x3a, "hold 0x3a");
static_assert(offsetof(OutdoorVillagerBehaviour, shown) == 0xe0, "shown");
static_assert(offsetof(OutdoorVillagerBehaviour, unk_f4) == 0xf4, "0xf4");
static_assert(sizeof(OutdoorVillagerBehaviour) == 0xfc, "behaviour size");

/* The class's vtable. */
extern const u8 data_ov068_022771c0[];
/* A copy of data_020ca4cc[0] (main's scene_object_base.c), made when the overlay starts: half
 * the angle within which a viewer must face an object to act on it. */
extern s16 data_ov068_02278260;
/* An angle: how far from facing this console's player the player may still act on it while
 * the byte at 0xa04 is set. */
extern s16 data_020c80f0;

/* The effect set its effect plays, and the frames between two (a random part, then the
 * least). */
#define OUTDOOR_VILLAGER_EFFECT_SET 0x81
#define OUTDOOR_VILLAGER_EFFECT_FIRST_DRAW 15
#define OUTDOOR_VILLAGER_EFFECT_DRAW 10
#define OUTDOOR_VILLAGER_EFFECT_LEAST 15
#define OUTDOOR_VILLAGER_EFFECT_OFF (-1)

/* The distances of OutdoorVillager_CanPair and OutdoorVillager_Ask54. */
#define OUTDOOR_VILLAGER_PAIR_PLAYER_NEAR 0x6000
#define OUTDOOR_VILLAGER_ASK_NEAR 0x5000
#define OUTDOOR_VILLAGER_ASK_FAR 0xe000

/* What a reaction-1 or no-reaction talk's end does to the record's byte 0x1e. */
#define OUTDOOR_VILLAGER_ENDED_BYTE_1E (-3)

static u8 *ov_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static u32 *ov_word(void *object, u32 offset)
{
    return (u32 *) (void *) ov_at(object, offset);
}

static OutdoorVillagerBehaviour *ov_behaviour(u8 *object)
{
    return (OutdoorVillagerBehaviour *) (void *) ov_at(object, OUTDOOR_VILLAGER_BEHAVIOUR);
}

static SceneBase *ov_talk(u8 *object)
{
    return (SceneBase *) (void *) ov_at(object, OUTDOOR_VILLAGER_TALK);
}

/* Its town record, as kept at 0x830. */
static u8 *ov_town_record(u8 *object)
{
    return *(u8 **) (void *) ov_at(object, OUTDOOR_VILLAGER_RECORD);
}

/* The code at vtable slot `slot` of `object`. */
static uintptr_t ov_slot(void *object, u32 slot)
{
    u32 vtable = *(const u32 *) object;
    return *(const u32 *) (uintptr_t) (vtable + slot);
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *ov_record(u8 *object)
{
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) ov_slot(object, OUTDOOR_VILLAGER_SLOT_RECORD))(object);
}

/* ---- The destructors */

/* func_ov068_022667e0 (slot 0x40): its members from the last to the first, then the town
 * villager's body (VillagerSceneObject_DestructBody). Returns the object. */
u8 *OutdoorVillager_Destruct(u8 *object)
{
    *(const u8 **) (void *) object = data_ov068_022771c0;
    OutdoorVillagerEffect_Destruct((OutdoorVillagerEffect *) (void *) ov_at(object, OUTDOOR_VILLAGER_EFFECT));
    HeldItemLink_Destruct((HeldItemLink *) (void *) ov_at(object, OUTDOOR_VILLAGER_LINK));
    OutdoorVillagerBehaviour_Destruct(ov_behaviour(object));
    OutdoorVillagerWatch_Destruct((OutdoorVillagerWatch *) (void *) ov_at(object, OUTDOOR_VILLAGER_WATCH));
    VillagerSceneObject_DestructBody(object);
    return object;
}
CLEAN_AS(func_ov068_022667e0, OutdoorVillager_Destruct)

/* func_ov068_0226682c (slot 0x44): the same, then the object freed (Heap_FreeAux). */
u8 *OutdoorVillager_DestructDelete(u8 *object)
{
    OutdoorVillager_Destruct(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov068_0226682c, OutdoorVillager_DestructDelete)

/* ---- The talks and the pairing */

/* func_ov068_02266cf4 (slot 0x90): told a talk it was in ended: its mood applied, the saved
 * behaviour resumed (else behaviour 0), unpaired, and the pairing's cooldown started. */
void OutdoorVillager_OnTalkEnd(u8 *object)
{
    OutdoorVillagerBehaviour *behaviour = ov_behaviour(object);
    VillagerMood_Apply((VillagerMood *) (void *) ov_at(object, OUTDOOR_VILLAGER_MOOD));
    if (OutdoorVillagerBehaviour_Resume(behaviour, object) == 0) {
        OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_DEFAULT);
    }
    VillagerSceneObject_SetWord644((u32 *) (void *) object, 0);
    VillagerSceneObject_SetByte648(object, 0);
    OutdoorVillagerWalks_StartCooldown(behaviour);
}
CLEAN_AS(func_ov068_02266cf4, OutdoorVillager_OnTalkEnd)

/* func_ov068_02266d40 (slot 0x8c): told it joined a talk as a speaker: behaviour 10. */
void OutdoorVillager_OnSpeakerJoined(u8 *object)
{
    OutdoorVillagerBehaviour_Start(ov_behaviour(object), object, OUTDOOR_VILLAGER_DO_SPEAKER);
}
CLEAN_AS(func_ov068_02266d40, OutdoorVillager_OnSpeakerJoined)

/* func_ov068_02266d54 (slot 0xbc): when paired, the pairing ends: a running act's effects
 * reset (OutdoorVillagerObject_ResetActEffects), the saved behaviour resumed (else behaviour 0), the cooldown
 * started, and unpaired; 1. Unpaired already: 0. */
int OutdoorVillager_Unpair(u8 *object)
{
    OutdoorVillagerBehaviour *behaviour = ov_behaviour(object);
    if (VillagerSceneObject_HasWord644(object) == 0) {
        return 0;
    }
    OutdoorVillagerObject_ResetActEffects(object);
    if (OutdoorVillagerBehaviour_Resume(behaviour, object) == 0) {
        OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_DEFAULT);
    }
    OutdoorVillagerWalks_StartCooldown(behaviour);
    VillagerSceneObject_SetWord644((u32 *) (void *) object, 0);
    VillagerSceneObject_SetByte648(object, 0);
    return 1;
}
CLEAN_AS(func_ov068_02266d54, OutdoorVillager_Unpair)

/* func_ov068_02266da8 (slot 0xb8): paired with `partner` when its slot 0xb4 agrees: the
 * partner kept at 0x644, the byte at 0x648 set, the behaviour running saved to resume and
 * behaviour 9 started; whether it was. */
int OutdoorVillager_Pair(u8 *object, u8 *partner)
{
    OutdoorVillagerBehaviour *behaviour = ov_behaviour(object);
    if (((int (*)(u8 *)) ov_slot(object, OUTDOOR_VILLAGER_SLOT_CAN_PAIR))(object) == 0) {
        return 0;
    }
    VillagerSceneObject_SetWord644((u32 *) (void *) object, (u32) (uintptr_t) partner);
    VillagerSceneObject_SetByte648(object, 1);
    OutdoorVillagerBehaviour_SaveResume(behaviour);
    OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_PAIRED);
    return 1;
}
CLEAN_AS(func_ov068_02266da8, OutdoorVillager_Pair)

/* func_ov068_02266df4 (slot 0xb4): whether it may be paired: with a memory of this console's
 * player (OutdoorVillagerRecords_MemoryOfPlayer) that is in use, or without one while the player is not within
 * 0x6000 of it; and its action idle, behaviour 0 running with the cooldown out, not paired,
 * and no town event (11) when it started.
 * QUIRK: with a current player record the memory is looked up a second time. */
int OutdoorVillager_CanPair(u8 *object)
{
    VillagerMemory *memory = OutdoorVillagerRecords_MemoryOfPlayer(object);
    if (PlayerRecords_Current() != NULL) {
        memory = OutdoorVillagerRecords_MemoryOfPlayer(object);
    }
    if (memory == NULL) {
        if (SceneObject_IsNearActor(object, OUTDOOR_VILLAGER_PAIR_PLAYER_NEAR, OUTDOOR_VILLAGER_PLAYER_ACTOR) != 0) {
            return 0;
        }
    } else if (VillagerMemoryEntry_InUse(memory) == 0) {
        return 0;
    }
    if (SceneAction_IsBusy((const SceneAction *) (void *) ov_at(object, OUTDOOR_VILLAGER_ACTION)) != 0) {
        return 0;
    }
    if (OutdoorVillagerBehaviour_IsIdle(ov_behaviour(object)) == 0) {
        return 0;
    }
    if (VillagerSceneObject_HasWord644(object) != 0) {
        return 0;
    }
    return VillagerSceneObject_Event(object) == VILLAGER_SCENE_OBJECT_NO_EVENT;
}
CLEAN_AS(func_ov068_02266df4, OutdoorVillager_CanPair)

/* ---- The events */

/* The lines of its next talk when an event starts: paired, behaviour 7 running, the byte at
 * 0xa04 set, else by the town event when it started (none: 0). */
static u32 ov_lines_for_event(u8 *object)
{
    static const u8 by_event[10] = {5, 3, 4, 6, 7, 8, 9, 10, 11, 11};
    int event = VillagerSceneObject_Event(object);
    if (event < 10) {
        return by_event[event];
    }
    return OUTDOOR_VILLAGER_LINES_DEFAULT;
}

/* The talk of the event, with `lines`, and this console's player's object as its motion
 * argument. */
static void ov_start_talk(u8 *object, u32 lines)
{
    VillagerTalkScene_Start((VillagerTalk *) (void *) ov_at(object, OUTDOOR_VILLAGER_TALK), object, lines);
    SceneBase_SetMotionArg(ov_talk(object), SceneObject_ActorObject(object, OUTDOOR_VILLAGER_PLAYER_ACTOR));
}

/* After an event that kept it at reaction 0: it stands at the middle of its home's tile,
 * then behaviour 12 (for the villager VillagerState_GetIndex162 names or a status of 3 to
 * 7) or 3. */
static void ov_ended_reaction_0(u8 *object)
{
    OutdoorVillagerBehaviour *behaviour = ov_behaviour(object);
    int status = VillagerStatus_Get(ov_record(object));
    VillagerPlot *home = VillagerHome_Tile(ov_record(object));
    Vec3 *position = (Vec3 *) (void *) ov_at(object, OUTDOOR_VILLAGER_POSITION);
    Vec3 *last = (Vec3 *) (void *) ov_at(object, OUTDOOR_VILLAGER_LAST_POSITION);
    AcreTile_TileCentre(position, home->x, home->z);
    last->x = position->x;
    last->y = position->y;
    last->z = position->z;
    int named = VillagerState_GetIndex162();
    if (named == VillagerStatus_Index(ov_record(object)) || (unsigned int) (status - 3) <= 4) {
        OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_12);
    } else {
        OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_3);
    }
}

/* func_ov068_02266f44 (slot 0x4c): told of an event (`participant` is the base class's), then
 * the base class's slot (SceneObject_Vfunc4c):
 * - 3, an event starts: the participant kept at 0x560; the lines of the talk to come: paired
 *   (the partner is kept at 0x9f8 and told it joined as a speaker, its slot 0x8c), behaviour 7
 *   running, the byte at 0xa04 set, else by the town event (ov_lines_for_event); with the
 *   default lines the tally of its record's state entry counts one; behaviour 8;
 * - 1: by the reaction, its lines and behaviour (0: 0xd and 14, 1: 0xf and 20, 2: 0x10 and
 *   22, else the lines kept and behaviour 5); the talk starts with them;
 * - 0: the participant kept, the talk starts with the lines kept (the partner as its second
 *   speaker), behaviour 5; after lines 2 the record's byte 0x1e is cleared; partner and lines
 *   forgotten;
 * - 5: the participant kept, the behaviour running saved to resume, behaviour 6;
 * - 8, the event ended: by the reaction: 0, home (ov_ended_reaction_0); 2, behaviour 0;
 *   either then reaction none; otherwise behaviour 18 with the byte at 0xa04 set, else the
 *   saved behaviour (or 0) and the record's tally started; then the object's approach set
 *   back (SceneObjectBase_DefaultApproach) and the record's byte 0x1e lowered by 3;
 * - 4, refused: behaviour 18 with the byte at 0xa04 set, else the saved behaviour (or 0). */
void OutdoorVillager_OnEvent(u8 *object, int code, int participant)
{
    OutdoorVillagerBehaviour *behaviour = ov_behaviour(object);
    u32 *lines = ov_word(object, OUTDOOR_VILLAGER_LINES);
    u32 *partner = ov_word(object, OUTDOOR_VILLAGER_PARTNER);
    u32 *reaction = ov_word(object, OUTDOOR_VILLAGER_REACTION);
    u8 *byte_a04 = ov_at(object, OUTDOOR_VILLAGER_BYTE_A04);

    switch (code) {
        case OUTDOOR_VILLAGER_EVENT_STARTS:
            *ov_at(object, OUTDOOR_VILLAGER_PARTICIPANT) = (u8) participant;
            if (VillagerSceneObject_HasWord644(object) != 0) {
                *lines = OUTDOOR_VILLAGER_LINES_PAIRED;
                *partner = VillagerSceneObject_Word644((u32 *) (void *) object);
                u8 *other = (u8 *) (uintptr_t) *partner;
                ((void (*)(u8 *)) ov_slot(other, OUTDOOR_VILLAGER_SLOT_SPEAKER_JOINED))(other);
            } else if (OutdoorVillagerWalks_IsDoing(behaviour, OUTDOOR_VILLAGER_DO_7) != 0) {
                *lines = OUTDOOR_VILLAGER_LINES_DOING_7;
            } else if (*byte_a04 != 0) {
                *lines = OUTDOOR_VILLAGER_LINES_BYTE_A04;
            } else {
                *lines = ov_lines_for_event(object);
            }
            if (*lines == OUTDOOR_VILLAGER_LINES_DEFAULT) {
                VillagerTally *tally = OutdoorVillagerRecords_Tally(object);
                if (tally != NULL) {
                    VillagerTally_Count(tally);
                }
            }
            OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_STARTS);
            break;
        case OUTDOOR_VILLAGER_EVENT_1: {
            int next = OUTDOOR_VILLAGER_DO_TALK;
            switch (*reaction) {
                case OUTDOOR_VILLAGER_REACTION_0:
                    next = OUTDOOR_VILLAGER_DO_14;
                    *lines = OUTDOOR_VILLAGER_LINES_REACTION_0;
                    break;
                case OUTDOOR_VILLAGER_REACTION_1:
                    next = OUTDOOR_VILLAGER_DO_20;
                    *lines = OUTDOOR_VILLAGER_LINES_REACTION_1;
                    break;
                case OUTDOOR_VILLAGER_REACTION_2:
                    next = OUTDOOR_VILLAGER_DO_22;
                    *lines = OUTDOOR_VILLAGER_LINES_REACTION_2;
                    break;
                default:
                    break;
            }
            ov_start_talk(object, *lines);
            OutdoorVillagerBehaviour_Start(behaviour, object, next);
            break;
        }
        case OUTDOOR_VILLAGER_EVENT_0:
            *ov_at(object, OUTDOOR_VILLAGER_PARTICIPANT) = (u8) participant;
            ov_start_talk(object, *lines);
            if (*partner != 0) {
                SceneBase_SetSecondSpeaker(ov_talk(object), (u8 *) (uintptr_t) *partner);
            }
            OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_TALK);
            if (*lines == OUTDOOR_VILLAGER_LINES_DOING_7 && ov_record(object) != NULL) {
                VillagerEntry_ClearByte1E(ov_record(object));
            }
            *partner = 0;
            *lines = OUTDOOR_VILLAGER_LINES_DEFAULT;
            break;
        case OUTDOOR_VILLAGER_EVENT_5:
            *ov_at(object, OUTDOOR_VILLAGER_PARTICIPANT) = (u8) participant;
            OutdoorVillagerBehaviour_SaveResume(behaviour);
            OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_6);
            break;
        case OUTDOOR_VILLAGER_EVENT_ENDED:
            if (*reaction == OUTDOOR_VILLAGER_REACTION_0) {
                ov_ended_reaction_0(object);
                *reaction = OUTDOOR_VILLAGER_REACTION_NONE;
            } else if (*reaction == OUTDOOR_VILLAGER_REACTION_2) {
                OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_DEFAULT);
                *reaction = OUTDOOR_VILLAGER_REACTION_NONE;
            } else if (*byte_a04 != 0) {
                OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_18);
            } else {
                if (OutdoorVillagerBehaviour_Resume(behaviour, object) == 0) {
                    OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_DEFAULT);
                }
                VillagerTally *tally = OutdoorVillagerRecords_Tally(object);
                if (tally != NULL) {
                    VillagerTally_Start(tally);
                }
            }
            SceneObjectBase_DefaultApproach((SceneObjectBase *) (void *) object);
            if (ov_record(object) != NULL) {
                VillagerEntry_AddByte1E(ov_record(object), OUTDOOR_VILLAGER_ENDED_BYTE_1E);
            }
            break;
        case OUTDOOR_VILLAGER_EVENT_REFUSED:
            if (*byte_a04 != 0) {
                OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_18);
            } else if (OutdoorVillagerBehaviour_Resume(behaviour, object) == 0) {
                OutdoorVillagerBehaviour_Start(behaviour, object, OUTDOOR_VILLAGER_DO_DEFAULT);
            }
            break;
        default:
            break;
    }
    SceneObject_Vfunc4c(object, code, participant);
}
CLEAN_AS(func_ov068_02266f44, OutdoorVillager_OnEvent)

/* func_ov068_022672a0 (slot 0x54): whether `other` may start an event with it from a
 * distance: its slot 0x48 agrees (OutdoorVillager_MayAct), the byte at 0x838 is clear,
 * behaviour 0 runs, byte 0x18 of its record's state entry is 0 or 1, `other` is not
 * within 0x5000 but within 0xe000, and it faces `other` within data_ov068_02278260 either way
 * (SceneObjectBase_Faces). The state byte is read first. */
int OutdoorVillager_Ask54(u8 *object, u8 *other)
{
    s16 half_angle = data_ov068_02278260;
    unsigned int level = OutdoorVillagerRecords_Byte18(object);
    if (((int (*)(u8 *, u8 *)) ov_slot(object, OUTDOOR_VILLAGER_SLOT_MAY_ACT))(object, other) == 0) {
        return 0;
    }
    if (VillagerSceneObject_HasByte838(object) != 0) {
        return 0;
    }
    if (OutdoorVillagerWalks_IsDoing(ov_behaviour(object), OUTDOOR_VILLAGER_DO_DEFAULT) == 0) {
        return 0;
    }
    if (level > 1) {
        return 0;
    }
    if (SceneObject_IsNear(object, other, OUTDOOR_VILLAGER_ASK_NEAR) != 0) {
        return 0;
    }
    if (SceneObject_IsNear(object, other, OUTDOOR_VILLAGER_ASK_FAR) == 0) {
        return 0;
    }
    return SceneObjectBase_Faces((SceneObjectBase *) (void *) object, (SceneObjectBase *) (void *) other, (s16) -half_angle,
                                 half_angle) != 0;
}
CLEAN_AS(func_ov068_022672a0, OutdoorVillager_Ask54)

/* func_ov068_02267330 (slot 0x48): whether the player may act on it: its action idle and the byte
 * at 0x838 clear; with the byte at 0xa04 set, also this console's
 * player's object (when there is one) no further than data_020c80f0 either way of where it
 * faces (SceneObject_AngleTo).
 * QUIRK: the angle's size is taken as a 16-bit value: -0x8000 stays negative and passes. */
int OutdoorVillager_MayAct(u8 *object)
{
    if (SceneAction_IsBusy((const SceneAction *) (void *) ov_at(object, OUTDOOR_VILLAGER_ACTION)) != 0 ||
        VillagerSceneObject_HasByte838(object) != 0) {
        return 0;
    }
    if (*ov_at(object, OUTDOOR_VILLAGER_BYTE_A04) != 0) {
        int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
        if (player != 0) {
            int angle = SceneObject_AngleTo(object, (u8 *) (uintptr_t) (u32) player);
            if (angle < 0) {
                angle = (s16) -angle;
            }
            if (angle > data_020c80f0) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov068_02267330, OutdoorVillager_MayAct)

/* ---- The effect */

/* func_ov068_02266e78 */
void OutdoorVillagerEffect_SetCountdown(OutdoorVillagerEffect *effect, int frames)
{
    effect->countdown = (u16) frames;
}
CLEAN_AS(func_ov068_02266e78, OutdoorVillagerEffect_SetCountdown)

/* func_ov068_02266e7c */
int OutdoorVillagerEffect_Countdown(OutdoorVillagerEffect *effect)
{
    return effect->countdown;
}
CLEAN_AS(func_ov068_02266e7c, OutdoorVillagerEffect_Countdown)

/* func_ov068_02266e80: no more effects, and the state table's index 0x160 cleared when it
 * names the villager (VillagerCheck_ClearIndex160IfSelf). */
void OutdoorVillagerEffect_Stop(OutdoorVillagerEffect *effect, u8 *villager)
{
    effect->wait = OUTDOOR_VILLAGER_EFFECT_OFF;
    VillagerCheck_ClearIndex160IfSelf(ov_town_record(villager));
}
CLEAN_AS(func_ov068_02266e80, OutdoorVillagerEffect_Stop)

/* func_ov068_02266e98: a frame: the wait and the countdown run down; when the wait reaches 0,
 * effect 0x81 at joint 16 and the next wait drawn (15 to 29 frames) while the state table
 * names the villager at 0x160, else no more effects; while off, a wait of 15 to 24 frames
 * drawn once it names the villager. */
void OutdoorVillagerEffect_Tick(OutdoorVillagerEffect *effect, u8 *villager)
{
    if (effect->wait > 0) {
        effect->wait--;
    }
    if (effect->countdown != 0) {
        effect->countdown--;
    }
    if (effect->wait == 0) {
        Vec3 at = *(const Vec3 *) (const void *) ov_at(villager, OUTDOOR_VILLAGER_JOINT_16_POINT);
        EffectSystem_StartOneShotSetNumberCopy(OUTDOOR_VILLAGER_EFFECT_SET, &at, NULL, NULL);
        if (VillagerCheck_IsIndex160(ov_town_record(villager)) != 0) {
            effect->wait = (s8) (MainRandom_Below(OUTDOOR_VILLAGER_EFFECT_FIRST_DRAW) + OUTDOOR_VILLAGER_EFFECT_LEAST);
        } else {
            effect->wait = OUTDOOR_VILLAGER_EFFECT_OFF;
        }
    } else if (effect->wait == OUTDOOR_VILLAGER_EFFECT_OFF) {
        if (VillagerCheck_IsIndex160(ov_town_record(villager)) != 0) {
            effect->wait = (s8) (MainRandom_Below(OUTDOOR_VILLAGER_EFFECT_DRAW) + OUTDOOR_VILLAGER_EFFECT_LEAST);
        }
    }
}
CLEAN_AS(func_ov068_02266e98, OutdoorVillagerEffect_Tick)

/* func_ov068_02266f30 */
void OutdoorVillagerEffect_Init(OutdoorVillagerEffect *effect)
{
    effect->wait = OUTDOOR_VILLAGER_EFFECT_OFF;
    effect->countdown = 0;
}
CLEAN_AS(func_ov068_02266f30, OutdoorVillagerEffect_Init)

/* func_ov068_02266f3c: the destructor; nothing to release. */
void OutdoorVillagerEffect_Destruct(OutdoorVillagerEffect *effect)
{
    (void) effect;
}
CLEAN_AS(func_ov068_02266f3c, OutdoorVillagerEffect_Destruct)

/* func_ov068_02266f40: the constructor; nothing to set. */
void OutdoorVillagerEffect_Construct(OutdoorVillagerEffect *effect)
{
    (void) effect;
}
CLEAN_AS(func_ov068_02266f40, OutdoorVillagerEffect_Construct)
