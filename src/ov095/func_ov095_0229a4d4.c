/* func_ov095_0229a4d4 @ 0x0229a4d4, 0x24c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x43 - 0x2c];
    unsigned char unk_43;
} UnkStruct_0229a4d4;

extern int func_ov095_02299bb4(UnkStruct_0229a4d4 *);
extern void func_ov095_0229a1d4(UnkStruct_0229a4d4 *);
extern void func_ov095_0229aa3c(UnkStruct_0229a4d4 *);
extern void func_ov095_0229a9d4(UnkStruct_0229a4d4 *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

void func_ov095_0229a4d4(UnkStruct_0229a4d4 *self, void *pad)
{
    if (func_ov095_02299bb4(self)) {
        return;
    }

    if (self->unk_28 < 0x70) {
        return;
    }

    if (self->unk_28 <= 0x8d) {
        int n = self->unk_28 - 0x70;
        int x = n % 10;
        int y = n / 10;

        if (func_ov002_022088cc(pad)) {
            if (y > 0) {
                y--;
                self->unk_28 = self->unk_28 - 10;
            } else {
                func_ov095_0229a1d4(self);
                return;
            }
        } else if (func_ov002_022088bc(pad)) {
            if (y < 2) {
                y++;
                self->unk_28 = self->unk_28 + 10;
            } else {
                self->unk_28 = 0x91;
                return;
            }
        }

        if (func_ov002_022088ac(pad)) {
            if (x > 0) {
                self->unk_28 = self->unk_28 - 1;
            } else {
                self->unk_43 = 1;
                if (y == 0) {
                    self->unk_28 = 0x8f;
                } else {
                    self->unk_28 = 0x90;
                }
            }
        } else if (func_ov002_0220889c(pad)) {
            if (x < 9) {
                self->unk_28 = self->unk_28 + 1;
            } else {
                if (y == 0) {
                    self->unk_28 = 0x8e;
                } else {
                    self->unk_28 = 0x90;
                }
            }
        }
        return;
    }

    switch (self->unk_28) {
        case 0x8e:
            if (func_ov002_022088cc(pad)) {
                func_ov095_0229a1d4(self);
            } else if (func_ov002_022088bc(pad)) {
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = 0x83;
                } else {
                    self->unk_28 = 0x90;
                }
            } else if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x79;
            } else if (func_ov002_0220889c(pad)) {
                self->unk_28 = 0x8f;
            }
            break;
        case 0x8f:
            if (func_ov002_022088cc(pad)) {
                func_ov095_0229a1d4(self);
            } else if (func_ov002_022088bc(pad)) {
                self->unk_28 = 0x90;
            } else if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x8e;
            } else if (func_ov002_0220889c(pad)) {
                self->unk_43 = 2;
                self->unk_28 = 0x70;
            }
            break;
        case 0x90:
            if (func_ov002_022088cc(pad)) {
                self->unk_28 = 0x8f;
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
                break;
            }
            if (func_ov002_022088bc(pad)) {
                func_ov095_0229aa3c(self);
                if (self->unk_28 != 0x90) {
                    break;
                }
            }
            if (func_ov002_022088ac(pad)) {
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x8d;
                } else {
                    self->unk_28 = 0x83;
                }
            } else if (func_ov002_0220889c(pad)) {
                self->unk_43 = 2;
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x84;
                } else {
                    self->unk_28 = 0x7a;
                }
            }
            break;
        case 0x91:
            if (func_ov002_022088cc(pad)) {
                self->unk_28 = 0x8a;
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
            } else if (func_ov002_0220889c(pad)) {
                func_ov095_0229aa3c(self);
            } else if (func_ov002_022088bc(pad)) {
                func_ov095_0229a9d4(self);
            }
            break;
    }
}
