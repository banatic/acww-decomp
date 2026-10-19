/* The node callbacks of a scene object's model (scene_object_nodes.h). */
#include "scene_object_nodes.h"

#include "clean.h"
#include "layered_model.h"
#include "model_matrix.h"
#include "scene_look.h"
#include "globe.h"
#include "item_code.h"
#include "scene_query.h"

/* The object's parts read here (scene_object.h). */
#define SCENE_OBJECT_NODES_PERSON 0xea /* u16 */
#define SCENE_OBJECT_NODES_MODEL 0xec
#define SCENE_OBJECT_NODES_LOOK 0x3b0

/* The persons treated apart: 0xd011 keeps its animation's translations but node 16's, 0xd016
 * has its root bent onto the curved ground. */
#define SCENE_OBJECT_NODES_PERSON_D011 0xd011
#define SCENE_OBJECT_NODES_PERSON_D016 0xd016
#define SCENE_OBJECT_NODES_ROOT 0
#define SCENE_OBJECT_NODES_NODE_16 16
/* What AnimatedModel_RestoreNodeTranslation is given as the root's height. */
#define SCENE_OBJECT_NODES_HEIGHT 0x800

/* The head joint's number (15), turned by the look. */
extern const s32 data_020c8150;
extern const fx16 FX_SinCosTable_[4096 * 2];

extern void MTX_RotY33_(Mtx33 *mtx, fx32 sine, fx32 cosine);
extern void MTX_RotX33_(Mtx33 *mtx, fx32 sine, fx32 cosine);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *ab);
/* The callbacks themselves, handed on by their addresses. */
extern void func_0201c48c(void *state);
extern void func_0201c49c(void *state);
extern void func_0201c6a8(void *state);

static u8 *scene_object_nodes_object(const G3dRenderState *state)
{
    return state->object->user; /* the scene object, or null */
}

static LayeredModel *scene_object_nodes_model(u8 *object)
{
    return (LayeredModel *) (void *) (object + SCENE_OBJECT_NODES_MODEL);
}

static void scene_object_nodes_hand_on(G3dRenderState *state, void (*next)(void *), u8 timing)
{
    state->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) next;
    state->hook_timings[G3D_COMMAND_NODE_DESC] = timing;
}

/* Whether the object is person `code`, the variant of a code with one left out. */
static int scene_object_nodes_is_person(u8 *object, u16 code)
{
    u16 *person = (u16 *) (void *) (object + SCENE_OBJECT_NODES_PERSON);
    if (ItemCode_HasVariant(person) != 0) {
        u16 wanted = code;
        int own = ItemCode_VariantItem(person);
        return own == ItemCode_VariantItem(&wanted);
    }
    return *person == code;
}

/* The joint's rotation turned by `angle` (its low 16 bits; rotate_y: about its y axis, else its
 * x axis), when the angle is not 0. */
static void scene_object_nodes_turn(Mtx33 *rotation, int angle, int rotate_y)
{
    if (angle == 0) {
        return;
    }
    int index = (u16) angle >> 4;
    Mtx33 turn;
    if (rotate_y) {
        MTX_RotY33_(&turn, FX_SinCosTable_[index * 2], FX_SinCosTable_[index * 2 + 1]);
    } else {
        MTX_RotX33_(&turn, FX_SinCosTable_[index * 2], FX_SinCosTable_[index * 2 + 1]);
    }
    MTX_Concat33(rotation, &turn, rotation);
}

/* The model's own translation of `node` (its entry in the node information). */
static const s32 *scene_object_nodes_rest_translation(const u8 *node_info, int node)
{
    const u8 *entries = node_info + *(const u16 *) (const void *) (node_info + 6);
    const u8 *entry = entries + *(const u16 *) (const void *) entries * node;
    return (const s32 *) (const void *) (node_info + *(const u32 *) (const void *) (entry + 4) + 4);
}

/* func_0201c48c: after a node: the command's callback is SceneObjectNodes_Before again. */
void SceneObjectNodes_After(G3dRenderState *state)
{
    scene_object_nodes_hand_on(state, func_0201c6a8, G3D_TIMING_A);
}
CLEAN_AS(func_0201c48c, SceneObjectNodes_After)

/* func_0201c49c: once the node's joint is computed, with the scene object:
 * - its animation's translation is replaced by the model's own (from node 2 on; the root is
 *   lowered to a height of 0x800), unless the object is person 0xd011 and func_020b66d8 and
 *   func_020b6708 do not both agree, when only node 16's is;
 * - the head joint (data_020c8150) is turned by the look's angles (scene_look.h) while its kind
 *   is a valid one: about its y axis by the pitch, its x axis by the yaw;
 * - the root of person 0xd016 is put onto the curved ground: its translation's y and z moved
 *   and the joint tilted about its x axis by the ground's angle there;
 * - the node is blended by its layer (LayeredModel_ApplyNodeB).
 * Then the command's callback is SceneObjectNodes_After. */
void SceneObjectNodes_Joint(G3dRenderState *state)
{
    int node = state->command[1];
    u8 *object = scene_object_nodes_object(state);

    if (object != NULL) {
        if (!scene_object_nodes_is_person(object, SCENE_OBJECT_NODES_PERSON_D011) ||
            (SceneQuery_CurrentIn20() != 0 && SceneQuery_CurrentIndexIn20() == 1)) {
            AnimatedModel_RestoreNodeTranslation(state, SCENE_OBJECT_NODES_HEIGHT);
        } else if (node == SCENE_OBJECT_NODES_NODE_16) {
            const s32 *rest = scene_object_nodes_rest_translation(state->node_info, node);
            Vec3 *translation = &state->joint->translation;
            translation->x = rest[0];
            translation->y = rest[1];
            translation->z = rest[2];
        }
    }

    if (node == data_020c8150 && object != NULL) {
        const SceneLook *look = (const SceneLook *) (const void *) (object + SCENE_OBJECT_NODES_LOOK);
        if (look->kind < SCENE_LOOK_KINDS) {
            Mtx33 *rotation = &state->joint->rotation;
            scene_object_nodes_turn(rotation, look->pitch, 1);
            scene_object_nodes_turn(rotation, look->yaw, 0);
        }
    }

    if (node == SCENE_OBJECT_NODES_ROOT && object != NULL &&
        scene_object_nodes_is_person(object, SCENE_OBJECT_NODES_PERSON_D016)) {
        G3dJointResult *joint = state->joint;
        Vec3 bent = joint->translation;
        Vec3 from = joint->translation;
        int tilt = Globe_Bend(&bent, &from);
        joint->translation.z = bent.z;
        joint->translation.y = (s32) ((u32) bent.y - (u32) Globe_Radius());
        scene_object_nodes_turn(&joint->rotation, tilt, 0);
    }

    if (object != NULL) {
        LayeredModel_ApplyNodeB(scene_object_nodes_model(object), state);
    }
    scene_object_nodes_hand_on(state, func_0201c48c, G3D_TIMING_C);
}
CLEAN_AS(func_0201c49c, SceneObjectNodes_Joint)

/* func_0201c6a8: before a node: the joints take the animation of the node's layer
 * (LayeredModel_PrepareNodeB), with the scene object; then the command's callback is
 * SceneObjectNodes_Joint. */
void SceneObjectNodes_Before(G3dRenderState *state)
{
    u8 *object = scene_object_nodes_object(state);
    if (object != NULL) {
        LayeredModel_PrepareNodeB(scene_object_nodes_model(object), state);
    }
    scene_object_nodes_hand_on(state, func_0201c49c, G3D_TIMING_B);
}
CLEAN_AS(func_0201c6a8, SceneObjectNodes_Before)
