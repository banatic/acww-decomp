/* A villager out walking in the town: actor profile 0x84 (main's spawner.c,
 * Spawner_PlaceTownVillagers), whose profile record (data_ov068_022771a0) makes it with
 * OutdoorVillagerObject_New. It is a town villager scene object (main's villager_scene_slots.h)
 * of vtable data_ov068_022771c0, 0xa10 bytes in all, with these parts read here:
 *
 * - 0x838 a byte (villager_scene_object.c) behaviour 18 sets and behaviours 19, 21 and 23
 *   clear; while it is set the player may not act on it (slot 0x48);
 * - 0x898 its watch (outdoor_villager_watch.h): where it looks while free: the player, an
 *   insect or a fish shadow of overlay 3 near it;
 * - 0x8b8 its behaviour (outdoor_villager_acts.h): one of 24 at a time, each a start and an
 *   update (member functions of the behaviour, in the table data_ov068_02278484), the update
 *   stepping through steps of its own by the byte `step`;
 * - 0x9b4 a held item link (main's held_item_link.h), which the object's held item link pointer
 *   (0x628) names once it starts;
 * - 0x9f4 its effect (OutdoorVillagerEffect below);
 * - 0x9f8 the villager it is paired with while their talk starts, 0x9fc the lines its next talk
 *   says (OUTDOOR_VILLAGER_LINES_*), 0xa00 an effect handle (-1 for none), 0xa04 a byte that
 *   sends it to behaviour 18 once an event ends, 0xa05 a byte that sends it to behaviour 19,
 *   0xa06 a frame count (to 100) that sends it to behaviour 21 at 100, 0xa0c how its last
 *   behaviour wants the next talk to go (OUTDOOR_VILLAGER_REACTION_*).
 *
 * Its own vtable slots: 0x40 and 0x44 the destructors, 0x48 whether the player may act on it,
 * 0x4c told of an event, 0x54 the other question of an event (main's event_kinds.h), 0x8c told
 * it joined a talk as a speaker, 0x90 told a talk it was in ended, and 0xb4 to 0xbc its pairing
 * with another villager (the word at 0x644, villager_scene_object.h). */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_H

#include "autoload_2/vector.h"
#include "main/villager_memory_entry.h"
#include "main/villager_state.h"
#include "types.h"

/* The parts of the object, by place (main's scene_object.c and villager_scene_slots.c name the
 * base class's). */
#define OUTDOOR_VILLAGER_POSITION 0x5c        /* Vec3 */
#define OUTDOOR_VILLAGER_LAST_POSITION 0x68   /* Vec3 */
#define OUTDOOR_VILLAGER_ANIM_FRAME 0x190     /* fx32: the body animation's frame */
#define OUTDOOR_VILLAGER_ANIM 0x334           /* SpeakerAnim */
#define OUTDOOR_VILLAGER_LOOK 0x3b0           /* SceneLook */
#define OUTDOOR_VILLAGER_JOINT_16_POINT 0x478 /* Vec3 */
#define OUTDOOR_VILLAGER_FLAGS 0x4e8          /* u32 */
#define OUTDOOR_VILLAGER_EMITTER 0x514        /* SoundEmitter */
#define OUTDOOR_VILLAGER_FOOTSTEPS 0x558      /* Footsteps */
#define OUTDOOR_VILLAGER_PARTICIPANT 0x560    /* u8: the participant of the last event told */
#define OUTDOOR_VILLAGER_MOTION 0x564         /* SceneMotion */
#define OUTDOOR_VILLAGER_ACTION 0x618         /* SceneAction */
#define OUTDOOR_VILLAGER_TALK 0x680           /* VillagerTalk, a SceneBase first */
#define OUTDOOR_VILLAGER_RECORD 0x830         /* u8 *: the town record */
#define OUTDOOR_VILLAGER_MOOD 0x83c           /* VillagerMood */
#define OUTDOOR_VILLAGER_WATCH 0x898          /* OutdoorVillagerWatch */
#define OUTDOOR_VILLAGER_BEHAVIOUR 0x8b8      /* OutdoorVillagerBehaviour */
#define OUTDOOR_VILLAGER_LINK 0x9b4           /* HeldItemLink */
#define OUTDOOR_VILLAGER_EFFECT 0x9f4         /* OutdoorVillagerEffect */
#define OUTDOOR_VILLAGER_PARTNER 0x9f8        /* u8 *: the villager paired with, or null */
#define OUTDOOR_VILLAGER_LINES 0x9fc          /* u32: OUTDOOR_VILLAGER_LINES_* */
#define OUTDOOR_VILLAGER_EFFECT_HANDLE 0xa00  /* s32: -1 for none */
#define OUTDOOR_VILLAGER_BYTE_A04 0xa04       /* u8 */
#define OUTDOOR_VILLAGER_COUNT_A06 0xa06      /* u16 */
#define OUTDOOR_VILLAGER_REACTION 0xa0c       /* u32: OUTDOOR_VILLAGER_REACTION_* */

