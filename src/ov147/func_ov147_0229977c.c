/* func_ov147_0229977c @ 0x0229977c, 0x70 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229977c {
    u8 pad_00[0x40];
    void *unk_40;
};

struct Cfg {
    u8 *arrA;
    u8 *arrB;
    u8 count;
};

extern void *func_0206837c(void *arg);
extern void func_020ab670(void *ctx, int a, int b);
extern void func_020ab628(void *ctx, int i, u8 *pair, int c4, u8 *p5, int c6, int c7);
extern void func_020ab5f8(void *ctx);
extern void func_02068388(void *arg, int flag);

void func_ov147_0229977c(struct UnkStruct_0229977c *obj, struct Cfg *cfg)
{
    void *base;
    void *ctx;
    int zero1;
    int zero2;
    u8 pair[2];
    u8 *arrA;
    u8 *arrB;
    u8 count;
    int i;
    u8 b0;
    int flag;

    base = obj->unk_40;
    ctx = func_0206837c(base);

    arrA = cfg->arrA;
    arrB = cfg->arrB;
    count = cfg->count;

    func_020ab670(ctx, count, count - 1);

    zero1 = 0;
    zero2 = 0;

    for (i = 0; i < count; i++) {
        flag = zero1;
        b0 = arrA[i];
        if (b0 == 0x12 || b0 <= 1) {
            flag = 1;
        }
        pair[0] = b0;
        pair[1] = arrB[i];
        func_020ab628(ctx, i, pair, 1, &pair[1], zero2, flag);
    }

    func_020ab5f8(ctx);
    func_02068388(base, 1);
}
