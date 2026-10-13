/* func_ov146_0229985c @ 0x0229985c, 0x1f0 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa8];
    volatile int a8;
    unsigned char pad_AC[2];
    short ae;
    unsigned char pad_B0[2];
    volatile unsigned char st;
    unsigned char pad_B3[3];
    volatile unsigned char b6;
} UnkStruct_0229985c;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern void func_ov146_02299838(UnkStruct_0229985c *o);
extern void func_ov146_022997ec(UnkStruct_0229985c *o);

int func_ov146_0229985c(UnkStruct_0229985c *o, void *in)
{
    unsigned int st;
    int v;
    int m;
    unsigned char t;

    st = o->st;
    if (st >= 3 && st <= 9) {
        if (func_ov002_0220889c(in) != 0) {
            o->st = 2;
        } else if (func_ov002_022088cc(in) != 0) {
            if (o->st > 3) {
                o->st = o->st - 1;
                if (o->st == 3) {
                    m = o->a8 & 0xf;
                    if (m != 0) {
                        o->a8 = o->a8 - m;
                    }
                }
                return 1;
            } else {
                v = o->a8;
                if (v >= 0x10) {
                    o->a8 = o->a8 - 0x10;
                    return 1;
                } else if (v > 0) {
                    o->a8 = 0;
                    return 1;
                }
            }
        } else if (func_ov002_022088bc(in) != 0) {
            t = o->st;
            if (t - 3 + o->ae >= o->b6 - 1) {
                o->st = 0;
            } else {
                if (t < 8) {
                    o->st = o->st + 1;
                } else {
                    v = o->a8;
                    m = v & 0xf;
                    if (m != 0) {
                        o->a8 = o->a8 + (0x10 - m);
                        return 1;
                    } else if (v <= 0x190) {
                        o->a8 = o->a8 + 0x10;
                        return 1;
                    } else {
                        o->st = 0;
                    }
                }
            }
        }
    } else {
        switch (st) {
            case 0:
                if (func_ov002_022088cc(in) != 0) {
                    if (o->b6 != 0) {
                        func_ov146_02299838(o);
                    }
                } else if (func_ov002_0220889c(in) != 0) {
                    o->st = 1;
                }
                break;
            case 1:
                if (func_ov002_022088cc(in) != 0) {
                    if (o->b6 != 0) {
                        func_ov146_02299838(o);
                    } else {
                        o->st = 2;
                    }
                } else if (func_ov002_022088ac(in) != 0) {
                    o->st = 0;
                } else if (func_ov002_0220889c(in) != 0) {
                    o->st = 2;
                }
                break;
            case 2:
                if (func_ov002_022088bc(in) != 0) {
                    o->st = 1;
                } else if (func_ov002_022088ac(in) != 0) {
                    func_ov146_022997ec(o);
                }
                break;
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}
