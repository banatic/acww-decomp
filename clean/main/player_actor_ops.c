/* What the rest of the game asks of a session player's field actor (player_actor_ops.h). */
#include "player_actor_ops.h"

#include "acre_tile.h"
#include "angle_sector.h"
#include "clean.h"
#include "event_queue.h"
#include "face_texture.h"
#include "field_actor.h"
#include "field_actor_parts.h"
#include "globe.h"
#include "held_item.h"
#include "item_code.h"
#include "item_info.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_exit.h"
#include "scene_kinds.h"
#include "scene_tables.h"
#include "session.h"
#include "session_players.h"

/* Overlay 4: asks for state 0x8d with a point. */
extern int func_ov004_022265dc(FieldActor *actor, const Vec3 *point, int priority, int arg);
/* Overlay 4: an object of the room in front of this console's actor; negative for none. */
extern int func_ov004_0223bbc0(int *a, int *b, void *c, void *d);
/* Overlay 4: what leaving states 0x2c, 0x29, 0x2a, 0xa, 0xf and 0xd does to the actor (its place
 * and yaw among it), each given the state it leaves for. */
extern void func_ov004_02228774(FieldActor *actor, int next);
extern void func_ov004_02228ac4(FieldActor *actor, int next);
extern void func_ov004_02228b90(FieldActor *actor, int next);
extern void func_ov004_0222b85c(FieldActor *actor, int next);
extern void func_ov004_0222ae34(FieldActor *actor, int next);
extern void func_ov004_0222b2d8(FieldActor *actor, int next);

extern NetSession *data_020ccf94;
extern AcreMap *data_021c80bc; /* the map of the scene */
extern u8 data_020e54a8;       /* 0 outdoors, 1 in a room */
/* The distance ahead of the actor at which its item is looked for, and the one at which it
 * stands after leaving states 0x29 and 0x2a. */
extern const fx32 data_020e2f7c;
extern const fx32 data_020d18b4;
/* The count state 0x14 is asked for with, by its kind (from 1). */
extern const u8 data_020d1894[];

/* The priority and argument most requests here are made with. */
#define PLAYER_ACTOR_OPS_PRIORITY_5 5
#define PLAYER_ACTOR_OPS_PRIORITY_6 6
#define PLAYER_ACTOR_OPS_ARG -1

#define PLAYER_ACTOR_OPS_ITEM_NONE 0xfff1

/* Words of the actor its header leaves unnamed: the object under it and that object's kind
 * (FieldActor_NoteObjectUnderfoot; -1 and 0 for none), the point at 0x450 (the head's; all
 * zero for none), the look it is asked to turn to (with flag 0x15), and the byte at 0x8eb. */
#define PLAYER_ACTOR_OPS_OBJECT(actor) FIELD_ACTOR_FIELD(actor, int, 0x804)
#define PLAYER_ACTOR_OPS_OBJECT_KIND(actor) FIELD_ACTOR_FIELD(actor, int, 0x808)
#define PLAYER_ACTOR_OPS_HEAD_POINT(actor) FIELD_ACTOR_FIELD(actor, Vec3, 0x450)
#define PLAYER_ACTOR_OPS_LOOK_PITCH(actor) FIELD_ACTOR_FIELD(actor, u16, 0x460)
#define PLAYER_ACTOR_OPS_LOOK_YAW(actor) FIELD_ACTOR_FIELD(actor, u16, 0x462)
#define PLAYER_ACTOR_OPS_MADE_WITH(actor) FIELD_ACTOR_FIELD(actor, u32, 8) /* the actor's argument */

/* The object kind of a door (SceneExit_DoorInfo) and how far beyond the door the actor is sent. */
#define PLAYER_ACTOR_OPS_KIND_DOOR 3
#define PLAYER_ACTOR_OPS_NO_OBJECT -1
#define PLAYER_ACTOR_OPS_DOOR_STEP 0x6000

/* From this animation on the actor's looks and held item are left alone. */
#define PLAYER_ACTOR_OPS_FIXED_LOOKS_ANIMATION 0xa1

/* The flags of FieldActor.flags these functions use by number. */
#define PLAYER_ACTOR_OPS_FLAG_1 1
#define PLAYER_ACTOR_OPS_FLAG_4 4
#define PLAYER_ACTOR_OPS_FLAG_BUSY 5
#define PLAYER_ACTOR_OPS_FLAG_7 7
#define PLAYER_ACTOR_OPS_FLAG_8 8
#define PLAYER_ACTOR_OPS_FLAG_B 0xb
#define PLAYER_ACTOR_OPS_FLAG_E 0xe
#define PLAYER_ACTOR_OPS_FLAG_10 0x10
#define PLAYER_ACTOR_OPS_FLAG_13 0x13
#define PLAYER_ACTOR_OPS_FLAG_LOOK 0x15
#define PLAYER_ACTOR_OPS_FLAG_17 0x17

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "anim");
static_assert(offsetof(FieldActor, held) == 0x5a0, "held");
static_assert(offsetof(FieldActor, line_mode) == 0x5cc, "line_mode");
static_assert(offsetof(FieldActor, unk_698) == 0x698, "unk_698");
static_assert(sizeof(FieldActorBlock48) == 0x30, "FieldActorBlock48");
static_assert(offsetof(FieldActor, start_position) == 0x6f4, "start_position");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, unk_70D) == 0x70d, "unk_70D");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next_state");

