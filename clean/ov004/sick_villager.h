/* A villager in a room who talks with the lines of the message files "q12_sick1_2" and
 * "q12_sick3_5" (class vtable 0x022541d8, 0xa94 bytes, made by func_ov004_02222a88): a town
 * villager scene object (main's villager_scene_slots.h) that walks about the room, stops now
 * and then for an act, talks to this console's player and may be offered, from the player's
 * pockets, the item 0x155e (the predicate func_ov004_02222a30).
 *
 * The stage of the town's villager move record (main's villager_move.h, byte 0xba) is read at
 * its set-up into its talk scene; above stage 1 the base's byte 0x897 is set: its file is then
 * "q12_sick3_5", it walks with other animations and longer waits, and while walking shows the
 * mood effect 3 every 14 frames.
 *
 * Beyond the base class's members it holds whether the current stage of that record names a
 * player (0x898, set by its line), whether the player answered since (0x899), whether its
 * action sound was played (0x89a), its state (0x89c), its talk scene (0x8a0, a town villager's
 * talk scene with the stage and a pointer back to it, vtable 0x02254148), its drawing member
 * (0xa4c), a spawner part (0xa54) and the waits and points of its walk (0xa74 to 0xa90).
 *
 * Its states (0x89c), each an entry and an update function, through tables of member pointers
 * filled the first time each is used:
 *   0  wander: it stands and walks about the room; at its goal, or when the base's byte 0x508
 *              is set while it walks, it acts (state 1);
 *   1  act:    act 7 for 70 frames, then act 0 and 20 to 39 frames of waiting; then state 0;
 *   2  halt:   from state 1 its act ends;
 *   3  turn:   it turns to the player to talk, then 4;
 *   4  talk:   the event ends once the talk has closed;
 *   5  ask:    the talk is kept; once it is gone the player's pockets are opened for the items
 *              the predicate takes: state 6;
 *   6  pockets: nothing (its talk scene's vtable slot 0x80 reads the choice);
 *   7  back:   on to state 4. */
#ifndef CLEAN_OV004_SICK_VILLAGER_H
#define CLEAN_OV004_SICK_VILLAGER_H

#include "autoload_2/vector.h"
#include "main/villager_talk.h"
#include "member_pointer.h"
#include "types.h"

enum SickVillagerState {
    SICK_VILLAGER_WANDER = 0,
    SICK_VILLAGER_ACT = 1,
    SICK_VILLAGER_HALT = 2,
    SICK_VILLAGER_TURN = 3,
    SICK_VILLAGER_TALK = 4,
    SICK_VILLAGER_ASK = 5,
    SICK_VILLAGER_POCKETS = 6,
    SICK_VILLAGER_BACK = 7,
    SICK_VILLAGER_STATES = 8
};

struct SickVillager;

/* Its talk scene (0x1ac bytes, vtable data_ov004_02254148). */
typedef struct SickVillagerTalk {
    VillagerTalk base;             /* 0x000 */
    u8 stage;                      /* 0x1a4: the town's villager move record's, at its set-up */
    u8 unk_1a5[3];                 /* 0x1a5 */
    struct SickVillager *villager; /* 0x1a8: the villager it belongs to */
} SickVillagerTalk;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define SICK_VILLAGER_BASE_SIZE 0x898

typedef struct SickVillager {
    u8 base[SICK_VILLAGER_BASE_SIZE]; /* 0x000: the town villager scene object */
    u8 stage_named;                   /* 0x898: the record's current stage names a player */
    u8 answered;                      /* 0x899: the player answered since its line */
    u8 sound_played;                  /* 0x89a */
    u8 unk_89b;                       /* 0x89b */
    s32 state;                        /* 0x89c: enum SickVillagerState */
    SickVillagerTalk talk;            /* 0x8a0 */
    MemberPointer draw;               /* 0xa4c: run by its vtable slot 0x24 */
    u8 spawner[0x20];                 /* 0xa54: a spawner part (main's spawner.h) */
    s16 turn_yaw;                     /* 0xa74: the direction it turns to */
    u16 wander_wait;                  /* 0xa76: frames before its next turn or walk */
    Vec3 walk_point;                  /* 0xa78: the point the mover heads for */
    Vec3 goal;                        /* 0xa84: the point it walks to */
    u8 act_wait;                      /* 0xa90: frames left of state 1 */
    u8 unk_a91[3];                    /* 0xa91 */
} SickVillager;

SickVillagerTalk *SickVillagerTalk_Delete(SickVillagerTalk *talk);
SickVillager *SickVillager_Destroy(SickVillager *villager);
SickVillager *SickVillager_Delete(SickVillager *villager);
SickVillagerTalk *SickVillagerTalk_Destroy(SickVillagerTalk *talk);
int SickVillager_HasActionSound(SickVillager *villager);
SickVillager *SickVillager_ActionSoundPlayed(SickVillager *villager);
void SickVillager_UpdateBack(SickVillager *villager);
int SickVillager_EnterBack(SickVillager *villager);
void SickVillager_UpdatePockets(SickVillager *villager);
int SickVillager_EnterPockets(SickVillager *villager);
void SickVillager_UpdateAsk(SickVillager *villager);
int SickVillager_EnterAsk(SickVillager *villager);
void SickVillager_UpdateTalk(SickVillager *villager);
int SickVillager_EnterTalk(SickVillager *villager);
void SickVillager_UpdateTurn(SickVillager *villager);
int SickVillager_EnterTurn(SickVillager *villager);
void SickVillager_UpdateHalt(SickVillager *villager);
int SickVillager_EnterHalt(SickVillager *villager);
void SickVillager_UpdateAct(SickVillager *villager);
int SickVillager_EnterAct(SickVillager *villager);
void SickVillager_UpdateWander(SickVillager *villager);
int SickVillager_EnterWander(SickVillager *villager);
void SickVillager_Update(SickVillager *villager);
int SickVillager_SetState(SickVillager *villager, int state);
void SickVillagerTalk_OnAnswer(SickVillagerTalk *talk);
void SickVillagerTalk_OnMessageEnded(SickVillagerTalk *talk);
void SickVillagerTalk_OnMessageBegun(SickVillagerTalk *talk);

void SickVillagerTalk_Line(SickVillagerTalk *talk, VillagerTalkLine *out);
void SickVillagerTalk_TakeItem(SickVillagerTalk *talk);
void SickVillagerTalk_OnCommandEnd(SickVillagerTalk *talk, int command);
void SickVillagerTalk_Start(SickVillagerTalk *talk, SickVillager *villager);
void SickVillagerTalk_NameStagePlayer(void);
int SickVillagerTalk_StageNamesPlayer(SickVillagerTalk *talk);
int SickVillagerTalk_Stage(SickVillagerTalk *talk);
void SickVillager_OnEvent(SickVillager *villager, unsigned int code, int participant);
int SickVillager_MayAct(SickVillager *villager);
void SickVillager_MeetPlayer(SickVillager *villager);
void SickVillager_UnlinkItemTiles(SickVillager *villager);
int SickVillager_Frame(SickVillager *villager);
int SickVillager_CanDelete(SickVillager *villager);
int SickVillager_Draw(SickVillager *villager);
int SickVillager_DrawModel(SickVillager *villager);
int SickVillager_Start(SickVillager *villager);
int SickVillager_Init(SickVillager *villager);
int SickVillager_IsAskedItem(u16 *item, int state);
SickVillager *SickVillager_New(void);

#endif
