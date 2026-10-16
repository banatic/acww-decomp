/* Two processes that keep the other players' field actors in step (player_processes.h). */
#include "player_processes.h"

#include "activity_vars.h"
#include "actor.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "collision_query.h"
#include "link_global.h"
#include "player_actor_ops.h"
#include "player_actors.h"
#include "scene_query.h"
#include "session.h"
#include "session_players.h"
#include "session_record.h"

static_assert(sizeof(Process) == 0x50, "player processes");

extern const u32 data_020e2f90[]; /* the spawning process's vtable */
extern const u32 data_020e2fe8[]; /* the reporting process's vtable */
extern const u32 data_020da13c[]; /* the scene objects' base class's */

extern NetSession *data_020ccf94;

/* The scenes of the link activities: in 0xd, 0x2f and 0xe the served player's actor is made at
 * a fixed place; in 0x2e nothing is made; in none of them, nor in 0xc, is a report kept. */
#define PLAYER_PROCESSES_SCENE_0C 0x0c
#define PLAYER_PROCESSES_SCENE_0D 0x0d
#define PLAYER_PROCESSES_SCENE_0E 0x0e
#define PLAYER_PROCESSES_SCENE_2E 0x2e
#define PLAYER_PROCESSES_SCENE_2F 0x2f

/* The class of the object whose presence lets the served player's actor be made. */
#define PLAYER_PROCESSES_PROFILE_72 0x72

/* The served player's place: x, z in scenes 0xd and 0x2f, z in scene 0xe, and the yaw there. */
#define PLAYER_PROCESSES_SERVED_X 0x10000
#define PLAYER_PROCESSES_SERVED_Z_0D 0x5000
#define PLAYER_PROCESSES_SERVED_Z_0E 0x11800
#define PLAYER_PROCESSES_SERVED_YAW_0E (-0x8000)

/* A field actor's argument holds the state it starts in at bits 22-29 (PlayerActorOps_StartState). */
#define PLAYER_PROCESSES_START_STATE(state) (((u32) (state) << 22) & 0x3fc00000u)
#define PLAYER_PROCESSES_STATE_REPORTED 2 /* an actor made where its player reports it */
#define PLAYER_PROCESSES_STATE_SERVED 0x10

/* The flag of this system's actor (FieldActor.flags) that lets actors be made from the last
 * reports, and keeps those of players gone from the scene. */
#define PLAYER_PROCESSES_FLAG_KEEP 0x1b

/* What is passed as the unused argument of the questions of session_players.h. */
#define PLAYER_PROCESSES_ANY (-1)

/* func_02096738 (vtable slot 3): nothing to take down; done at once. */
int PlayerSpawnProcess_Delete(void)
{
    return 1;
}
CLEAN_AS(func_02096738, PlayerSpawnProcess_Delete)

/* func_0209673c (vtable slot 9): nothing to draw. */
int PlayerSpawnProcess_Draw(void)
{
    return 1;
}
CLEAN_AS(func_0209673c, PlayerSpawnProcess_Draw)

static int player_processes_served_scene(void)
{
    return SceneQuery_Current() == PLAYER_PROCESSES_SCENE_0D || SceneQuery_Current() == PLAYER_PROCESSES_SCENE_2F;
}

/* In scenes 0xd, 0x2f and 0xe: unless the activity's flag 0x3c08 is set, while an object of
 * class 0x72 exists and is not being deleted, the actor of the player the activity serves
 * (its slot 0x3c1c in scenes 0xd and 0x2f, the link's served slot in 0xe) is made if it has
 * none, on the floor at a fixed place, starting in state 0x10. */