/* The start state in the actor's argument: bits 22 to 29 (the player is bits 30 and 31). */
static int player_actor_ops_start_state(u32 made_with)
{
    return (int) ((made_with >> 22) & 0xff);
}

/* The actor may be interrupted by a request of its state's end priority from now on. */
static void player_actor_ops_open_queue(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
}

/* func_020953a0: does nothing. */
void PlayerActorOps_Nothing(void) {}
CLEAN_AS(func_020953a0, PlayerActorOps_Nothing)

/* func_020953a4: notes the kind of the object under this console's actor. */
void PlayerActorOps_NoteObjectKind(int *kind)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor != NULL) {
        PLAYER_ACTOR_OPS_OBJECT_KIND(actor) = *kind;
    }
}
CLEAN_AS(func_020953a4, PlayerActorOps_NoteObjectKind)

/* func_020953c4: notes the object under this console's actor. */
void PlayerActorOps_NoteObject(unsigned int *object)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor != NULL) {
        PLAYER_ACTOR_OPS_OBJECT(actor) = (int) *object;
    }
}
CLEAN_AS(func_020953c4, PlayerActorOps_NoteObject)

/* func_020953e4: while this console's actor stands (state 2), the item on the map a step ahead
 * of it (AcreTile_ItemAt, layer 0); NULL otherwise. In a room only for player 0 in a house's
 * room where no object of the room is ahead; outdoors not on a marked tile. */
u16 *PlayerActorOps_ItemAhead(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL || actor->state != 2) {
        return NULL;
    }

    Vec3 ahead;
    FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_020e2f7c);
    if (data_020e54a8 == 1) {
        int a;
        int b;
        if (SceneKinds_CurrentIsHouseRoom() != 0 && data_020ccf94->local_player == 0 &&
            func_ov004_0223bbc0(&a, &b, NULL, NULL) < 0) {
            return AcreTile_ItemAt(data_021c80bc, &ahead, 0);
        }
        return NULL;
    }
    AcreMap *map = data_021c80bc;
    if (AcreTile_IsMarkedAt(map, &ahead) != 0) {
        return NULL;
    }
    return AcreTile_ItemAt(map, &ahead, 0);
}
CLEAN_AS(func_020953e4, PlayerActorOps_ItemAhead)

/* func_0209549c: a copy of the 48-byte block at 0x698 of player `player`'s actor, two words at
 * a time from the front (as the ROM copies, so overlapping blocks come out the same).
 * REQUIRES: the actor exists (it is not checked for NULL). */
void PlayerActorOps_CopyBlock698(struct FieldActorBlock48 *out, int player)
{
    const u32 *from = (const u32 *) (const void *) &SessionPlayers_FieldActor(player)->unk_698;
    u32 *to = (u32 *) (void *) out;
    for (size_t i = 0; i < sizeof(FieldActorBlock48) / sizeof(u32); i += 2) {
        u32 first = from[i];
        u32 second = from[i + 1];
        to[i] = first;
        to[i + 1] = second;
    }
}
CLEAN_AS(func_0209549c, PlayerActorOps_CopyBlock698)

/* func_020954c0: the head point of player `player`'s actor, taken back from the drawn globe
 * (Globe_Unbend); whether there is one (an actor whose point is not all zero). */
int PlayerActorOps_HeadPoint(Vec3 *out, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    const Vec3 *head = &PLAYER_ACTOR_OPS_HEAD_POINT(actor);
    if (head->x == 0 && head->y == 0 && head->z == 0) {
        return 0;
    }
    out->x = head->x;
    out->y = head->y;
    out->z = head->z;
    Globe_Unbend(out, out);
    return 1;
}
CLEAN_AS(func_020954c0, PlayerActorOps_HeadPoint)

/* func_02095518: player `player`'s actor is to look at `pitch` and `yaw` (flag 0x15 set if it
 * was not); whether it has an actor. */
