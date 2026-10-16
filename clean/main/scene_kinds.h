/* More questions about the scene (scene_query.h has the others): the groups of scenes some
 * code tests, each for the current scene (SceneQuery_Current) and for a scene given; the
 * running scene's setup end; and the scene's sound kind.
 *
 * The groups:
 * - 6 and 7, the scenes of a session between systems: the scene's process places and numbers
 *   every player of the session in them (scene_process.h, scene_setup.c);
 * - 6 to 8;
 * - 1 to 5, the player's house rooms (room_cells.h), each as a yes/no and as the room's index
 *   (0-4, -1 outside them). */
#ifndef CLEAN_MAIN_SCENE_KINDS_H
#define CLEAN_MAIN_SCENE_KINDS_H

#include "types.h"

/* The scenes of a session between systems. */
#define SCENE_KINDS_SESSION_FIRST 6
#define SCENE_KINDS_SESSION_SECOND 7

int SceneKinds_CurrentIsSession(void);
int SceneKinds_IsSession(int scene);
int SceneKinds_CurrentIn6To8(void);
int SceneKinds_In6To8(int scene);
int SceneKinds_CurrentIsHouseRoom(void);
int SceneKinds_IsHouseRoom(unsigned int scene);
int SceneKinds_CurrentHouseRoomIndex(void);
int SceneKinds_HouseRoomIndex(unsigned int scene);
int SceneKinds_SetupEnd(void);
int SceneKinds_SoundKind(int between_scenes);

#endif