static void player_processes_spawn_served(void)
{
    if (ActivityVars_Flag3C08() != 0) {
        return;
    }
    Process *object = Actor_FindNextOfProfile(PLAYER_PROCESSES_PROFILE_72, NULL);
    if (object == NULL) {
        return;
    }
    if (object->state == STATE_DELETING) {
        return;
    }
    int player;
    if (player_processes_served_scene()) {
        player = ActivityVars_Slot3C1C();
    } else {
        player = (int) LinkGlobal_ServedSlot();
    }
    if (player >= SESSION_PLAYERS_COUNT) {
        return;
    }
    if (SessionPlayers_ActorOf(player) != NULL) {
        return;
    }
    Vec3 position;
    s16 angle[3] = {0, 0, 0};
    fx32 floor = CollisionQuery_FloorHeight(0);
    position.x = PLAYER_PROCESSES_SERVED_X;
    position.y = floor;
    if (player_processes_served_scene()) {
        position.z = PLAYER_PROCESSES_SERVED_Z_0D;
    } else {
        position.z = PLAYER_PROCESSES_SERVED_Z_0E;
        angle[1] = PLAYER_PROCESSES_SERVED_YAW_0E;
    }
    SessionPlayers_SetLookIndex(player, SessionPlayers_FreeLookIndex());
    PlayerActors_Spawn((unsigned int) player, &position, angle, PLAYER_PROCESSES_START_STATE(PLAYER_PROCESSES_STATE_SERVED));
}

/* Player `player`'s actor made where the player reports it, in state 2, when it reports a
 * state in the current scene; whether it was made. */
static int player_processes_spawn_reported(int player)
{
    int state;
    u8 scene;
    int x;
    int z;
    s16 yaw;
    if (!SessionPlayers_State(&state, PLAYER_PROCESSES_ANY, player) || state >= SESSION_PLAYERS_NO_STATE) {
        return 0;
    }
    if (!SessionPlayers_ScenePoint(&scene, &x, &z, PLAYER_PROCESSES_ANY, player)) {
        return 0;
    }
    if (SceneQuery_Current() != scene) {
        return 0;
    }
    if (!SessionPlayers_Yaw(&yaw, PLAYER_PROCESSES_ANY, player)) {
        return 0;
    }
    Vec3 position = {.x = x, .y = CollisionQuery_FloorHeight(0), .z = z};
    s16 angle[3] = {0, yaw, 0};
    SessionPlayers_SetLookIndex(player, SessionPlayers_FreeLookIndex());
    PlayerActors_Spawn((unsigned int) player, &position, angle, PLAYER_PROCESSES_START_STATE(PLAYER_PROCESSES_STATE_REPORTED));
    return 1;
}

/* Player `player`'s actor made at its last reported place in its last reported state, when
 * that was in the current scene. */
static void player_processes_spawn_saved(int player)
{
    u8 *scene = SessionPlayers_SavedScene(player);
    int *state = SessionPlayers_SavedState(player);
    if (*scene != SceneQuery_Current()) {
        return;
    }
    if (*state == SESSION_PLAYERS_NO_STATE) {
        return;
    }
    Vec3 position = *SessionPlayers_SavedPosition(player);
    s16 angle[3] = {0, SessionPlayers_SavedYaw(player)[0], 0};
    SessionPlayers_SetLookIndex(player, SessionPlayers_FreeLookIndex());
    PlayerActors_Spawn((unsigned int) player, &position, angle, PLAYER_PROCESSES_START_STATE(*state));
}

/* Whether player `player` reports a state in the current scene. */
static int player_processes_reported_here(int player)
{
    int state;
    u8 scene;
    int x;
    int z;
    if (!SessionPlayers_State(&state, PLAYER_PROCESSES_ANY, player)) {
        return 0;
    }
    if (state >= SESSION_PLAYERS_NO_STATE) {
        return 0;
    }
    if (!SessionPlayers_ScenePoint(&scene, &x, &z, PLAYER_PROCESSES_ANY, player)) {
        return 0;
    }
    return SceneQuery_Current() == scene;
}

