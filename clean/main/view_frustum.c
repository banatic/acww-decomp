/* The view frustum (view_frustum.h). */
#include "view_frustum.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"

static_assert(offsetof(ViewFrustum, normals) == 0x04, "the normals");
static_assert(offsetof(ViewFrustum, aspect) == 0x4c, "the aspect ratio");
static_assert(offsetof(ViewFrustum, near_distance) == 0x50, "the near distance");
static_assert(offsetof(ViewFrustum, far_distance) == 0x54, "the far distance");
static_assert(offsetof(ViewFrustum, half_fov) == 0x58, "the field of view");

/* What ViewFrustum_Construct sets: 4:3, 20 degrees (0x0e38), 1.0 and 5000.0. */
#define DEFAULT_ASPECT 0x1555
#define DEFAULT_HALF_FOV 0x0e38
#define DEFAULT_NEAR 0x1000
#define DEFAULT_FAR 0x1388000

extern const u8 data_020da70c[]; /* the vtable */
extern const fx16 FX_SinCosTable_[4096 * 2];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *axb);
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);

/* How far `v` lies along `normal`: z first, as the game multiplies. */
static fx32 along(const Vec3 *v, const Vec3 *normal)
{
    fx32 z = FX_MulFunc(v->z, normal->z);
    fx32 x = FX_MulFunc(v->x, normal->x);
    fx32 y = FX_MulFunc(v->y, normal->y);
    return z + (x + y);
}

/* func_0203a7b8: `point` taken into view space by `view` (in `*out`); its depth there when a
 * sphere of `radius` around it reaches into the frustum, else VIEW_FRUSTUM_OUTSIDE. */
int ViewFrustum_Depth(ViewFrustum *frustum, const Mtx43 *view, const Vec3 *point, fx32 radius, Vec3 *out)
{
    MTX_MultVec43(point, view, out);
    fx32 depth = -out->z;
    if (depth < frustum->near_distance - radius || depth > frustum->far_distance + radius) {
        return VIEW_FRUSTUM_OUTSIDE;
    }
    for (int plane = 0; plane < VIEW_FRUSTUM_PLANES; plane++) {
        if (along(out, &frustum->normals[plane]) > radius) {
            return VIEW_FRUSTUM_OUTSIDE;
        }
    }
    return depth;
}
CLEAN_AS(func_0203a7b8, ViewFrustum_Depth)

/* func_0203a89c: the side planes from the field of view and aspect ratio: each normal is the
 * cross product of two neighbouring corners of the near rectangle, normalized. */
void ViewFrustum_ComputePlanes(ViewFrustum *frustum)
{
    int index = frustum->half_fov >> 4;
    fx32 slope = FX_Div(FX_SinCosTable_[index * 2], FX_SinCosTable_[index * 2 + 1]);
    fx32 half_height = FX_MulFunc(frustum->near_distance, slope);
    fx32 half_width = FX_MulFunc(frustum->aspect, half_height);
    Vec3 corners[4] = {
        {-half_width, -half_height, -frustum->near_distance}, /* bottom left */
        {-half_width, half_height, -frustum->near_distance},  /* top left */
        {half_width, half_height, -frustum->near_distance},   /* top right */
        {half_width, -half_height, -frustum->near_distance},  /* bottom right */
    };
    VEC_CrossProduct(&corners[1], &corners[0], &frustum->normals[VIEW_FRUSTUM_LEFT]);
    VEC_CrossProduct(&corners[2], &corners[1], &frustum->normals[VIEW_FRUSTUM_TOP]);
    VEC_CrossProduct(&corners[3], &corners[2], &frustum->normals[VIEW_FRUSTUM_RIGHT]);
    VEC_CrossProduct(&corners[0], &corners[3], &frustum->normals[VIEW_FRUSTUM_BOTTOM]);
    for (int plane = 0; plane < VIEW_FRUSTUM_PLANES; plane++) {
        VEC_Normalize(&frustum->normals[plane], &frustum->normals[plane]);
    }
}
CLEAN_AS(func_0203a89c, ViewFrustum_ComputePlanes)

/* func_0203a958 */
void ViewFrustum_Set(ViewFrustum *frustum, fx32 aspect, u16 half_fov, fx32 near_distance, fx32 far_distance)
{
    frustum->aspect = aspect;
    frustum->half_fov = half_fov;
    frustum->near_distance = near_distance;
    frustum->far_distance = far_distance;
    ViewFrustum_ComputePlanes(frustum);
}
CLEAN_AS(func_0203a958, ViewFrustum_Set)

/* func_0203a970: a frustum of 4:3, 20 degrees above and below, from 1.0 to 5000.0. */
ViewFrustum *ViewFrustum_Construct(ViewFrustum *frustum)
{
    frustum->vtable = data_020da70c;
    ViewFrustum_Set(frustum, DEFAULT_ASPECT, DEFAULT_HALF_FOV, DEFAULT_NEAR, DEFAULT_FAR);
    return frustum;
}
CLEAN_AS(func_0203a970, ViewFrustum_Construct)

/* func_0203a9a8 (vtable slot 0): the destructor. */
void ViewFrustum_Destruct(ViewFrustum *frustum)
{
    frustum->vtable = data_020da70c;
}
CLEAN_AS(func_0203a9a8, ViewFrustum_Destruct)

/* func_0203a9b4 (slot 1): destroyed and freed. */
ViewFrustum *ViewFrustum_DestructDelete(ViewFrustum *frustum)
{
    frustum->vtable = data_020da70c;
    Heap_OperatorDeleteB(frustum);
    return frustum;
}
CLEAN_AS(func_0203a9b4, ViewFrustum_DestructDelete)
