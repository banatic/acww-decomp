/* Rotation quaternions in 20.12 fixed point: their product, their rotation matrix and their
 * normalization. The snowballs of overlay 3 roll with them (snowman.c). */
#ifndef CLEAN_MAIN_QUATERNION_H
#define CLEAN_MAIN_QUATERNION_H

#include "autoload_2/matrix.h"
#include "model_matrix.h"
#include "types.h"

/* x, y and z the vector part, w the scalar part. */
typedef struct Quat {
    fx32 x, y, z, w;
} Quat;

void Quat_Multiply(const Quat *a, const Quat *b, Quat *product);
void Quat_ToMtx43(const Quat *q, Mtx43 *mtx);
void Quat_ToMtx33(const Quat *q, Mtx33 *mtx);
void Quat_Normalize(Quat *q);

#endif
