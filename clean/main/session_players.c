/* The players of the multiplayer session (session_players.h). */
#include "session_players.h"

#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "ov003/field_actor.h"
#include "packed_bytes.h"
#include "scene_query.h"
#include "session.h"
#include "session_record.h"

static_assert(offsetof(SessionPlayers, record_number) == 0x10, "session players");
static_assert(offsetof(SessionPlayers, look_index) == 0x14, "session players");
static_assert(offsetof(SessionPlayers, sun_date) == 0x18, "session players");
static_assert(offsetof(SessionPlayers, sun_countdown) == 0x1a, "session players");
static_assert(offsetof(SessionPlayers, sun_flags) == 0x1c, "session players");
static_assert(offsetof(SessionPlayers, saved_state) == 0x20, "session players");
static_assert(offsetof(SessionPlayers, saved_scene) == 0x30, "session players");
static_assert(offsetof(SessionPlayers, saved_position) == 0x34, "session players");
static_assert(offsetof(SessionPlayers, saved_yaw) == 0x64, "session players");
static_assert(sizeof(SessionPlayersStateRecord) == 12, "state record");

extern SessionPlayers data_021d5684[];
extern NetSession *data_020ccf94;
/* The shared record of each player's point (0-3), yaw (4-7) and state (8-11). */
extern const int data_020d1864[];
extern const int data_020d1874[];
extern const int data_020d1884[];

/* The constructor and destructor of a point, handed to __cxa_vec_ctor and __cxa_vec_cleanup:
 * the game's own (they do nothing). */
extern void func_020012e8(void *point);
extern void func_020012dc(void *point);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The sun date a new table starts with: year 0, month 1, day 1. */
#define SESSION_PLAYERS_FIRST_DATE (1u << 7 | 1u << 11)

/* The bits of the byte func_02096440 splits and func_0209645c joins. */
#define SESSION_PLAYERS_LOW_MASK 0x0f
#define SESSION_PLAYERS_HIGH_SHIFT 4
#define SESSION_PLAYERS_HIGH_MASK 0x07

static SessionPlayers *session_players(void)
{
    return data_021d5684;
}

/* func_02096190: player `player`'s field actor (4: this system's) as an integer handle; 0 for
 * none. */
int SessionPlayers_ActorHandle(int player)
{
    return SessionPlayers_HandleOf((int) (uintptr_t) SessionPlayers_FieldActor(player));
}
CLEAN_AS(func_02096190, SessionPlayers_ActorHandle)

/* func_020961a4: a field actor as its handle: the same value. */
int SessionPlayers_HandleOf(int object)
{
    return object;
}
CLEAN_AS(func_020961a4, SessionPlayers_HandleOf)

/* func_020961a8: player `player`'s field actor (4: this system's) as the actor it is; NULL for
 * none. */
void *SessionPlayers_ActorOf(int player)
{
    return SessionPlayers_AsActor(SessionPlayers_FieldActor(player));
}
CLEAN_AS(func_020961a8, SessionPlayers_ActorOf)

/* func_020961bc: a field actor as the actor it is: the same address. */
void *SessionPlayers_AsActor(void *object)
{
    return object;
}
CLEAN_AS(func_020961bc, SessionPlayers_AsActor)

/* func_020961c0: the lowest index of looks no player holds; 4 when all are held. */
int SessionPlayers_FreeLookIndex(void)
{
    return SessionPlayers_FirstFreeLook(session_players());
}
CLEAN_AS(func_020961c0, SessionPlayers_FreeLookIndex)

/* func_020961d0: player `player`'s index of looks. */
int SessionPlayers_LookIndex(int player)
{
    return SessionPlayers_GetLook(session_players(), player);
}
CLEAN_AS(func_020961d0, SessionPlayers_LookIndex)

/* func_020961e0: player `player`'s index of looks given up. */
void SessionPlayers_ClearLookIndex(int player)
{
    SessionPlayers_ResetLook(session_players(), player);
}
CLEAN_AS(func_020961e0, SessionPlayers_ClearLookIndex)

/* func_020961f0: player `player`'s index of looks set. */
void SessionPlayers_SetLookIndex(int player, int index)
{
    SessionPlayers_PutLook(session_players(), player, index);
}
CLEAN_AS(func_020961f0, SessionPlayers_SetLookIndex)

/* func_02096204: what was reported of player `player` forgotten: no state, no scene, the
 * position and yaw 0. */
