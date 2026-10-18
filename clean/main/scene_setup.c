/* A scene's setup run in steps over several frames (scene_setup.h). */
#include "scene_setup.h"

#include "clean.h"
#include "itcm/vector.h"
#include "main/actor.h"
#include "main/player_records.h"
#include "main/session.h"
#include "game_process.h"
#include "player_actors.h"
#include "scene_exit.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session_players.h"

static_assert(sizeof(SceneSetupPoint) == 0x14, "scene setup point");
static_assert(sizeof(SceneSetupObject) == 4, "scene setup object");
static_assert(sizeof(SceneSetupStep) == 8, "scene setup step");
static_assert(offsetof(SceneSetupEnd, param) == 6, "scene setup end");
static_assert(offsetof(SceneSetup, end) == 8, "scene setup");

/* Each step kind's function. */
typedef int (*SceneSetupStepFunc)(SceneSetupStep *step, u8 *item, u64 start);
extern const SceneSetupStepFunc data_020e41ec[];

/* The parent of the objects made here. */
extern int data_021f42f4;
/* The multiplayer session and the town's four players' records. */
extern NetSession *data_020ccf94;
extern u8 data_021dc7bc[];

extern u64 OS_GetTick(void);

/* Scenes that make no players' actors. */
#define SCENE_SETUP_NO_PLAYERS_A 0x0d
#define SCENE_SETUP_NO_PLAYERS_B 0x0e
#define SCENE_SETUP_NO_PLAYERS_C 0x2f
/* The classes of the objects made after the players and at the end. */
#define SCENE_SETUP_AFTER_PLAYERS_CLASS 0x0b
#define SCENE_SETUP_END_CLASS 0x0c
#define SCENE_SETUP_PLAYERS 4
/* A frame's budget, in milliseconds. */
#define SCENE_SETUP_BUDGET_MS 40
/* Without a linked session, the players stand this far apart across the entry. */
#define SCENE_SETUP_PLAYER_SPACING 0x400
#define SCENE_SETUP_PLAYER_OFFSET 0x800
/* A point's coordinates are kept in sixteenths of a unit. */
#define SCENE_SETUP_POINT_UNIT 0x100

/* Whether more than the frame's budget has passed since `start` (the ticks run at 33.514 MHz
 * / 64). */
static int scene_setup_over_budget(u64 start)
{
    return (u32) ((OS_GetTick() - start) * 64 / 33514) > SCENE_SETUP_BUDGET_MS;
}

/* A point's position, angles and parameter. */
static void scene_setup_point(const SceneSetupPoint *point, Vec3 *position, s16 *angle, int *param)
{
    position->x = point->x * SCENE_SETUP_POINT_UNIT;
    position->y = point->y * SCENE_SETUP_POINT_UNIT;
    position->z = point->z * SCENE_SETUP_POINT_UNIT;
    angle[0] = point->angle[0];
    angle[1] = point->angle[1];
    angle[2] = point->angle[2];
    *param = point->param;
}

/* The angles (a turn about Y only) and parameter of main's entry record. */
static void scene_setup_entry_angle(s16 *angle, int *param)
{
    int yaw = SceneExit_Angle((const SceneExit *) (uintptr_t) SceneTables_EntryRecord());
    angle[0] = 0;
    angle[1] = (s16) yaw;
    angle[2] = 0;
    *param = SceneExit_PlayerParam((const SceneExit *) (uintptr_t) SceneTables_EntryRecord());
}

/* func_020b0abc */
int SceneSetup_Run(SceneSetup *setup, u8 *step, u8 *item, u64 start)
{
    return SceneSetup_RunSteps(setup->steps, step, item, start);
}
CLEAN_AS(func_020b0abc, SceneSetup_Run)

/* func_020b0ad4 */
void SceneSetup_End(SceneSetup *setup)
{
    SceneSetup_SpawnEndObject(setup->end);
}
CLEAN_AS(func_020b0ad4, SceneSetup_End)