int PlayerActorOps_SetLook(int pitch, int yaw, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_LOOK) == 0) {
        FieldActor_SetFlag(actor, PLAYER_ACTOR_OPS_FLAG_LOOK);
    }
    PLAYER_ACTOR_OPS_LOOK_PITCH(actor) = (u16) pitch;
    PLAYER_ACTOR_OPS_LOOK_YAW(actor) = (u16) yaw;
    return 1;
}
CLEAN_AS(func_02095518, PlayerActorOps_SetLook)

/* func_02095558: sets the sun level in player `player`'s record; whether it has one. */
int PlayerActorOps_SetSunLevel(int level, int player)
{
    u8 *record = PlayerRecords_OfPlayer(player);
    if (record == NULL) {
        return 0;
    }
    PlayerRecord_SetSunLevel(record, level);
    return 1;
}
CLEAN_AS(func_02095558, PlayerActorOps_SetSunLevel)

/* func_02095578: sets or clears flag 0 in player `player`'s record and loads the face that goes
 * with it into the actor (the record's face, 0x10 further with the flag); whether both exist and
 * the actor's looks were not fixed by its animation. */
int PlayerActorOps_SetFlag0(int set, int player)
{
    u8 *record = PlayerRecords_OfPlayer(player);
    if (record == NULL) {
        return 0;
    }
    PlayerRecord_SetFlag0(record, set);
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL || actor->animation >= PLAYER_ACTOR_OPS_FIXED_LOOKS_ANIMATION) {
        return 0;
    }
    u32 face = PlayerRecord_Face(record);
    if (set != 0) {
        face += 0x10;
    }
    FaceTexture_Load(&actor->unk_70D[0], (int) face);
    return 1;
}
CLEAN_AS(func_02095578, PlayerActorOps_SetFlag0)

/* func_020955e0: puts on `item` as player `player`'s clothes (part 0), part C (1) or head item
 * (2): in the record, then on the actor (the cloth set and bound, or the part asked for, the
 * head with the record's head kind and hair colour); whether both exist and the actor's looks
 * were not fixed by its animation. Another part changes nothing but answers the same. */
