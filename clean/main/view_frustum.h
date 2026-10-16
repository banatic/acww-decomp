/* The view frustum the actors are culled against (one object, data_021f6a6c, built at start-up
 * by __sinit_020c6e38; the camera also sets one up, func_0203c48c): a near and a far distance and
 * the four side planes of a pyramid from the eye, given by half of the vertical field of view
 * and the aspect ratio. Distances are in 20.12 fixed point, in view space, where the camera looks
 * down -Z. */
#ifndef CLEAN_MAIN_VIEW_FRUSTUM_H
#define CLEAN_MAIN_VIEW_FRUSTUM_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "types.h"

/* ViewFrustum_Depth's answer for a point outside. */
#define VIEW_FRUSTUM_OUTSIDE 0x7fffffff

/* The planes' order. */
enum ViewFrustumPlane { VIEW_FRUSTUM_LEFT, VIEW_FRUSTUM_TOP, VIEW_FRUSTUM_RIGHT, VIEW_FRUSTUM_BOTTOM, VIEW_FRUSTUM_PLANES };

/* A C++ object whose vtable (data_020da70c) has only the destructors. */
typedef struct ViewFrustum {
    const u8 *vtable;
    Vec3 normals[VIEW_FRUSTUM_PLANES]; /* 0x04: unit normals pointing out of the frustum */
    u8 unk_34[0x18];
    fx32 aspect;        /* 0x4c: width over height */
    fx32 near_distance; /* 0x50 */
    fx32 far_distance;  /* 0x54 */
    u16 half_fov;       /* 0x58: an angle, half of the vertical field of view */
} ViewFrustum;

int ViewFrustum_Depth(ViewFrustum *frustum, const Mtx43 *view, const Vec3 *point, fx32 radius, Vec3 *out);
void ViewFrustum_ComputePlanes(ViewFrustum *frustum);
void ViewFrustum_Set(ViewFrustum *frustum, fx32 aspect, u16 half_fov, fx32 near_distance, fx32 far_distance);
ViewFrustum *ViewFrustum_Construct(ViewFrustum *frustum);
void ViewFrustum_Destruct(ViewFrustum *frustum);
ViewFrustum *ViewFrustum_DestructDelete(ViewFrustum *frustum);

#endif
