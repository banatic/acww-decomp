/* 4x3 matrices (matrix.h). Applying a transform to a matrix puts it first: `mtx` becomes the
 * transform times `mtx`, so it acts in the matrix's own space. */
#include "matrix.h"

#include "clean.h"

extern void MTX_RotX43_(Mtx43 *mtx, fx32 sin, fx32 cos);
extern void MTX_RotY43_(Mtx43 *mtx, fx32 sin, fx32 cos);
extern void MTX_RotZ43_(Mtx43 *mtx, fx32 sin, fx32 cos);
extern void MTX_Scale43_(Mtx43 *mtx, fx32 x, fx32 y, fx32 z);
/* `product` = `a` times `b`. */
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *product);

/* Sine and cosine of each of 4096 angles, interleaved (NitroSDK's table). */
extern const fx16 FX_SinCosTable_[4096 * 2];

/* The table's entry for `angle`: its top 12 bits. */
static int sin_cos_index(int angle)
{
    return (u16) angle >> 4;
}

/* func_020e95fc: a rotation by `angle` about Z. */
void Mtx43_RotZ(Mtx43 *mtx, int angle)
{
    int i = sin_cos_index(angle);
    MTX_RotZ43_(mtx, FX_SinCosTable_[2 * i], FX_SinCosTable_[2 * i + 1]);
}
CLEAN_AS(func_020e95fc, Mtx43_RotZ)

/* func_020e9640: a rotation by `angle` about Y. */
void Mtx43_RotY(Mtx43 *mtx, int angle)
{
    int i = sin_cos_index(angle);
    MTX_RotY43_(mtx, FX_SinCosTable_[2 * i], FX_SinCosTable_[2 * i + 1]);
}
CLEAN_AS(func_020e9640, Mtx43_RotY)

/* func_020e9684: a rotation by `angle` about X. */
void Mtx43_RotX(Mtx43 *mtx, int angle)
{
    int i = sin_cos_index(angle);
    MTX_RotX43_(mtx, FX_SinCosTable_[2 * i], FX_SinCosTable_[2 * i + 1]);
}
CLEAN_AS(func_020e9684, Mtx43_RotX)

/* func_020e96c8: a translation by (x, y, z). */
void Mtx43_Translation(Mtx43 *mtx, fx32 x, fx32 y, fx32 z)
{
    *mtx = (Mtx43){{
        {0x1000, 0, 0},
        {0, 0x1000, 0},
        {0, 0, 0x1000},
        {x, y, z},
    }};
}
CLEAN_AS(func_020e96c8, Mtx43_Translation)

/* func_020e9714: `mtx` rotated by `angle` about Z. */
void Mtx43_RotateZ(Mtx43 *mtx, int angle)
{
    Mtx43 rotation;
    Mtx43_RotZ(&rotation, angle);
    MTX_Concat43(&rotation, mtx, mtx);
}
CLEAN_AS(func_020e9714, Mtx43_RotateZ)

/* func_020e9744: `mtx` rotated by `angle` about Y. */
void Mtx43_RotateY(Mtx43 *mtx, int angle)
{
    Mtx43 rotation;
    Mtx43_RotY(&rotation, angle);
    MTX_Concat43(&rotation, mtx, mtx);
}
CLEAN_AS(func_020e9744, Mtx43_RotateY)

/* func_020e9774: `mtx` rotated by `angle` about X. */
void Mtx43_RotateX(Mtx43 *mtx, int angle)
{
    Mtx43 rotation;
    Mtx43_RotX(&rotation, angle);
    MTX_Concat43(&rotation, mtx, mtx);
}
CLEAN_AS(func_020e9774, Mtx43_RotateX)

/* func_020e97a4: `mtx` rotated about Z, then Y, then X, each only when its angle is not 0. */
void Mtx43_RotateZYX(Mtx43 *mtx, int x_angle, int y_angle, int z_angle)
{
    if (z_angle != 0) {
        Mtx43_RotateZ(mtx, z_angle);
    }
    if (y_angle != 0) {
        Mtx43_RotateY(mtx, y_angle);
    }
    if (x_angle != 0) {
        Mtx43_RotateX(mtx, x_angle);
    }
}
CLEAN_AS(func_020e97a4, Mtx43_RotateZYX)

/* func_020e9838: `mtx` scaled by (x, y, z). */
void Mtx43_Scale(Mtx43 *mtx, fx32 x, fx32 y, fx32 z)
{
    Mtx43 scale;
    MTX_Scale43_(&scale, x, y, z);
    MTX_Concat43(&scale, mtx, mtx);
}
CLEAN_AS(func_020e9838, Mtx43_Scale)

/* func_020e9868: `mtx` translated by (x, y, z). */
void Mtx43_Translate(Mtx43 *mtx, fx32 x, fx32 y, fx32 z)
{
    Mtx43 translation;
    Mtx43_Translation(&translation, x, y, z);
    MTX_Concat43(&translation, mtx, mtx);
}
CLEAN_AS(func_020e9868, Mtx43_Translate)