/* func_02096740 (vtable slot 6): the other players' actors made and deleted (see the header);
 * done each frame.
 * QUIRK: the current scene is asked for again for each comparison, as the ROM's code does. */
int PlayerSpawnProcess_Execute(void)
{
    NetSession *session = data_020ccf94;
    int own_slot = session->local_slot;

    if (SceneQuery_Current() == PLAYER_PROCESSES_SCENE_2E) {
        return 1;
    }
    if (SceneQuery_Current() == PLAYER_PROCESSES_SCENE_0D || SceneQuery_Current() == PLAYER_PROCESSES_SCENE_2F ||
        SceneQuery_Current() == PLAYER_PROCESSES_SCENE_0E) {
        player_processes_spawn_served();
        return 1;
    }

    if (Session_IsSlotTaken(session, own_slot) == 0) {
        return 1;
    }
    if (SessionPlayers_ActorOf(SESSION_PLAYERS_OWN) == NULL) {
        return 1;
    }
    int own = PlayerActors_OwnPlayer();

    for (int player = 0; player < SESSION_PLAYERS_COUNT; player++) {
        if (Session_IsLocalPlayer(session, player)) {
            continue;
        }
        if (Session_IsSlotTaken(session, player) == 0) {
            continue;
        }
        if (SessionPlayers_ActorOf(player) != NULL) {
            continue;
        }
        if (player_processes_spawn_reported(player)) {
            continue;
        }
        if (PlayerActorOps_TestFlag(PLAYER_PROCESSES_FLAG_KEEP, own) == 0) {
            continue;
        }
        player_processes_spawn_saved(player);
    }

    for (int player = 0; player < SESSION_PLAYERS_COUNT; player++) {
        if (Session_IsLocalPlayer(session, player)) {
            continue;
        }
        if (PlayerActorOps_TestFlag(PLAYER_PROCESSES_FLAG_KEEP, own) != 0) {
            continue;
        }
        Process *actor = SessionPlayers_ActorOf(player);
        if (actor == NULL) {
            continue;
        }
        if (actor->state == STATE_DELETING) {
            continue;
        }
        if (!player_processes_reported_here(player)) {
            Process_RequestDelete(actor);
        }
    }
    return 1;
}
CLEAN_AS(func_02096740, PlayerSpawnProcess_Execute)

/* func_02096a44 (vtable slot 0): nothing to set up; done at once. */
int PlayerSpawnProcess_Create(void)
{
    return 1;
}
CLEAN_AS(func_02096a44, PlayerSpawnProcess_Create)

/* func_02096a48 (vtable slot 17): the destructor, and the object freed to the heap processes
 * come from. */
Process *PlayerSpawnProcess_DestructFree(Process *self)
{
    self->vtable = data_020e2f90;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02096a48, PlayerSpawnProcess_DestructFree)

/* func_02096a70 (vtable slot 16): the destructor: the bases' vtables put back in turn. */
Process *PlayerSpawnProcess_Destruct(Process *self)
{
    self->vtable = data_020e2f90;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_02096a70, PlayerSpawnProcess_Destruct)

/* func_02096a90: the constructor: the base process's, then the vtables in turn. */
Process *PlayerSpawnProcess_Construct(Process *self)
{
    Process_Construct(self);
    self->vtable = data_020da13c;
    self->vtable = data_020e2f90;
    return self;
}
CLEAN_AS(func_02096a90, PlayerSpawnProcess_Construct)

/* func_02096ab0: the profile's create: the process allocated zeroed and constructed.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void PlayerSpawnProcess_Spawn(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));
    if (self != NULL) {
        PlayerSpawnProcess_Construct(self);
    }
}
CLEAN_AS(func_02096ab0, PlayerSpawnProcess_Spawn)

/* func_02096ac8 (vtable slot 3): nothing to take down; done at once. */
int PlayerReportProcess_Delete(void)
{
    return 1;
}
CLEAN_AS(func_02096ac8, PlayerReportProcess_Delete)

