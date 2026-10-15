/* func_ov068_0226863c @ 0x0226863c, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020164a0(void *p, int x);
extern int func_02019de8(void *p);
extern int func_ov068_0226ccb0(void *self, void *ctx);
extern void func_ov068_0226cce8(void *self, void *ctx, int x);
extern int func_02012508(void *a, void *b, void *c, int d, int e);

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
