/* A town villager of the rooms whose talk takes its lines from the "ev_nbirth" message files
 * (class vtable 0x02253674, 0xa70 bytes, made by func_ov004_0221d4f4): a town villager scene
 * object (main's villager_scene_slots.h) that walks about the room, comes to this console's
 * player, talks, asks for an item from the player's pockets and gives one in return.
 *
 * Beyond the base class's members it holds its state (0x898, one of 14, each an entry function
 * and an update called through tables of member pointers), whether its action sound was played
 * (0x89c), its talk scene (0x8a0, a town villager's talk scene with a pointer back to it, vtable
 * 0x022535e4), the item it gives (0xa50), two countdowns (0xa52, 0xa53), and the direction and
 * points of its walk about the room (0xa54 to 0xa6c).
 *
 * The states:
 *   0  wander:   it stands, then turns to and walks to points of the room picked at random
 *                (BirthdayGuest_PickGoal), waiting 20 to 89 frames after a turn and 20 to 99
 *                after a walk, stepping aside when something is ahead;
 *   1  face:     it turns to and looks at the room's guest (BirthdayGuest_Current);
 *   2, 3 acts:   a countdown of 30 or 50 frames: at 20 (or 40) frames left it shows an act
 *                (3; 10 or 23 at random), at 1 act 0, at 0 it goes back to state 0;
 *   4  halt:     entered from states 1 to 3, its act ends;
 *   5  turn:     it turns to the player to talk, then 6;
 *   6, 9 talk:   the event ends once the talk has closed (9 follows state 8);
 *   7  call:     it asks for an event about itself (EventQueue_RequestKind6) each frame;
 *   8  approach: it walks (or runs, beyond 0x4000) to the player's start position for up to 50
 *                frames, until within 0x3000, then turns to talk (state 9);
 *   10 ask:      the talk waits for more messages; once its line is out, the pockets screen
 *                opens on the pockets holding an item (state 11);
 *   11, 12:      nothing (its talk scene follows the pockets screen);
 *   13 thanks:   a message 0x11 or 0x12, then state 6.
 *
 * Its talk scene's messages (the receiver's slots): 4 and 5 ask a question (the first answer
 * goes on to 9 or 10 when the player holds an item, to 6 when not; the second to 7 or 8); 9 and
 * 10 lead to state 10; 11 to 14 are followed by 15 or 16, which name the item it picked to give
 * (by its fondness of the player, BirthdayVillager_PickGift) and hand it over (state 13); 17 and
 * 18 mark its memory of the player (bit 7). */
#ifndef CLEAN_OV004_BIRTHDAY_VILLAGER_H
#define CLEAN_OV004_BIRTHDAY_VILLAGER_H

#include "autoload_2/vector.h"
#include "main/villager_memories.h"
#include "main/villager_talk.h"
#include "member_pointer.h"
#include "types.h"

enum BirthdayVillagerState {
    BIRTHDAY_VILLAGER_WANDER = 0,
    BIRTHDAY_VILLAGER_FACE = 1,
    BIRTHDAY_VILLAGER_ACT_SHORT = 2,
    BIRTHDAY_VILLAGER_ACT_LONG = 3,
    BIRTHDAY_VILLAGER_HALT = 4,
    BIRTHDAY_VILLAGER_TURN = 5,
    BIRTHDAY_VILLAGER_TALK = 6,
    BIRTHDAY_VILLAGER_CALL = 7,
    BIRTHDAY_VILLAGER_APPROACH = 8,
    BIRTHDAY_VILLAGER_GREET = 9,
    BIRTHDAY_VILLAGER_ASK = 10,
    BIRTHDAY_VILLAGER_CHOOSING = 11,
    BIRTHDAY_VILLAGER_STATE_12 = 12,
    BIRTHDAY_VILLAGER_THANKS = 13,
    BIRTHDAY_VILLAGER_STATES = 14
};

struct BirthdayVillager;

/* Its talk scene (0x1a8 bytes, vtable data_ov004_022535e4). */
typedef struct BirthdayVillagerTalk {
    VillagerTalk base;                 /* 0x000 */
    struct BirthdayVillager *villager; /* 0x1a4: the villager it belongs to */
} BirthdayVillagerTalk;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define BIRTHDAY_VILLAGER_BASE_SIZE 0x898

typedef struct BirthdayVillager {
    u8 base[BIRTHDAY_VILLAGER_BASE_SIZE]; /* 0x000: the town villager scene object */
    s32 state;                            /* 0x898: enum BirthdayVillagerState */
    u8 sound_played;                      /* 0x89c: its action sound was played */
    u8 unk_89d[3];                        /* 0x89d */
    BirthdayVillagerTalk talk;            /* 0x8a0 */
    MemberPointer unk_a48;                /* 0xa48: run by its vtable slot 0x24 */
    u16 gift;                             /* 0xa50: the item it gives, 0xfff1 for none */
    u8 approach_wait;                     /* 0xa52: frames left to approach the player */
    u8 act_wait;                          /* 0xa53: frames left of an act of states 2 and 3 */
    s16 turn_yaw;                         /* 0xa54: the direction of its next walk */
    u16 wander_wait;                      /* 0xa56: frames before its next turn or walk */
    Vec3 walk_point;                      /* 0xa58: the point the mover heads for */
    Vec3 goal;                            /* 0xa64: the point it walks to */
} BirthdayVillager;

