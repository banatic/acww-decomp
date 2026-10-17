/* The villager who comes to the player's house at the time it said it would (class vtable
 * data_ov068_02278140, 0xa7c bytes, made by func_ov068_022766e8): a town villager scene object
 * (main's villager_scene_slots.h) that rings at the door, talks from outside, comes in, walks
 * about the room, comments on its furniture and leaves. Its lines come from the villager's
 * "q10_*" message files ("q10_call", "q10_door", "q10_first", "q10_furniture", "q10_layout",
 * "q10_back", "q10_wait", then "q_bye").
 *
 * The visit is the record at 0xa4 of the villagers' part of this console's player's record
 * (main's villager_part_handover.h): its date (0x1c) is the time agreed, and the visit may
 * start from that minute to 30 minutes after it (HouseVisitor_IsDue). The low five bits of its
 * object (0x10) say how far it went (HOUSE_VISITOR_VISIT_*), and the low three bits of its
 * byte 0x24 take the rating the villager gave the room.
 *
 * Beyond the base class's members it holds whether its action sound was played (the base's
 * byte 0x897), its state (0x898, one of 11, each an entry and an update called through tables
 * of C++ pointers to member functions filled once), its talk scene (0x89c, a town villager's
 * talk scene with a pointer back to it, vtable data_ov068_022780b0), its drawing member
 * (0xa44, cleared while it is behind the door) and the members below.
 *
 * The states:
 *   0  outside: hidden at the middle of the room's front edge, facing in; once the visit is
 *              due and the player is away from there it asks for an event (kind 6);
 *   1  ring:   the doorbell (sound 0x4ca) and the room rated; after 30 frames it talks from
 *              outside ("q10_call"; its talk scene's event 0x14 then gives state 2);
 *   2  called: once the talk has closed the door opens (sound 0x4cb), state 3;
 *   3  enter:  after 40 frames it is drawn and walks two tiles in, then state 4;
 *   4  stop:   it stands, state 5, and the event ends;
 *   5  arrived: it waits near the door for the player, its countdowns running (as in 6);
 *   6  wander: it walks about the room; when its stay or its talks run out it asks for a
 *              talk to leave ("q10_back"), and when the player stands at the claimed unit
 *              (the door) for one to stop them ("q10_wait");
 *   7  held:   an event of another runs;
 *   8  turn:   it turns to the player and talks, then 9;
 *   9  talk:   the event ends once the talk has closed;
 *   10 leave:  once the talk has closed the visit is over and the scene's exit is taken. */
#ifndef CLEAN_OV068_HOUSE_VISITOR_H
#define CLEAN_OV068_HOUSE_VISITOR_H

#include "autoload_2/vector.h"
#include "main/villager_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

enum HouseVisitorState {
    HOUSE_VISITOR_OUTSIDE = 0,
    HOUSE_VISITOR_RING = 1,
    HOUSE_VISITOR_CALLED = 2,
    HOUSE_VISITOR_ENTER = 3,
    HOUSE_VISITOR_STOP = 4,
    HOUSE_VISITOR_ARRIVED = 5,
    HOUSE_VISITOR_WANDER = 6,
    HOUSE_VISITOR_HELD = 7,
    HOUSE_VISITOR_TURN = 8,
    HOUSE_VISITOR_TALK = 9,
    HOUSE_VISITOR_LEAVE = 10,
    HOUSE_VISITOR_STATES = 11
};

/* How far the visit went (the low five bits of the visit's object). */
#define HOUSE_VISITOR_VISIT_AGREED 0  /* not started */
#define HOUSE_VISITOR_VISIT_RANG 1    /* it rang and talked from outside */
#define HOUSE_VISITOR_VISIT_IN 2      /* let in ("q10_door" said, or the talk ended) */
#define HOUSE_VISITOR_VISIT_GREETED 3 /* "q10_first" said */
#define HOUSE_VISITOR_VISIT_OVER 4

/* What its talk says (HouseVisitor.talk_kind), set by the line it starts with. */
#define HOUSE_VISITOR_SAYS_CHAT 0      /* a town villager's lines: the scene runs as such */
#define HOUSE_VISITOR_SAYS_CALL 1      /* "q10_call" from outside */
#define HOUSE_VISITOR_SAYS_DOOR 2      /* "q10_door" */
#define HOUSE_VISITOR_SAYS_FURNITURE 3 /* "q10_furniture" */
#define HOUSE_VISITOR_SAYS_LAYOUT 4    /* "q10_layout", by the room's advice */
#define HOUSE_VISITOR_SAYS_FIRST 5     /* "q10_first" */
#define HOUSE_VISITOR_SAYS_BACK 6      /* "q10_back": it is time to go */
#define HOUSE_VISITOR_SAYS_BYE 7       /* "q_bye" */
#define HOUSE_VISITOR_SAYS_WAIT 8      /* "q10_wait": the player is at the door */

struct HouseVisitor;

/* Its talk scene (0x1a8 bytes, vtable data_ov068_022780b0). */
typedef struct HouseVisitorTalk {
    VillagerTalk base;            /* 0x000 */
    struct HouseVisitor *visitor; /* 0x1a4: the villager it belongs to */
} HouseVisitorTalk;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define HOUSE_VISITOR_BASE_SIZE 0x898

