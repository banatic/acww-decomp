/* The players of the multiplayer session as this system knows them: the table at data_021d5684
 * (static_init.c constructs it) holds, by player number (0-3):
 *
 *   the player's field actor (set by the actor when it is made, cleared when it goes);
 *   the number of the player record it plays with (player_records.h; 7 for none);
 *   the index into the field actor's tables of looks by player (0-3; 4 for none), each player
 *   given the lowest index no other player holds;
 *   where the player was last reported: its state (0x93 for none), its scene (0x33 for none),
 *   its position and its yaw, from which the actor of another system's player is made again
 *   (player_processes.h);
 *
 * and, once, the sun level's flags, countdown and date of the player at this system
 * (field_actor_looks.c).
 *
 * The questions about a player's state, scene, point and yaw are answered from its field actor
 * for the player at this system and from the shared records (session_record.h) the others send:
 * records 0-3 (the point), 4-7 (the yaw) and 8-11 (built by SessionPlayers_WriteStateRecord) by
 * player. Player 4 stands for the player at this system throughout. */
#ifndef CLEAN_MAIN_SESSION_PLAYERS_H
#define CLEAN_MAIN_SESSION_PLAYERS_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;

#define SESSION_PLAYERS_COUNT 4
#define SESSION_PLAYERS_OWN 4         /* the player at this system */
#define SESSION_PLAYERS_NO_RECORD 7   /* no player record */
#define SESSION_PLAYERS_NO_LOOK 4     /* no index of looks */
#define SESSION_PLAYERS_NO_STATE 0x93 /* no state reported */
#define SESSION_PLAYERS_NO_SCENE 0x33 /* no scene reported */

typedef struct SessionPlayers {
    struct FieldActor *actors[SESSION_PLAYERS_COUNT]; /* 0x00 */
    u8 record_number[SESSION_PLAYERS_COUNT];          /* 0x10 */
    u8 look_index[SESSION_PLAYERS_COUNT];             /* 0x14 */
    u16 sun_date;                                     /* 0x18: year (7 bits), month (4) and day (5) */
    u16 sun_countdown;                                /* 0x1a */
    u8 sun_flags;                                     /* 0x1c */
    u8 unk_1D[3];
    int saved_state[SESSION_PLAYERS_COUNT];     /* 0x20 */
    u8 saved_scene[SESSION_PLAYERS_COUNT];      /* 0x30 */
    Vec3 saved_position[SESSION_PLAYERS_COUNT]; /* 0x34 */
    s16 saved_yaw[SESSION_PLAYERS_COUNT];       /* 0x64 */
} SessionPlayers;

/* The record of state a player sends (records 8-11, 12 bytes). */
typedef struct SessionPlayersStateRecord {
    u8 scene;    /* the scene (PackedBytes_JoinScene, number 0) */
    u8 state;    /* the field actor's state plus 1; 0 for none */
    u8 value[2]; /* the actor's halfword at 0xc84 (PackedBytes_WriteHalf) */
    u8 saved[8]; /* the actor's saved arguments of its state (0x8f0) */
} SessionPlayersStateRecord;

int SessionPlayers_ActorHandle(int player);
int SessionPlayers_HandleOf(int object);
void *SessionPlayers_ActorOf(int player);
void *SessionPlayers_AsActor(void *object);
int SessionPlayers_FreeLookIndex(void);
int SessionPlayers_LookIndex(int player);
void SessionPlayers_ClearLookIndex(int player);
void SessionPlayers_SetLookIndex(int player, int index);
void SessionPlayers_ClearSaved(int player);
s16 *SessionPlayers_SavedYaw(int player);
Vec3 *SessionPlayers_SavedPosition(int player);
u8 *SessionPlayers_SavedScene(int player);
int *SessionPlayers_SavedState(int player);
u8 *SessionPlayers_SunFlags(void);
u16 *SessionPlayers_SunCountdown(void);
u16 *SessionPlayers_SunDate(void);
u8 SessionPlayers_RecordNumber(int player);
void SessionPlayers_ClearRecordNumber(int player);
void SessionPlayers_SetRecordNumber(int player, int number);
void SessionPlayers_ClearActor(int player);
void SessionPlayers_SetActor(int player, struct FieldActor *actor);
SessionPlayers *SessionPlayers_Destruct(SessionPlayers *players);
SessionPlayers *SessionPlayers_Construct(SessionPlayers *players);

int SessionPlayers_FirstFreeLook(SessionPlayers *players);
int SessionPlayers_GetLook(SessionPlayers *players, int player);
void SessionPlayers_ResetLook(SessionPlayers *players, int player);
void SessionPlayers_PutLook(SessionPlayers *players, int player, int index);
u8 SessionPlayers_GetRecord(SessionPlayers *players, int player);
void SessionPlayers_ResetRecord(SessionPlayers *players, int player);
void SessionPlayers_PutRecord(SessionPlayers *players, int player, int number);
struct FieldActor *SessionPlayers_GetActor(SessionPlayers *players, int player);
void SessionPlayers_ResetActor(SessionPlayers *players, int player);
void SessionPlayers_PutActor(SessionPlayers *players, int player, struct FieldActor *actor);

void SessionPlayers_SplitLowHigh(const u8 *byte, u8 *low, u8 *high);
void SessionPlayers_JoinLowHigh(u8 *byte, unsigned int low, unsigned int high);
void SessionPlayers_ReadItemOperation(const u8 *payload, u16 *item, int *operation);
void SessionPlayers_WriteItemKind(u8 *payload, int item, u8 kind);

void SessionPlayers_WriteStateRecord(u8 *record, int id);
int SessionPlayers_State(int *state, int unused, int player);
int SessionPlayers_Yaw(s16 *yaw, int unused, int player);
int SessionPlayers_ScenePoint(u8 *scene, int *x, int *z, int unused, int player);
u8 *SessionPlayers_StateRecord(int player);
u8 *SessionPlayers_YawRecord(int player);
u8 *SessionPlayers_PointRecord(int player);
struct FieldActor *SessionPlayers_FieldActor(int player);

#endif
