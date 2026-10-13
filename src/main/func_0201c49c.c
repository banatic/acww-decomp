/* func_0201c49c @ 0x0201c49c, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 m[3][3];
} MtxFx33;
typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 *unk_00;
    u8 *unk_04;
    u8 pad_08[0x24 - 0x08];
    void *unk_24;
    u8 pad_28[0xb4 - 0x28];
    u8 *unk_B4;
    u8 pad_B8[0xd4 - 0xb8];
    u8 *unk_D4;
} UnkStruct_0201c49c;

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_020b66d8(void);
extern int func_020b6708(void);
extern void func_02054f68(UnkStruct_0201c49c *s, int k);
extern void MTX_RotY33_(MtxFx33 *d, fx32 s, fx32 c);
extern void MTX_RotX33_(MtxFx33 *d, fx32 s, fx32 c);
extern void MTX_Concat33(MtxFx33 *a, MtxFx33 *b, MtxFx33 *d);
extern int func_0203f844(Vec *a, Vec *b);
extern int func_0203f758(void);
extern void func_02054394(void *p, UnkStruct_0201c49c *s);
extern void func_0201c48c(void);
extern s16 FX_SinCosTable_[];
extern int data_020c8150;

void func_0201c49c(UnkStruct_0201c49c *self)
{
    u16 w[2];
    MtxFx33 mx;
    MtxFx33 my;
    Vec v1;
    MtxFx33 mz;
    Vec v2;
    u8 *e;
    u8 *q;
    Vec *vp;
    int kind;
    int ok;
    int t;
    int k;
    int a;

    kind = self->unk_00[1];
    e = *(u8 **) (self->unk_04 + 0x2c);
    if (e != 0) {
        if (func_0204bcdc(e + 0xea) != 0) {
            w[0] = 0xd011;
            t = func_0204bc64(e + 0xea);
            ok = (t == func_0204bc64(&w[0])) ? 1 : 0;
        } else {
            ok = (*(u16 *) (e + 0xea) == 0xd011) ? 1 : 0;
        }
        if (ok == 0) {
            goto reset;
        }
        if (func_020b66d8() != 0 && func_020b6708() == 1) {
            goto reset;
        }
        if (kind == 0x10) {
            u8 *hdr = self->unk_D4;
            u8 *sec = hdr + *(u16 *) (hdr + 6);
            u8 *ent = sec + *(u16 *) sec * kind;
            u8 *rec = hdr + *(int *) (ent + 4);
            Vec *sv = (Vec *) (rec + 4);
            u8 *dst = self->unk_B4;
            *(int *) (dst + 0x4c) = sv->x;
            *(int *) (dst + 0x50) = sv->y;
            *(int *) (dst + 0x54) = sv->z;
        }
        goto after;
    reset:
        func_02054f68(self, 0x800);
    after:;
    }
    if (kind == data_020c8150 && e != 0 && *(u8 *) (e + 0x3b0) < 6) {
        MtxFx33 *cur = (MtxFx33 *) (self->unk_B4 + 0x28);
        a = *(s16 *) (e + 0x3ca);
        if (a != 0) {
            k = (int) (u16) a >> 4;
            MTX_RotY33_(&my, FX_SinCosTable_[k * 2], FX_SinCosTable_[k * 2 + 1]);
            MTX_Concat33(cur, &my, cur);
        }
        a = *(s16 *) (e + 0x3d2);
        if (a != 0) {
            k = (int) (u16) a >> 4;
            MTX_RotX33_(&mx, FX_SinCosTable_[k * 2], FX_SinCosTable_[k * 2 + 1]);
            MTX_Concat33(cur, &mx, cur);
        }
    }
    if (kind == 0 && e != 0) {
        if (func_0204bcdc(e + 0xea) != 0) {
            w[1] = 0xd016;
            t = func_0204bc64(e + 0xea);
            ok = (t == func_0204bc64(&w[1])) ? 1 : 0;
        } else {
            ok = (*(u16 *) (e + 0xea) == 0xd016) ? 1 : 0;
        }
        if (ok != 0) {
            u8 *obj = self->unk_B4;
            u8 *base = obj;
            q = base + 0x28;
            vp = (Vec *) (obj + 0x4c);
            v1.x = vp->x;
            v1.y = vp->y;
            v1.z = vp->z;
            v2.x = vp->x;
            v2.y = vp->y;
            v2.z = vp->z;
            t = func_0203f844(&v1, &v2);
            vp->z = v1.z;
            vp->y = v1.y - func_0203f758();
            if (t != 0) {
                k = (int) (u16) t >> 4;
                MTX_RotX33_(&mz, FX_SinCosTable_[k * 2], FX_SinCosTable_[k * 2 + 1]);
                MTX_Concat33((MtxFx33 *) q, &mz, (MtxFx33 *) q);
            }
        }
    }
    if (e != 0) {
        e = e + 0xec;
        func_02054394(e, self);
    }
    self->unk_24 = (void *) func_0201c48c;
    *(u8 *) ((u8 *) self + 0x92) = 3;
}
