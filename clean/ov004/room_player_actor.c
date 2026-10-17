/* What the room objects ask of this console's player's field actor (room_player_actor.h). */
#include "room_player_actor.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/angle_sector.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/player_actor_ops.h"
#include "main/session_players.h"
#include "ov004/field_actor_place_states.h"
#include "ov004/field_actor_room_states.h"
#include "ov004/field_actor_room_states2.h"
#include "ov004/field_actor_rooms.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");

/* This console's player. */
#define RPA_OWN SESSION_PLAYERS_OWN

#define RPA_PRIORITY 6
#define RPA_NO_ARG (-1)

/* The fixed point (state 0x12) is asked for below the usual priority. */
#define RPA_FIXED_POINT_PRIORITY 5

/* The last animation of state 0x8a's sequence, played once without a blend. */
#define RPA_ANIM_98 0x98

/* State 0x28 at the spot is entered with a blend of 10 frames. */
#define RPA_SPOT_STAY_BLEND 0x0a

/* The kind of the object under the actor (its word at 0x808) whose way out is a walk 6.0
 * along z to the exit (state 0x8c); any other walks out with state 0x40. */
#define RPA_OBJECT_KIND(actor) FIELD_ACTOR_FIELD(actor, int, 0x808)
#define RPA_KIND_EXIT_AHEAD 4
#define RPA_EXIT_AHEAD 0x6000

/* What RoomPlayerActor_RequestSpotMove is asked for. */
#define RPA_SPOT_STEP_OFF 0
#define RPA_SPOT_TURN_PLUS 1
#define RPA_SPOT_TURN_MINUS 2

/* The spot is approached from behind its facing. */
#define RPA_HALF_TURN 0x8000

/* The actor's flag set while its head item and part C are taken off. */
#define RPA_FLAG_HEADWEAR_OFF 0x0c
#define RPA_ITEM_NONE 0xfff1

/* The states the players' points are asked for in. */
#define RPA_STATE_PLACE 0x08
#define RPA_STATE_SPOT 0x28

/* The flags of this console's actor PlayerActorOps_TestFlag is asked about. */
#define RPA_FLAG_2 0x02
#define RPA_FLAG_15 0x0f

/* func_ov004_0222be34: this console's actor plays animation 0x98 once (no blend); whether there
 * is an actor. */
