/* func_ov134_022997dc @ 0x022997dc, 0x1a4 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct _S UnkStruct_022997dc;
struct _S {
    int unk_00;        // 0x00
    int unk_04;        // 0x04
    char pad_08[0x10]; // 0x08..0x17
    int unk_18;        // 0x18
    char pad_1C[0x94]; // 0x1c..0xaf
    unsigned char b0;  // 0xb0
    char pad_B1[0x06]; // 0xb1..0xb6
    signed char b7;    // 0xb7
};

extern volatile unsigned short data_021fbe40; // 0x021fbe40

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_0220a4d4(void *);
extern void func_ov134_02299980(UnkStruct_022997dc *, int);
extern int func_ov134_02299774(UnkStruct_022997dc *);
extern int func_ov134_02299734(UnkStruct_022997dc *);
extern void func_ov134_0229a1d8(UnkStruct_022997dc *, int);
extern void func_ov134_02299a3c(UnkStruct_022997dc *);
extern int func_ov134_022995c0(UnkStruct_022997dc *, int);
extern void func_ov134_022995a0(UnkStruct_022997dc *, int);
extern void func_ov134_022995b0(UnkStruct_022997dc *, int);
extern void func_0200467c(int);

int func_ov134_022997dc(UnkStruct_022997dc *self, void *other)
{
    if (self->b0 != 0) {
        goto L_else;
    }

    // L_b0_zero
    self->b7 = 0;
    if (func_ov002_022088ac(other) != 0) {
        goto L_b0_ok;
    }
    goto L_ret0;

L_b0_ok:
    self->b0 = 1;
    func_ov134_02299980(self, func_ov002_0220a4d4(&self->unk_18));
    return 1;

L_else:
    if (func_ov002_0220889c(other) == 0) {
        goto L_else_zero;
    }
    self->b0 = 0;
    self->b7 = 0;
    return 1;

L_else_zero:
    if (self->b7 >= 6) {
        goto L_ge6;
    }
    goto L_less6;

L_ge6:
    if ((data_021fbe40 & 0x40) == 0) {
        goto L_ge6_flag0;
    }
    if (func_ov134_02299774(self) == 0) {
        goto L_label9908;
    }
    // L_ge6_pass
    if (self->unk_04 != 0) {
        func_ov134_0229a1d8(self, self->unk_00 + self->unk_04);
        self->unk_04 = 0;
        func_ov134_02299a3c(self);
    }
    if (func_ov134_022995c0(self, 0x100)) {
        func_ov134_022995a0(self, 0x100);
        func_0200467c(0xb);
    } else {
        func_ov134_022995b0(self, 0x100);
    }
    return 3;

L_ge6_flag0:
    self->b7 = 0;
    goto L_label9908;

L_less6:
    if (self->b7 > -6) {
        goto L_label9908;
    }
    // L_less6_continue
    if ((data_021fbe40 & 0x80) == 0) {
        goto L_less6_flag0;
    }
    if (func_ov134_02299734(self) == 0) {
        goto L_label9908;
    }
    // L_less6_pass
    if (self->unk_04 != 0) {
        func_ov134_0229a1d8(self, self->unk_00 + self->unk_04);
        self->unk_04 = 0;
        func_ov134_02299a3c(self);
    }
    if (func_ov134_022995c0(self, 0x100)) {
        func_ov134_022995a0(self, 0x100);
        func_0200467c(0xb);
    } else {
        func_ov134_022995b0(self, 0x100);
    }
    return 3;

L_less6_flag0:
    self->b7 = 0;
    goto L_label9908;

L_label9908:
    if (func_ov002_022088cc(other) == 0) {
        goto L_fn4_zero;
    }
    // L_fn4_nonzero
    if (self->b7 < 0) {
        self->b7 = 1;
    } else {
        self->b7 = self->b7 + 1;
    }
    if (func_ov134_02299774(self) != 0) {
        return 2;
    }
    goto L_ret0;

L_fn4_zero:
    if (func_ov002_022088bc(other) == 0) {
        goto L_ret0;
    }
    // L_fn5_nonzero
    if (self->b7 > 0) {
        self->b7 = -1;
    } else {
        self->b7 = self->b7 - 1;
    }
    if (func_ov134_02299734(self) != 0) {
        return 2;
    }

L_ret0:
    return 0;
}