/* The vtable slots called here. */
#define OUTDOOR_VILLAGER_SLOT_MAY_ACT 0x48
#define OUTDOOR_VILLAGER_SLOT_RECORD 0x64
#define OUTDOOR_VILLAGER_SLOT_SPEAKER_JOINED 0x8c
#define OUTDOOR_VILLAGER_SLOT_CAN_PAIR 0xb4

/* The field actor of this console's player. */
#define OUTDOOR_VILLAGER_PLAYER_ACTOR 4

/* The behaviours (the table data_ov068_02278484) started here. */
#define OUTDOOR_VILLAGER_DO_DEFAULT 0 /* what it does when no behaviour is saved to resume */
#define OUTDOOR_VILLAGER_DO_3 3       /* after an event, when the reaction was 0 */
#define OUTDOOR_VILLAGER_DO_TALK 5    /* told of event 0: its talk started */
#define OUTDOOR_VILLAGER_DO_6 6       /* told of event 5 */
#define OUTDOOR_VILLAGER_DO_7 7
#define OUTDOOR_VILLAGER_DO_STARTS 8   /* told an event starts (3) */
#define OUTDOOR_VILLAGER_DO_PAIRED 9   /* paired with another villager (slot 0xb8) */
#define OUTDOOR_VILLAGER_DO_SPEAKER 10 /* joined a talk as a speaker (slot 0x8c) */
/* As 3, for the villager VillagerState_GetIndex162 names or with a status of 3 to 7. */
#define OUTDOOR_VILLAGER_DO_12 12
#define OUTDOOR_VILLAGER_DO_14 14 /* told of event 1 after reaction 0 */
#define OUTDOOR_VILLAGER_DO_18 18 /* after an event while the byte at 0xa04 is set */
#define OUTDOOR_VILLAGER_DO_20 20 /* told of event 1 after reaction 1 */
#define OUTDOOR_VILLAGER_DO_22 22 /* told of event 1 after reaction 2 */

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define OUTDOOR_VILLAGER_EVENT_0 0
#define OUTDOOR_VILLAGER_EVENT_1 1
#define OUTDOOR_VILLAGER_EVENT_STARTS 3
#define OUTDOOR_VILLAGER_EVENT_REFUSED 4
#define OUTDOOR_VILLAGER_EVENT_5 5
#define OUTDOOR_VILLAGER_EVENT_ENDED 8

/* What the last behaviour wants of the next talk (0xa0c): the lines and the behaviour event 1
 * gives. Behaviour 19 sets 1, behaviour 21 sets 2, the talks they lead to set 3. */
#define OUTDOOR_VILLAGER_REACTION_0 0
#define OUTDOOR_VILLAGER_REACTION_1 1
#define OUTDOOR_VILLAGER_REACTION_2 2
#define OUTDOOR_VILLAGER_REACTION_NONE 3

/* The lines its talk says (VillagerTalkScene_Start's `lines`, 0x9fc). */
#define OUTDOOR_VILLAGER_LINES_DEFAULT 0
#define OUTDOOR_VILLAGER_LINES_PAIRED 1     /* paired with another villager */
#define OUTDOOR_VILLAGER_LINES_DOING_7 2    /* while behaviour 7 runs */
#define OUTDOOR_VILLAGER_LINES_BYTE_A04 0xe /* while the byte at 0xa04 is set */
#define OUTDOOR_VILLAGER_LINES_REACTION_0 0xd
#define OUTDOOR_VILLAGER_LINES_REACTION_1 0xf
#define OUTDOOR_VILLAGER_LINES_REACTION_2 0x10

/* Its effect (0x9f4): while it is the villager the state table names at 0x160
 * (VillagerCheck_IsIndex160), effect 0x81 at its joint 16 every 15 to 29 frames. The countdown
 * runs down with the wait (OutdoorVillagerEffect_Tick); while it is not 0, the overlay's choice
 * of a behaviour (func_ov068_0226befc) may start behaviour 11. */
