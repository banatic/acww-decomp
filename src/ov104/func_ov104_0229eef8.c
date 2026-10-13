/* func_ov104_0229eef8 @ 0x0229eef8, 0x140 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb0];
    u16 flag;
    u8 pad_B2[0x2d02];
    u8 sub[1];
} UnkStruct_0229eef8;

extern int func_ov104_0229c364(UnkStruct_0229eef8 *self, int a);
extern void func_ov104_0229cb04(UnkStruct_0229eef8 *self);
extern void func_0206fc4c(int a);
extern void func_ov104_0229caa0(UnkStruct_0229eef8 *self, int a);
extern int func_0206f990(int a);
extern int func_0206f8e0(int a);
extern int func_0206f860(int a);
extern void func_0209aa80(void);
extern void func_0209788c(void);
extern void func_020ee470(UnkStruct_0229eef8 *self);
extern int func_020978bc(void *p, int a);
extern int func_020984e8(int a);
extern int func_02099020(int a, int b);
extern int func_ov104_0229c648(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c944(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c870(UnkStruct_0229eef8 *self, void *p, int a);
extern int func_ov104_0229c7e8(UnkStruct_0229eef8 *self, void *p);
extern int func_ov104_0229c6a0(UnkStruct_0229eef8 *self, void *p);
extern void func_02097b24(int a);

int func_ov104_0229eef8(UnkStruct_0229eef8 *self)
{
    int r;

    r = func_ov104_0229c364(self, 0x400);
    if (r != 0) {
        func_ov104_0229cb04(self);
        func_0206fc4c(0);
        goto tail;
    }

    r = func_ov104_0229c364(self, 0x800);
    if (r != 0) {
        r = func_ov104_0229c364(self, 0x1000);
        if (r != 0) {
            return 1;
        }

        if (self->flag & 4) {
            func_0206fc4c(0);
        } else {
            func_0206fc4c(1);
        }
        func_ov104_0229caa0(self, 1);
        func_0206f990(self->flag);
        goto tail;
    } else {
        int r4;
        int r9;
        int r10;
        int z;

        func_0206fc4c(1);
        r4 = 0;
        r9 = func_020978bc(self->sub, 0xa);
        if (r9 <= 0) {
            r4 = 4;
        }

        r10 = func_02099020(func_020984e8(r9), 1);
        if (r10 != 0) {
            r4 |= func_ov104_0229c648(self, self->sub);
        }
        r4 |= func_ov104_0229c944(self, self->sub);
        r4 |= func_ov104_0229c870(self, self->sub, 0);

        if (r4 & 4) {
            func_0206fc4c(0);
        } else if (r4 & 0x10) {
            func_02097b24(0x10);
            r4 |= func_ov104_0229c7e8(self, self->sub);
            if (r4 & 0x20) {
                r4 |= func_ov104_0229c6a0(self, self->sub);
            }
        }

        func_ov104_0229caa0(self, 0);
        z = func_0206f8e0(func_0206f990(r4));
        if (z == 1 || func_0206f860(z) != 0) {
            func_0209aa80();
        }
    }

tail:
    func_0209788c();
    func_020ee470(self);
    return 1;
}
