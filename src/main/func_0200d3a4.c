/* func_0200d3a4 @ 0x0200d3a4, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200e9a8(void *self, void *loc, s32 *x, s32 *y, s16 *v);
extern int func_020b65c4(void);
extern int FX_MulFunc(s32 a, s32 b);
extern int func_0200e93c(void *self, s32 dx, s32 dy, s32 sum, s32 v, s16 *arr);
extern void func_020113bc(s16 *p, s32 v);
extern void func_020110a0(void *self, s16 *p);
extern void func_02011490(s32 *p, s32 val);

typedef struct UnkStruct_0200d3a4 {
    u8 pad_00[0x5c];
    s32 unk_5C;
    u8 pad_60[4];
    s32 unk_64;
    u8 pad_68[0x26];
    s16 unk_8E;
} UnkStruct_0200d3a4;

int func_0200d3a4(UnkStruct_0200d3a4 *self)
{
    struct {
        u8 id;
        u8 pad;
        s16 v;
        s16 arr[2];
        s32 x;
        s32 y;
    } loc;
    s32 dx, dy, sum, ret;

    if (func_0200e9a8(self, &loc, &loc.x, &loc.y, &loc.v) == 0) {
        return 0;
    }
    if (func_020b65c4() != loc.id) {
        return 0;
    }

    dx = loc.x - self->unk_5C;
    dy = loc.y - self->unk_64;
    sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);

    ret = func_0200e93c(self, dx, dy, sum, loc.v, loc.arr);
    if (ret == 0) {
        loc.arr[1] = self->unk_8E;
        func_020113bc(&loc.arr[1], loc.v);
        func_020110a0(self, &loc.arr[1]);
        func_02011490(&self->unk_5C, loc.x);
        func_02011490(&self->unk_64, loc.y);
    }
    return ret;
}
