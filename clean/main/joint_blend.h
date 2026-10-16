/* The blend of a joint from the pose it had to its new animation's (a C++ class of main,
 * vtable data_020dd174, 0x3c bytes; the Ramp of frame_ctrl.h with the pose). The animated and
 * layered models (animated_model.h, layered_model.h) keep one per animation: while its weight
 * ramps from 0 to 1.0, the node callback before a node records the node's pose
 * (JointBlend_RecordPose) and the one after it mixes that pose into the node's new transform
 * (JointBlend_Apply). The rotations are mixed row by row and made orthonormal again. */
#ifndef CLEAN_MAIN_JOINT_BLEND_H
#define CLEAN_MAIN_JOINT_BLEND_H

#include "autoload_2/vector.h"
#include "main/animated_model.h"
#include "types.h"

/* A 3x3 rotation as its three rows (the layout of NitroSDK's MtxFx33). */
typedef struct JointBlendAxes {
    Vec3 x;
    Vec3 y;
    Vec3 z;
} JointBlendAxes;

typedef struct JointBlend {
    const void *vtable;      /* 0x00 */
    JointBlendAxes rotation; /* 0x04: the pose blended from */
    Vec3 translation;        /* 0x28 */
    fx32 weight;             /* 0x34: of the new transform, 0 to 1.0 (Ramp_Step) */
    fx32 rate;               /* 0x38: 0 when no blend runs */
} JointBlend;

void JointBlend_RecordPose(JointBlend *blend, AnimatedModelNodeState *state);
void JointBlend_Apply(JointBlend *blend, AnimatedModelNodeState *state);
void JointBlend_MixVec(const Vec3 *to, const Vec3 *from, Vec3 *out, fx32 weight);
void JointBlend_MixAxes(const JointBlendAxes *to, const JointBlendAxes *from, JointBlendAxes *out, fx32 weight);
void JointBlend_Normalize(Vec3 *v);
void JointBlend_Destruct(JointBlend *blend);
JointBlend *JointBlend_Delete(JointBlend *blend);
void JointBlend_DestructComplete(JointBlend *blend);
JointBlend *JointBlend_Construct(JointBlend *blend);
JointBlend *JointBlend_ConstructBase(JointBlend *blend);

#endif
