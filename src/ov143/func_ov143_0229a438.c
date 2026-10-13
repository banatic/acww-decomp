/* func_ov143_0229a438 @ 0x0229a438, 0xa8 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkSelf {
    unsigned char pad[0xa4];
    unsigned char unk_A4;
} UnkSelf;

extern int func_ov002_02208014(UnkSelf *self);
extern void func_ov002_02208008(UnkSelf *self);
extern int func_ov002_02207fe4(UnkSelf *self);
extern int func_ov002_02207fd8(UnkSelf *self);
extern void func_ov143_0229a2c8(UnkSelf *self);
extern void func_ov143_02299fd0(UnkSelf *self);
extern void func_ov143_02299f6c(UnkSelf *self);
extern void func_ov143_0229a014(UnkSelf *self);
extern void func_ov143_0229a3e0(UnkSelf *self);
extern void func_ov143_0229a404(UnkSelf *self);

extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;

void func_ov143_0229a438(UnkSelf *self)
{
    unsigned char old;
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov143_0229a2c8(self);
        return;
    }

    old = self->unk_A4;
    func_ov002_02208008(self);

    if (func_ov002_02207fe4(self) != 0) {
        self->unk_A4 = 0x14;
    } else if (func_ov002_02207fd8(self) != 0) {
        self->unk_A4 = 0x15;
    }

    if (old != self->unk_A4) {
        func_ov143_02299fd0(self);
        return;
    }

    flags = data_021fbe40.flags;

    if ((flags & 1) != 0) {
        func_ov143_02299f6c(self);
        return;
    }

    if ((flags & 2) != 0) {
        func_ov143_0229a014(self);
        func_ov143_0229a3e0(self);
        return;
    }

    if ((flags & 8) != 0) {
        func_ov143_0229a014(self);
        func_ov143_0229a404(self);
    }
}
