/* The blend of a joint from its pose to its new animation's (joint_blend.h). */
#include "joint_blend.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(JointBlend, translation) == 0x28, "JointBlend translation");
static_assert(offsetof(JointBlend, weight) == 0x34, "JointBlend weight");
static_assert(sizeof(JointBlend) == 0x3c, "JointBlend size");
static_assert(sizeof(JointBlendAxes) == sizeof(Mtx33), "JointBlendAxes layout");

/* The class's vtable. */
extern const u8 data_020dd174[];

/* NitroSDK: `m` set to the identity; `product` = `a` x `b`. */
extern void MTX_Identity33_(void *m);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *product);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The hardware divider and square-root unit. */
#define REG_DIVCNT (*(volatile u16 *) 0x04000280)
#define REG_DIV_NUMER_L (*(volatile u32 *) 0x04000290)
#define REG_DIV_NUMER_H (*(volatile u32 *) 0x04000294)
#define REG_DIV_DENOM_L (*(volatile u32 *) 0x04000298)
#define REG_DIV_DENOM_H (*(volatile u32 *) 0x0400029c)
#define REG_DIV_RESULT_L (*(volatile u32 *) 0x040002a0)
#define REG_DIV_RESULT_H (*(volatile u32 *) 0x040002a4)
#define REG_SQRTCNT (*(volatile u16 *) 0x040002b0)
#define REG_SQRT_RESULT (*(volatile u32 *) 0x040002b4)
#define REG_SQRT_PARAM_L (*(volatile u32 *) 0x040002b8)
#define REG_SQRT_PARAM_H (*(volatile u32 *) 0x040002bc)
#define DIV_MODE_64_64 2
#define SQRT_MODE_64BIT 1
#define UNIT_BUSY 0x8000

#define ONE 0x1000 /* 1.0 in 20.12 */

/* The nodes whose translation is blended too: the first two, the model's root ones. */
#define JOINT_BLEND_LAST_MOVED_NODE 1

/* The node a node descriptor command places (its byte 1). */
static int command_node(const G3dRenderState *state)
{
    return state->command[1];
}

/* A joint result's rotation as its rows. */
static JointBlendAxes *joint_axes(G3dJointResult *joint)
{
    return (JointBlendAxes *) (void *) &joint->rotation;
}

/* weight * to + (1.0 - weight) * from, taken in 64 bits (wrapping as the ARM's products do)
 * and cut back to 20.12. */
static fx32 mix(fx32 to, fx32 from, fx32 weight, fx32 rest)
{
    u64 sum = (u64) (s64) weight * (u64) (s64) to + (u64) (s64) rest * (u64) (s64) from;
    return (fx32) ((s64) sum >> 12);
}

/* 1.0 - weight, wrapping at 32 bits. */
static fx32 rest_of(fx32 weight)
{
    return (fx32) ((u32) ONE - (u32) weight);
}

/* func_02056aa0: the pose of the node being placed recorded from the joint result the render
 * object keeps for it: its rotation (the identity when it was left all zero) and its
 * translation. */
void JointBlend_RecordPose(JointBlend *blend, G3dRenderState *state)
{
    G3dJointResult *results = state->object->joint_results;
    G3dJointResult *joint = &results[command_node(state)];
    const fx32 *m = &joint->rotation.m[0][0];

    if (m[0] == 0 && m[1] == 0 && m[2] == 0 && m[3] == 0 && m[4] == 0 && m[5] == 0 && m[6] == 0 && m[7] == 0 && m[8] == 0) {
        MTX_Identity33_(&blend->rotation);
    } else {
        blend->rotation = *joint_axes(joint);
    }
    blend->translation = joint->translation;
}
CLEAN_AS(func_02056aa0, JointBlend_RecordPose)

/* func_02056b18: the node's new transform mixed with the recorded pose by the weight. The
 * translation only for the first two nodes and when the joint has one; the rotation always,
 * the identity first when the joint's was left unwritten, which it is no longer. */
void JointBlend_Apply(JointBlend *blend, G3dRenderState *state)
{
    int node = command_node(state);

    if (!(state->joint->flags & G3D_JOINT_TRANSLATION_ZERO) && node <= JOINT_BLEND_LAST_MOVED_NODE) {
        Vec3 translation;
        JointBlend_MixVec(&state->joint->translation, &blend->translation, &translation, blend->weight);
        state->joint->translation = translation;
    }
    if (state->joint->flags & G3D_JOINT_ROTATION_IDENTITY) {
        MTX_Identity33_(&state->joint->rotation);
    }
    JointBlendAxes rotation;
    JointBlend_MixAxes(joint_axes(state->joint), &blend->rotation, &rotation, blend->weight);
    *joint_axes(state->joint) = rotation;
    state->joint->flags &= ~(u32) G3D_JOINT_ROTATION_IDENTITY;
}
CLEAN_AS(func_02056b18, JointBlend_Apply)

/* func_02056bb4: `out` = weight * `to` + (1.0 - weight) * `from`. */
void JointBlend_MixVec(const Vec3 *to, const Vec3 *from, Vec3 *out, fx32 weight)
{
    fx32 rest = rest_of(weight);
    out->x = mix(to->x, from->x, weight, rest);
    out->y = mix(to->y, from->y, weight, rest);
    out->z = mix(to->z, from->z, weight, rest);
}
CLEAN_AS(func_02056bb4, JointBlend_MixVec)

