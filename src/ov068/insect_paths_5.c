/* insect_paths_5: 7 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022710e4 @ 0x022710e4, 0x7c bytes, Thumb
 * func_ov068_02271068 @ 0x02271068, 0x7c bytes, Thumb
 * func_ov068_02270e80 @ 0x02270e80, 0x1e8 bytes, Thumb
 * func_ov068_02270df8 @ 0x02270df8, 0x88 bytes, Thumb
 * func_ov068_02270d54 @ 0x02270d54, 0xa4 bytes, Thumb
 * func_ov068_02270d24 @ 0x02270d24, 0x30 bytes, Thumb
 * func_ov068_02270b00 @ 0x02270b00, 0x224 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x232];
    short b;
    char pad_234[6];
    short a;
    char pad_23C[0x10];
    unsigned char flag;
} UnkStruct_02271068;

typedef struct {
    unsigned char pad_00[0xf4];
    unsigned int unk_F4;
    unsigned char pad_F8[0x130 - 0xf8];
    unsigned char unk_130[0x204 - 0x130];
    unsigned char unk_204[0x210 - 0x204];
    unsigned int unk_210[3];
    unsigned int unk_21C;
    unsigned char pad_220[0x232 - 0x220];
    unsigned short unk_232;
    unsigned char pad_234[0x23a - 0x234];
    unsigned short unk_23A;
    unsigned char pad_23C[0x251 - 0x23c];
    unsigned char unk_251;
} UnkStruct_02270df8;

struct UnkStruct_02270d54 {
    u8 pad_00[0x204];
    u32 unk_204;
    u8 pad_208[4];
    u32 unk_20C;
    u32 unk_210;
    u32 unk_214;
    u8 pad_218[0x35];
    u8 unk_24D;
};

extern int func_ov003_02219cb4(int *p);
extern int FX_Div(int a, int b);
extern int func_020644cc(int n);
extern void func_ov003_022353a4(void *self, int a, int b);
extern void func_ov003_02234cc4(void *self);
extern int func_020ea990(void *a, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_020959ac(void);
extern void func_ov003_0223597c(int *out, int ang);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_02234dac(void *self, int a, int b, int c);
extern char *func_020961a8(int);
extern void *func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(void *, int, int);
extern void func_02035684(int, int, int);
extern int func_020e8bb0(void *addr, u32 a, u32 b, u32 c, u32 d);
extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);
extern int func_02095ea4(int, int);
extern int func_02070070(void);
extern int func_020e8870(void *buf, int val, int k);
extern void func_ov068_02270a64(void *a, void *b, int c);

int func_ov068_022710e4(int *self)
{
    int *p;
    int *q;
    p = (int *) ((char *) self + 0x204);
    if (func_ov003_02219cb4(p) && (q = (int *) func_020961a8(4)) != 0) {
        if (*p < q[23]) {
            *p = *p - FX_Div(0x14000, 0x10000);
        } else {
            *p = *p + FX_Div(0x14000, 0x10000);
        }
        if (func_020644cc(0x64) > 50) {
            *((char *) self + 0x24c) = 0;
        } else {
            *((char *) self + 0x24c) = 1;
        }
        return 1;
    }
    return 0;
}

int func_ov068_02271068(UnkStruct_02271068 *self)
{
    short a = self->a;
    short b = self->b;
    short timer = b - 1;

    if (timer < 0) {
        return 1;
    }
    if (self->flag != 0) {
        if (a > 2730) {
            self->flag = 0;
        }
    } else if (a < -2730) {
        self->flag = 1;
    }
    if (self->flag != 0) {
        a += 546;
    } else {
        a -= 546;
    }
    self->a = a;
    self->b = timer;
    return 0;
}

void func_ov068_02270e80(char *self, short *p)
{
    int d1;
    unsigned int rnd;
    char *o;
    int v3[3];
    int *p204;
    short cnt;
    short d;
    short lim;
    short na;
    unsigned char *q;

    o = (char *) func_020961a8(4);
    p204 = (int *) (self + 0x204);
    d = 0;
    v3[0] = d;
    v3[1] = d;
    v3[2] = d;
    *p = *p + 0xaaa;
    func_ov003_022353a4(self, d, 1);
    func_ov003_02234cc4(self);
    if (o == 0) {
        goto done;
    }
    o = (char *) ((int) o + 0x5c);
    d1 = func_020ea990(o, p204);
    rnd = (unsigned char) func_020644cc(0x64);
    cnt = *(unsigned char *) (self + 0x254);
    d = *(short *) (self + 0x23a);
    d = func_0200322c(p204, o) - d;
    if (*(unsigned char *) (self + 0x24a) != 0) {
        if (cnt < 0xfe) {
            cnt = cnt + 1;
            *(unsigned char *) (self + 0x254) = cnt;
        }
        if (cnt >= 0x3c) {
            if (d1 < FX_Div(0x1000, 0x10000)) {
                if (func_020959ac() != 0) {
                    *(unsigned char *) (self + 0x24a) = 0;
                    *p = 0;
                    *(unsigned char *) (self + 0x251) = 9;
                }
            }
        }
    }
    if (d1 < 0x2000) {
        if (d1 < FX_Div(0x1000, 0x4000)) {
            if (*(unsigned char *) (self + 0x24a) == 0) {
                *(unsigned char *) (self + 0x24a) = 1;
                *(unsigned char *) (self + 0x254) = 0;
            }
        }
        if (d >= -0x555 && d <= 0x555) {
            goto done;
        }
        if (d > 0 && rnd > 0xf) {
            d = 0x555;
            goto done;
        }
        if (d < 0 && rnd > 0xf) {
            d = -0x555;
            goto done;
        }
        d = 0;
    } else {
        if (d1 > FX_Div(0x1000, 0x2000)) {
            if (*(unsigned char *) (self + 0x24a) != 0 && cnt < 0x3c) {
                *(unsigned char *) (self + 0x24a) = 0;
                *(unsigned char *) (self + 0x254) = 0;
            }
        }
        lim = FX_Div(0x555, 0x4000);
        if (d >= (short) -lim && d <= lim) {
            goto done;
        }
        if (d > 0 && rnd > 0x14) {
            d = lim;
            goto done;
        }
        if (d < 0 && rnd > 0x14) {
            d = (short) -lim;
            goto done;
        }
        d = 0;
    }
done:
    na = d + *(short *) (self + 0x23a);
    *(short *) (self + 0x23a) = na;
    func_ov003_0223597c(v3, na);
    p204[0] = p204[0] + FX_MulFunc(v3[0], 0x8000);
    p204[2] = p204[2] + FX_MulFunc(v3[2], 0x8000);
    func_ov003_02234dac(self, *p, 0x2800, (func_020644cc(8) + 0x12) << 12);
}

void func_ov068_02270df8(UnkStruct_02270df8 *obj)
{
    char *ret;
    unsigned int *arr;
    void *p;
    int val;

    ret = func_020961a8(4);
    arr = obj->unk_210;

    if (ret != 0) {
        val = func_0200322c(&obj->unk_204, ret + 0x5c);
        obj->unk_23A = (unsigned short) val;
    }

    p = func_0209d088(obj->unk_130);
    NNS_G3dMdlSetMdlAlpha(p, 0, 0x1f);

    obj->unk_251 = 2;
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;
    obj->unk_232 = 0x28;
    obj->unk_F4 = 0x2d000;
    obj->unk_21C = 0xf0;

    func_02035684(25, 0, 0);
}

void func_ov068_02270d54(struct UnkStruct_02270d54 *p)
{
    char *r = (char *) p + 0x204;
    u32 *q = (u32 *) ((char *) p + 0x210);
    u32 tmp = q[0];
    int flag = 0;

    if (func_020e8bb0(&tmp, 0x1000, 0x200, 0x1000, 0x19a) == 0) {
        flag = 1;
    }

    q[0] = tmp;
    q[1] = tmp;
    q[2] = tmp;

    if (func_020e8bb0(r + 4, 0x2800, 0x199, 0x1000, 0x400) == 0 && flag) {
        *((u8 *) p + 0x251) = 0;
        q[0] = 0x1000;
        q[1] = 0x1000;
        q[2] = 0x1000;
        func_02035624(0x19);
        func_020356c4(0x1a, 0x3f, 0x7f, 0);
        func_02095ea4(0x1a, 4);
    }
}

void func_ov068_02270d24(int *r0, int r1)
{
    if (r1 == 0) {
        r0[2] -= 0x52;
    } else {
        r0[2] += 0x52;
    }

    if (r0[2] < 0x1000) {
        r0[2] = 0x1000;
    } else if (r0[2] > 0x2000) {
        r0[2] = 0x2000;
    }
}

void func_ov068_02270b00(u8 *self)
{
    char *ret;
    int *f204;
    int sum;
    u8 *f256;
    char *retOff;
    int local2;
    int local3;
    int startVal;
    s16 buf;
    int vecA[3];
    int vecB[3];

    ret = func_020961a8(4);
    f204 = (int *) (self + 0x204);

    startVal = *(s16 *) (self + 0x23a);
    buf = (s16) startVal;

    {
        s16 f232 = *(s16 *) (self + 0x232);
        f256 = self + 0x256;

        if (f232 > 0) {
            *(s16 *) (self + 0x232) = f232 - 1;
        } else if (func_02070070() != 0) {
            buf = buf + 0x1554;
            *(s16 *) (self + 0x23a) = buf;
            func_ov003_0223597c((int *) vecA, buf);

            f204[0] += (fx32) FX_MulFunc((fx32) 0x23000, (fx32) vecA[0]);
            f204[2] += (fx32) FX_MulFunc((fx32) 0x23000, (fx32) vecA[2]);

            func_ov068_02270a64(self + 0x210, self + 0x50, startVal - buf);
            *f256 = 9;
            return;
        }
    }

    if (ret == 0) {
        return;
    }

    retOff = ret + 0x5c;
    local2 = func_0200322c(f204, retOff);
    sum = *(u8 *) (self + 0x257) + *(int *) (self + 0x21c);
    local3 = func_020ea990(f204, retOff);

    if (local3 < 0x1000) {
        self[0x251] = 3;
        *(s16 *) (self + 0x242) = 0;
        return;
    }

    if (*f256 != 0) {
        *f256 -= 1;
        func_020e8870(&buf, local2, 0xe38);
    } else if (sum < 0xfa) {
        func_020e8870(&buf, local2, 0x93e);
    } else if (sum < 0x104) {
        func_020e8870(&buf, local2, 0x7d2);
    } else {
        func_020e8870(&buf, local2, 0x666);
    }

    {
        int d = (local2 - buf) / 182;
        if (d < 0) {
            d = -d;
        }
        if ((u8) d > 15 && sum > 0xb4) {
            sum -= 2;
            *(int *) (self + 0x21c) = sum;
        } else if (sum < 0x122) {
            sum += 7;
            *(int *) (self + 0x21c) = sum;
        }
    }

    *(s16 *) (self + 0x23a) = buf;

    func_ov003_0223597c((int *) vecB, buf);

    if (local3 > 0xe000) {
        int r6 = sum << 12;
        f204[0] += (fx32) FX_Div((fx32) ((fx32) FX_MulFunc((fx32) r6, (fx32) vecB[0])), (fx32) 0x3800);
        f204[2] += (fx32) FX_Div((fx32) ((fx32) FX_MulFunc((fx32) r6, (fx32) vecB[2])), (fx32) 0x3800);
    } else {
        int r6 = sum << 12;
        f204[0] += (fx32) FX_Div((fx32) ((fx32) FX_MulFunc((fx32) r6, (fx32) vecB[0])), (fx32) 0x5000);
        f204[2] += (fx32) FX_Div((fx32) ((fx32) FX_MulFunc((fx32) r6, (fx32) vecB[2])), (fx32) 0x5000);
    }

    func_ov068_02270a64(self + 0x210, self + 0x50, (startVal - buf) * 5);
}
