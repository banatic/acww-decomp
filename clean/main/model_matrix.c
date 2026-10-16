/* The current model matrix and the saved ones (model_matrix.h). */
#include "model_matrix.h"

#include "clean.h"

extern Mtx43 data_021cfe68;   /* the current matrix */
extern Mtx43 data_021cfe98[]; /* the saved ones */

extern void MTX_Copy33To43_(const Mtx33 *src, Mtx43 *dst);
extern void MTX_Identity43_(Mtx43 *mtx);
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *ab);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static void apply(const Mtx43 *transform)
{
    MTX_Concat43(transform, &data_021cfe68, &data_021cfe68);
}

/* func_02070c50: the rotation and the translation, multiplied by `scale` when there is one. */
void ModelMatrix_ApplyScaledTransform(const Mtx33 *rotation, const Vec3 *translation, const Vec3 *scale)
{
    Mtx43 transform;
    MTX_Copy33To43_(rotation, &transform);
    if (scale == NULL) {
        transform.m[3][0] = translation->x;
        transform.m[3][1] = translation->y;
        transform.m[3][2] = translation->z;
    } else {
        transform.m[3][0] = FX_MulFunc(translation->x, scale->x);
        transform.m[3][1] = FX_MulFunc(translation->y, scale->y);
        transform.m[3][2] = FX_MulFunc(translation->z, scale->z);
    }
    apply(&transform);
}
CLEAN_AS(func_02070c50, ModelMatrix_ApplyScaledTransform)

/* func_02070ca4: the rotation alone (NitroSDK's MTX_Copy33To43 gives no translation). */
void ModelMatrix_ApplyRotation(const Mtx33 *rotation)
{
    Mtx43 transform;
    MTX_Copy33To43_(rotation, &transform);
    apply(&transform);
}
CLEAN_AS(func_02070ca4, ModelMatrix_ApplyRotation)

/* func_02070cc4 */
void ModelMatrix_ApplyTranslation(const Vec3 *translation)
{
    Mtx43 transform;
    MTX_Identity43_(&transform);
    transform.m[3][0] = translation->x;
    transform.m[3][1] = translation->y;
    transform.m[3][2] = translation->z;
    apply(&transform);
}
CLEAN_AS(func_02070cc4, ModelMatrix_ApplyTranslation)

/* func_02070cf4 */
void ModelMatrix_ApplyTransform(const Mtx33 *rotation, const Vec3 *translation)
{
    Mtx43 transform;
    MTX_Copy33To43_(rotation, &transform);
    transform.m[3][0] = translation->x;
    transform.m[3][1] = translation->y;
    transform.m[3][2] = translation->z;
    apply(&transform);
}
CLEAN_AS(func_02070cf4, ModelMatrix_ApplyTransform)

/* func_02070d24: make saved matrix `index` the current one. */
void ModelMatrix_Load(int index)
{
    data_021cfe68 = data_021cfe98[index];
}
CLEAN_AS(func_02070d24, ModelMatrix_Load)

/* func_02070d4c: save the current matrix as matrix `index`. */
void ModelMatrix_Save(int index)
{
    data_021cfe98[index] = data_021cfe68;
}
CLEAN_AS(func_02070d4c, ModelMatrix_Save)