/* func_02056c20: the rotation between `from` and `to` by the weight: the first two rows mixed
 * and scaled to length 1, the third their cross product, the second made square to the other
 * two again. */
void JointBlend_MixAxes(const JointBlendAxes *to, const JointBlendAxes *from, JointBlendAxes *out, fx32 weight)
{
    fx32 rest = rest_of(weight);

    out->x.x = mix(to->x.x, from->x.x, weight, rest);
    out->x.y = mix(to->x.y, from->x.y, weight, rest);
    out->x.z = mix(to->x.z, from->x.z, weight, rest);
    out->y.x = mix(to->y.x, from->y.x, weight, rest);
    out->y.y = mix(to->y.y, from->y.y, weight, rest);
    out->y.z = mix(to->y.z, from->y.z, weight, rest);

    JointBlend_Normalize(&out->x);
    JointBlend_Normalize(&out->y);
    VEC_CrossProduct(&out->x, &out->y, &out->z);
    VEC_CrossProduct(&out->z, &out->x, &out->y);
}
CLEAN_AS(func_02056c20, JointBlend_MixAxes)

/* One coordinate of the vector scaled by `scale`, 1 / its length in 0.45 fixed point (2^45 /
 * length, length in 20.12), rounded to nearest. The products wrap at 64 bits as the ARM's do. */
static fx32 normalized(fx32 coordinate, s64 scale)
{
    u64 product = (u64) scale * (u64) (s64) coordinate + ((u64) 1 << 44);
    return (fx32) ((s64) product >> 45);
}

/* func_02056d0c: `v` scaled to length 1, by the hardware: 2^56 / the squared length (in
 * 40.24) from the divider, times the square root of 4 x the squared length from the
 * square-root unit, is 2^45 / the length. A zero vector is left as it is.
 * HW: the divider is set to 64/64 bits, the numerator and denominator written low word first;
 * the square-root unit to 64 bits, its parameter written low word first; then the square root
 * is waited for and read, then the quotient, low word first. */
void JointBlend_Normalize(Vec3 *v)
{
    u64 squares = (u64) ((s64) v->y * v->y) + (u64) ((s64) v->x * v->x) + (u64) ((s64) v->z * v->z);
    if (squares == 0) {
        return;
    }

    REG_DIVCNT = DIV_MODE_64_64;
    REG_DIV_NUMER_L = 0;
    REG_DIV_NUMER_H = 1u << 24; /* 2^56 */
    REG_DIV_DENOM_L = (u32) squares;
    REG_DIV_DENOM_H = (u32) (squares >> 32);
    REG_SQRTCNT = SQRT_MODE_64BIT;
    REG_SQRT_PARAM_L = (u32) (squares << 2);
    REG_SQRT_PARAM_H = (u32) ((squares << 2) >> 32);

    while (REG_SQRTCNT & UNIT_BUSY) {
    }
    s32 root = (s32) REG_SQRT_RESULT;
    while (REG_DIVCNT & UNIT_BUSY) {
    }
    u32 quotient_low = REG_DIV_RESULT_L;
    u32 quotient_high = REG_DIV_RESULT_H;
    u64 quotient = ((u64) quotient_high << 32) | quotient_low;

    s64 scale = (s64) (quotient * (u64) (s64) root);
    v->x = normalized(v->x, scale);
    v->y = normalized(v->y, scale);
    v->z = normalized(v->z, scale);
}
CLEAN_AS(func_02056d0c, JointBlend_Normalize)

/* func_02056eb0: the destructor. */
void JointBlend_Destruct(JointBlend *blend)
{
    blend->vtable = data_020dd174;
}
CLEAN_AS(func_02056eb0, JointBlend_Destruct)

/* func_02056ebc: the deleting destructor (the vtable's second entry). */
JointBlend *JointBlend_Delete(JointBlend *blend)
{
    blend->vtable = data_020dd174;
    Heap_OperatorDeleteB(blend);
    return blend;
}
CLEAN_AS(func_02056ebc, JointBlend_Delete)

/* func_02056ed4: the complete destructor (the vtable's first entry). */
void JointBlend_DestructComplete(JointBlend *blend)
{
    blend->vtable = data_020dd174;
}
CLEAN_AS(func_02056ed4, JointBlend_DestructComplete)

/* The constructors' work: the recorded rotation cleared (not the translation) and no blend
 * running. */
static void construct(JointBlend *blend)
{
    blend->vtable = data_020dd174;
    MI_CpuFill8(&blend->rotation, 0, sizeof(blend->rotation));
    blend->weight = 0;
    blend->rate = 0;
}

/* func_02056ee0: the constructor (the layered models'). */
JointBlend *JointBlend_Construct(JointBlend *blend)
{
    construct(blend);
    return blend;
}
CLEAN_AS(func_02056ee0, JointBlend_Construct)

/* func_02056f04: the same constructor (the blended model's). */
JointBlend *JointBlend_ConstructBase(JointBlend *blend)
{
    construct(blend);
    return blend;
}
CLEAN_AS(func_02056f04, JointBlend_ConstructBase)
