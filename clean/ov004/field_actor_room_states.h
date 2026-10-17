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

#endif