void SessionPlayers_ClearSaved(int player)
{
    *SessionPlayers_SavedState(player) = SESSION_PLAYERS_NO_STATE;
    *SessionPlayers_SavedScene(player) = SESSION_PLAYERS_NO_SCENE;
    Vec3 *position = SessionPlayers_SavedPosition(player);
    position->x = 0;
    position->y = 0;
    position->z = 0;
    *SessionPlayers_SavedYaw(player) = 0;
}
CLEAN_AS(func_02096204, SessionPlayers_ClearSaved)

/* func_02096238: player `player`'s last reported yaw.
 * REQUIRES: 0 <= player (the ROM indexes the array with any value; so do the five below). */
s16 *SessionPlayers_SavedYaw(int player)
{
    return &session_players()->saved_yaw[player];
}
CLEAN_AS(func_02096238, SessionPlayers_SavedYaw)

/* func_02096244: player `player`'s last reported position. */
Vec3 *SessionPlayers_SavedPosition(int player)
{
    return &session_players()->saved_position[player];
}
CLEAN_AS(func_02096244, SessionPlayers_SavedPosition)

/* func_02096254: player `player`'s last reported scene. */
u8 *SessionPlayers_SavedScene(int player)
{
    return &session_players()->saved_scene[player];
}
CLEAN_AS(func_02096254, SessionPlayers_SavedScene)

/* func_02096260: player `player`'s last reported state. */
int *SessionPlayers_SavedState(int player)
{
    return &session_players()->saved_state[player];
}
CLEAN_AS(func_02096260, SessionPlayers_SavedState)

/* func_0209626c: the sun level's flags. */
u8 *SessionPlayers_SunFlags(void)
{
    return &session_players()->sun_flags;
}
CLEAN_AS(func_0209626c, SessionPlayers_SunFlags)

/* func_02096274: the sun level's countdown. */
u16 *SessionPlayers_SunCountdown(void)
{
    return &session_players()->sun_countdown;
}
CLEAN_AS(func_02096274, SessionPlayers_SunCountdown)

/* func_0209627c: the date the sun level was last stored, packed. */
u16 *SessionPlayers_SunDate(void)
{
    return &session_players()->sun_date;
}
CLEAN_AS(func_0209627c, SessionPlayers_SunDate)

/* func_02096284: the number of player `player`'s record; 7 for none. */
u8 SessionPlayers_RecordNumber(int player)
{
    return SessionPlayers_GetRecord(session_players(), player);
}
CLEAN_AS(func_02096284, SessionPlayers_RecordNumber)

/* func_02096294: player `player` given no record. */
void SessionPlayers_ClearRecordNumber(int player)
{
    SessionPlayers_ResetRecord(session_players(), player);
}
CLEAN_AS(func_02096294, SessionPlayers_ClearRecordNumber)

/* func_020962a4: player `player` given record `number`. */
void SessionPlayers_SetRecordNumber(int player, int number)
{
    SessionPlayers_PutRecord(session_players(), player, number);
}
CLEAN_AS(func_020962a4, SessionPlayers_SetRecordNumber)

/* func_020962b8: player `player`'s field actor gone. */
void SessionPlayers_ClearActor(int player)
{
    SessionPlayers_ResetActor(session_players(), player);
}
CLEAN_AS(func_020962b8, SessionPlayers_ClearActor)

/* func_020962c8: player `player`'s field actor noted. */
void SessionPlayers_SetActor(int player, struct FieldActor *actor)
{
    SessionPlayers_PutActor(session_players(), player, actor);
}
CLEAN_AS(func_020962c8, SessionPlayers_SetActor)

/* func_020962dc: the destructor: the positions' (which do nothing). */
SessionPlayers *SessionPlayers_Destruct(SessionPlayers *players)
{
    __cxa_vec_cleanup(players->saved_position, SESSION_PLAYERS_COUNT, sizeof(Vec3),
                      (void (*)(void *))(uintptr_t) func_020012dc);
    return players;
}
CLEAN_AS(func_020962dc, SessionPlayers_Destruct)

/* func_020962f8: the constructor: the positions constructed, every player without a record, an
 * index of looks or a reported place, and the sun level's date the first of the year 0 with
 * its countdown and flags 0.
 * QUIRK: the record numbers and indexes of looks cleared are those of the table at
 * data_021d5684, whichever table is constructed (the game constructs only that one). */
