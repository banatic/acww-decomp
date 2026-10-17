/* More of overlay 4's states of the field actor (main's field_actor_parts.h has the state
 * tables; field_actor_rooms.h the door states):
 *   0x44  the actor fades in (its models' alpha up to 31 by 6 a frame) while its animation
 *         plays, with footsteps at frames 1, 6, 12 and 20; at its end it nudges one thing and
 *         state 2 is asked for;
 *   0x7a  the head's kind is cleared (from frame 3; the hair colour kept), then state 0x7b;
 *   0x7b  an animation, then state 0x7c with the same two bytes;
 *   0x7c  an effect at frame 10; from frame 11 the head takes the request's kind and hair
 *         colour, which go into the player's record; at its end, the stick pushed towards where
 *         the actor faces asks for state 0x2c. On leaving, this console's actor sends both to the session;
 *   0x7d  the telephone picked up: this console's actor stands at the tile ahead moved 2.0
 *         in z, at yaw 0x8000, while the telephone's animation plays from its start; then
 *         state 0x7e;
 *   0x7e  on the telephone: the actor follows what is reported, the telephone's animation
 *         plays from its end;
 *   0x7f  the telephone hung up: the pick-up animation plays backwards, as does the
 *         telephone's; then state 2;
 *   0x8a  animations 0x95, 0x96 and 0x97 one after another (after 0x98, state 0x28).
 * Each request carries its two bytes (0x7a to 0x7c) or nothing; each message handler asks for
 * the state again with priority 6 (0x7a to 0x7c and 0x8a do nothing). */
#ifndef CLEAN_OV004_FIELD_ACTOR_ROOM_STATES_H
#define CLEAN_OV004_FIELD_ACTOR_ROOM_STATES_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;
struct StateRequest;

/* The work at 0x7d4 of states 0x7a to 0x7c: the head's kind and hair colour asked for. */
typedef struct FieldActorHairWork {
    u8 kind;
    u8 hair_color;
    u8 applied; /* state 0x7c: the head has taken them */
} FieldActorHairWork;

void FieldActorRoomStates_UpdateFadeIn(struct FieldActor *actor);
int FieldActorRoomStates_EndFadeIn(struct FieldActor *actor);
void FieldActorRoomStates_FadeInSteps(struct FieldActor *actor);

