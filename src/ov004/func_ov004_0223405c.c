/* func_ov004_0223405c @ 0x0223405c, 0x3bc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define BYTE(o, k) (*(u8 *) ((o) + (k)))
#define HALF(o, k) (*(u16 *) ((o) + (k)))
#define SHALF(o, k) (*(short *) ((o) + (k)))
#define VEC(o, k) ((Vec *) ((o) + (k)))
extern u8 data_ov004_02247927[], data_ov004_02247926[], data_ov004_02247934[];
extern u8 data_ov004_022593a0;
extern char *data_ov004_022593b4, *data_ov004_022593b8;
extern Vec data_ov004_022593dc, data_ov004_022593c4;
extern short FX_SinCosTable_[];
extern void func_02089bec(char *, Vec *, int, int, int, int, int, u8, int);
extern void func_02089fc8(char *);
extern int FX_MulFunc(int, int);
extern int func_02031168(Vec *, int, Vec *, int, int);
extern void func_ov004_02234024(void *, int *, int, int, int, int);
#define DRAW(pos, flag) func_02089bec(*slot + 4, (pos), extent, width, 0x100, (flag), 20, (u8) kind, (height << 12) >> 3)
static inline void copyvec(Vec *dst, const Vec *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
void func_ov004_0223405c(void *self, char **slot, int kind)
{
    int radius, offset;
    Vec *position = VEC(*slot, 0x1a8);
    Vec *second;
    int x0, z0, x1, z1, tx0, tz0, tx1, tz1;
    int v1;
    char *v3;
    char *v4;
    char *v2;
    Vec *points;
    int extent, width, height, i;
    height = BYTE(*slot, 0x164);
    v1 = kind * 17;
    extent = (data_ov004_02247927[v1] << 12) >> 7;
    if (!BYTE(*slot, 0x1c7)) {
        return;
    }
    width = (data_ov004_02247926[v1] << 12) >> 7;
    if (data_ov004_022593a0 == 0) {
        DRAW(position, 0x140);
    } else if (data_ov004_022593a0 == 1) {
        if (kind == 0x24) {
            if (data_ov004_022593b4) {
                DRAW(VEC(data_ov004_022593b4, 0x26c), 0x340);
            }
            v1 = kind * 17;
        } else if (kind == 0x23) {
            if (data_ov004_022593b8) {
                DRAW(VEC(data_ov004_022593b8, 0x264), 0x340);
            }
        } else if (kind == 0x26) {
            DRAW(position, 0x140);
        } else {
            DRAW(position, 0x340);
        }
    }
    func_02089fc8(*slot + 4);
    radius = (data_ov004_02247934[v1] << 12) >> 7;
    offset = extent - (radius >> 1);
    for (i = 0; i < 2; i++) {
        copyvec(&VEC(*slot, 0x1d0)[i], VEC(*slot, 0x1a8));
        if (i == 0) {
            v3 = *slot;
            VEC(v3, 0x1d0)[i].x += FX_MulFunc(offset, FX_SinCosTable_[(HALF(v3, 0x1c0) >> 4) * 2]);
            v4 = *slot;
            VEC(v4, 0x1d0)[i].z += FX_MulFunc(offset, FX_SinCosTable_[(HALF(v4, 0x1c0) >> 4) * 2 + 1]);
            x0 = VEC(*slot, 0x1d0)[i].x;
            z0 = VEC(*slot, 0x1d0)[i].z;
        } else {
            v2 = *slot;
            v1 = ((u16) (short) (SHALF(v2, 0x1c0) + 0x8000) >> 4) * 2;
            VEC(v2, 0x1d0)[i].x += FX_MulFunc(offset, FX_SinCosTable_[v1]);
            second = &VEC(*slot, 0x1d0)[i];
            second->z += FX_MulFunc(offset, FX_SinCosTable_[v1 + 1]);
            x1 = VEC(*slot, 0x1d0)[i].x;
            z1 = VEC(*slot, 0x1d0)[i].z;
        }
        if (data_ov004_022593a0 == 0) {
            if (kind < 17) {
                func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593dc, 0x11c00, 0x5c00);
            } else if (kind != 25) {
                func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593c4, 0x11c00, 0x5c00);
            } else {
                func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593dc, 0x11c00, 0x5c00);
            }
        } else {
            switch (BYTE(*slot, 0x1c8)) {
                case 0:
                    if (func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593dc, 0x1a000, 0x4dc3)) {
                        BYTE(*slot, 0x1f0) = 1;
                    }
                    break;
                case 1:
                    if (func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593dc, 0x26000, 0x4dc3)) {
                        BYTE(*slot, 0x1f0) = 1;
                    }
                    break;
                case 2:
                    if (func_02031168(&VEC(*slot, 0x1d0)[i], radius, &data_ov004_022593dc, 0x2a000, 0x4dc3)) {
                        BYTE(*slot, 0x1f0) = 1;
                    }
                    break;
            }
        }
        if (i == 0) {
            tx0 = VEC(*slot, 0x1d0)[i].x;
            tz0 = VEC(*slot, 0x1d0)[i].z;
        } else {
            tx1 = VEC(*slot, 0x1d0)[i].x;
            tz1 = VEC(*slot, 0x1d0)[i].z;
        }
    }
    func_ov004_02234024(self, &VEC(*slot, 0x1a8)->x, x0, tx0, x1, tx1);
    func_ov004_02234024(self, &VEC(*slot, 0x1b0)->x, z0, tz0, z1, tz1);
    copyvec(VEC(*slot, 0x1b4), position);
}
