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

#include "main/g3d_render.h"
#include "itcm/node_hook.h"
#include "main/animated_model.h"
#include "types.h"

void SceneObjectNodes_After(G3dRenderState *state);
void SceneObjectNodes_Joint(G3dRenderState *state);
void SceneObjectNodes_Before(G3dRenderState *state);

#endif