void FieldActorRoomStates_UpdateHairOff(struct FieldActor *actor);
void FieldActorRoomStates_StepHairOff(struct FieldActor *actor);
void FieldActorRoomStates_HairOffMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairOff(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairOff(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdateHairWait(struct FieldActor *actor);
void FieldActorRoomStates_EndHairWait(struct FieldActor *actor);
void FieldActorRoomStates_HairWaitMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairWait(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairWait(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdateHairOn(struct FieldActor *actor);
void FieldActorRoomStates_EndHairOn(struct FieldActor *actor);
void FieldActorRoomStates_StepHairOn(struct FieldActor *actor);
void FieldActorRoomStates_LeaveHairOn(struct FieldActor *actor);
void FieldActorRoomStates_HairOnMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairOn(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairOn(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdatePickUp(struct FieldActor *actor);
void FieldActorRoomStates_EndPickUp(struct FieldActor *actor);
void FieldActorRoomStates_StandPickUp(struct FieldActor *actor);
void FieldActorRoomStates_PickUpMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterPickUp(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_PutPickUpPoint(Vec3 *work, Vec3 point);
int FieldActorRoomStates_RequestPickUp(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateOnPhone(struct FieldActor *actor);
void FieldActorRoomStates_OnPhoneMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterOnPhone(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestOnPhone(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateHangUp(struct FieldActor *actor);
void FieldActorRoomStates_EndHangUp(struct FieldActor *actor);
void FieldActorRoomStates_HangUpMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHangUp(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHangUp(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateSequence8A(struct FieldActor *actor);
void FieldActorRoomStates_StepSequence8A(struct FieldActor *actor);
void FieldActorRoomStates_Sequence8AMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSequence8A(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestSequence8A(struct FieldActor *actor, int priority, int arg);

/* The states around the room's exits, the chests and the item shown (each message handler of
 * 0x41 to 0x44 asks for the state again with priority 9, of 0x2e and 0x2f with priority 6 and
 * the chest's index kept at 0x8f0; 0x36, 0x37 and 0x40 do nothing):
 *   0x2e  at a chest: animation 0x3b, 0x3c or 0x3d (the chest's index, 0 to 2) loops;
 *   0x2f  closing a chest: animation 0x38, 0x39 or 0x3a plays backwards; at its end the
 *         standing animation loops;
 *   0x36  an item taken out: the object of main's obj_020dd33c.h starts with the actor's item
 *         and the request's four values while animation 0x2e plays (sounds in scene 9); then
 *         state 0x10;
 *   0x37  the item put back: animation 0x2e backwards, the object finished at its end; then
 *         state 0x10;
 *   0x40  walking to an exit: the actor eases to the exit's point and yaw (for door kind 2 1.0
 *         beyond the door's point, for kind 0 where it stands, at yaw 0x8000), rising (kind 1)
 *         or sinking (kind 2) as it nears it; there it asks for state 0x41 (kind 1) or 0x42.
 *         An exit to a scene one player at a time may enter (main's scene_claim.h) is claimed
 *         first: given, the exit is taken; refused, a talk opens and the actor walks back to
 *         the tile after its own (state 0x6f);
 *   0x41  through an exit rising: animation 0x3e; from frame 6 the models fade out, from
 *         frame 5 this console's actor takes the exit once the screen is not closed;
 *   0x42  the same sinking: animation 0x3f, fading from frame 9;
 *   0x43  the actor fades in like state 0x44, with animation 0x40 (both are start states of
 *         the rooms). */

/* The two arguments of a request for state 0x40 (SceneExit_DoorInfo). */
typedef struct FieldActorExitWalkArgs {
    int door_kind;  /* 0 to 2 */
    s16 door_angle; /* the way the door faces */
} FieldActorExitWalkArgs;

/* State 0x40's work at 0x7d4. */
typedef struct FieldActorExitWalk {
    int door_kind; /* 0x00: 1 rises, 2 sinks */
    s16 yaw;       /* 0x04: the yaw the actor takes the exit at */
    u8 pad_06[2];
    fx32 x;   /* 0x08: the point the actor takes the exit at */
    fx32 z;   /* 0x0c */
    u8 phase; /* 0x10: FieldActorExitPhase */
} FieldActorExitWalk;

/* FieldActorExitWalk.phase */
enum FieldActorExitPhase {
    FIELD_ACTOR_EXIT_AT_POINT = 0, /* walking to the point (no claim, or the claim given) */
    FIELD_ACTOR_EXIT_CLAIM = 1,    /* the scene to be claimed */
    FIELD_ACTOR_EXIT_ANSWER = 2,   /* waiting for the claim's answer */
    FIELD_ACTOR_EXIT_TALK = 3,     /* refused: the talk asked for, waiting for it to open */
    FIELD_ACTOR_EXIT_TALKING = 4,  /* waiting for the talk to close */
};

/* The four values a request for state 0x36 carries for Obj020dd33c_Start. */
typedef struct FieldActorItemOutArgs {
    u32 look;
    u8 stage;
    u8 pad_05[3];
    u32 kind;
    u32 second; /* the second actor (an address) */
} FieldActorItemOutArgs;

void FieldActorRoomStates_FadeInMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterFadeIn(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestFadeIn(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateFadeIn43(struct FieldActor *actor);
int FieldActorRoomStates_EndFadeIn43(struct FieldActor *actor);
void FieldActorRoomStates_FadeIn43Steps(struct FieldActor *actor);
void FieldActorRoomStates_FadeIn43Message(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterFadeIn43(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestFadeIn43(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateExitSink(struct FieldActor *actor);
void FieldActorRoomStates_TakeExitSink(struct FieldActor *actor);
void FieldActorRoomStates_FadeExitSink(struct FieldActor *actor);
void FieldActorRoomStates_FollowExitSink(struct FieldActor *actor, int moved);
void FieldActorRoomStates_StepExitSink(struct FieldActor *actor);
void FieldActorRoomStates_ExitSinkMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterExitSink(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestExitSink(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateExitRise(struct FieldActor *actor);
void FieldActorRoomStates_TakeExitRise(struct FieldActor *actor);
void FieldActorRoomStates_FadeExitRise(struct FieldActor *actor);
void FieldActorRoomStates_FollowExitRise(struct FieldActor *actor, int moved);
void FieldActorRoomStates_StepExitRise(struct FieldActor *actor);
void FieldActorRoomStates_ExitRiseMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterExitRise(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestExitRise(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateExitWalk(struct FieldActor *actor);
void FieldActorRoomStates_RunExitWalk(struct FieldActor *actor);
void FieldActorRoomStates_MoveExitWalk(struct FieldActor *actor);
void FieldActorRoomStates_AnimateExitWalk(struct FieldActor *actor);
void FieldActorRoomStates_StandExitWalk(struct FieldActor *actor);
void FieldActorRoomStates_ExitWalkMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterExitWalk(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_SetExitWalkWork(FieldActorExitWalk *work, int door_kind, s16 yaw, fx32 x, fx32 z, u8 phase);
int FieldActorRoomStates_RequestExitWalk(struct FieldActor *actor, int priority, s16 arg);
void FieldActorRoomStates_PutExitWalkArgs(FieldActorExitWalkArgs *args, int door_kind, u16 door_angle);

void FieldActorRoomStates_UpdateItemBack(struct FieldActor *actor);
void FieldActorRoomStates_EndItemBack(struct FieldActor *actor);
void FieldActorRoomStates_ItemBackMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterItemBack(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestItemBack(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateItemOut(struct FieldActor *actor);
void FieldActorRoomStates_EndItemOut(struct FieldActor *actor);
void FieldActorRoomStates_ItemOutSounds(struct FieldActor *actor);
void FieldActorRoomStates_ItemOutMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterItemOut(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestItemOut(struct FieldActor *actor, const u16 *item, int look, int stage, int kind, int second,
                                        int priority, s16 arg);
void FieldActorRoomStates_SetItemOutArgs(FieldActorItemOutArgs *args, int look, u8 stage, int kind, int second);

void FieldActorRoomStates_UpdateChestClose(struct FieldActor *actor);
void FieldActorRoomStates_EndChestClose(struct FieldActor *actor);
void FieldActorRoomStates_ChestCloseMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterChestClose(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetChestCloseSaved(const u8 *saved, u8 *index);
void FieldActorRoomStates_PutChestCloseSaved(u8 *saved, u8 index);
void FieldActorRoomStates_PutChestCloseWork(u32 *work, u32 index);
int FieldActorRoomStates_RequestChestClose(struct FieldActor *actor, int index, int priority, int arg);
void FieldActorRoomStates_PutChestCloseArgs(u32 *payload, u32 index);

void FieldActorRoomStates_UpdateAtChest(struct FieldActor *actor);
void FieldActorRoomStates_AtChestMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterAtChest(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetAtChestSaved(const u8 *saved, u8 *index);
void FieldActorRoomStates_PutAtChestSaved(u8 *saved, u8 index);
void FieldActorRoomStates_PutAtChestWork(u32 *work, u32 index);
int FieldActorRoomStates_RequestAtChest(struct FieldActor *actor, int index, int priority, int arg);
void FieldActorRoomStates_PutAtChestArgs(u8 *payload, u8 index);

/* The state before a chest, and the states of a spot the actor is set at (each message
 * handler asks for its state again with priority 6; that of 0x2b does nothing):
 *   0x2d  to a chest: the actor eases to the request's point and yaw; while it stands
 *         (animation 0 or 0x1a) animation 0x3b, 0x3c or 0x3d (the chest's index, 0 to 2)
 *         starts once; at that animation's end state 0x2e is asked for with the index;
 *   0x27  the actor set at the request's point and yaw: animation 0x23 and sound 0x4c5; at
 *         its end state 0x28;
 *   0x28  at the spot: animation 0x24 loops; while one of the musics 0x63 to 0xab plays, the
 *         body follows the music's beat. This console's actor pushed ahead or a quarter turn
 *         either side, where the room is free there, asks for state 0x2b that way;
 *   0x2b  the place 2.0 ahead that way (straight, yaw + 0x4000 or yaw - 0x4000) is claimed
 *         (main's place_claim.h); given, state 0x2c (straight) or a turn first (0x2a, 0x29);
 *         refused, or with an object met, state 0x28 again;
 *   0x2a  a quarter turn to yaw + 0x4000: animation 0x25 and sound 0x4c9; then state 0x2c;
 *   0x29  a quarter turn to yaw - 0x4000: animation 0x26 and sound 0x4c9; then state 0x2c;
 *   0x2c  off the spot to the point 2.0 ahead: animation 0x27, sound 0x4c6 at frame 13; at its
 *         end state 2. On leaving it this console's actor lets its claim go, and the actor
 *         stands at the point.
 * In a room (data_020e54a8 1) the room object at the actor's position plays its sounds
 * (ov004/room_point_sound.h): sound 2 on entering 0x2c, sound 0 each frame of 0x2b and 0x28,
 * sound 1 at frame 12 of 0x27 (at the work's point). */

/* State 0x2d's work at 0x7d4, and a request's arguments for it. */
typedef struct FieldActorChestApproach {
    fx32 x;   /* 0x00: where the actor stands before the chest */
    fx32 z;   /* 0x04 */
    s16 yaw;  /* 0x08 */
    u8 index; /* 0x0a: the chest's index, 0 to 2 */
} FieldActorChestApproach;

/* State 0x2b's work: the place claimed and the way (FieldActorSpotWay). */
typedef struct FieldActorSpotClaim {
    Vec3 point;
    u8 way;
} FieldActorSpotClaim;

/* The ways off a spot: the index into data_ov004_0224776c (the yaw subtracted). */
enum FieldActorSpotWay {
    FIELD_ACTOR_SPOT_STRAIGHT = 0,
    FIELD_ACTOR_SPOT_PLUS = 1,  /* yaw + 0x4000, state 0x2a first */
    FIELD_ACTOR_SPOT_MINUS = 2, /* yaw - 0x4000, state 0x29 first */
};

/* State 0x28's work: the actor's cull flags on entering it (main/actor.h), and whether the
 * body has met the music's beat. */
typedef struct FieldActorSpotStay {
    u32 cull_flags;
    u8 on_beat;
} FieldActorSpotStay;

/* State 0x27's work, and a request's arguments for it: the point and the yaw. */
typedef struct FieldActorSpotEnter {
    fx32 x;
    fx32 z;
    s16 yaw;
} FieldActorSpotEnter;

void FieldActorRoomStates_UpdateChestApproach(struct FieldActor *actor);
void FieldActorRoomStates_EndChestApproach(struct FieldActor *actor);
void FieldActorRoomStates_AnimateChestApproach(struct FieldActor *actor);
void FieldActorRoomStates_StandChestApproach(struct FieldActor *actor);
void FieldActorRoomStates_ChestApproachMessage(struct FieldActor *actor, s16 arg);
void FieldActorRoomStates_EnterChestApproach(struct FieldActor *actor, const struct StateRequest *request, int previous);
u16 FieldActorRoomStates_GetChestApproachSaved(const u8 *saved, u8 *index, u32 *x, u32 *z, u16 *yaw);
void FieldActorRoomStates_PutChestApproachSaved(u8 *saved, char index, int x, int z, s16 yaw);
void FieldActorRoomStates_SetChestApproachWork(FieldActorChestApproach *work, char index, int x, int z, s16 yaw);
int FieldActorRoomStates_RequestChestApproach(struct FieldActor *actor, int index, int x, int z, s16 yaw, int priority,
                                              s16 arg);
void FieldActorRoomStates_PutChestApproachArgs(FieldActorChestApproach *args, char index, int x, int z, s16 yaw);

void FieldActorRoomStates_UpdateSpotStepOff(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotStepOff(struct FieldActor *actor);
void FieldActorRoomStates_ContactSpotStepOff(struct FieldActor *actor);
int FieldActorRoomStates_StepSpotStepOff(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotStepOff(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotStepOffMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotStepOff(struct FieldActor *actor, const struct StateRequest *request, int previous);
void *FieldActorRoomStates_PutSpotStepOffWork(Vec3 *work, const Vec3 *point);
int FieldActorRoomStates_RequestSpotStepOff(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateSpotClaim(struct FieldActor *actor);
void FieldActorRoomStates_RunSpotClaim(struct FieldActor *actor);
void FieldActorRoomStates_ContactSpotClaim(struct FieldActor *actor);
void FieldActorRoomStates_SpotClaimMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotClaim(struct FieldActor *actor, const struct StateRequest *request, int previous);
void *FieldActorRoomStates_SetSpotClaimWork(FieldActorSpotClaim *work, const Vec3 *point, int way);
int FieldActorRoomStates_RequestSpotClaim(struct FieldActor *actor, int way, int priority, int arg);
void FieldActorRoomStates_PutSpotClaimArgs(u8 *payload, u8 way);

void FieldActorRoomStates_UpdateSpotTurnPlus(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotTurnPlus(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotTurnPlus(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotTurnPlusMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotTurnPlus(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestSpotTurnPlus(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateSpotTurnMinus(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotTurnMinus(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotTurnMinus(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotTurnMinusMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotTurnMinus(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestSpotTurnMinus(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateSpotStay(struct FieldActor *actor);
void FieldActorRoomStates_TryLeaveSpotStay(struct FieldActor *actor);
void FieldActorRoomStates_BeatSpotStay(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotStay(struct FieldActor *actor);
void FieldActorRoomStates_SpotStayMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotStay(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestSpotStay(struct FieldActor *actor, u16 blend, int priority, int arg);

void FieldActorRoomStates_UpdateSpotEnter(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotEnter(struct FieldActor *actor);
void FieldActorRoomStates_StepSpotEnter(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotEnter(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotEnterMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotEnter(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetSpotEnterSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw);
void FieldActorRoomStates_PutSpotEnterSaved(u8 *saved, int x, int z, int yaw);
void FieldActorRoomStates_SetSpotEnterWork(FieldActorSpotEnter *work, int x, int z, int yaw);
int FieldActorRoomStates_RequestSpotEnter(struct FieldActor *actor, const int *x, const int *z, const s16 *yaw, int priority,
                                          s16 arg);
int FieldActorRoomStates_RequestSpotEnterAhead(struct FieldActor *actor, int priority, int arg);
void FieldActorRoomStates_PutSpotEnterArgs(FieldActorSpotEnter *args, int x, int z, int yaw);

/* The way onto a spot and the moves of a room object (each message handler asks for its
 * state again with priority 6; those of 0x22 and 0x23 do nothing):
 *   0x24  to a spot: the request names the spot's point and yaw and the side the actor comes
 *         from (FieldActorSpotWay; data_ov004_0224776c's entry is added to the yaw). The actor
 *         eases to the point 2.0 from the spot that way (data_ov004_02254af8 is -2.0) while
 *         animation 0x1a loops, and this console's actor claims the spot's place (main's
 *         place_claim.h). Refused, state 2; given, and once the actor is there, state 0x25
 *         (straight), 0x27 (way 1) or 0x26 (way 2), each asked for with the point 2.0 ahead and
 *         the yaw turned so that the actor ends at the spot's yaw plus 0x8000;
 *   0x26  as 0x27 with animation 0x22; 0x25 as 0x27 with animation 0x21 blended over 3 frames;
 *   0x20  pushing the room object data_ov004_02259784 holds: once the animation is over, where
 *         the object can move ahead and this console's actor is player 0 in a house's room, the
 *         object moves and state 0x22 is asked for; else sound 0x6d the first time when only the
 *         room's objects stop it, and while the stick still pushes ahead nothing more, else
 *         state 0x1e;
 *   0x21  pulling it the same way (backwards, the stick pulled back): animation 0x1e, then
 *         state 0x23;
 *   0x22  a step ahead with the object: animation 0x1f, the actor taken to the point 2.0 ahead
 *         on leaving; at its end state 0x1e while A is held, else state 2;
 *   0x23  a step back: animation 0x20, the actor kept by the walls from where the frame began
 *         and taken to the point 2.0 behind on leaving; its end as 0x22's. */

/* State 0x24's work and a request's arguments for it. */
typedef struct FieldActorSpotApproach {
    fx32 x;  /* 0x00: where the actor stands (the request: the spot) */
    fx32 z;  /* 0x04 */
    s16 yaw; /* 0x08 */
    u8 way;  /* 0x0a: FieldActorSpotWay */
} FieldActorSpotApproach;

/* The work of states 0x22 and 0x23: where the step ends. */
typedef struct FieldActorObjectStep {
    fx32 x;
    fx32 z;
} FieldActorObjectStep;

/* The work of states 0x20 and 0x21. */
typedef struct FieldActorObjectMove {
    u8 warned; /* the move was refused once (with sound 0x6d when only objects stopped it) */
} FieldActorObjectMove;

void FieldActorRoomStates_UpdateSpotEnterMinus(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotEnterMinus(struct FieldActor *actor);
void FieldActorRoomStates_StepSpotEnterMinus(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotEnterMinus(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotEnterMinusMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotEnterMinus(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetSpotEnterMinusSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw);
void FieldActorRoomStates_PutSpotEnterMinusSaved(u8 *saved, int x, int z, int yaw);
void FieldActorRoomStates_SetSpotEnterMinusWork(FieldActorSpotEnter *work, int x, int z, int yaw);
int FieldActorRoomStates_RequestSpotEnterMinus(struct FieldActor *actor, const int *x, const int *z, const s16 *yaw,
                                               int priority, s16 arg);
int FieldActorRoomStates_RequestSpotEnterMinusAhead(struct FieldActor *actor, int priority, int arg);
void FieldActorRoomStates_PutSpotEnterMinusArgs(FieldActorSpotEnter *args, int x, int z, int yaw);

void FieldActorRoomStates_UpdateSpotEnterStraight(struct FieldActor *actor);
void FieldActorRoomStates_EndSpotEnterStraight(struct FieldActor *actor);
void FieldActorRoomStates_StepSpotEnterStraight(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotEnterStraight(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotEnterStraightMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSpotEnterStraight(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetSpotEnterStraightSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw);
void FieldActorRoomStates_PutSpotEnterStraightSaved(u8 *saved, int x, int z, int yaw);
void FieldActorRoomStates_SetSpotEnterStraightWork(FieldActorSpotEnter *work, int x, int z, int yaw);
int FieldActorRoomStates_RequestSpotEnterStraight(struct FieldActor *actor, const int *x, const int *z, const s16 *yaw,
                                                  int priority, s16 arg);
int FieldActorRoomStates_RequestSpotEnterStraightAhead(struct FieldActor *actor, int priority, int arg);
void FieldActorRoomStates_PutSpotEnterStraightArgs(FieldActorSpotEnter *args, int x, int z, int yaw);

void FieldActorRoomStates_UpdateSpotApproach(struct FieldActor *actor);
void FieldActorRoomStates_RunSpotApproach(struct FieldActor *actor);
void FieldActorRoomStates_StandSpotApproach(struct FieldActor *actor);
void FieldActorRoomStates_LeaveSpotApproach(struct FieldActor *actor, int next);
void FieldActorRoomStates_SpotApproachMessage(struct FieldActor *actor, s16 arg);
void FieldActorRoomStates_EnterSpotApproach(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_GetSpotApproachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw, u8 *way);
void FieldActorRoomStates_PutSpotApproachSaved(u8 *saved, int x, int z, int yaw, u8 way);
void FieldActorRoomStates_SetSpotApproachWork(FieldActorSpotApproach *work, int x, int z, s16 yaw, u8 way);
int FieldActorRoomStates_RequestSpotApproach(struct FieldActor *actor, int x, int z, int yaw, u8 way, int priority, s16 arg);
void FieldActorRoomStates_PutSpotApproachArgs(FieldActorSpotApproach *args, int x, int z, s16 yaw, u8 way);

void FieldActorRoomStates_UpdatePullStep(struct FieldActor *actor);
void FieldActorRoomStates_EndPullStep(struct FieldActor *actor);
void FieldActorRoomStates_MovePullStep(struct FieldActor *actor);
void FieldActorRoomStates_LeavePullStep(struct FieldActor *actor);
void FieldActorRoomStates_PullStepMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterPullStep(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_SetPullStepWork(FieldActorObjectStep *work, int x, int z);
int FieldActorRoomStates_RequestPullStep(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdatePushStep(struct FieldActor *actor);
void FieldActorRoomStates_EndPushStep(struct FieldActor *actor);
void FieldActorRoomStates_LeavePushStep(struct FieldActor *actor);
void FieldActorRoomStates_PushStepMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterPushStep(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_SetPushStepWork(FieldActorObjectStep *work, int x, int z);
int FieldActorRoomStates_RequestPushStep(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdatePull(struct FieldActor *actor);
void FieldActorRoomStates_RunPull(struct FieldActor *actor);
void FieldActorRoomStates_PullMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterPull(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestPull(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdatePush(struct FieldActor *actor);
void FieldActorRoomStates_RunPush(struct FieldActor *actor);

#endif
