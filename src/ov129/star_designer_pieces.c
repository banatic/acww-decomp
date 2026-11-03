/* star_designer_pieces: 2 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229b85c @ 0x0229b85c, 0xb4 bytes, Thumb
 * func_ov129_0229b800 @ 0x0229b800, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xaa];
    u16 unk_AA;
    u8 pad_AC[4];
    u8 unk_B0;
    u8 pad_B1[2];
    u8 unk_B3;
} UnkStruct_0229b85c;

typedef struct UnkStruct_0229b800 {
    u8 pad_00[0xb1];
    u8 unk_B1;
} UnkStruct_0229b800;

extern unsigned short func_ov129_0229bbd8(UnkStruct_0229b85c *self, int previous, unsigned char current);
extern int func_ov129_0229bca4(UnkStruct_0229b85c *self, u8 b0);
extern int func_ov129_0229bd1c(UnkStruct_0229b85c *self);
extern void func_ov129_0229b9a0(UnkStruct_0229b85c *self);
extern int func_ov129_0229ba2c(UnkStruct_0229b85c *self);
extern int func_ov129_0229b9d8(UnkStruct_0229b800 *self);
extern int func_ov129_0229b910(UnkStruct_0229b800 *self);
extern void func_0200467c(int a);
extern void func_ov129_0229bee4(UnkStruct_0229b800 *self, int a);

int func_ov129_0229b85c(UnkStruct_0229b85c *self)
{
    int idx;
    int c;
    int v;
    int r;

    if (self->unk_B0 == 0xff) {
        goto L_ba;
    }
    if (self->unk_B3 == self->unk_B0) {
        goto L_ba;
    }
    if (self->unk_B3 != 0xff) {
        goto L_880;
    }
    self->unk_B3 = self->unk_B0;
    return 1;

L_880:
    idx = func_ov129_0229bbd8(self, self->unk_B3, self->unk_B0);
    if (idx == 0xffff) {
        goto L_89c;
    }
    if (((u8 *) self + idx)[0x2f98] != 3) {
        goto L_89c;
    }
    self->unk_AA = (u16) idx;
    goto L_ba;

L_89c:
    if (func_ov129_0229bca4(self, self->unk_B0) != 0) {
        self->unk_B3 = self->unk_B0;
        return 1;
    }

L_ba:
    c = self->unk_AA;
    if (c == 0xffff) {
        goto L_8fa;
    }
    v = ((u8 *) self + c)[0x2f98];
    if (v == 2) {
        goto L_8f2;
    }
    if (v != 3) {
        goto L_8fa;
    }
    r = func_ov129_0229bd1c(self);
    *((u16 *) ((u8 *) self + 0x2f78 + 2 * r)) = self->unk_AA;
    func_ov129_0229b9a0(self);
    return 2;

L_8f2:
    return func_ov129_0229ba2c(self);

L_8fa:
    return 0;
}

int func_ov129_0229b800(UnkStruct_0229b800 *self)
{
    int r = 0;

    switch (self->unk_B1) {
        case 0:
            r = func_ov129_0229b9d8(self);
            break;
        case 1:
            r = func_ov129_0229b910(self);
            break;
        case 2:
            r = func_ov129_0229b85c((UnkStruct_0229b85c *) self);
            break;
    }

    if (r == 1) {
        func_0200467c(0x880);
    }
    switch (r) {
        case 1:
        case 2:
            func_ov129_0229bee4(self, 1);
            break;
    }
    return r;
}
