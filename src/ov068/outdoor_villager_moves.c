/* outdoor_villager_moves: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022686c4 @ 0x022686c4, 0x94 bytes, Thumb
 * func_ov068_0226863c @ 0x0226863c, 0x88 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0226863c {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

struct Context {
    u8 pad_00[0x190];
    u32 unk_190;
    u8 pad_194[0x1a0];
    u8 unk_334[0x230];
    u8 unk_564[0x450];
    u8 unk_9B4[0x3c];
    u8 unk_9F0;
};

extern int func_020164a0(void *p, int n);
extern int func_02019de8(void *p);
extern int func_02012508(void *a, void *b, void *c, int d, int e);
extern int func_ov068_0226ccb0(void *a, void *b);
extern void func_ov068_0226cce8(void *a, void *b, int c);
extern int func_020121f8(void *p);
extern char *func_020121e0(void *p, int n);

void func_ov068_022686c4(unsigned char *self, void *work)
{
    unsigned short h;

    if (func_020164a0((char *) work + 0x334, 0) != 0xd6) {
        return;
    }

    if (func_02019de8((char *) work + 0x564) != 0) {
        h = 0xfff1;
        func_02012508((char *) work + 0x9b4, work, &h, 0, 3);
        self[0x1c] = 2;
        if (func_ov068_0226ccb0(self, work) == 0) {
            func_ov068_0226cce8(self, work, 0);
        }
    } else {
        int n;

        n = func_020121f8((char *) work + 0x9b4);
        if (n != 0) {
            n -= 0x249;
            if (n < 0) {
                n = 0;
            }
        }
        func_020121e0((char *) work + 0x9b4, n);
    }
}

void func_ov068_0226863c(struct UnkStruct_0226863c *self, struct Context *ctx)
{
    if (func_020164a0(ctx->unk_334, 0) == 0xcd) {
        if (func_02019de8(ctx->unk_564) != 0) {
            self->unk_1C = 2;
            if (func_ov068_0226ccb0(self, ctx) == 0) {
                func_ov068_0226cce8(self, ctx, 0);
            }
        } else {
            if (((ctx->unk_190 << 4) >> 16) == 5) {
                u16 val = 0xfff1;
                func_02012508(ctx->unk_9B4, ctx, &val, 0, 3);
                ctx->unk_9F0 = 0;
            }
        }
    }
}
