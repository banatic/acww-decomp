/* func_ov144_022996d4 @ 0x022996d4, 0x250 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xb8 - 0xa8];
    short unk_B8;
    char pad_BA[0xc1 - 0xba];
    volatile unsigned char unk_C1;
} UnkStruct_022996d4;

extern void func_ov144_02299a00(UnkStruct_022996d4 *);
extern void func_ov144_02299924(UnkStruct_022996d4 *);
extern void func_ov144_0229993c(UnkStruct_022996d4 *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

int func_ov144_022996d4(UnkStruct_022996d4 *self, void *pad)
{
    unsigned char old = self->unk_C1;

    if (pad == 0) {
        return 0;
    }

    if (old <= 8) {
        if (func_ov002_022088ac(pad)) {
            func_ov144_02299a00(self);
        } else if (func_ov002_0220889c(pad)) {
            if (self->unk_A4 > 0) {
                self->unk_C1 = 10;
            } else {
                self->unk_C1 = 9;
            }
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C1 != 0) {
                self->unk_C1 = self->unk_C1 - 1;
                if (self->unk_C1 == 0) {
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
            if (self->unk_A4 == 0) {
                if (self->unk_C1 < self->unk_B8 - 1) {
                    self->unk_C1 = self->unk_C1 + 1;
                }
            } else {
                if (self->unk_C1 < 7) {
                    self->unk_C1 = self->unk_C1 + 1;
                } else {
                    int a = self->unk_A0;
                    int t = a & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 + (0x10 - t);
                        return 1;
                    }
                    if (a <= self->unk_A4 - 0x10) {
                        self->unk_A0 = self->unk_A0 + 0x10;
                        return 1;
                    }
                }
            }
        }
    }

    switch (self->unk_C1) {
        case 9:
            if (func_ov002_022088ac(pad)) {
                func_ov144_02299924(self);
            } else if (func_ov002_022088cc(pad)) {
                if (self->unk_A4 > 0) {
                    self->unk_C1 = 10;
                }
            }
            break;
        case 10:
            if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 9;
            } else if (func_ov002_022088ac(pad)) {
                func_ov144_02299924(self);
            }
            break;
        case 11:
            if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 13;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c(self);
            }
            break;
        case 12:
            if (func_ov002_022088cc(pad)) {
                self->unk_C1 = 13;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c(self);
            }
            break;
        case 13:
            if (func_ov002_022088cc(pad)) {
                self->unk_C1 = 11;
            } else if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 12;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c(self);
            }
            break;
    }

    if (old != self->unk_C1) {
        return 1;
    }
    return 0;
}
