/* Two places of main a scene's exits can lead back to (scene_exit.h): a scene, a point and an
 * angle in it, the parameter the player's actor is made with there and the tile the point is on.
 *
 * - The saved place (data_021f69a0, exits to SCENE_EXIT_TO_SAVED_PLACE): where the player is
 *   when ScenePlace_SavePlayer is called.
 * - The marked place (data_021f69b8, exits to SCENE_EXIT_TO_MARKED_PLACE): set by overlays
 *   (ScenePlace_SetMarked), back to (48.0, 0, 48.0) in scene 0 with ScenePlace_ResetMarked.
 * Both are C++ global objects built by __sinit_020c6e38 (ScenePlace_Construct). */
#ifndef CLEAN_MAIN_SCENE_PLACE_H
#define CLEAN_MAIN_SCENE_PLACE_H

#include "autoload_2/vector.h"
#include "types.h"

/* The scenes are 0 to SCENE_PLACE_SCENES - 1. */
#define SCENE_PLACE_SCENES 0x33

typedef struct ScenePlace {
    Vec3 position;    /* 0x00 */
    u32 player_param; /* 0x0c */
    s16 angle;        /* 0x10 */
    u8 scene;         /* 0x12 */
    s8 tile_x;        /* 0x13: -1 for none */
    s8 tile_z;        /* 0x14: -1 for none */
    u8 unused[3];
} ScenePlace;

void ScenePlace_ResetMarked(void);
int ScenePlace_SetMarked(int unused, int scene, const Vec3 *position, int player_param, short angle, int tile_x, int tile_z);
int ScenePlace_SavePlayer(int unused, int z_offset);
int ScenePlace_SetSaved(int unused, int scene, const Vec3 *position, int player_param, short angle, int tile_x, int tile_z);
int ScenePlace_IsScene(unsigned int scene);
signed char ScenePlace_TileZ(const ScenePlace *place);
signed char ScenePlace_TileX(const ScenePlace *place);
int ScenePlace_Scene(const ScenePlace *place);
int ScenePlace_Angle(const ScenePlace *place);
int ScenePlace_PlayerParam(const ScenePlace *place);
void *ScenePlace_Position(ScenePlace *place);
void ScenePlace_Set(ScenePlace *place, unsigned char scene, const Vec3 *position, unsigned int player_param, short angle,
                    unsigned int tile_x, unsigned int tile_z);
void ScenePlace_Reset(ScenePlace *place);
void ScenePlace_Destruct(void *object);
int ScenePlace_Construct(ScenePlace *place);

#endif