/* func_02096acc (vtable slot 9): nothing to draw. */
int PlayerReportProcess_Draw(void)
{
    return 1;
}
CLEAN_AS(func_02096acc, PlayerReportProcess_Draw)

/* What player `slot` reports kept as its last place, unless its place is in one of the link
 * activities' scenes or it reports no state, scene and point or yaw; an item the player's
 * state 0x75 cleared is taken away first (PlayerActors_ClearItemOnState75). */
static void player_processes_keep_report(int slot)
{
    int player = slot;
    u8 scene = (u8) LinkGlobal_PlaceScene(slot);
    int *saved_state = SessionPlayers_SavedState(player);
    u8 *saved_scene = SessionPlayers_SavedScene(player);
    Vec3 *saved_position = SessionPlayers_SavedPosition(player);
    s16 *saved_yaw = SessionPlayers_SavedYaw(player);
    if (scene == PLAYER_PROCESSES_SCENE_0C || scene == PLAYER_PROCESSES_SCENE_0D || scene == PLAYER_PROCESSES_SCENE_0E ||
        scene == PLAYER_PROCESSES_SCENE_2F || scene == PLAYER_PROCESSES_SCENE_2E) {
        return;
    }
    int state;
    int x;
    int z;
    s16 yaw;
    if (!SessionPlayers_State(&state, PLAYER_PROCESSES_ANY, player)) {
        return;
    }
    if (!SessionPlayers_ScenePoint(&scene, &x, &z, PLAYER_PROCESSES_ANY, player)) {
        return;
    }
    if (!SessionPlayers_Yaw(&yaw, PLAYER_PROCESSES_ANY, player)) {
        return;
    }
    PlayerActors_ClearItemOnState75(&player, &scene, saved_state, &state, &x, &z);
    *saved_state = state;
    *saved_scene = scene;
    saved_position->x = x;
    saved_position->y = 0;
    saved_position->z = z;
    *saved_yaw = yaw;
}

/* func_02096ad0 (vtable slot 6): each other player's report kept (slots 3 down to 0), then,
 * while this system has its slot and its player's actor, this player's yaw, point and state
 * records updated to be sent; done each frame. */
int PlayerReportProcess_Execute(void)
{
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_PLAYERS_COUNT - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) == 0) {
            continue;
        }
        if (Session_IsLocalSlot(session, slot)) {
            continue;
        }
        player_processes_keep_report(slot);
    }

    NetSession *now = data_020ccf94;
    if (Session_IsSlotTaken(now, now->local_slot) != 0) {
        Actor *actor = SessionPlayers_ActorOf(SESSION_PLAYERS_OWN);
        if (actor != NULL) {
            int own = session->local_player;
            if (own < SESSION_PLAYERS_COUNT) {
                SessionRecord_Update(own + 4, &actor->angle[1], 0, 0);
                SessionRecord_Update(own, &actor->position, 0, 0);
                SessionRecord_Update(own + 8, NULL, 0, 0);
            }
        }
    }
    return 1;
}
CLEAN_AS(func_02096ad0, PlayerReportProcess_Execute)

/* func_02096c04 (vtable slot 0): nothing to set up; done at once. */
int PlayerReportProcess_Create(void)
{
    return 1;
}
CLEAN_AS(func_02096c04, PlayerReportProcess_Create)

/* func_02096c08 (vtable slot 17): the destructor, and the object freed to the heap processes
 * come from. */
Process *PlayerReportProcess_DestructFree(Process *self)
{
    self->vtable = data_020e2fe8;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02096c08, PlayerReportProcess_DestructFree)

/* func_02096c30 (vtable slot 16): the destructor: the bases' vtables put back in turn. */
Process *PlayerReportProcess_Destruct(Process *self)
{
    self->vtable = data_020e2fe8;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_02096c30, PlayerReportProcess_Destruct)
