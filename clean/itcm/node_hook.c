/* The node callbacks' first test (node_hook.h). */
#include "node_hook.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(offsetof(G3dRenderObject, joint_results) == 0x34, "the joint results");
static_assert(offsetof(G3dRenderState, object) == 0x04, "the render object");

/* func_01ffcc10: TRUE (the callback does nothing) unless the command being run places a node
 * and the render object keeps its joints' results. `model` is not used. */
int NodeHook_IsSkipped(void *model, G3dRenderState *state)
{
    (void) model;
    if ((state->command[0] & 0x1f) != G3D_COMMAND_NODEDESC) {
        return TRUE;
    }
    return state->object->joint_results == NULL;
}
CLEAN_AS(func_01ffcc10, NodeHook_IsSkipped)
