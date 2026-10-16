/* Scenes that one player at a time may enter: scenes 0x1f and 0x22 (data_020d1ad8, each with
 * the scene its exit leads back to: 0x1d and 0x20).
 *
 * Each scene below 0x33 has a mask of the session slots in it (data_021dc70c, 51 masks, bits
 * 0-3). A slot is given a scene when, with its bit added, no more than one bit is set; the
 * session's host (slot 0) decides. Overlay 4 takes an exit of the scene's exit table
 * (data_021f6948's word 0x0c, read by func_020b6140 and func_020b6044; func_020b6098 leaves
 * through one) with SceneClaim_TakeExit, which fills the exit being taken (data_021dc6e8,
 * SceneClaimExit) and its answer:
 *   - to a scene that needs no claim, at once SCENE_CLAIM_GIVEN;
 *   - where claims are decided here (the session not linked, or this system the host), at once
 *     SCENE_CLAIM_GIVEN or SCENE_CLAIM_REFUSED;
 *   - else SCENE_CLAIM_WAITING while the host is asked with message 0x33 (the scene); it
 *     answers with message 0x34 (a byte, nonzero when given).
 * Leaving a claimed scene for the scene its exit leads to lets the claim go (SceneClaim_Leave
 * at each change of scene, while data_020e54a8 is 1): on the host at once, else by message
 * 0x35 (the scene) to the host. */
#ifndef CLEAN_MAIN_SCENE_CLAIM_H
#define CLEAN_MAIN_SCENE_CLAIM_H

#include "autoload_2/vector.h"
#include "types.h"

#define SCENE_CLAIM_SCENES 0x33 /* the masks: scenes 0-0x32 */
#define SCENE_CLAIM_ROOMS 2     /* the scenes that need a claim */

/* SceneClaimExit.answer */
enum SceneClaimAnswer {
    SCENE_CLAIM_WAITING = 0,
    SCENE_CLAIM_REFUSED = 1,
    SCENE_CLAIM_GIVEN = 2,
};

/* The exit being taken (data_021dc6e8, a C++ global object). */
typedef struct SceneClaimExit {
    u8 scene; /* 0x00: where the exit leads */
    u8 pad_01[3];
    Vec3 position;  /* 0x04: where the player stands to take it */
    Vec3 next_tile; /* 0x10: the player's x, the z of the centre of the tile after the
                     * player's, height 0 */
    u16 angle;      /* 0x1c: the angle the player takes it at */
    u8 exit;        /* 0x1e: its number in the exit table; 0xff for none */
    u8 answer;      /* 0x1f: SceneClaimAnswer */
    u8 placed;      /* 0x20: the exit's byte 0x18: its own position and angle are used */
    u8 pad_21[3];
} SceneClaimExit;

/* The session slots in a scene: bit n for slot n (bits 0-3). */
typedef struct SceneClaimMask {
    u8 slots;
} SceneClaimMask;

/* A scene that needs a claim (data_020d1ad8). */
typedef struct SceneClaimRoom {
    u8 scene;   /* the claimed scene */
    u8 exit_to; /* the scene its exit leads to, where the claim is let go */
} SceneClaimRoom;

void SceneClaim_ReceiveRelease(const unsigned char *scene, int slot);
void SceneClaim_ReceiveAnswer(unsigned char *given);
void SceneClaim_ReceiveRequest(unsigned char *scene, int slot);
void SceneClaim_Leave(void);
void SceneClaim_Release(unsigned char scene, int slot);
int SceneClaim_Exit(void);
int SceneClaim_TakeExit(int exit);
int SceneClaim_IsClaimedExit(int exit);
int SceneClaim_IsClaimed(int scene);
void SceneClaim_Reset(void);

void SceneClaimExit_SetNextTile(SceneClaimExit *target, const Vec3 *next_tile);
void SceneClaimExit_SetAngle(SceneClaimExit *target, int angle);
void SceneClaimExit_SetPosition(SceneClaimExit *target, const Vec3 *position);
void SceneClaimExit_SetScene(SceneClaimExit *target, int scene);
void SceneClaimExit_SetPlaced(SceneClaimExit *target, unsigned char placed);
void SceneClaimExit_SetExit(SceneClaimExit *target, int exit);
void SceneClaimExit_SetAnswer(SceneClaimExit *target, int answer);
int SceneClaimExit_NextTile(SceneClaimExit *target);
int SceneClaimExit_Position(SceneClaimExit *target);
unsigned char SceneClaimExit_Placed(SceneClaimExit *target);
int SceneClaimExit_Answer(SceneClaimExit *target);
void SceneClaimExit_Clear(SceneClaimExit *target);
void SceneClaimExit_Destruct(void *target);
int SceneClaimExit_Construct(SceneClaimExit *target);

int SceneClaimMasks_CountWith(SceneClaimMask *masks, unsigned int scene, int slot);
void SceneClaimMasks_Remove(SceneClaimMask *masks, unsigned int scene, int slot);
void SceneClaimMasks_Add(SceneClaimMask *masks, unsigned int scene, int slot);
void SceneClaimMasks_Clear(char *masks);
int SceneClaimMask_CountWith(unsigned char *mask, int slot);
void SceneClaimMask_Destruct(void *mask);
int SceneClaimMask_Count(void *mask);
int SceneClaimMask_Has(const unsigned char *mask, int slot);
void SceneClaimMask_Remove(unsigned char *mask, int slot);
void SceneClaimMask_Add(unsigned char *mask, int slot);
void SceneClaimMask_Clear(SceneClaimMask *mask);
void *SceneClaimMasks_Destruct(void *masks);
void *SceneClaimMask_Construct(void *mask);

#endif
