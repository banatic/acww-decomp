/* A villager who stands in the room and talks to the player with the lines of the message file
 * "ai_shop3" (class vtable 0x02253fd4, 0xa44 bytes, made by Shop3Villager_New, the entry
 * data_ov004_02253f24 of the overlay's table of profiles): a town villager scene object (main's
 * villager_scene_slots.h). The same file gives main's greetings of a villager in a scene of
 * the set 20 at index 1 (villager_talk_greeting.c).
 *
 * Beyond the base class's members it holds its state (0x898) and its talk scene (0x89c, a town
 * villager's talk scene with a pointer back to it, vtable 0x02253f44).
 *
 * Its states (0x898), each an entry and an update function (C++ members taking the villager),
 * from the table data_ov004_02257f48 (filled at start-up by __sinit_ov004_0224e5b0), set by
 * Shop3Villager_SetState:
 *   0  talk:  it turns to the talk's partner and talks; once its action is idle the object's
 *             event ends: state 1;
 *   1  idle:  nothing;
 *   2  stand: it stands; where it starts and where it goes back to after an event. */
#ifndef CLEAN_OV004_SHOP3_VILLAGER_H
#define CLEAN_OV004_SHOP3_VILLAGER_H

#include "main/villager_talk.h"
#include "member_pointer.h"
#include "types.h"

enum Shop3VillagerState {
    SHOP3_VILLAGER_TALK = 0,
    SHOP3_VILLAGER_IDLE = 1,
    SHOP3_VILLAGER_STAND = 2,
    SHOP3_VILLAGER_STATES = 3
};

struct Shop3Villager;

/* Its talk scene (0x1a8 bytes, vtable data_ov004_02253f44). */
typedef struct Shop3VillagerTalk {
    VillagerTalk base;              /* 0x000 */
    struct Shop3Villager *villager; /* 0x1a4: the villager it belongs to */
} Shop3VillagerTalk;

/* A state's functions in data_ov004_02257f48. */
typedef struct Shop3VillagerStep {
    MemberPointer enter;  /* 0x00: int (villager); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (villager) */
} Shop3VillagerStep;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define SHOP3_VILLAGER_BASE_SIZE 0x898

typedef struct Shop3Villager {
    u8 base[SHOP3_VILLAGER_BASE_SIZE]; /* 0x000: the town villager scene object */
    s32 state;                         /* 0x898: enum Shop3VillagerState */
    Shop3VillagerTalk talk;            /* 0x89c */
} Shop3Villager;

Shop3Villager *Shop3Villager_Destroy(Shop3Villager *villager);
Shop3Villager *Shop3Villager_Delete(Shop3Villager *villager);
void Shop3Villager_OnEvent(Shop3Villager *villager, int code);
int Shop3Villager_MayAct(Shop3Villager *villager);
void Shop3VillagerTalk_OnAnswer(void);
void Shop3VillagerTalk_OnMessageEnded(void);
int Shop3VillagerTalk_Line(Shop3VillagerTalk *talk, VillagerTalkLine *out);
void Shop3VillagerTalk_Start(Shop3VillagerTalk *talk, Shop3Villager *villager);
Shop3VillagerTalk *Shop3VillagerTalk_Delete(Shop3VillagerTalk *talk);
Shop3VillagerTalk *Shop3VillagerTalk_Destroy(Shop3VillagerTalk *talk);
Shop3VillagerTalk *Shop3VillagerTalk_Construct(Shop3VillagerTalk *talk);
int Shop3Villager_UpdateIdle(void);
int Shop3Villager_UpdateTalk(Shop3Villager *villager);
int Shop3Villager_EnterTalk(Shop3Villager *villager);
int Shop3Villager_UpdateStand(void);
int Shop3Villager_EnterStand(Shop3Villager *villager);
void Shop3Villager_SetState(Shop3Villager *villager, int state);
int Shop3Villager_RunState(Shop3Villager *villager);
int Shop3Villager_Start(Shop3Villager *villager);
int Shop3Villager_Init(Shop3Villager *villager);
Shop3Villager *Shop3Villager_New(void);

#endif
