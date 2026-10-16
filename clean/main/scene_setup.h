/* A scene's setup run in steps over several frames (data_021f6948 points to the scene's
 * SceneSetup; func_020b6d8c runs it, func_020b6db4 ends it).
 *
 * A setup is a list of steps; each step has a kind, which picks its function in the table at
 * data_020e41ec, and a list of items:
 *   kind 0 (SceneSetup_SpawnActors): actors made at points (SceneSetupPoint);
 *   kind 1 (SceneSetup_SpawnPlayers): the players' actors, at the step's four points or where
 *          main's entry record (data_021f69d0) puts this system's player;
 *   kind 2 (SceneSetup_SpawnObjects): objects of a class with a parameter (SceneSetupObject).
 * The step and the item reached are kept in two bytes (data_021f42dc and data_021f42e4), so a
 * setup that has run longer than about 40 ms in a frame stops and goes on from there the next
 * frame. */
#ifndef CLEAN_MAIN_SCENE_SETUP_H
#define CLEAN_MAIN_SCENE_SETUP_H

#include "autoload_2/vector.h"
#include "types.h"

/* An actor's place: its class, its position in sixteenths of a unit and its angles, and the
 * parameter it is made with. */
typedef struct SceneSetupPoint {
    u16 profile;
    s16 x;
    s16 y;
    s16 z;
    s16 angle[3];
    u16 unused;
    int param;
} SceneSetupPoint;

/* An object of class `profile` made with `param`. */
typedef struct SceneSetupObject {
    u16 profile;
    u16 param;
} SceneSetupObject;

typedef struct SceneSetupStep {
    u8 kind;
    u8 count; /* the items */
    u8 unused[2];
    void *items;
} SceneSetupStep;

typedef struct SceneSetupSteps {
    u16 count;
    u16 unused;
    SceneSetupStep *steps;
} SceneSetupSteps;

/* What the halfword 6 of is handed to the object of class 0x0c made at the end. */
typedef struct SceneSetupEnd {
    u8 unk_00[6];
    u16 param;
} SceneSetupEnd;

typedef struct SceneSetup {
    SceneSetupSteps *steps;
    u32 unk_04;
    SceneSetupEnd *end;
} SceneSetup;

int SceneSetup_Run(SceneSetup *setup, u8 *step, u8 *item, u64 start);
void SceneSetup_End(SceneSetup *setup);
void SceneSetup_SpawnEndObject(SceneSetupEnd *end);
int SceneSetup_RunSteps(SceneSetupSteps *steps, u8 *step, u8 *item, u64 start);
int SceneSetup_SpawnObjects(SceneSetupStep *step, u8 *item, u64 start);
int SceneSetup_SpawnPlayers(SceneSetupStep *step);
int SceneSetup_PlayerPlace(const SceneSetupPoint *points, int player, int linked, Vec3 *position, s16 *angle, int *param);
int SceneSetup_SpawnActors(SceneSetupStep *step, u8 *item, u64 start);

#endif
