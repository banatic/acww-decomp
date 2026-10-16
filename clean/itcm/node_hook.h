/* A test the game's node callbacks of 3D models (func_02054394 and its neighbours) start with,
 * on NitroSystem's G3D render state (NNSG3dRS). */
#ifndef CLEAN_ITCM_NODE_HOOK_H
#define CLEAN_ITCM_NODE_HOOK_H

#include "types.h"

/* The parts of NitroSystem's NNSG3dRenderObj the test reads. */
typedef struct G3dRenderObject {
    u8 unk_00[0x34];
    void *joint_results; /* 0x34: recJntAnm, where the joints' animation results are kept */
} G3dRenderObject;

/* The parts of NitroSystem's NNSG3dRS the test reads. */
typedef struct G3dRenderState {
    const u8 *command;             /* 0x00: the model's command being run */
    const G3dRenderObject *object; /* 0x04 */
} G3dRenderState;

/* The model command that places a node (NNS_G3D_SBC_NODEDESC), in the low 5 bits of the
 * command's first byte. */
#define G3D_COMMAND_NODEDESC 6

int NodeHook_IsSkipped(void *model, G3dRenderState *state);

#endif
