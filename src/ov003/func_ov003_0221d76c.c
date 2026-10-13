/* func_ov003_0221d76c @ 0x0221d76c, 0x1d0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
} Pair;
typedef struct {
    Pair p[6];
} Copy48;
struct UnkStruct_0221d76c;
extern u32 data_ov003_0223c8f8;
extern int data_ov003_0223c908[3];
extern int data_ov003_0223c8fc;
extern void *data_ov003_0223c928[];
extern void *data_021c9b1c;
extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void);
extern void func_01ffd070(void *, void *, void *);
extern void func_02003348(int, int, void *, int, void *);
extern int func_ov003_0221d5f4(void *);
extern int func_ov003_022203b8(void);
extern int func_ov003_022203c0(void);
extern int func_ov003_0221ffc0(int, int);
extern int func_ov003_0221ffb4(int, int);
extern void NNS_G3dBindMdlTex(void *, void *);
extern void NNS_G3dBindMdlPltt(void *, void *);
extern int func_ov003_0221fe9c(void *);
extern int func_ov003_0221d64c(void *);
extern int func_ov003_0221fea4(int, int);
extern int func_02055f2c(void *, int, int);
extern int func_ov003_0221feb4(void *);
extern int func_0205650c(void *, u32, void *);
extern int func_ov003_0221fea0(void *);
extern int func_02056424(void *, int, int, int, int, int);
extern int func_02055e00(void *);
extern int func_020563dc(void *, int);
struct UnkStruct_0221d76c {
    u8 pad_00[0x5c];
    u8 unk_5C;
    u8 pad_5D[0x136 - 0x5d];
    u16 type;
    u8 pad_138[0x198 - 0x138];
    u32 unk_198;
    u8 pad_19C[0x1a0 - 0x19c];
    u8 copySrc[48];
    u8 pad_1D0[0x2b4 - 0x1d0];
    u8 unk_2B4;
    u8 pad_2B5[0x310 - 0x2b5];
    u32 unk_310;
    u8 pad_314[0x318 - 0x314];
    u8 copyDst[48];
    u8 pad_348[0x36c - 0x348];
    u8 unk_36C;
};
int func_ov003_0221d76c(struct UnkStruct_0221d76c *self)
{
    int inRange = 0;
    unsigned int t;
    int idx;
    int r4;
    int val;
    int r7;
    u8 buf[8];
    void *p;
    int tmp1;
    int tmp2;
    int tmp3;
    int tmp4;
    int tmp5;
    int tmp6;
    int tmp7;
    int tmp8;
    t = self->type;
    if ((t >= 0x5001u) && (t <= 0x5008u)) {
        inRange = 1;
    }
    if (inRange) {
        idx = ((int) t) - 0x5001;
    } else {
        idx = -1;
    }
    if ((data_ov003_0223c8f8 & 1) == 0) {
        data_ov003_0223c908[0] = 0xffffe000;
        data_ov003_0223c908[1] = 0x1000;
        data_ov003_0223c908[2] = 0x2000;
        __register_global_object(&data_ov003_0223c908, func_020012dc, &data_ov003_0223c8fc);
        data_ov003_0223c8f8 |= 1;
    }
    func_01ffd070(buf, &self->unk_5C, &data_ov003_0223c908);
    func_02003348(0x18, idx, buf, 0, self);
    data_ov003_0223c928[idx] = self;
    val = func_ov003_0221d5f4(self);
    r4 = val;
    r7 = func_ov003_0221ffc0((int) func_ov003_022203c0(), r4);
    r4 = func_ov003_0221ffb4((int) func_ov003_022203c0(), r4);
    p = (void *) self->unk_198;
    if (r7 != 0) {
        NNS_G3dBindMdlTex(p, (void *) r7);
    }
    if (r4 != 0) {
        NNS_G3dBindMdlTex(p, (void *) r4);
        NNS_G3dBindMdlPltt(p, (void *) r4);
    }
    if (func_ov003_0221fe9c((void *) func_ov003_022203b8()) != 0) {
        r4 = func_ov003_0221d64c(self) >> 2;
        tmp1 = func_ov003_0221fea4((int) func_ov003_022203b8(), r4);
        if (func_02055f2c(&self->unk_2B4, tmp1, 0) != 0) {
            tmp2 = func_ov003_0221fea4((int) func_ov003_022203b8(), r4);
            tmp3 = func_ov003_0221feb4((void *) func_ov003_022203b8());
            NNS_G3dBindMdlTex((void *) tmp2, (void *) tmp3);
            tmp4 = func_ov003_0221fea4((int) func_ov003_022203b8(), r4);
            tmp5 = func_ov003_0221feb4((void *) func_ov003_022203b8());
            NNS_G3dBindMdlPltt((void *) tmp4, (void *) tmp5);
            if (func_0205650c(&self->unk_36C, self->unk_310, data_021c9b1c) != 0) {
                tmp6 = func_ov003_0221fea0((void *) func_ov003_022203b8());
                tmp7 = func_ov003_0221feb4((void *) func_ov003_022203b8());
                func_02056424(&self->unk_36C, tmp6, tmp7, 0, 0x1000, 0);
                tmp8 = func_02055e00(&self->unk_2B4);
                func_020563dc(&self->unk_36C, tmp8);
                *((Copy48 *) self->copyDst) = *((Copy48 *) self->copySrc);
            }
        }
    }
    return 1;
}