/* func_020b0ae0: the object of class 0x0c made under the default parent with `end`'s
 * parameter. */
void SceneSetup_SpawnEndObject(SceneSetupEnd *end)
{
    GameProcess_SpawnChild(SCENE_SETUP_END_CLASS, data_021f42f4, end->param, 0);
}
CLEAN_AS(func_020b0ae0, SceneSetup_SpawnEndObject)

/* func_020b0b00: runs the steps from `*step` (from the first without it) until all are done,
 * one fails, or (when `step` is given) the frame's budget since `start` is spent with steps
 * left. Each step finished resets `*item` and moves `*step` on. Whether all are done.
 * REQUIRES: every step's kind is 0-2. */
int SceneSetup_RunSteps(SceneSetupSteps *steps, u8 *step, u8 *item, u64 start)
{
    int i = step != NULL ? *step : 0;
    SceneSetupStep *current = steps->steps + i;
    while (i < (int) steps->count) {
        SceneSetupStepFunc run = data_020e41ec[current->kind];
        if (run != NULL && run(current, item, start) == 0) {
            return 0;
        }
        current++;
        i++;
        if (item != NULL) {
            *item = 0;
        }
        if (step != NULL) {
            *step = (u8) (*step + 1);
        }
        if (i >= (int) steps->count) {
            break;
        }
        if (step != NULL && scene_setup_over_budget(start)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020b0b00, SceneSetup_RunSteps)

/* func_020b0bbc: step kind 2: makes the step's objects under the default parent from `*item`
 * (from the first without it), stopping early (when `item` is given) once the frame's budget
 * since `start` is spent with objects left. Whether all are made.
 * QUIRK: one object is made even when none are left; the index is kept in a byte. */
int SceneSetup_SpawnObjects(SceneSetupStep *step, u8 *item, u64 start)
{
    u8 i = item != NULL ? *item : 0;
    const SceneSetupObject *object = (const SceneSetupObject *) step->items + i;
    for (;;) {
        GameProcess_SpawnChild(object->profile, data_021f42f4, object->param, 0);
        object++;
        i++;
        if (item != NULL) {
            *item = (u8) (*item + 1);
        }
        if (i >= step->count) {
            return 1;
        }
        if (item != NULL && scene_setup_over_budget(start)) {
            return 0;
        }
    }
}
CLEAN_AS(func_020b0bbc, SceneSetup_SpawnObjects)

/* func_020b0c4c: step kind 1: in a scene with players' actors, each player that has a place
 * (SceneSetup_PlayerPlace, the step's items being the four players' points) gets its actor;
 * without a linked session each also takes the next turn first. Then the object of class 0x0b
 * is made; always 1.
 * QUIRK: whether this system's slot is taken is asked and not used. */
int SceneSetup_SpawnPlayers(SceneSetupStep *step)
{
    const SceneSetupPoint *points = step->items;
    Vec3 position;
    s16 angle[3];
    int param;

    if (points != NULL && SceneQuery_Current() != SCENE_SETUP_NO_PLAYERS_A &&
        SceneQuery_Current() != SCENE_SETUP_NO_PLAYERS_B && SceneQuery_Current() != SCENE_SETUP_NO_PLAYERS_C) {
        if (SceneKinds_CurrentIsSession() != 0) {
            Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot);
            for (int player = 0; player < SCENE_SETUP_PLAYERS; player++) {
                if (SceneSetup_PlayerPlace(points, player, 1, &position, angle, &param) != 0) {
                    PlayerActors_Spawn(player, &position, angle, param);
                }
            }
        } else {
            for (int player = 0; player < SCENE_SETUP_PLAYERS; player++) {
                if (SceneSetup_PlayerPlace(points, player, 0, &position, angle, &param) != 0) {
                    SessionPlayers_SetLookIndex(player, SessionPlayers_FreeLookIndex());
                    PlayerActors_Spawn(player, &position, angle, param);
                }
            }
        }
    }
    GameProcess_SpawnChild(SCENE_SETUP_AFTER_PLAYERS_CLASS, data_021f42f4, 0, 0);
    return 1;
}
CLEAN_AS(func_020b0c4c, SceneSetup_SpawnPlayers)

/* func_020b0d08: where session player `player` starts; whether it has a place.
 * In a linked session (`linked`) a player whose record is one of the town's four that holds a
 * player stands at its record's point, except this system's player while the entry record's
 * byte 1 is clear, who stands at the entry. Otherwise only this system's player has a place:
 * the first point while the entry record's byte 1 is set, else the entry, moved across it by
 * the player's number (0-3) unless func_020b6660 says otherwise. */
int SceneSetup_PlayerPlace(const SceneSetupPoint *points, int player, int linked, Vec3 *position, s16 *angle, int *param)
{
    if (linked != 0) {
        int record = SessionPlayers_RecordNumber(player);
        if (record >= PLAYER_RECORDS_TOWN) {
            return 0;
        }
        if (PlayerRecords_TownExists(data_021dc7bc, SessionPlayers_RecordNumber(player)) == 0) {
            return 0;
        }
        if (Session_IsLocalPlayer(data_020ccf94, player) != 0 &&
            SceneExit_UsesOwnPoint((const SceneExit *) (uintptr_t) SceneTables_EntryRecord()) == 0) {
            *position = *(Vec3 *) (uintptr_t) SceneExit_Position((SceneExit *) (uintptr_t) SceneTables_EntryRecord());
            scene_setup_entry_angle(angle, param);
        } else {
            scene_setup_point(&points[record], position, angle, param);
        }
        return 1;
    }

    if (Session_IsLocalPlayer(data_020ccf94, player) == 0) {
        return 0;
    }
    if (SceneExit_UsesOwnPoint((const SceneExit *) (uintptr_t) SceneTables_EntryRecord()) != 0) {
        scene_setup_point(&points[0], position, angle, param);
        return 1;
    }
    Vec3 offset = {0, 0, 0};
    if (SceneQuery_CurrentIs0() == 0) {
        offset.x = (player & 3) * SCENE_SETUP_PLAYER_SPACING - SCENE_SETUP_PLAYER_OFFSET;
        Vec_RotateY(&offset, SceneExit_Angle((const SceneExit *) (uintptr_t) SceneTables_EntryRecord()));
    }
    Vec3 sum;
    Vec_Add(&sum, (const Vec3 *) (uintptr_t) SceneExit_Position((SceneExit *) (uintptr_t) SceneTables_EntryRecord()), &offset);
    *position = sum;
    scene_setup_entry_angle(angle, param);
    return 1;
}
CLEAN_AS(func_020b0d08, SceneSetup_PlayerPlace)

/* func_020b0ea8: step kind 0: makes the step's actors at their points from `*item` (from the
 * first without it), stopping early (when `item` is given) once the frame's budget since
 * `start` is spent with actors left. Whether all are made.
 * QUIRK: one actor is made even when none are left. */
int SceneSetup_SpawnActors(SceneSetupStep *step, u8 *item, u64 start)
{
    int i = item != NULL ? *item : 0;
    const SceneSetupPoint *point = (const SceneSetupPoint *) step->items + i;
    for (;;) {
        Vec3 position = {point->x * SCENE_SETUP_POINT_UNIT, point->y * SCENE_SETUP_POINT_UNIT,
                         point->z * SCENE_SETUP_POINT_UNIT};
        Actor_Spawn(point->profile, point->param, &position, point->angle, NULL);
        point++;
        i++;
        if (item != NULL) {
            *item = (u8) (*item + 1);
        }
        if (i >= step->count) {
            return 1;
        }
        if (item != NULL && scene_setup_over_budget(start)) {
            return 0;
        }
    }
}
CLEAN_AS(func_020b0ea8, SceneSetup_SpawnActors)