SessionPlayers *SessionPlayers_Construct(SessionPlayers *players)
{
    __cxa_vec_ctor(players->saved_position, SESSION_PLAYERS_COUNT, sizeof(Vec3), (void (*)(void *))(uintptr_t) func_020012e8,
                   (void (*)(void *))(uintptr_t) func_020012dc);
    for (unsigned int player = 0; player < SESSION_PLAYERS_COUNT; player++) {
        SessionPlayers_ResetRecord(session_players(), (int) player);
        SessionPlayers_ResetLook(session_players(), (int) player);
        players->saved_state[player] = SESSION_PLAYERS_NO_STATE;
        players->saved_scene[player] = SESSION_PLAYERS_NO_SCENE;
        players->saved_position[player].x = 0;
        players->saved_position[player].y = 0;
        players->saved_position[player].z = 0;
        players->saved_yaw[player] = 0;
    }
    players->sun_date = SESSION_PLAYERS_FIRST_DATE;
    players->sun_countdown = 0;
    players->sun_flags = 0;
    return players;
}
CLEAN_AS(func_020962f8, SessionPlayers_Construct)

/* func_02096398: the lowest index of looks (0-3) no player of `players` holds; 4 when all are
 * held. */
int SessionPlayers_FirstFreeLook(SessionPlayers *players)
{
    for (unsigned int index = 0; index < SESSION_PLAYERS_COUNT; index++) {
        int held = 0;
        for (int player = 0; player < SESSION_PLAYERS_COUNT; player++) {
            if (index == (unsigned int) SessionPlayers_GetLook(players, player)) {
                held = 1;
                break;
            }
        }
        if (!held) {
            return (int) index;
        }
    }
    return SESSION_PLAYERS_NO_LOOK;
}
CLEAN_AS(func_02096398, SessionPlayers_FirstFreeLook)

/* func_020963d4: player `player`'s index of looks; 4 past player 3.
 * REQUIRES: 0 <= player (the ROM reads before the array for a negative one; so do the
 * functions below for theirs). */
int SessionPlayers_GetLook(SessionPlayers *players, int player)
{
    if (player < SESSION_PLAYERS_COUNT) {
        return players->look_index[player];
    }
    return SESSION_PLAYERS_NO_LOOK;
}
CLEAN_AS(func_020963d4, SessionPlayers_GetLook)

/* func_020963e4: player `player`'s index of looks given up. */
void SessionPlayers_ResetLook(SessionPlayers *players, int player)
{
    SessionPlayers_PutLook(players, player, SESSION_PLAYERS_NO_LOOK);
}
CLEAN_AS(func_020963e4, SessionPlayers_ResetLook)

/* func_020963f0: player `player`'s index of looks set (its low 8 bits).
 * REQUIRES: player < 4, as for the two setters below (not checked). */
void SessionPlayers_PutLook(SessionPlayers *players, int player, int index)
{
    players->look_index[player] = (u8) index;
}
CLEAN_AS(func_020963f0, SessionPlayers_PutLook)

/* func_020963f8: the number of player `player`'s record; 7 past player 3. */
u8 SessionPlayers_GetRecord(SessionPlayers *players, int player)
{
    if (player < SESSION_PLAYERS_COUNT) {
        return players->record_number[player];
    }
    return SESSION_PLAYERS_NO_RECORD;
}
CLEAN_AS(func_020963f8, SessionPlayers_GetRecord)

/* func_02096408: player `player` given no record. */
void SessionPlayers_ResetRecord(SessionPlayers *players, int player)
{
    SessionPlayers_PutRecord(players, player, SESSION_PLAYERS_NO_RECORD);
}
CLEAN_AS(func_02096408, SessionPlayers_ResetRecord)

/* func_02096414: player `player` given record `number` (its low 8 bits). */
void SessionPlayers_PutRecord(SessionPlayers *players, int player, int number)
{
    players->record_number[player] = (u8) number;
}
CLEAN_AS(func_02096414, SessionPlayers_PutRecord)

/* func_0209641c: player `player`'s field actor; NULL past player 3. */
struct FieldActor *SessionPlayers_GetActor(SessionPlayers *players, int player)
{
    if (player < SESSION_PLAYERS_COUNT) {
        return players->actors[player];
    }
    return NULL;
}
CLEAN_AS(func_0209641c, SessionPlayers_GetActor)

