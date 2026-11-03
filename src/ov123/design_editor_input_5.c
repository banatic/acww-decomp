/* design_editor_input_5: 6 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229afc0 @ 0x0229afc0, 0x11c bytes, Thumb
 * func_ov123_0229afa8 @ 0x0229afa8, 0x18 bytes, Thumb
 * func_ov123_0229ae84 @ 0x0229ae84, 0x124 bytes, Thumb
 * func_ov123_0229ae7c @ 0x0229ae7c, 0x6 bytes, Thumb
 * func_ov123_0229ae74 @ 0x0229ae74, 0x6 bytes, Thumb
 * func_ov123_0229ae24 @ 0x0229ae24, 0x50 bytes, Thumb
 */

typedef struct {
    char pad_00[0xa1];
    unsigned char unk_A1;
    char pad_A2[3];
    unsigned char unk_A5;
    char pad_A6[4];
    unsigned char unk_AA;
} UnkStruct_0229ae84;

struct UnkStruct_0229ae24 {
    char pad_00[0xA4];
    unsigned char flag;
    char pad_A5[3];
    unsigned char x;
    unsigned char y;
};

extern int func_ov002_0220a7c0(int a, int b, int c, int d);
extern int _s32_div_f(int a, int b);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov123_0229b5cc(UnkStruct_0229ae84 *);
extern void func_ov123_0229b598(UnkStruct_0229ae84 *);
extern void func_ov123_0229a278(UnkStruct_0229ae84 *, unsigned char arg1);
extern void func_ov123_0229a248(UnkStruct_0229ae84 *, unsigned char arg1);
extern void func_ov123_0229b0dc(UnkStruct_0229ae84 *, unsigned char);
extern void func_0200467c(int);
extern void func_ov123_02299dc4(UnkStruct_0229ae84 *);
extern void func_ov123_0229b160(UnkStruct_0229ae84 *, unsigned char);
extern void func_ov123_02299980(UnkStruct_0229ae84 *);
extern void func_ov123_0229b56c(UnkStruct_0229ae84 *, int, int);
extern int func_ov123_02299650(UnkStruct_0229ae84 *, int);
extern void func_0206fc4c(int);
extern int func_0206fca4(void);
extern void func_ov123_0229b41c(UnkStruct_0229ae84 *);
extern void func_ov123_0229b384(UnkStruct_0229ae84 *);

int func_ov123_0229afc0(int a, int b, int c)
{
    if (func_ov002_0220a7c0(a + 0x5030, 9, b, c) != 0) {
        return 0x1d;
    }
    if (func_ov002_0220a7c0(a + 0x5030, 8, b, c) != 0) {
        return 0x1e;
    }
    if (b >= 8 && b <= 0x28 && c >= 0x18 && c <= 0x38) {
        return 0xd;
    }
    if (b >= 0x40 && b < 0xc0 && c >= 8 && c < 0x88) {
        return 0x21;
    }
    if (b >= 0xca) {
        if (c >= 8) {
            if (b < 0xe1) {
                if (c < 0x50) {
                    if (c < 0x20) {
                        return 0;
                    } else if (c < 0x38) {
                        return 1;
                    } else {
                        return 2;
                    }
                } else {
                    if (c >= 0x58 && c < 0x88) {
                        if (c < 0x70) {
                            return 3;
                        } else {
                            return 4;
                        }
                    } else if (c >= 0x90 && c < 0xa8) {
                        return 5;
                    }
                }
            } else if (b < 0xf9) {
                if (c < 0x50) {
                    if (c < 0x20) {
                        return 6;
                    } else if (c < 0x38) {
                        return 7;
                    } else {
                        return 8;
                    }
                } else {
                    if (c >= 0x58 && c < 0xa0) {
                        if (c < 0x70) {
                            return 9;
                        } else if (c < 0x88) {
                            return 0xa;
                        } else {
                            return 0xb;
                        }
                    }
                }
            }
        }
    }
    if (b >= 8 && b <= 0x28 && c >= 0x80 && c <= 0x94) {
        return 0xc;
    }
    if (b >= 8 && b < 0xbc && c >= 0x94 && c <= 0xa4) {
        return (unsigned char) (_s32_div_f(b - 8, 0xc) + 0xe);
    }
    return 0x22;
}

int func_ov123_0229afa8(int arg)
{
    return func_ov123_0229afc0(arg, data_021f6c58, data_021f6c54);
}

void func_ov123_0229ae84(UnkStruct_0229ae84 *self)
{
    unsigned char cmd;

    cmd = self->unk_A5;

    if (cmd == 0x1d) {
        func_ov123_0229b5cc(self);
        return;
    }

    if (cmd == 0x1e) {
        func_ov123_0229b598(self);
        return;
    }

    if (cmd <= 0xb && cmd != 5) {
        func_ov123_0229a278(self, cmd);
        return;
    }

    if (cmd == 0xc) {
        unsigned char val;

        func_ov123_0229a248(self, cmd);
        val = (unsigned char) ((self->unk_A1 + 1) & 0xf);
        func_ov123_0229b0dc(self, val);
        func_0200467c(0x868);
        return;
    }

    if (cmd == 5) {
        func_ov123_0229a248(self, cmd);
        func_ov123_02299dc4(self);
        return;
    }

    if (cmd >= 0xe && cmd <= 0x1c) {
        unsigned char idx;

        idx = (unsigned char) (cmd - 0xd);
        func_ov123_0229b160(self, idx);
        func_0200467c(0x86a);
        return;
    }

    if (cmd == 0xd) {
        func_ov123_02299980(self);
    }

    if (self->unk_A5 == 0x1f) {
        int state;

        func_ov123_0229b56c(self, 2, 3);
        if (func_ov123_02299650(self, 8) != 0) {
            func_0206fc4c(0);
            func_0200467c(0x28);
        } else {
            state = func_0206fca4();
            if (state == 2) {
                goto LA;
            }
            if (state != 3) {
                goto LC;
            }
            goto LB;
        LA:
            func_ov123_0229b41c(self);
            goto LC;
        LB:
            func_ov123_0229b384(self);
        LC:
            func_0206fc4c(1);
            func_0200467c(0x27);
        }
        return;
    }

    if (self->unk_A5 == 0x20) {
        func_ov123_0229b56c(self, 9, 4);
        if (func_ov123_02299650(self, 8) != 0) {
            self->unk_AA = 0x1e;
            func_0200467c(0x29);
        } else {
            self->unk_AA = 0x1d;
            func_0200467c(0x2a);
        }
        return;
    }
}

int func_ov123_0229ae7c(int unused, int a)
{
    return a * 4 + 0x42;
}

int func_ov123_0229ae74(int unused, int a)
{
    return a * 4 + 10;
}

void func_ov123_0229ae24(struct UnkStruct_0229ae24 *self)
{
    int a;
    int b;

    a = data_021f6c58;
    b = data_021f6c54 + 16;
    if (self->flag == 1) {
        a += 2;
        b += 2;
    }
    a -= 64;
    if (a < 0) {
        a = 0;
    } else if (a > 127) {
        a = 127;
    }
    b -= 24;
    if (b < 0) {
        b = 0;
    } else if (b > 127) {
        b = 127;
    }
    self->x = a >> 2;
    self->y = b >> 2;
}
