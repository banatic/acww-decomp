/* insect_paths: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02270008 @ 0x02270008, 0x68 bytes, Thumb
 * func_ov068_0226fea4 @ 0x0226fea4, 0x164 bytes, Thumb
 * func_ov068_0226fe28 @ 0x0226fe28, 0x7c bytes, Thumb
 * func_ov068_0226fe00 @ 0x0226fe00, 0x28 bytes, Thumb
 */

#include "types.h"

#define FX_F32_TO_FX32(x) ((int) (((x) > 0) ? ((x) * 4096.0f + 0.5f) : ((x) * 4096.0f - 0.5f)))

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02270008;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct UnkStruct_0226fe28 {
    unsigned char pad_00[0x204];
    unsigned char unk_204;
    unsigned char pad_205[0x220 - 0x205];
    unsigned int unk_220;
    unsigned char pad_224[0x228 - 0x224];
    unsigned int unk_228;
    unsigned char pad_22C[0x240 - 0x22c];
    unsigned short unk_240;
    unsigned char pad_242[0x244 - 0x242];
    unsigned short unk_244;
    unsigned char pad_246[0x24a - 0x246];
    unsigned char unk_24A;
    unsigned char pad_24B[0x251 - 0x24b];
    unsigned char unk_251;
    unsigned char pad_252[0x254 - 0x252];
    unsigned char unk_254;
    unsigned char unk_255;
};

struct UnkStruct_0226fe00 {
    char pad_00[0x130];
    char unk_130[0x251 - 0x130];
    char unk_251;
};

extern int FX_Div(int a, int b);
extern int func_020644cc(int a);
extern void func_ov003_0223597c(VecFx32 *v, int ang);
extern int FX_MulFunc(int a, int b);
extern int func_0200322c(void *a, void *b);
extern void *func_0209d088(void *arg);
extern void NNS_G3dMdlSetMdlAlpha(void *dest, int value, int size);

void func_ov068_02270008(int mode, UnkStruct_02270008 *p)
{
    if (mode == 1 || mode == 4) {
        p->unk_00 += FX_Div(0xfffff000, 0x10000);
        p->unk_04 = FX_Div(0x10000, 0x10000);
        p->unk_08 += FX_Div(0xffffc000, 0x10000);
    } else {
        p->unk_04 = FX_Div(0x9000, 0x10000);
        p->unk_08 += FX_Div(0x3000, 0x10000);
    }
}

void func_ov068_0226fea4(u8 *self, s16 *buf, int step, int period, u8 limit, int scale)
{
    unsigned int r;
    int *p;
    VecFx32 v;
    int flag;

    flag = self[0x24b];
    r = (u8) func_020644cc(100);
    p = (int *) (self + 0x204);

    if (self[0x24f] % period == 0) {
        if (r > limit) {
            flag = (flag == 0) ? 1 : 0;
            self[0x24b] = flag;
        }
    }

    if (r > self[0x252]) {
        if (flag != 0) {
            *buf = *buf + step;
        } else {
            *buf = *buf - step;
        }
    }

    func_ov003_0223597c(&v, *buf);
    *(s16 *) (self + 0x23a) = *buf;

    if (self[0x24a] != 0) {
        float f = 1.25f;
        if (*(s8 *) (self + 0x24d) == 0xa || *(s8 *) (self + 0x24d) == 0x33) {
            f = 1.5f;
        }
        p[0] = p[0] + FX_MulFunc(FX_MulFunc(FX_F32_TO_FX32(f), scale), v.x);
        p[2] = p[2] + FX_MulFunc(FX_MulFunc(FX_F32_TO_FX32(f), scale), v.z);
    } else {
        p[0] = p[0] + FX_MulFunc(scale, v.x);
        p[2] = p[2] + FX_MulFunc(scale, v.z);
    }
}

void func_ov068_0226fe28(struct UnkStruct_0226fe28 *self, int *count_ptr)
{
    if (*count_ptr <= 0) {
        return;
    }
    if (self->unk_24A != 0) {
        return;
    }
    if (self->unk_254 < self->unk_255) {
        return;
    }

    self->unk_240 = func_0200322c(count_ptr, &self->unk_204);
    self->unk_244 = 0x14 * (func_020644cc(4) + 7);
    self->unk_251 = 7;
    self->unk_24A = 1;
    self->unk_220 = self->unk_228;
}

void func_ov068_0226fe00(struct UnkStruct_0226fe00 *obj)
{
    NNS_G3dMdlSetMdlAlpha(func_0209d088(&obj->unk_130), 0, 0x1f);
    obj->unk_251 = 0x12;
}
