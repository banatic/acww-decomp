/* The node callbacks of a scene object's model (class 0x020d8c64, obj_020d8c64.h; the model
 * is its member at 0xec, layered_model.h). SpeakerAnim_Init (speaker_anim.h) hands the model
 * SceneObjectNodes_Before for the node command (NODEDESC, 6) with the object as the render
 * object's user data; each callback then hands the command's slot to the next one, so that
 * for each node the three run in turn at NitroSystem's three timings:
 *
 * - before the node (timing 1, SceneObjectNodes_Before): the joints take the animation of the
 *   node's layer (LayeredModel_PrepareNodeB);
 * - once the node's joint is computed (timing 2, SceneObjectNodes_Joint): the translations
 *   are put back to the model's own, the head joint (15) turned by where the object looks, the
 *   root of person 0xd016 bent onto the curved ground, and the node blended by its layer
 *   (LayeredModel_ApplyNodeB);
 * - after the node (timing 3, SceneObjectNodes_After): nothing but the hand-over. */
#ifndef CLEAN_MAIN_SCENE_OBJECT_NODES_H
#define CLEAN_MAIN_SCENE_OBJECT_NODES_H

#include "itcm/node_hook.h"
#include "main/animated_model.h"
#include "types.h"

/* NitroSystem's NNSG3dRS, the parts used here. */
typedef struct SceneObjectNodeState {
    G3dRenderState state;      /* 0x00: the command being run (its byte 1 the node) */
    u32 flag;                  /* 0x08 */
    u32 callbacks[32];         /* 0x0c: by command: the game's functions (their addresses) */
    u8 timings[32];            /* 0x8c: by command: when its callback runs */
    u8 unk_ac[8];              /* 0xac */
    AnimatedModelJoint *joint; /* 0xb4: the node's joint result */
    u8 unk_b8[0x1c];           /* 0xb8 */
    const u8 *node_info;       /* 0xd4: the model's node information (NNSG3dResNodeInfo) */
} SceneObjectNodeState;

void SceneObjectNodes_After(SceneObjectNodeState *state);
void SceneObjectNodes_Joint(SceneObjectNodeState *state);
void SceneObjectNodes_Before(SceneObjectNodeState *state);

#endif