typedef struct OutdoorVillagerEffect {
    s8 wait;       /* 0x00: frames to the next effect; -1 while it is not that villager */
    u8 unk_01;     /* 0x01 */
    u16 countdown; /* 0x02 */
} OutdoorVillagerEffect;

/* The behaviour member (0x8b8, 0xfc bytes): the parts read and written in these files. */
typedef struct OutdoorVillagerBehaviour {
    u8 unk_00[0x10];
    s32 current;       /* 0x10: the behaviour running, 0 to 23 */
    const void *entry; /* 0x14: its row of data_ov068_02278484 */
    s32 resume;        /* 0x18: the behaviour to resume (24 for none) */
    u8 step;           /* 0x1c: the step of its update */
    u8 unk_1d[3];
    s32 wait;     /* 0x20: frames a step waits */
    s32 cooldown; /* 0x24: frames before it may be paired again */
    u8 unk_28[0x10];
    u8 count_38; /* 0x38: the times behaviour 19 started while `hold_3a` ran */
    u8 unk_39;
    u16 hold_3a; /* 0x3a: 1200 when behaviour 19 ends without reaction 1 */
    u8 unk_3c[0xa4];
    u8 shown; /* 0xe0: behaviour 23 ran */
    u8 unk_e1[0x13];
    s32 unk_f4; /* 0xf4: 1200 when a reaction's talk ends */
    u8 unk_f8[4];
} OutdoorVillagerBehaviour;

/* The behaviour member's functions and the villager's used in these files (Clean ones in
 * outdoor_villager_behaviour.c, outdoor_villager_records.c and outdoor_villager_object.c;
 * outdoor_villager_acts.h has the steps). */
/* Starts behaviour `index` (0 to 23; others are ignored): its start runs with `villager`. */
void OutdoorVillagerBehaviour_Start(OutdoorVillagerBehaviour *self, u8 *villager, int index);
/* Starts the behaviour saved to resume (when one is); whether one was. */
int OutdoorVillagerBehaviour_Resume(OutdoorVillagerBehaviour *self, u8 *villager);
/* The behaviour running saved to resume, and the one to resume set. */
void OutdoorVillagerBehaviour_SaveResume(OutdoorVillagerBehaviour *self);
void OutdoorVillagerBehaviour_SetResume(OutdoorVillagerBehaviour *self, int index);
/* Whether behaviour 0 runs and the cooldown is out. */
int OutdoorVillagerBehaviour_IsIdle(OutdoorVillagerBehaviour *self);
/* The member's destructor. */
OutdoorVillagerBehaviour *OutdoorVillagerBehaviour_Destruct(OutdoorVillagerBehaviour *self);
/* With an act of kind 8 running whose number is not 0, act 0's first part on its act effects. */
void OutdoorVillagerObject_ResetActEffects(u8 *villager);
/* Byte 0x18 of the state entry of its town record (VillagerState_GetByte18), 0 without one. */
u8 OutdoorVillagerRecords_Byte18(u8 *villager);
/* The tally of the state entry of its town record (VillagerState_Tally), or null. */
VillagerTally *OutdoorVillagerRecords_Tally(u8 *villager);
/* Its memory of this console's player (VillagerMemory_Of), or null. */
VillagerMemory *OutdoorVillagerRecords_MemoryOfPlayer(u8 *villager);

u8 *OutdoorVillager_Destruct(u8 *object);
u8 *OutdoorVillager_DestructDelete(u8 *object);
void OutdoorVillager_OnTalkEnd(u8 *object);
void OutdoorVillager_OnSpeakerJoined(u8 *object);
int OutdoorVillager_Unpair(u8 *object);
int OutdoorVillager_Pair(u8 *object, u8 *partner);
int OutdoorVillager_CanPair(u8 *object);
void OutdoorVillager_OnEvent(u8 *object, int code, int participant);
int OutdoorVillager_Ask54(u8 *object, u8 *other);
int OutdoorVillager_MayAct(u8 *object);

void OutdoorVillagerEffect_SetCountdown(OutdoorVillagerEffect *effect, int frames);
int OutdoorVillagerEffect_Countdown(OutdoorVillagerEffect *effect);
void OutdoorVillagerEffect_Stop(OutdoorVillagerEffect *effect, u8 *villager);
void OutdoorVillagerEffect_Tick(OutdoorVillagerEffect *effect, u8 *villager);
void OutdoorVillagerEffect_Init(OutdoorVillagerEffect *effect);
void OutdoorVillagerEffect_Destruct(OutdoorVillagerEffect *effect);
void OutdoorVillagerEffect_Construct(OutdoorVillagerEffect *effect);

#endif
