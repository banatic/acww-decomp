/* The ways out of a scene and main's entry record.
 *
 * A SceneExit (0x1c bytes) says where a way out of a scene leads: the scene, the point and angle
 * the player is put at there and the parameter their actor is made with, two bytes handed to the
 * change of scene, and the door's own kind and facing. Each scene's exits are a table its setup
 * points to (data_021f6948's word 0x0c, SceneExitScene); overlays build theirs at start-up with
 * SceneExit_Init.
 *
 * Main's entry record (data_021f69d0, SceneTables_EntryRecord) is a SceneExit too: the exit
 * being taken. Its scene is SCENE_EXIT_NONE until one of SceneExit_SetTo, SceneExit_SetToScene,
 * SceneExit_SetToSceneOnly or SceneExit_Take fills it; the first one wins until it is cleared
 * (SceneExit_Clear). Scene_setup.c puts the player where it says; SceneExit_RequestChange asks
 * for the process between scenes (scene_change.h) with its two bytes.
 *
 * An exit whose scene is 0x3c-0x3f leads to a place worked out when it is taken
 * (SceneExit_ResolveSpecial): one of the two places of scene_place.h, or the front of a
 * building of the town map. */
#ifndef CLEAN_MAIN_SCENE_EXIT_H
#define CLEAN_MAIN_SCENE_EXIT_H

#include "autoload_2/vector.h"
#include "main/scene_setup.h"
#include "types.h"

/* SceneExit.scene of a free entry record. */
#define SCENE_EXIT_NONE 0x3f

/* The scenes of the exits that lead to a place worked out when taken. */
#define SCENE_EXIT_TO_MARKED_PLACE 0x3c /* the marked place (data_021f69b8, scene_place.h) */
#define SCENE_EXIT_TO_BUILDING_500B 0x3d
#define SCENE_EXIT_TO_BUILDINGS_5014 0x3e /* buildings 0x5014-0x501a */
#define SCENE_EXIT_TO_SAVED_PLACE 0x3f    /* the player's saved place (data_021f69a0) */

/* What SceneExit_ResolveSpecial answers: the exit is read from the table, or it leads to the
 * saved or the marked place (which SceneExit_Take writes back). */
enum SceneExitSource { SCENE_EXIT_FROM_TABLE = 1, SCENE_EXIT_FROM_SAVED = 2, SCENE_EXIT_FROM_MARKED = 3 };

typedef struct SceneExit {
    u8 scene;         /* 0x00: the scene gone to; SCENE_EXIT_NONE in a free entry record */
    u8 own_point;     /* 0x01: nonzero when the scene's own point is used, not `position` */
    s16 angle;        /* 0x02: the player's angle there */
    Vec3 position;    /* 0x04: the player's point there */
    u32 player_param; /* 0x10: what the player's actor is made with */
    u8 change_arg;    /* 0x14: what process class 5 (scene_change.h) is asked for with */
    u8 next_arg;      /* 0x15: kept for process class 6 (global_021dc5b0.h) */
    s16 door_angle;   /* 0x16: the way the door faces */
    u8 door_kind;     /* 0x18 */
    u8 unused[3];
} SceneExit;

/* A scene's exits. */
typedef struct SceneExitList {
    SceneExit *exits;
    u8 count;
} SceneExitList;

/* What data_021f6948 points to: the scene's setup and, after it, its exits. */
typedef struct SceneExitScene {
    SceneSetup setup;
    SceneExitList *exits; /* 0x0c */
} SceneExitScene;

int SceneExit_NextArg(const SceneExit *exit);
void SceneExit_SetChangeArg(SceneExit *exit, int value);
int SceneExit_ChangeArg(const SceneExit *exit);
int SceneExit_UsesOwnPoint(const SceneExit *exit);
int SceneExit_PlayerParam(const SceneExit *exit);
int SceneExit_Angle(const SceneExit *exit);
int SceneExit_Position(SceneExit *exit);
void SceneExit_RequestChange(int change_arg, int next_arg);
int SceneExit_NextScene(void);
int SceneExit_Scene(const SceneExit *exit);
void SceneExit_Clear(SceneExit *exit);
int SceneExit_DoorPoint(const SceneExit *entry, int index, Vec3 *point, const Vec3 *from);
int SceneExit_DoorInfo(const SceneExit *entry, int index, int *kind, s16 *door_angle);
int SceneExit_Take(SceneExit *entry, int index);
int SceneExit_Resolve(const SceneExit *entry, int index, u8 *scene, Vec3 *position, int *player_param, s16 *angle,
                      u8 *change_arg, u8 *next_arg, int *tile_x, int *tile_z);
int SceneExit_ResolveSpecial(const SceneExit *entry, int index, u8 *scene, Vec3 *position, int *player_param, s16 *angle,
                             int *tile_x, int *tile_z, u8 *change_arg, u8 *next_arg);
int SceneExit_SetTo(SceneExit *exit, unsigned char scene, const Vec3 *position, unsigned int player_param, short angle,
                    unsigned char change_arg, unsigned char next_arg);
int SceneExit_SetToScene(SceneExit *exit, unsigned char scene, unsigned char change_arg, unsigned char next_arg);
unsigned char SceneExit_SetToSceneOnly(SceneExit *exit, unsigned char scene);
void SceneExit_Init(SceneExit *exit, unsigned char scene, const Vec3 *position, int player_param, short angle,
                    unsigned char change_arg, unsigned char next_arg, short door_angle, unsigned char door_kind);
void SceneExit_Destruct(void *object);
void SceneExit_Construct(SceneExit *exit);

#endif