typedef struct HouseVisitor {
    u8 base[HOUSE_VISITOR_BASE_SIZE]; /* 0x000: the town villager scene object */
    s32 state;                        /* 0x898: enum HouseVisitorState */
    HouseVisitorTalk talk;            /* 0x89c */
    MemberPointer draw;               /* 0xa44: run by its vtable slot 0x24, null while hidden */
    int rating;                       /* 0xa4c: the room's rating (RoomScore_Advice's count) */
    u8 enter_wait;                    /* 0xa50: frames before it comes in (state 3) */
    u8 unk_a51;
    u16 walk_wait;     /* 0xa52: frames before its next turn or walk */
    s32 advice;        /* 0xa54: what the room lacks (RoomScore_Advice's flags) */
    u8 time_up;        /* 0xa58: its stay ran out: it says "q10_back" */
    u8 player_leaving; /* 0xa59: the player went to the door: it says "q10_wait" */
    u8 talk_kind;      /* 0xa5a: HOUSE_VISITOR_SAYS_* */
    u8 unk_a5b;
    u8 talks_left; /* 0xa5c: the talks before it leaves */
    u8 unk_a5d;
    s16 stay;        /* 0xa5e: frames before it leaves; -1 for no limit */
    u8 leave_wait;   /* 0xa60: frames it waits once its stay or talks ran out */
    s8 ring_wait;    /* 0xa61: frames from the doorbell to its call; -1 once called */
    s16 turn_yaw;    /* 0xa62: the direction it turns to */
    Vec3 walk_point; /* 0xa64: the point the mover heads for */
    Vec3 goal;       /* 0xa70: the point it walks to */
} HouseVisitor;

HouseVisitorTalk *HouseVisitorTalk_Delete(HouseVisitorTalk *talk);
HouseVisitor *HouseVisitor_Destroy(HouseVisitor *visitor);
HouseVisitor *HouseVisitor_Delete(HouseVisitor *visitor);
HouseVisitorTalk *HouseVisitorTalk_Destroy(HouseVisitorTalk *talk);
int HouseVisitor_HasActionSound(HouseVisitor *visitor);
void HouseVisitor_ActionSoundPlayed(HouseVisitor *visitor);
void HouseVisitor_UpdateLeave(HouseVisitor *visitor);
int HouseVisitor_EnterLeave(void);
void HouseVisitor_UpdateTalk(HouseVisitor *visitor);
int HouseVisitor_EnterTalk(void);
int HouseVisitor_UpdateTurn(HouseVisitor *visitor);
int HouseVisitor_EnterTurn(HouseVisitor *visitor);
void HouseVisitor_UpdateHeld(void);
int HouseVisitor_EnterHeld(void);
void HouseVisitor_UpdateWander(HouseVisitor *visitor);
int HouseVisitor_EnterWander(HouseVisitor *visitor);
void HouseVisitor_UpdateArrived(HouseVisitor *visitor);
int HouseVisitor_EnterArrived(HouseVisitor *visitor);
void HouseVisitor_UpdateStop(HouseVisitor *visitor);
void HouseVisitor_EnterStop(HouseVisitor *visitor);
void HouseVisitor_UpdateEnter(HouseVisitor *visitor);
int HouseVisitor_EnterEnter(HouseVisitor *visitor);
void HouseVisitor_UpdateCalled(HouseVisitor *visitor);
int HouseVisitor_EnterCalled(HouseVisitor *visitor);
void HouseVisitor_UpdateRing(HouseVisitor *visitor);
int HouseVisitor_EnterRing(HouseVisitor *visitor);
void HouseVisitor_UpdateOutside(HouseVisitor *visitor);
int HouseVisitor_EnterOutside(HouseVisitor *visitor);
void HouseVisitor_Update(HouseVisitor *visitor);
int HouseVisitor_SetState(HouseVisitor *visitor, int state);
void HouseVisitorTalk_OnAnswer(HouseVisitorTalk *talk, int arg);
void HouseVisitorTalk_OnMessageEnded(HouseVisitorTalk *talk, int event);
void HouseVisitorTalk_OnMessageBegun(HouseVisitorTalk *talk, int arg);
void HouseVisitorTalk_Line(HouseVisitorTalk *talk, VillagerTalkLine *out);
void HouseVisitorTalk_Start(HouseVisitorTalk *talk, HouseVisitor *visitor);
void HouseVisitor_MarkGreeted(void *unused);
int HouseVisitor_IsLetIn(void *unused);
void HouseVisitor_MarkLetIn(void *unused);
int HouseVisitor_IsPastRing(void *unused);
void HouseVisitor_MarkRang(void *unused);
int HouseVisitor_HasStarted(void *unused);
void HouseVisitor_OnEvent(HouseVisitor *visitor, int code, unsigned char participant);
int HouseVisitor_MayAct(HouseVisitor *visitor);
void HouseVisitor_MarkOver(void);
int HouseVisitor_IsDue(void *unused);
void HouseVisitor_SlowPace(HouseVisitor *visitor);
void HouseVisitor_UpdatePlayerMemory(HouseVisitor *visitor);
void HouseVisitor_UnlinkFurnitureTiles(void *unused);
int HouseVisitor_Frame(HouseVisitor *visitor);
int HouseVisitor_CanDelete(HouseVisitor *visitor);
int HouseVisitor_RunDraw(HouseVisitor *visitor);
int HouseVisitor_Draw(HouseVisitor *visitor);
int HouseVisitor_Start(HouseVisitor *visitor);
int HouseVisitor_Init(HouseVisitor *visitor);
HouseVisitor *HouseVisitor_New(void);

#endif