int RoomPlayerActor_PlayAnimation98(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    FieldActor_PlayAnimationOnce(actor, RPA_ANIM_98, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222be34, RoomPlayerActor_PlayAnimation98)

/* func_ov004_0222be58: this console's actor asked for state 0x8a; whether it was queued. */
int RoomPlayerActor_RequestSequence8A(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestSequence8A(actor, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222be58, RoomPlayerActor_RequestSequence8A)

/* func_ov004_0222be7c: this console's actor lowers its bar for requests to its state's end
 * priority and is asked for state 0x12 (the fixed point) with priority 5; whether it was
 * queued. */
int RoomPlayerActor_RequestFixedPoint(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    return FieldActorRoomStates2_RequestFixedPoint(actor, RPA_FIXED_POINT_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222be7c, RoomPlayerActor_RequestFixedPoint)

/* func_ov004_0222beb4: this console's actor asked for state 0x28 (staying at the spot) with a
 * blend of 10; whether it was queued. */
int RoomPlayerActor_RequestSpotStay(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestSpotStay(actor, RPA_SPOT_STAY_BLEND, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222beb4, RoomPlayerActor_RequestSpotStay)

/* func_ov004_0222bed8: this console's actor asked for state 0x7f (the telephone hung up). */
int RoomPlayerActor_RequestHangUp(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestHangUp(actor, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222bed8, RoomPlayerActor_RequestHangUp)

/* func_ov004_0222befc: this console's actor asked for state 0x7d (the telephone picked up). */
int RoomPlayerActor_RequestPickUp(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestPickUp(actor, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222befc, RoomPlayerActor_RequestPickUp)

/* func_ov004_0222bf20: this console's actor asked for state 0x7a (a new head kind and hair
 * colour, the old head taken off first). */
int RoomPlayerActor_RequestHairOff(const u8 *kind, const u8 *hair_color)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestHairOff(actor, *kind, *hair_color, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222bf20, RoomPlayerActor_RequestHairOff)

/* func_ov004_0222bf50: this console's actor asked for state 0x37 (the item put back). */
int RoomPlayerActor_RequestItemBack(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestItemBack(actor, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222bf50, RoomPlayerActor_RequestItemBack)

/* func_ov004_0222bf74: this console's actor asked for state 0x36 (an item taken out) with the
 * item and what the pointers hold; `second` is handed on as it is (main's scene motion passes
 * its object). Whether it was queued, as a pointer-sized word. */
void *RoomPlayerActor_RequestItemOut(const u16 *item, const int *look, const u8 *stage, const int *kind, int second)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return NULL;
    }
    int queued = FieldActorRoomStates_RequestItemOut(actor, item, *look, *stage, *kind, second, RPA_PRIORITY, RPA_NO_ARG);
    return (void *) (intptr_t) queued;
}
CLEAN_AS(func_ov004_0222bf74, RoomPlayerActor_RequestItemOut)

/* func_ov004_0222bfb4: this console's actor sent out of the room: standing on an object of kind
 * 4 it walks through the exit (state 0x8c) to the point 6.0 further in z than it stands, else
 * it walks out (state 0x40). Whether it was queued. */
int RoomPlayerActor_RequestExit(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (RPA_OBJECT_KIND(actor) == RPA_KIND_EXIT_AHEAD) {
        Vec3 point = actor->position;
        point.z += RPA_EXIT_AHEAD;
        return FieldActorRooms_RequestExit(actor, &point, RPA_PRIORITY, RPA_NO_ARG);
    }
    return FieldActorRoomStates_RequestExitWalk(actor, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222bfb4, RoomPlayerActor_RequestExit)

/* func_ov004_0222c00c: this console's actor asked for state 0x2f (chest `*index` closed). */
int RoomPlayerActor_RequestChestClose(const int *index)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestChestClose(actor, *index, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222c00c, RoomPlayerActor_RequestChestClose)

/* func_ov004_0222c030: this console's actor asked for state 0x2d (walking to chest `*index`,
 * to stand at the point and yaw given).
 * QUIRK: the index is handed on as a byte. */
int RoomPlayerActor_RequestChestApproach(const int *index, const s32 *x, const s32 *z, const s16 *yaw)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActorRoomStates_RequestChestApproach(actor, (u8) *index, *x, *z, *yaw, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222c030, RoomPlayerActor_RequestChestApproach)

/* func_ov004_0222c070: this console's actor asked to leave the spot (kind 0, state 0x2c) or to
 * turn on it (kind 1: state 0x2a, kind 2: state 0x29); other kinds ask nothing. Always 0. */
int RoomPlayerActor_RequestSpotMove(int kind)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    switch (kind) {
        case RPA_SPOT_STEP_OFF:
            FieldActorRoomStates_RequestSpotStepOff(actor, RPA_PRIORITY, RPA_NO_ARG);
            break;
        case RPA_SPOT_TURN_PLUS:
            FieldActorRoomStates_RequestSpotTurnPlus(actor, RPA_PRIORITY, RPA_NO_ARG);
            break;
        case RPA_SPOT_TURN_MINUS:
            FieldActorRoomStates_RequestSpotTurnMinus(actor, RPA_PRIORITY, RPA_NO_ARG);
            break;
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222c070, RoomPlayerActor_RequestSpotMove)

/* func_ov004_0222c0b8: unless a request of priority 6 or more is queued already, this console's
 * actor asked for state 0x24 (walking to the spot at the point given, to face away from
 * `*facing`, by way `*way`); whether it was queued. */
int RoomPlayerActor_RequestSpotApproach(const s32 *x, const s32 *z, const s16 *facing, const u8 *way)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_QueuePriority(actor) >= RPA_PRIORITY) {
        return 0;
    }
    s16 yaw = (s16) (*facing + RPA_HALF_TURN);
    return FieldActorRoomStates_RequestSpotApproach(actor, *x, *z, yaw, *way, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222c0b8, RoomPlayerActor_RequestSpotApproach)

/* func_ov004_0222c110: this console's actor asked for state 0x0a (off the claimed place over
 * `side`, with the sun level stored when `store_sun`); queued, it takes its aiming mode and the
 * answer is 1, else 0. */
int RoomPlayerActor_RequestPlaceOff(int side, int store_sun)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActorPlaceStates_RequestOff(actor, side, store_sun, RPA_PRIORITY, RPA_NO_ARG) == 0) {
        return 0;
    }
    FieldActor_TakeAimMode(actor);
    return 1;
}
CLEAN_AS(func_ov004_0222c110, RoomPlayerActor_RequestPlaceOff)

/* func_ov004_0222c14c: unless a request of priority 6 or more is queued already, this console's
 * actor asked for state 0x0e (to a place at the point and yaw given); the side is 1 when
 * `*yaw - facing` lies on the negative side (AngleSector_Side), else 0. Whether it was queued;
 * the last argument is not read. */
int RoomPlayerActor_RequestPlaceApproach(const fx32 *x, const fx32 *z, const s16 *yaw, s16 facing, int unused)
{
    (void) unused;
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_QueuePriority(actor) >= RPA_PRIORITY) {
        return 0;
    }
    int side = AngleSector_Side((s16) (*yaw - facing)) == ANGLE_SECTOR_NEGATIVE ? 1 : 0;
    return FieldActorPlaceStates_RequestApproach(actor, *x, *z, *yaw, (u8) side, RPA_PRIORITY, RPA_NO_ARG);
}
CLEAN_AS(func_ov004_0222c14c, RoomPlayerActor_RequestPlaceApproach)

/* func_ov004_0222c1b0: this console's actor's head item and part C taken off (`on` 0) or put
 * back on (`on` nonzero) from its record; the actor's flag 12 says they are off. When they are
 * already as asked nothing happens; else the flag changes, the head is asked for with the
 * record's head kind and hair colour (and the face), and when that was taken part C too.
 * Whether there is an actor. */
int RoomPlayerActor_SwitchHeadwear(int on)
{
    FieldActor *actor = SessionPlayers_FieldActor(RPA_OWN);
    if (actor == NULL) {
        return 0;
    }
    u16 head;
    u16 part_c;
    if (on != 0) {
        if (FieldActor_TestFlag(actor, RPA_FLAG_HEADWEAR_OFF) == 0) {
            return 1;
        }
        FieldActor_RecordHeadItem(&head, actor);
        FieldActor_RecordPartCItem(&part_c, actor);
        FieldActor_ClearFlag(actor, RPA_FLAG_HEADWEAR_OFF);
    } else {
        if (FieldActor_TestFlag(actor, RPA_FLAG_HEADWEAR_OFF) != 0) {
            return 1;
        }
        part_c = RPA_ITEM_NONE;
        head = RPA_ITEM_NONE;
        FieldActor_SetFlag(actor, RPA_FLAG_HEADWEAR_OFF);
    }
    unsigned int kind = FieldActor_RecordHeadKind(actor);
    unsigned int hair_color = FieldActor_RecordHairColor(actor);
    if (FieldActor_RequestHead(actor, &head, (u8) kind, (u8) hair_color, 1) != 0) {
        FieldActor_RequestPartC(actor, &part_c);
    }
    return 1;
}
CLEAN_AS(func_ov004_0222c1b0, RoomPlayerActor_SwitchHeadwear)

/* func_ov004_0222c25c: where session player `player` stands while at a claimed place (state
 * 8); whether it is there. */
int RoomPlayerActor_PointAtPlace(Vec3 *point, int player)
{
    return RoomPlayerActor_PointInState(point, player, RPA_STATE_PLACE);
}
CLEAN_AS(func_ov004_0222c25c, RoomPlayerActor_PointAtPlace)

/* func_ov004_0222c268: the same while at the spot (state 0x28). */
int RoomPlayerActor_PointAtSpot(Vec3 *point, int player)
{
    return RoomPlayerActor_PointInState(point, player, RPA_STATE_SPOT);
}
CLEAN_AS(func_ov004_0222c268, RoomPlayerActor_PointAtSpot)

/* func_ov004_0222c274: session player `player`'s position into `point` when it has an actor in
 * `state`; whether it did (else `point` is left alone). */
int RoomPlayerActor_PointInState(Vec3 *point, int player, int state)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL || actor->state != state) {
        return 0;
    }
    point->x = actor->position.x;
    point->y = actor->position.y;
    point->z = actor->position.z;
    return 1;
}
CLEAN_AS(func_ov004_0222c274, RoomPlayerActor_PointInState)

/* func_ov004_0222c2b0: this console's actor's flag 2 (0 without an actor). */
int RoomPlayerActor_TestFlag2(void)
{
    return PlayerActorOps_TestFlag(RPA_FLAG_2, RPA_OWN);
}
CLEAN_AS(func_ov004_0222c2b0, RoomPlayerActor_TestFlag2)

/* func_ov004_0222c2bc: this console's actor's flag 15 (0 without an actor). */
int RoomPlayerActor_TestFlag15(void)
{
    return PlayerActorOps_TestFlag(RPA_FLAG_15, RPA_OWN);
}
CLEAN_AS(func_ov004_0222c2bc, RoomPlayerActor_TestFlag15)