/* func_0209642c: player `player`'s field actor gone. */
void SessionPlayers_ResetActor(SessionPlayers *players, int player)
{
    SessionPlayers_PutActor(players, player, NULL);
}
CLEAN_AS(func_0209642c, SessionPlayers_ResetActor)

/* func_02096438: player `player`'s field actor noted. */
void SessionPlayers_PutActor(SessionPlayers *players, int player, struct FieldActor *actor)
{
    players->actors[player] = actor;
}
CLEAN_AS(func_02096438, SessionPlayers_PutActor)

/* func_02096440: a message's byte split into its bits 0-3 and 4-6. */
void SessionPlayers_SplitLowHigh(const u8 *byte, u8 *low, u8 *high)
{
    *low = *byte & SESSION_PLAYERS_LOW_MASK;
    *high = (u8) ((*byte >> SESSION_PLAYERS_HIGH_SHIFT) & SESSION_PLAYERS_HIGH_MASK);
}
CLEAN_AS(func_02096440, SessionPlayers_SplitLowHigh)

/* func_0209645c: a message's byte from `low` (bits 0-3) and `high` (bits 4-6). */
void SessionPlayers_JoinLowHigh(u8 *byte, unsigned int low, unsigned int high)
{
    *byte = (u8) (((high << SESSION_PLAYERS_HIGH_SHIFT) & (SESSION_PLAYERS_HIGH_MASK << SESSION_PLAYERS_HIGH_SHIFT)) |
                  (low & SESSION_PLAYERS_LOW_MASK));
}
CLEAN_AS(func_0209645c, SessionPlayers_JoinLowHigh)

/* func_0209646c: a message's item (bytes 0-1) and operation (byte 2). */
void SessionPlayers_ReadItemOperation(const u8 *payload, u16 *item, int *operation)
{
    *item = PackedBytes_ReadItem(payload);
    *operation = payload[2];
}
CLEAN_AS(func_0209646c, SessionPlayers_ReadItemOperation)

/* func_02096484: a message's item (bytes 0-1) and kind (byte 2). */
void SessionPlayers_WriteItemKind(u8 *payload, int item, u8 kind)
{
    PackedBytes_WriteItem(payload, item);
    payload[2] = kind;
}
CLEAN_AS(func_02096484, SessionPlayers_WriteItemKind)

/* func_0209649c: the writer of the state records (8-11): from this system's field actor, the
 * current scene, its state plus 1, its halfword at 0xc84 and the 8 bytes it saved for its
 * state; without the actor, the state byte 0x94 (no state). SessionRecord_GetSize(id) bytes are
 * copied into `record`.
 * BUG: without the actor only the state byte is set, and the rest of the record is copied from
 * uninitialised stack bytes; the state byte is left so too when the actor's state is not found
 * (which does not happen for this system's player). */
void SessionPlayers_WriteStateRecord(u8 *record, int id)
{
    int state;
    SessionPlayersStateRecord built;
#ifdef BUGFIX
    memset(&built, 0, sizeof(built));
#endif
    FieldActor *actor = SessionPlayers_FieldActor(SESSION_PLAYERS_OWN);
    if (actor != NULL) {
        PackedBytes_JoinScene(&built.scene, SceneQuery_Current(), 0);
        if (SessionPlayers_State(&state, -1, SESSION_PLAYERS_OWN)) {
            built.state = (u8) (state + 1);
        }
        PackedBytesHalf value = {.value = (u32) (s32) actor->unk_C84};
        PackedBytes_WriteHalf(built.value, value);
        MI_CpuCopy8(&actor->saved, built.saved, sizeof(built.saved));
    } else {
        built.state = SESSION_PLAYERS_NO_STATE + 1;
    }
    MI_CpuCopy8(&built, record, SessionRecord_GetSize((u32) id));
}
CLEAN_AS(func_0209649c, SessionPlayers_WriteStateRecord)

/* Player `player`, or this system's for 4. */
static int session_players_number(int player)
{
    if (player == SESSION_PLAYERS_OWN) {
        return data_020ccf94->local_player;
    }
    return player;
}

/* func_02096518: player `player`'s state into `state`, from its field actor for this system's
 * player and from its state record otherwise; 0, writing nothing, without the actor or a
 * reported state. */
