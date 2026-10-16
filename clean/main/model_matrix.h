/* The current model matrix of main's 3D drawing (data_021cfe68, a 4x3 matrix) and the matrices
 * saved from it (data_021cfe98, indexed by a byte). func_02054ed4 applies a node's transform
 * with these: a 3x3 rotation and a translation, either of which may be left out, and a scale
 * the translation can be multiplied by. Each applies its matrix before the current one
 * (current = transform x current). */
#ifndef CLEAN_MAIN_MODEL_MATRIX_H
#define CLEAN_MAIN_MODEL_MATRIX_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "types.h"

/* A rotation and scale (NitroSDK's MtxFx33). */
typedef struct Mtx33 {
    fx32 m[3][3];
} Mtx33;

void ModelMatrix_ApplyScaledTransform(const Mtx33 *rotation, const Vec3 *translation, const Vec3 *scale);
void ModelMatrix_ApplyRotation(const Mtx33 *rotation);
void ModelMatrix_ApplyTranslation(const Vec3 *translation);
void ModelMatrix_ApplyTransform(const Mtx33 *rotation, const Vec3 *translation);
void ModelMatrix_Load(int index);
void ModelMatrix_Save(int index);

#endif
