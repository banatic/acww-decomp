/* The node callbacks' first test (node_hook.h). */
#include "node_hook.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

/* The layouts of g3d_render.h. */
static_assert(offsetof(G3dRenderObject, joint_anims) == 0x10, "render object joint animations");
static_assert(offsetof(G3dRenderObject, user) == 0x2c, "render object user");
static_assert(offsetof(G3dRenderObject, joint_results) == 0x34, "render object joint results");
static_assert(sizeof(G3dRenderObject) == 0x54, "render object");
static_assert(offsetof(G3dJointResult, rotation) == 0x28, "joint rotation");
static_assert(offsetof(G3dJointResult, translation) == 0x4c, "joint translation");
static_assert(sizeof(G3dJointResult) == 0x58, "joint result");
static_assert(offsetof(G3dMaterialResult, polygon_attr) == 0x0c, "material polygon attributes");
static_assert(offsetof(G3dMaterialResult, texture_image) == 0x10, "material texture image");
static_assert(offsetof(G3dMaterialResult, translate_t) == 0x28, "material translation");
static_assert(offsetof(G3dMaterialResult, width) == 0x2c, "material width");
static_assert(offsetof(G3dMaterialResult, magnify_h) == 0x34, "material magnification");
static_assert(sizeof(G3dMaterialResult) == 0x38, "material result");
static_assert(offsetof(G3dRenderState, hooks) == 0x0c, "render state hooks");
static_assert(offsetof(G3dRenderState, hook_timings) == 0x8c, "render state hook timings");
static_assert(offsetof(G3dRenderState, material) == 0xb0, "render state material");
static_assert(offsetof(G3dRenderState, joint) == 0xb4, "render state joint");
static_assert(offsetof(G3dRenderState, visible) == 0xb8, "render state visibility");
static_assert(offsetof(G3dRenderState, node_info) == 0xd4, "render state node information");
static_assert(offsetof(G3dRenderState, materials) == 0xd8, "render state materials");

/* func_01ffcc10: TRUE (the callback does nothing) unless the command being run places a node
 * and the render object keeps its joints' results. `model` is not used. */
int NodeHook_IsSkipped(void *model, G3dRenderState *state)
{
    (void) model;
    if ((state->command[0] & G3D_COMMAND_MASK) != G3D_COMMAND_NODE_DESC) {
        return TRUE;
    }
    return state->object->joint_results == NULL;
}
CLEAN_AS(func_01ffcc10, NodeHook_IsSkipped)