int PlayerActorOps_SetWorn(u16 *item, int part, int player)
{
    u8 *record = PlayerRecords_OfPlayer(player);
    if (record == NULL) {
        return 0;
    }
    switch (part) {
        case 0:
            PlayerRecord_SetClothes(record, item);
            break;
        case 1:
            PlayerRecord_SetPartCItem(record, item);
            break;
        case 2:
            PlayerRecord_SetHeadItem(record, item);
            break;
        default:
            break;
    }

    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL || actor->animation >= PLAYER_ACTOR_OPS_FIXED_LOOKS_ANIMATION) {
        return 0;
    }
    u16 copy;
    switch (part) {
        case 0:
            FieldActor_SetCloth(actor, item);
            FieldActor_BindCloth(actor);
            break;
        case 1:
            copy = *item;
            FieldActor_RequestPartC(actor, &copy);
            break;
        case 2: {
            copy = *item;
            unsigned int kind = FieldActor_RecordHeadKind(actor);
            unsigned int hair_color = FieldActor_RecordHairColor(actor);
            FieldActor_RequestHead(actor, &copy, (u8) kind, (u8) hair_color, 0);
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_020955e0, PlayerActorOps_SetWorn)

/* func_02095694: player `player` is to hold held model `number` (from 1; 0 or past the count:
 * nothing). The record's held item is set; unless the actor's looks are fixed by its animation
 * the actor takes the item in hand (with the record, or without one for nothing), its animation
 * restarts and, for an item, the held item is updated. Whether the actor took it; 0 without an
 * actor (then the record is left alone). The record is not checked for NULL: a player with an
 * actor has one. */
int PlayerActorOps_SetHeldModel(unsigned int number, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    u8 *record = PlayerRecords_OfPlayer(player);
    int none = number == 0 || ItemInfo_HeldModelCount() < number;
    HeldItemObject *held = (HeldItemObject *) (void *) actor->held;

    if (actor->animation >= PLAYER_ACTOR_OPS_FIXED_LOOKS_ANIMATION) {
        u16 item;
        if (none) {
            item = PLAYER_ACTOR_OPS_ITEM_NONE;
        } else {
            ItemInfo_HeldModelItem(&item, (int) (number - 1));
        }
        PlayerRecord_SetHeldItem(record, &item);
        return 0;
    }

    if (none) {
        u16 item = PLAYER_ACTOR_OPS_ITEM_NONE;
        PlayerRecord_SetHeldItem(record, &item);
        u16 taken = PLAYER_ACTOR_OPS_ITEM_NONE;
        HeldItem_Take(held, &taken, NULL);
        FieldActor_RestartAnimation(actor);
    } else {
        u16 item;
        ItemInfo_HeldModelItem(&item, (int) (number - 1));
        PlayerRecord_SetHeldItem(record, &item);
        HeldItem_Take(held, &item, record);
        FieldActor_RestartAnimation(actor);
        HeldItem_Update(held);
    }
    return 1;
}
CLEAN_AS(func_02095694, PlayerActorOps_SetHeldModel)

/* func_02095764: the item player `player`'s actor holds as its record says; ITEM_NONE without
 * an actor (written first either way). */
void PlayerActorOps_HeldItem(u16 *item, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    *item = PLAYER_ACTOR_OPS_ITEM_NONE;
    if (actor != NULL) {
        u16 held;
        FieldActor_RecordHeldItem(&held, actor);
        *item = held;
    }
}
CLEAN_AS(func_02095764, PlayerActorOps_HeldItem)

/* func_02095794: where player `player`'s actor was when its frame began, or NULL. */
Vec3 *PlayerActorOps_StartPosition(int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    return actor != NULL ? &actor->start_position : NULL;
}
CLEAN_AS(func_02095794, PlayerActorOps_StartPosition)

/* func_020957b4: this console's actor may be interrupted from now on and is asked for state
 * 0x14 with kind `*kind` and that kind's count (data_020d1894); whether it was queued.
 * REQUIRES: `*kind` is 1 or more (the table starts at kind 1). */
int PlayerActorOps_RequestState14(unsigned char *kind)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    u8 count = data_020d1894[*kind - 1];
    player_actor_ops_open_queue(actor);
    return FieldActor_RequestState14(actor, *kind, count, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_020957b4, PlayerActorOps_RequestState14)

/* func_02095804: this console's actor may be interrupted from now on and is asked for state
 * 0x13; whether it was queued. */
int PlayerActorOps_RequestState13(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    player_actor_ops_open_queue(actor);
    return FieldActor_RequestState13(actor, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095804, PlayerActorOps_RequestState13)

/* func_0209583c: this console's actor may be interrupted from now on; standing on a door, it is
 * asked for state 0x8d towards the point 6.0 beyond its position in the door's direction (the
 * door's facing from the scene's exits, else the actor's yaw, sorted into four sectors).
 * Whether it was queued; 0 off a door. */
int PlayerActorOps_StepOffDoor(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    player_actor_ops_open_queue(actor);
    if (PLAYER_ACTOR_OPS_OBJECT_KIND(actor) != PLAYER_ACTOR_OPS_KIND_DOOR) {
        return 0;
    }

    int object = PLAYER_ACTOR_OPS_OBJECT(actor);
    s16 facing = actor->yaw;
    if (object != PLAYER_ACTOR_OPS_NO_OBJECT) {
        int kind;
        SceneExit_DoorInfo((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), object, &kind, &facing);
    }
    int sector = AngleSector_Four(facing);
    Vec3 point = actor->position;
    switch (sector) {
        case 0:
            point.z += PLAYER_ACTOR_OPS_DOOR_STEP;
            break;
        case 1:
            point.x += PLAYER_ACTOR_OPS_DOOR_STEP;
            break;
        case 2:
            point.z -= PLAYER_ACTOR_OPS_DOOR_STEP;
            break;
        case 3:
            point.x -= PLAYER_ACTOR_OPS_DOOR_STEP;
            break;
        default:
            break;
    }
    return func_ov004_022265dc(actor, &point, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_0209583c, PlayerActorOps_StepOffDoor)

/* func_02095904: this console's actor is asked for state 0x10 for 3 frames; 1 at once when it
 * is in state 0x28 with flag 0xb. Whether it was queued. */
int PlayerActorOps_RequestState10(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (actor->state == 0x28 && FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_B) != 0) {
        return 1;
    }
    return FieldActor_RequestState10(actor, 3, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095904, PlayerActorOps_RequestState10)

/* func_02095944: this console's actor goes to an object the way `approach` says
 * (SceneObjectBase_ApproachKind): with approach 0 or 1 and a tool in hand (other than tool 10
 * with approach 1) it is asked for state 0x3d from where it stands; otherwise flag 1 is set and
 * it is asked for state 0x10 for 3 frames. */
void PlayerActorOps_Approach(unsigned int approach)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return;
    }
    int tool = FieldActor_HeldTool(actor);
    if (tool == 0 || (tool == 10 && approach == 1) || approach >= 2) {
        FieldActor_SetFlag(actor, PLAYER_ACTOR_OPS_FLAG_1);
        FieldActor_RequestState10(actor, 3, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
    } else {
        FieldActor_RequestState3D(actor, 0x10, (int) approach, actor->position.x, actor->position.z, actor->yaw,
                                  PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
    }
}
CLEAN_AS(func_02095944, PlayerActorOps_Approach)

/* func_020959ac: unless an event of kind 5 is unfinished or this console's actor has flag 0xb:
 * with nothing of priority 5 or more queued the actor is asked for state 0x79 (its answer);
 * otherwise, in state 0x4f with a line mode other than 5, for state 0x51 with 1 (answer 1).
 * Else 0. */
int PlayerActorOps_RequestState79(void)
{
    if (EventQueue_IsKind5Unfinished() != 0) {
        return 0;
    }
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL || FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_B) != 0) {
        return 0;
    }
    if (FieldActor_QueuePriorityAbove(actor) < 5) {
        return FieldActor_RequestState79(actor, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
    }
    if (actor->state != 0x4f || actor->line_mode == 5) {
        return 0;
    }
    FieldActor_RequestState51(actor, 1, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
    return 1;
}
CLEAN_AS(func_020959ac, PlayerActorOps_RequestState79)

/* func_02095a28: this console's actor is asked for state 0x32; whether it was queued. */
int PlayerActorOps_RequestState32(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState32(actor, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095a28, PlayerActorOps_RequestState32)

/* func_02095a4c: this console's actor is asked for state 0x30 with `item` and the four values;
 * whether it was queued. */
int PlayerActorOps_RequestState30(u16 *item, int *a, unsigned char *b, int *c, int d)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState30(actor, item, *a, *b, *c, d, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095a4c, PlayerActorOps_RequestState30)

/* func_02095a8c: player `player`'s actor is asked to turn to `yaw` (state 0x70); whether it was
 * queued. */
int PlayerActorOps_Turn(int yaw, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState70(actor, yaw, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095a8c, PlayerActorOps_Turn)

/* func_02095ab0: player `player`'s actor is asked to move to a copy of `point` with `accel`
 * (state 0x6f); whether it was queued. */
int PlayerActorOps_MoveTo(Vec3 *point, int accel, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    Vec3 copy = *point;
    return FieldActor_RequestState6F(actor, &copy, accel, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095ab0, PlayerActorOps_MoveTo)

/* func_02095aec: this console's actor is asked for state 0x85 with a copy of `*item`; whether it
 * was queued. */
int PlayerActorOps_RequestState85(unsigned short *item)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    u16 copy = *item;
    return FieldActor_RequestState85(actor, &copy, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095aec, PlayerActorOps_RequestState85)

/* func_02095b1c: this console's actor is asked for state 0x3f with `*item`; whether it was
 * queued. */
int PlayerActorOps_RequestState3F(unsigned short *item)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState3F(actor, *item, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095b1c, PlayerActorOps_RequestState3F)

/* func_02095b40: state 7 with `*item`, kind 2, then state 0x10. */
int PlayerActorOps_RequestState7Kind2Next10(u16 *item)
{
    return PlayerActorOps_RequestState7(item, 2, 0x10);
}
CLEAN_AS(func_02095b40, PlayerActorOps_RequestState7Kind2Next10)

/* func_02095b4c: state 7 with `*item`, kind 1, then state 0x10 (the answer is dropped). */
void PlayerActorOps_RequestState7Kind1Next10(u16 *item)
{
    PlayerActorOps_RequestState7(item, 1, 0x10);
}
CLEAN_AS(func_02095b4c, PlayerActorOps_RequestState7Kind1Next10)

/* func_02095b58: state 7 with `*item`, kind 0, then state 0x10. */
int PlayerActorOps_RequestState7Kind0Next10(u16 *item)
{
    return PlayerActorOps_RequestState7(item, 0, 0x10);
}
CLEAN_AS(func_02095b58, PlayerActorOps_RequestState7Kind0Next10)

/* func_02095b64: state 7 with no item, kind 3, then state 5. */
int PlayerActorOps_RequestState7NoItem(void)
{
    u16 item = PLAYER_ACTOR_OPS_ITEM_NONE;
    return PlayerActorOps_RequestState7(&item, 3, 5);
}
CLEAN_AS(func_02095b64, PlayerActorOps_RequestState7NoItem)

/* func_02095b84: state 7 with `*item`, kind 2, then state 5. */
int PlayerActorOps_RequestState7Kind2Next5(u16 *item)
{
    return PlayerActorOps_RequestState7(item, 2, 5);
}
CLEAN_AS(func_02095b84, PlayerActorOps_RequestState7Kind2Next5)

/* func_02095b90: state 7 with `*item`, kind 1, then state 5. */
int PlayerActorOps_RequestState7Kind1Next5(u16 *item)
{
    return PlayerActorOps_RequestState7(item, 1, 5);
}
CLEAN_AS(func_02095b90, PlayerActorOps_RequestState7Kind1Next5)

/* func_02095b9c: state 7 with `*item`, kind 0, then state 5. */
int PlayerActorOps_RequestState7Kind0Next5(u16 *item)
{
    return PlayerActorOps_RequestState7(item, 0, 5);
}
CLEAN_AS(func_02095b9c, PlayerActorOps_RequestState7Kind0Next5)

/* func_02095ba8: this console's actor is asked for state 7 with `*item`, `kind` and the state to
 * follow; whether it was queued. */
int PlayerActorOps_RequestState7(unsigned short *item, int kind, int next)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState7(actor, *item, kind, next, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095ba8, PlayerActorOps_RequestState7)

/* func_02095bdc: this console's actor ends what it does. The byte at 0x8eb is taken (and
 * cleared); in states 0x2c, 0x29 and 0x2a the answer is 1 at once. Otherwise the actor may be
 * interrupted from now on and is asked for state 0x76 with mode (the byte + 3) when the byte was
 * positive; else, outdoors, holding an item (its variant's base item not that of ITEM_NONE for
 * an item with variants) and no tool, outside state 0x39, for state 0x3d (2, 2, at 0, 0, yaw 0);
 * else for state 2 for 3 frames. The request's answer. */
int PlayerActorOps_FinishState(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    int state = actor->state;
    int pending = FIELD_ACTOR_UNK_8EB(actor);
    FIELD_ACTOR_UNK_8EB(actor) = 0;
    if (state == 0x2c || state == 0x29 || state == 0x2a) {
        return 1;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, state);
    if (pending > 0) {
        return (int) (intptr_t) FieldActor_RequestState76(actor, (u8) (pending + 3), 0, 0, PLAYER_ACTOR_OPS_PRIORITY_6,
                                                          PLAYER_ACTOR_OPS_ARG);
    }

    if (data_020e54a8 == 0) {
        u16 items[2];
        int empty;
        FieldActor_RecordHeldItem(&items[0], actor);
        if (ItemCode_HasVariant(&items[0])) {
            items[1] = PLAYER_ACTOR_OPS_ITEM_NONE;
            int held = ItemCode_VariantItem(&items[0]);
            empty = held == ItemCode_VariantItem(&items[1]);
        } else {
            empty = items[0] == PLAYER_ACTOR_OPS_ITEM_NONE;
        }
        if (!empty && FieldActor_HeldToolNumber(actor) == 0 && state != 0x39) {
            return FieldActor_RequestState3D(actor, 2, 2, 0, 0, 0, PLAYER_ACTOR_OPS_PRIORITY_6, PLAYER_ACTOR_OPS_ARG);
        }
    }
    return FieldActor_RequestState2(actor, 3, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095bdc, PlayerActorOps_FinishState)

/* func_02095ce0: this console's actor is asked for state 5 for 3 frames; whether it was queued. */
int PlayerActorOps_RequestState5(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState5(actor, 3, PLAYER_ACTOR_OPS_PRIORITY_5, PLAYER_ACTOR_OPS_ARG);
}
CLEAN_AS(func_02095ce0, PlayerActorOps_RequestState5)

/* func_02095d04: whether this console's actor has nothing of priority 5 or more queued. */
int PlayerActorOps_QueueBelow5(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    return actor != NULL && FieldActor_QueuePriority(actor) < 5;
}
CLEAN_AS(func_02095d04, PlayerActorOps_QueueBelow5)

/* func_02095d2c: whether this console's actor has flag 0xb in state 0x28, 2 or 8, while flag 8
 * of the event queue and the actor's flag 0x13 are clear. */
int PlayerActorOps_Flag0bInState28_2_8(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    int state = actor->state;
    if (EventQueue_TestFlag8() != 0 || FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_13) != 0) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_B) == 0) {
        return 0;
    }
    return state == 0x28 || state == 2 || state == 8;
}
CLEAN_AS(func_02095d2c, PlayerActorOps_Flag0bInState28_2_8)

/* func_02095d84: whether this console's actor may act: 1 with flag 0xb in state 0x28 or 0x7c;
 * else without flag 0x13 and with nothing of priority 5 or more queued. */
int PlayerActorOps_MayAct(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_B) != 0 && (actor->state == 0x28 || actor->state == 0x7c)) {
        return 1;
    }
    if (FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_13) != 0) {
        return 0;
    }
    return FieldActor_QueuePriority(actor) < 5;
}
CLEAN_AS(func_02095d84, PlayerActorOps_MayAct)

/* func_02095de0: whether this console's actor has nothing of priority 6 or more queued. */
int PlayerActorOps_QueueBelow6(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    return actor != NULL && FieldActor_QueuePriority(actor) < 6;
}
CLEAN_AS(func_02095de0, PlayerActorOps_QueueBelow6)

/* func_02095e08: whether this console's actor is free to act: none of its flags 0xb, 0x13, 7
 * and 8 nor the event queue's flag 8, not in state 0x3d, and nothing of priority 5 or more
 * queued. */
int PlayerActorOps_MayActFree(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL || FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_B) != 0) {
        return 0;
    }
    if (EventQueue_TestFlag8() != 0 || FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_13) != 0) {
        return 0;
    }
    if (actor->state == 0x3d || FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_7) != 0 ||
        FieldActor_TestFlag(actor, PLAYER_ACTOR_OPS_FLAG_8) != 0) {
        return 0;
    }
    return FieldActor_QueuePriority(actor) < 5;
}
CLEAN_AS(func_02095e08, PlayerActorOps_MayActFree)

