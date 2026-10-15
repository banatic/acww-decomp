/* 4x3 matrices (NitroSDK's MtxFx43): building a rotation, scale or translation, and applying
 * one to a matrix in place. Angles are 16-bit fractions of a turn (fx_math.h). */
#ifndef CLEAN_AUTOLOAD_2_MATRIX_H
#define CLEAN_AUTOLOAD_2_MATRIX_H

#include "types.h"

/* Three rows of rotation and scale, then the translation, in 20.12 fixed point. */
typedef struct Mtx43 {
    fx32 m[4][3];
} Mtx43;

void Mtx43_RotZ(Mtx43 *mtx, int angle);
void Mtx43_RotY(Mtx43 *mtx, int angle);
void Mtx43_RotX(Mtx43 *mtx, int angle);
void Mtx43_Translation(Mtx43 *mtx, fx32 x, fx32 y, fx32 z);
void Mtx43_RotateZ(Mtx43 *mtx, int angle);
void Mtx43_RotateY(Mtx43 *mtx, int angle);
void Mtx43_RotateX(Mtx43 *mtx, int angle);
void Mtx43_RotateZYX(Mtx43 *mtx, int x_angle, int y_angle, int z_angle);
void Mtx43_Scale(Mtx43 *mtx, fx32 x, fx32 y, fx32 z);
void Mtx43_Translate(Mtx43 *mtx, fx32 x, fx32 y, fx32 z);

#endif