int SessionPlayers_State(int *state, int unused, int player)
{
    (void) unused;
    player = session_players_number(player);
    if (Session_IsLocalPlayer(data_020ccf94, player)) {
        FieldActor *actor = SessionPlayers_FieldActor(SESSION_PLAYERS_OWN);
        if (actor == NULL) {
            return 0;
        }
        *state = actor->state;
        return 1;
    }
    u8 *record = SessionPlayers_StateRecord(player);
    if (record == NULL) {
        return 0;
    }
    u8 reported;
    MI_CpuCopy8(&record[offsetof(SessionPlayersStateRecord, state)], &reported, 1);
    if (reported == 0) {
        return 0;
    }
    *state = reported - 1;
    return 1;
}
CLEAN_AS(func_02096518, SessionPlayers_State)

/* func_0209658c: player `player`'s yaw into `yaw`, from its field actor for this system's
 * player and from its yaw record otherwise (only while its state record has a state below
 * 0x93); 0, writing nothing, when there is none. */
int SessionPlayers_Yaw(s16 *yaw, int unused, int player)
{
    player = session_players_number(player);
    if (Session_IsLocalPlayer(data_020ccf94, player)) {
        FieldActor *actor = SessionPlayers_FieldActor(SESSION_PLAYERS_OWN);
        if (actor == NULL) {
            return 0;
        }
        *yaw = actor->yaw;
        return 1;
    }
    int state;
    if (SessionPlayers_StateRecord(player) == NULL) {
        return 0;
    }
    if (!SessionPlayers_State(&state, unused, player)) {
        return 0;
    }
    if (state >= SESSION_PLAYERS_NO_STATE) {
        return 0;
    }
    u8 *record = SessionPlayers_YawRecord(player);
    if (record == NULL) {
        return 0;
    }
    *yaw = PackedBytes_ReadS16(record);
    return 1;
}
CLEAN_AS(func_0209658c, SessionPlayers_Yaw)

/* func_02096614: player `player`'s scene and the x and z of its position, from its field actor
 * (and the current scene) for this system's player and from its point and state records
 * otherwise (only while the state record has a state below 0x93); 0, writing nothing, when
 * there is none. */
int SessionPlayers_ScenePoint(u8 *scene, int *x, int *z, int unused, int player)
{
    player = session_players_number(player);
    if (Session_IsLocalPlayer(data_020ccf94, player)) {
        FieldActor *actor = SessionPlayers_FieldActor(SESSION_PLAYERS_OWN);
        if (actor == NULL) {
            return 0;
        }
        *scene = SceneQuery_Current();
        *x = actor->position.x;
        *z = actor->position.z;
        return 1;
    }
    u8 *state_record = SessionPlayers_StateRecord(player);
    if (state_record == NULL) {
        return 0;
    }
    int state;
    if (!SessionPlayers_State(&state, unused, player)) {
        return 0;
    }
    if (state >= SESSION_PLAYERS_NO_STATE) {
        return 0;
    }
    u8 *point_record = SessionPlayers_PointRecord(player);
    if (point_record == NULL) {
        return 0;
    }
    u32 point_x;
    u32 point_z;
    PackedBytes_UnpackPoint(point_record, &point_x, &point_z);
    *x = (int) point_x;
    *z = (int) point_z;
    PackedBytes_SplitScene(state_record, scene, NULL);
    return 1;
}
CLEAN_AS(func_02096614, SessionPlayers_ScenePoint)

/* func_020966c4: player `player`'s state record. */
u8 *SessionPlayers_StateRecord(int player)
{
    return Session_GetRecord(data_020ccf94, data_020d1884[player]);
}
CLEAN_AS(func_020966c4, SessionPlayers_StateRecord)

/* func_020966e0: player `player`'s yaw record. */
u8 *SessionPlayers_YawRecord(int player)
{
    return Session_GetRecord(data_020ccf94, data_020d1874[player]);
}
CLEAN_AS(func_020966e0, SessionPlayers_YawRecord)

/* func_020966fc: player `player`'s point record. */
u8 *SessionPlayers_PointRecord(int player)
{
    return Session_GetRecord(data_020ccf94, data_020d1864[player]);
}
CLEAN_AS(func_020966fc, SessionPlayers_PointRecord)

/* func_02096718: player `player`'s field actor (4: this system's player); NULL for none. */
struct FieldActor *SessionPlayers_FieldActor(int player)
{
    return SessionPlayers_GetActor(session_players(), session_players_number(player));
}
CLEAN_AS(func_02096718, SessionPlayers_FieldActor)
