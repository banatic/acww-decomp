/* A test the game's node callbacks of 3D models (func_02054394 and its neighbours) start with,
 * on NitroSystem's G3D render state (NNSG3dRS). */
#ifndef CLEAN_ITCM_NODE_HOOK_H
#define CLEAN_ITCM_NODE_HOOK_H

#include "main/g3d_render.h"
#include "types.h"

int NodeHook_IsSkipped(void *model, G3dRenderState *state);

#endif
