/* func_ov009_02264264 @ 0x02264264, 0xc4 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x30 - 0x2c];
    int unk_30;
    char pad_34[0x4c - 0x34];
    void *unk_4C;
} UnkStruct_02264264;

typedef struct {
    char pad_00[0xc];
    u16 unk_0C;
    char pad_0E[0x8e - 0xe];
    s16 unk_8E;
} UnkStruct_02264264_2;

extern void *func_020961a8(int a);
extern int func_0202fb28(UnkStruct_02264264 *self, Vec3 *p);
extern int func_ov009_0226321c(void *h, Vec3 *a, s16 *b);
extern int func_020e8b4c(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_0202f904(UnkStruct_02264264 *self, Vec3 *e, Vec3 *c, Vec3 *d);

int func_ov009_02264264(UnkStruct_02264264 *self, Vec3 *p, int off, UnkStruct_02264264_2 *ent)
{
    s16 b;
    Vec3 a;
    Vec3 c;
    Vec3 d;
    Vec3 e;
    unsigned int ok;
    int v;

    if (ent != 0 && self->unk_4C != 0) {
        ok = (ent->unk_0C == 9) ? 1 : 0;
        if (ok != 0) {
            if (func_020961a8(4) == ent) {
                v = func_0202fb28(self, p);
                if (v >= 0) {
                    if (v <= off + 0x666) {
                        if (func_ov009_0226321c(self->unk_4C, &a, &b) != 0) {
                            if (func_020e8b4c(b, ent->unk_8E) <= 0x1100) {
                                c.x = p->x;
                                c.y = p->y;
                                c.z = p->z;
                                c.y = c.y + off;
                                d.x = c.x;
                                d.y = c.y;
                                d.z = c.z;
                                d.x = d.x - FX_MulFunc(self->unk_28, 0x2000);
                                d.z = d.z - FX_MulFunc(self->unk_30, 0x2000);
                                if (func_0202f904(self, &e, &c, &d) != 0) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