BirthdayVillagerTalk *BirthdayVillagerTalk_Delete(BirthdayVillagerTalk *talk);
BirthdayVillager *BirthdayVillager_Destroy(BirthdayVillager *villager);
BirthdayVillager *BirthdayVillager_Delete(BirthdayVillager *villager);
BirthdayVillagerTalk *BirthdayVillagerTalk_Destroy(BirthdayVillagerTalk *talk);
int BirthdayVillager_HasActionSound(BirthdayVillager *villager);
BirthdayVillager *BirthdayVillager_ActionSoundPlayed(BirthdayVillager *villager);
void BirthdayVillager_UpdateThanks(BirthdayVillager *villager);
int BirthdayVillager_EnterThanks(BirthdayVillager *villager);
void BirthdayVillager_UpdateState12(BirthdayVillager *villager);
int BirthdayVillager_EnterState12(BirthdayVillager *villager);
void BirthdayVillager_UpdateChoosing(BirthdayVillager *villager);
int BirthdayVillager_EnterChoosing(BirthdayVillager *villager);
void BirthdayVillager_UpdateAsk(BirthdayVillager *villager);
int BirthdayVillager_EnterAsk(BirthdayVillager *villager);
void BirthdayVillager_UpdateGreet(BirthdayVillager *villager);
int BirthdayVillager_EnterGreet(BirthdayVillager *villager);
void BirthdayVillager_UpdateApproach(BirthdayVillager *villager);
int BirthdayVillager_EnterApproach(BirthdayVillager *villager);
int BirthdayVillager_UpdateCall(BirthdayVillager *villager);
int BirthdayVillager_EnterCall(BirthdayVillager *villager);
void BirthdayVillager_UpdateTalk(BirthdayVillager *villager);
int BirthdayVillager_EnterTalk(BirthdayVillager *villager);
void BirthdayVillager_UpdateTurn(BirthdayVillager *villager);
int BirthdayVillager_EnterTurn(BirthdayVillager *villager);
void BirthdayVillager_UpdateHalt(BirthdayVillager *villager);
int BirthdayVillager_EnterHalt(BirthdayVillager *villager);
void BirthdayVillager_UpdateActLong(BirthdayVillager *villager);
int BirthdayVillager_EnterActLong(BirthdayVillager *villager);
void BirthdayVillager_UpdateActShort(BirthdayVillager *villager);
int BirthdayVillager_EnterActShort(BirthdayVillager *villager);
void BirthdayVillager_UpdateFace(BirthdayVillager *villager);
int BirthdayVillager_EnterFace(BirthdayVillager *villager);
void BirthdayVillager_UpdateWander(BirthdayVillager *villager);
int BirthdayVillager_EnterWander(BirthdayVillager *villager);
void BirthdayVillager_Update(BirthdayVillager *villager);
int BirthdayVillager_SetState(BirthdayVillager *villager, int state);
void BirthdayVillagerTalk_OnAnswer(BirthdayVillagerTalk *talk);
void BirthdayVillagerTalk_OnMessageEnded(BirthdayVillagerTalk *talk);
void BirthdayVillagerTalk_OnMessageBegun(BirthdayVillagerTalk *talk);
u16 BirthdayVillager_PickGift(int fondness);
void BirthdayVillagerTalk_Line(BirthdayVillagerTalk *talk, VillagerTalkLine *out);

/* The room's birthday villager (set at its set-up, cleared once it may be deleted), or NULL. */
extern BirthdayVillager *data_ov004_02257a18;

void BirthdayVillagerTalk_Start(BirthdayVillagerTalk *talk, BirthdayVillager *villager);
void BirthdayVillagerTalk_TakeItem(BirthdayVillagerTalk *talk);
void BirthdayVillagerTalk_OnCommandEnd(BirthdayVillagerTalk *talk);
int BirthdayVillagerTalk_Fondness(BirthdayVillagerTalk *talk);
int BirthdayVillagerTalk_ChangeFondness(BirthdayVillagerTalk *talk, int delta);
int BirthdayVillagerTalk_LikesItem(BirthdayVillagerTalk *talk, u16 *item);
void BirthdayVillagerTalk_SetMemoryBit7(BirthdayVillagerTalk *talk);
int BirthdayVillagerTalk_MemoryBit7(BirthdayVillagerTalk *talk);
void BirthdayVillagerTalk_SetMemoryBit6(BirthdayVillagerTalk *talk);
int BirthdayVillagerTalk_MemoryBit6Clear(BirthdayVillagerTalk *talk);
void BirthdayVillagerTalk_SetMemoryBit11(BirthdayVillagerTalk *talk);
int BirthdayVillagerTalk_MemoryBit11Clear(BirthdayVillagerTalk *talk);
VillagerMemory *BirthdayVillagerTalk_PlayerMemory(BirthdayVillagerTalk *talk);
void BirthdayVillager_OnEvent(BirthdayVillager *villager, unsigned int code, int participant);
int BirthdayVillager_Ask58(BirthdayVillager *villager);
int BirthdayVillager_MayAct(BirthdayVillager *villager);
void BirthdayVillager_UpdatePlayerMemory(BirthdayVillager *villager);
int BirthdayVillager_RunState(BirthdayVillager *villager);
int BirthdayVillager_CanDelete(BirthdayVillager *villager);
int BirthdayVillager_RunDraw(BirthdayVillager *villager);
int BirthdayVillager_Draw(BirthdayVillager *villager);
int BirthdayVillager_Start(BirthdayVillager *villager);
int BirthdayVillager_Init(BirthdayVillager *villager);
int BirthdayVillager_CanOffer(u16 *item, int state);
int BirthdayVillager_CurrentMemoryBit7(void);
BirthdayVillager *BirthdayVillager_Current(void);
BirthdayVillager *BirthdayVillager_New(void);

#endif
