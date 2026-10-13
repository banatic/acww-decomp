/* func_ov142_02299c64 @ 0x02299c64, 0x2f8 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xc0 - 0xa8];
    volatile unsigned char unk_C0;
} UnkStruct_02299c64;

extern void func_ov142_02299fa4(UnkStruct_02299c64 *);
extern void func_ov142_02299f5c(UnkStruct_02299c64 *);
extern void func_ov142_0229a07c(UnkStruct_02299c64 *);
extern int func_ov142_0229a6d8(UnkStruct_02299c64 *);
extern void func_ov142_0229a05c(UnkStruct_02299c64 *);
extern void func_ov142_02299f8c(UnkStruct_02299c64 *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

int func_ov142_02299c64(UnkStruct_02299c64 *self, void *pad)
{
    unsigned char old = self->unk_C0;

    if (pad == 0) {
        return 0;
    }

    if (old <= 8) {
        if (func_ov002_0220889c(pad)) {
            func_ov142_02299fa4(self);
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C0 != 0) {
                self->unk_C0 = self->unk_C0 - 1;
            }
        } else if (func_ov002_022088bc(pad)) {
            if (self->unk_C0 < 8) {
                self->unk_C0 = self->unk_C0 + 1;
            }
        }
    } else if (old >= 9 && old <= 0x11) {
        if (func_ov002_022088ac(pad)) {
            func_ov142_02299f5c(self);
        } else if (func_ov002_0220889c(pad)) {
            func_ov142_0229a07c(self);
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C0 > 9) {
                self->unk_C0 = self->unk_C0 - 1;
                if (self->unk_C0 == 9) {
                    int t = self->unk_A0 & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 - t;
                    }
                }
            } else {
                if (self->unk_A0 >= 0x10) {
                    self->unk_A0 = self->unk_A0 - 0x10;
                    return 1;
                }
            }
        } else if (func_ov002_022088bc(pad)) {
            int n = self->unk_A4;
            if (n == 0) {
                if (self->unk_C0 < func_ov142_0229a6d8(self) + 8) {
                    self->unk_C0 = self->unk_C0 + 1;
                }
            } else {
                if (self->unk_C0 < 0x10) {
                    self->unk_C0 = self->unk_C0 + 1;
                } else {
                    int a = self->unk_A0;
                    int t = a & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 + (0x10 - t);
                        return 1;
                    }
                    if (a <= n - 0x10) {
                        self->unk_A0 = self->unk_A0 + 0x10;
                        return 1;
                    }
                }
            }
        }
    } else {
        switch (old) {
            case 0x13:
                if (func_ov002_022088ac(pad)) {
                    func_ov142_0229a05c(self);
                } else if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x12;
                }
                break;
            case 0x12:
                if (func_ov002_022088ac(pad)) {
                    func_ov142_0229a05c(self);
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x13;
                }
                break;
            case 0x14:
                if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x15;
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x16;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c(self);
                }
                break;
            case 0x15:
                if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x14;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c(self);
                }
                break;
            case 0x16:
                if (func_ov002_022088cc(pad)) {
                    self->unk_C0 = 0x14;
                } else if (func_ov002_0220889c(pad)) {
                    self->unk_C0 = 0x12;
                } else if (func_ov002_022088ac(pad)) {
                    func_ov142_02299f8c(self);
                } else if (func_ov002_022088bc(pad)) {
                    self->unk_C0 = 0x13;
                }
                break;
        }
    }

    if (old != self->unk_C0) {
        return 1;
    }
    return 0;
}
