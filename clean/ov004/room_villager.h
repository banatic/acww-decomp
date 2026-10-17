/* A town villager walking about a room (class vtable 0x022539cc, 0x8dc bytes, made by
 * func_ov004_0221ee98, the overlay's profile of kinds 0x85 and 0x89): a town villager scene
 * object (main's villager_scene_slots.h) that talks through the talk scene of its base (0x680)
 * and takes part in a multiplayer session's sharing of objects (main's scene_share.h).
 *
 * Beyond the base class's members it holds its drawing member (0x898), a small state machine
 * (0x8a0, RoomVillagerMachine), the room's free tiles (0x8b4, main's tile_grid.h, built at its
 * set-up), whether its action sound was played (0x8d4) and the lines its talk scene is started
 * with (0x8d8, VillagerTalkScene_Start).
 *
 * The machine's states, each an entry and an update function (C++ members of the machine
 * taking the villager), from a table of the overlay's data (data_ov004_02257cb8):
 *   0  wander:  it stands, and one frame in seven when its motion is done it turns to a
 *               random quarter (when not facing one) or, two times in three, walks to the free
 *               tile ahead of it (60 frames), else turns; a walk ends in a stand;
 *   1  talk:    it turns to the scene's partner and talks; once its action is idle its mood is
 *               applied and the object's event ends;
 *   2  turn:    it turns to the event's participant, then stands;
 *   3  await:   with the object ours and owned and held by this system, the talk starts
 *               (state 1); else when this system holds the scene and no one holds the object,
 *               it takes the state asked for next, or wanders;
 *   4  release: as the second half of state 3.
 * The machine's next state (5 for none) is taken by RoomVillagerMachine_TakeNext; its timer
 * (frames) runs down after each update. */
#ifndef CLEAN_OV004_ROOM_VILLAGER_H
#define CLEAN_OV004_ROOM_VILLAGER_H

#include "main/tile_grid.h"
#include "member_pointer.h"
#include "types.h"

enum RoomVillagerState {
    ROOM_VILLAGER_WANDER = 0,
    ROOM_VILLAGER_TALK = 1,
    ROOM_VILLAGER_TURN = 2,
    ROOM_VILLAGER_AWAIT = 3,
    ROOM_VILLAGER_RELEASE = 4,
    ROOM_VILLAGER_STATES = 5 /* also "no next state" */
};

/* A state's functions. */
typedef struct RoomVillagerStep {
    MemberPointer enter;  /* 0x00: int (machine, villager) */
    MemberPointer update; /* 0x08: (machine, villager) */
} RoomVillagerStep;

typedef struct RoomVillagerMachine {
    s32 state;                    /* 0x00: enum RoomVillagerState */
    const RoomVillagerStep *step; /* 0x04: the state's entry of the table */
    s32 next;                     /* 0x08: the state to take next, ROOM_VILLAGER_STATES for none */
    u8 phase;                     /* 0x0c: the step within the state, 0 on entry */
    u8 unk_0d[3];                 /* 0x0d */
    s32 timer;                    /* 0x10: frames, run down after each update */
} RoomVillagerMachine;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define ROOM_VILLAGER_BASE_SIZE 0x898

typedef struct RoomVillager {
    u8 base[ROOM_VILLAGER_BASE_SIZE]; /* 0x000: the town villager scene object */
    MemberPointer draw;               /* 0x898: run by its vtable slot 0x24 */
    RoomVillagerMachine machine;      /* 0x8a0 */
    TileGrid grid;                    /* 0x8b4: the room's free tiles */
    u8 sound_played;                  /* 0x8d4 */
    u8 unk_8d5[3];                    /* 0x8d5 */
    s32 talk_lines;                   /* 0x8d8: the lines its talk scene starts with */
} RoomVillager;

RoomVillager *RoomVillager_Destroy(RoomVillager *villager);
RoomVillager *RoomVillager_Delete(RoomVillager *villager);
void RoomVillager_OnEvent(RoomVillager *villager, int code, int participant);
int RoomVillager_MayAct(RoomVillager *villager);
int RoomVillager_UpdateRelease(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_EnterRelease(void);
int RoomVillager_UpdateAwait(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_EnterAwait(void);
int RoomVillager_UpdateTurn(RoomVillagerMachine *machine, RoomVillager *villager);
void RoomVillager_TurnStep0(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_EnterTurn(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_UpdateTalk(RoomVillagerMachine *machine, RoomVillager *villager);
void RoomVillager_TalkStep1(void);
int RoomVillager_TalkStep0(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_EnterTalk(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_UpdateWander(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_EnterWander(RoomVillagerMachine *machine, RoomVillager *villager);
int RoomVillager_FindStepAhead(RoomVillagerMachine *machine, int *x, int *z, RoomVillager *villager);
int RoomVillagerMachine_TakeNext(RoomVillagerMachine *machine, RoomVillager *villager);
void RoomVillagerMachine_ClearNext(RoomVillagerMachine *machine);
void RoomVillagerMachine_SetState(RoomVillagerMachine *machine, RoomVillager *villager, int state);
void RoomVillagerMachine_Update(RoomVillagerMachine *machine, RoomVillager *villager);
void RoomVillagerMachine_Destroy(RoomVillagerMachine *machine);
void RoomVillagerMachine_Construct(RoomVillagerMachine *machine);
int RoomVillager_RunState(RoomVillager *villager);
RoomVillager *RoomVillager_ActionSoundPlayed(RoomVillager *villager);
int RoomVillager_HasActionSound(RoomVillager *villager);
int RoomVillager_RunDraw(RoomVillager *villager);
int RoomVillager_Draw(RoomVillager *villager);
int RoomVillager_Start(RoomVillager *villager);
int RoomVillager_Init(RoomVillager *villager);
RoomVillager *RoomVillager_New(void);

#endif
