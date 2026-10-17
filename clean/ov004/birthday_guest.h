/* The other villager of the rooms' "ev_nbirth" talks (class vtable 0x02253868, 0xa6c bytes, made
 * by func_ov004_0221e2cc): a town villager scene object (main's villager_scene_slots.h) that
 * walks about the room near the birthday villager (birthday_villager.h, the room's one is
 * BirthdayVillager_Current), faces it now and then and acts with it, and talks to this
 * console's player.
 *
 * Beyond the base class's members it holds its state (0x898, one of 7, each an entry function
 * and an update called through tables of member pointers), whether its action sound was played
 * (the base's byte 0x897), its talk scene (0x89c, a town villager's talk scene with a pointer
 * back to it, vtable 0x022537d8), its drawing member (0xa44), the countdown of an act (0xa4c),
 * the frames before it may face the birthday villager again (0xa4e), the direction it turns to
 * (0xa50) and the wait and points of its walk about the room (0xa52 to 0xa6c).
 *
 * The states:
 *   0  wander: as the birthday villager's state 0, and: within 0x3334 of the birthday villager
 *              it faces it (state 1); from 0x6000 away, one walk in two heads for it;
 *   1  face:   it turns to the birthday villager, which turns to it (its state 1); once both
 *              face each other (within 0x500), both act (state 2 or 3 at random) and it waits
 *              300 frames before facing it again;
 *   2, 3 acts: the birthday villager's state 2 or 3 with it; act 3 for 30 frames or act 0x1a
 *              for 50, at 1 frame left act 0, at 0 back to state 0;
 *   4  halt:   from states 1 to 3 its act ends;
 *   5  turn:   it turns to the player to talk, then 6;
 *   6  talk:   the event ends once the talk has closed. */
#ifndef CLEAN_OV004_BIRTHDAY_GUEST_H
#define CLEAN_OV004_BIRTHDAY_GUEST_H

#include "autoload_2/vector.h"
#include "main/villager_memories.h"
#include "main/villager_talk.h"
#include "member_pointer.h"
#include "types.h"

enum BirthdayGuestState {
    BIRTHDAY_GUEST_WANDER = 0,
    BIRTHDAY_GUEST_FACE = 1,
    BIRTHDAY_GUEST_ACT_SHORT = 2,
    BIRTHDAY_GUEST_ACT_LONG = 3,
    BIRTHDAY_GUEST_HALT = 4,
    BIRTHDAY_GUEST_TURN = 5,
    BIRTHDAY_GUEST_TALK = 6,
    BIRTHDAY_GUEST_STATES = 7
};

struct BirthdayGuest;

/* Its talk scene (0x1a8 bytes, vtable data_ov004_022537d8). */
typedef struct BirthdayGuestTalk {
    VillagerTalk base;           /* 0x000 */
    struct BirthdayGuest *guest; /* 0x1a4: the villager it belongs to */
} BirthdayGuestTalk;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define BIRTHDAY_GUEST_BASE_SIZE 0x898

typedef struct BirthdayGuest {
    u8 base[BIRTHDAY_GUEST_BASE_SIZE]; /* 0x000: the town villager scene object */
    s32 state;                         /* 0x898: enum BirthdayGuestState */
    BirthdayGuestTalk talk;            /* 0x89c */
    MemberPointer draw;                /* 0xa44: run by its vtable slot 0x24 */
    u8 act_wait;                       /* 0xa4c: frames left of an act of states 2 and 3 */
    u8 unk_a4d;                        /* 0xa4d */
    u16 face_wait;                     /* 0xa4e: frames before it may face the birthday villager */
    s16 turn_yaw;                      /* 0xa50: the direction it turns to */
    u16 wander_wait;                   /* 0xa52: frames before its next turn or walk */
    Vec3 walk_point;                   /* 0xa54: the point the mover heads for */
    Vec3 goal;                         /* 0xa60: the point it walks to */
} BirthdayGuest;

BirthdayGuestTalk *BirthdayGuestTalk_Delete(BirthdayGuestTalk *talk);
BirthdayGuest *BirthdayGuest_Destroy(BirthdayGuest *guest);
BirthdayGuest *BirthdayGuest_Delete(BirthdayGuest *guest);
BirthdayGuestTalk *BirthdayGuestTalk_Destroy(BirthdayGuestTalk *talk);
int BirthdayGuest_HasActionSound(BirthdayGuest *guest);
BirthdayGuest *BirthdayGuest_ActionSoundPlayed(BirthdayGuest *guest);
void BirthdayGuest_UpdateTalk(BirthdayGuest *guest);
int BirthdayGuest_EnterTalk(BirthdayGuest *guest);
void BirthdayGuest_UpdateTurn(BirthdayGuest *guest);
int BirthdayGuest_EnterTurn(BirthdayGuest *guest);
void BirthdayGuest_UpdateHalt(BirthdayGuest *guest);
int BirthdayGuest_EnterHalt(BirthdayGuest *guest);
void BirthdayGuest_UpdateActLong(BirthdayGuest *guest);
int BirthdayGuest_EnterActLong(BirthdayGuest *guest);
void BirthdayGuest_UpdateActShort(BirthdayGuest *guest);
int BirthdayGuest_EnterActShort(BirthdayGuest *guest);
void BirthdayGuest_UpdateFace(BirthdayGuest *guest);
int BirthdayGuest_EnterFace(BirthdayGuest *guest);
void BirthdayGuest_UpdateWander(BirthdayGuest *guest);
int BirthdayGuest_EnterWander(BirthdayGuest *guest);
void BirthdayGuest_Update(BirthdayGuest *guest);
int BirthdayGuest_SetState(BirthdayGuest *guest, int state);
void BirthdayGuestTalk_OnAnswer(void);
void BirthdayGuestTalk_OnMessageEnded(void);
void BirthdayGuestTalk_OnMessageBegun(void);
void BirthdayGuestTalk_Line(BirthdayGuestTalk *talk, VillagerTalkLine *out);
void BirthdayGuestTalk_Start(BirthdayGuestTalk *talk, BirthdayGuest *guest);
void BirthdayGuestTalk_SetMemoryBit6(BirthdayGuestTalk *talk);
int BirthdayGuestTalk_MemoryBit6Clear(BirthdayGuestTalk *talk);
VillagerMemory *BirthdayGuestTalk_PlayerMemory(BirthdayGuestTalk *talk);
void BirthdayGuest_OnEvent(BirthdayGuest *guest, unsigned int code, int participant);
int BirthdayGuest_MayAct(BirthdayGuest *guest);
void BirthdayGuest_UpdatePlayerMemory(BirthdayGuest *guest);
void BirthdayGuest_UnlinkFurnitureTiles(BirthdayGuest *guest);
int BirthdayGuest_RunState(BirthdayGuest *guest);
int BirthdayGuest_CanDelete(BirthdayGuest *guest);
int BirthdayGuest_RunDraw(BirthdayGuest *guest);
int BirthdayGuest_Draw(BirthdayGuest *guest);
int BirthdayGuest_Start(BirthdayGuest *guest);
int BirthdayGuest_Init(BirthdayGuest *guest);
int BirthdayGuest_PickGoal(Vec3 *goal, Vec3 *from, int yaw);
BirthdayGuest *BirthdayGuest_Current(void);
BirthdayGuest *BirthdayGuest_New(void);

#endif