/* func_02095e84: clears flag `bit` of player `player`'s actor; whether it has one. */
int PlayerActorOps_ClearFlag(int bit, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    FieldActor_ClearFlag(actor, bit);
    return 1;
}
CLEAN_AS(func_02095e84, PlayerActorOps_ClearFlag)

/* func_02095ea4: sets flag `bit` of player `player`'s actor; whether it has one. */
int PlayerActorOps_SetFlag(int bit, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    FieldActor_SetFlag(actor, bit);
    return 1;
}
CLEAN_AS(func_02095ea4, PlayerActorOps_SetFlag)

/* func_02095ec4: sets flag 0x17 of this console's actor. */
int PlayerActorOps_SetOwnFlag17(void)
{
    return PlayerActorOps_SetFlag(PLAYER_ACTOR_OPS_FLAG_17, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02095ec4, PlayerActorOps_SetOwnFlag17)

/* func_02095ed0: sets (`on`) or clears flag 0x10 of player `player`'s actor. */
int PlayerActorOps_SwitchFlag10(int on, int player)
{
    if (on != 0) {
        return PlayerActorOps_SetFlag(PLAYER_ACTOR_OPS_FLAG_10, player);
    }
    return PlayerActorOps_ClearFlag(PLAYER_ACTOR_OPS_FLAG_10, player);
}
CLEAN_AS(func_02095ed0, PlayerActorOps_SwitchFlag10)

/* func_02095eec: sets (`on`) or clears flag 0xe of player `player`'s actor. */
void PlayerActorOps_SwitchFlag0e(int on, int player)
{
    if (on != 0) {
        PlayerActorOps_SetFlag(PLAYER_ACTOR_OPS_FLAG_E, player);
    } else {
        PlayerActorOps_ClearFlag(PLAYER_ACTOR_OPS_FLAG_E, player);
    }
}
CLEAN_AS(func_02095eec, PlayerActorOps_SwitchFlag0e)

/* func_02095f08: sets (`on`) or clears flag 0xb of this console's actor. */
int PlayerActorOps_SwitchOwnFlag0b(int on)
{
    if (on != 0) {
        return PlayerActorOps_SetFlag(PLAYER_ACTOR_OPS_FLAG_B, PLAYER_ACTOR_OPS_OWN);
    }
    return PlayerActorOps_ClearFlag(PLAYER_ACTOR_OPS_FLAG_B, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02095f08, PlayerActorOps_SwitchOwnFlag0b)

/* func_02095f28: flag 0xa20 of the state table for this console's actor's state. */
int PlayerActorOps_StateFlagA20(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_StateFlagA20(actor, actor->state);
}
CLEAN_AS(func_02095f28, PlayerActorOps_StateFlagA20)

/* func_02095f4c: whether this console's actor is in state 0x3f. */
int PlayerActorOps_InState3F(void)
{
    return PlayerActorOps_InState(0x3f, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02095f4c, PlayerActorOps_InState3F)

/* func_02095f58: whether this console's actor is in state 7 before frame 19 of its animation. */
int PlayerActorOps_EarlyInState7(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    return actor != NULL && actor->state == 7 && actor->anim.frame < 0x13000;
}
CLEAN_AS(func_02095f58, PlayerActorOps_EarlyInState7)

/* func_02095f90: this console's actor's state, or the state it was made to start in while that
 * is 0; PLAYER_ACTOR_OPS_NO_STATE without an actor. */
int PlayerActorOps_StateOrStartState(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return PLAYER_ACTOR_OPS_NO_STATE;
    }
    if (actor->state != 0) {
        return actor->state;
    }
    return player_actor_ops_start_state(PLAYER_ACTOR_OPS_MADE_WITH(actor));
}
CLEAN_AS(func_02095f90, PlayerActorOps_StateOrStartState)

/* func_02095fc0: where this console's actor will stand and face once it has left its state, and
 * the state it leaves for (PLAYER_ACTOR_OPS_NO_STATE without an actor; then nothing is written).
 * For states that end elsewhere the overlay's leaving code runs (0x29 and 0x2a then stand
 * data_020d18b4 ahead of where the actor was, in the yaw that code left); the actor's position
 * and yaw are put back afterwards. Other states give themselves and the actor's place. */
int PlayerActorOps_PlaceAfterState(Vec3 *position, s16 *yaw)
{
    FieldActor *actor = SessionPlayers_FieldActor(PLAYER_ACTOR_OPS_OWN);
    if (actor == NULL) {
        return PLAYER_ACTOR_OPS_NO_STATE;
    }
    Vec3 saved = actor->position;
    s16 saved_yaw = actor->yaw;
    int next = actor->state;
    switch (next) {
        case 0x10:
        case 0xe:
            next = 2;
            break;
        case 0x2c:
            next = 2;
            func_ov004_02228774(actor, next);
            break;
        case 0x29:
        case 0x2a: {
            if (next == 0x29) {
                func_ov004_02228ac4(actor, 0x2c);
            } else {
                func_ov004_02228b90(actor, 0x2c);
            }
            next = 2;
            Vec3 ahead;
            FieldActor_PointAhead(&ahead, actor, &saved, (const u16 *) &actor->yaw, &data_020d18b4);
            actor->position = ahead;
            break;
        }
        case 9:
        case 0xb:
        case 0xc:
            next = 8;
            break;
        case 0xa:
            next = 2;
            func_ov004_0222b85c(actor, next);
            break;
        case 0xf:
            next = 8;
            func_ov004_0222ae34(actor, next);
            break;
        case 0xd:
            next = 8;
            func_ov004_0222b2d8(actor, next);
            break;
        default:
            break;
    }
    position->x = actor->position.x;
    position->y = actor->position.y;
    position->z = actor->position.z;
    *yaw = actor->yaw;
    actor->position = saved;
    actor->yaw = saved_yaw;
    return next;
}
CLEAN_AS(func_02095fc0, PlayerActorOps_PlaceAfterState)

/* func_020960d8: player `player`'s actor's state, PLAYER_ACTOR_OPS_NO_STATE without one. */
int PlayerActorOps_State(int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    return actor != NULL ? actor->state : PLAYER_ACTOR_OPS_NO_STATE;
}
CLEAN_AS(func_020960d8, PlayerActorOps_State)

/* func_020960f8: whether player `player`'s actor is in `state`. */
int PlayerActorOps_InState(int state, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    return actor != NULL && actor->state == state;
}
CLEAN_AS(func_020960f8, PlayerActorOps_InState)

/* DWC_Alloc (a name the symbols give this function, not NitroDWC's): flag `bit` of player
 * `player`'s actor; 0 without one. */
int PlayerActorOps_TestFlag(int bit, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_TestFlag(actor, bit);
}
CLEAN_AS(DWC_Alloc, PlayerActorOps_TestFlag)

/* func_02096144: whether this console's actor is in state 0x90. */
int PlayerActorOps_InState90(void)
{
    return PlayerActorOps_InState(0x90, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02096144, PlayerActorOps_InState90)

/* func_02096150: whether this console's actor is in state 5. */
int PlayerActorOps_InState5(void)
{
    return PlayerActorOps_InState(5, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02096150, PlayerActorOps_InState5)

/* DWCi_GsMalloc (a name the symbols give this function, not NitroDWC's): flag 5 of player
 * `player`'s actor, set while it is busy. */
int PlayerActorOps_IsBusy(int player)
{
    return PlayerActorOps_TestFlag(PLAYER_ACTOR_OPS_FLAG_BUSY, player);
}
CLEAN_AS(DWCi_GsMalloc, PlayerActorOps_IsBusy)

/* func_02096168: flag 4 of this console's actor. */
int PlayerActorOps_TestOwnFlag4(void)
{
    return PlayerActorOps_TestFlag(PLAYER_ACTOR_OPS_FLAG_4, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02096168, PlayerActorOps_TestOwnFlag4)

/* func_02096174: flag 1 of this console's actor. */
int PlayerActorOps_TestOwnFlag1(void)
{
    return PlayerActorOps_TestFlag(PLAYER_ACTOR_OPS_FLAG_1, PLAYER_ACTOR_OPS_OWN);
}
CLEAN_AS(func_02096174, PlayerActorOps_TestOwnFlag1)

/* func_02096180: the state a field actor was made to start in, from its argument (bits 22 to
 * 29). */
int PlayerActorOps_StartState(int made_with)
{
    return player_actor_ops_start_state((u32) made_with);
}
CLEAN_AS(func_02096180, PlayerActorOps_StartState)

/* func_02096188: the session player a field actor was made for, from its argument (bits 30 and
 * 31). */
int PlayerActorOps_Player(int made_with)
{
    return (int) (((u32) made_with >> 30) & 3);
}
CLEAN_AS(func_02096188, PlayerActorOps_Player)
