/* func_ov143_02299c14 @ 0x02299c14, 0x202 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa4];
    volatile unsigned char unk_A4;
} UnkStruct_02299c14;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);

int func_ov143_02299c14(UnkStruct_02299c14 *o, void *in)
{
    unsigned int st;
    int n;

    if (in == 0) {
        return 0;
    }
    st = o->unk_A4;
    if (st < 8) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_A4 = o->unk_A4 + 8;
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->unk_A4 != 0) {
                o->unk_A4 = o->unk_A4 - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            o->unk_A4 = o->unk_A4 + 1;
        }
    } else if (st >= 8 && st <= 0xf) {
        if (func_ov002_022088bc(in) != 0) {
            n = o->unk_A4 - 8;
            if (n < 2) {
                o->unk_A4 = 0x10;
            } else if (n < 6) {
                o->unk_A4 = 0x11;
            } else {
                o->unk_A4 = 0x12;
            }
        } else if (func_ov002_022088cc(in) != 0) {
            o->unk_A4 = o->unk_A4 - 8;
        } else if (func_ov002_022088ac(in) != 0) {
            o->unk_A4 = o->unk_A4 - 1;
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->unk_A4 < 0xfU) {
                o->unk_A4 = o->unk_A4 + 1;
            }
        }
    } else {
        switch (st) {
            case 0x10:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 8;
                } else if (func_ov002_0220889c(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
            case 0x11:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0xb;
                } else if (func_ov002_0220889c(in) != 0) {
                    o->unk_A4 = 0x12;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x10;
                }
                break;
            case 0x12:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0xe;
                } else if (func_ov002_022088bc(in) != 0) {
                    o->unk_A4 = 0x13;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
            case 0x13:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0x12;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
        }
    }
    if (st != o->unk_A4) {
        return 1;
    }
    return 0;
}
