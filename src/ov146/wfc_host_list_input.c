/* wfc_host_list_input: 3 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229985c @ 0x0229985c, 0x1f0 bytes, Thumb
 * func_ov146_02299838 @ 0x02299838, 0x24 bytes, Thumb
 * func_ov146_022997ec @ 0x022997ec, 0x4c bytes, Thumb
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

struct UnkStruct_022997ec {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[6];
    unsigned char unk_B2;
    char pad_B3[3];
    unsigned char unk_B6;
    char pad_B7[0x1515];
    char unk_15CC;
};

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov002_02209eec(char *p);

void func_ov146_02299838(unsigned char *p);
void func_ov146_022997ec(struct UnkStruct_022997ec *param);

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
                        func_ov146_02299838((unsigned char *) o);
                    }
                } else if (func_ov002_0220889c(in) != 0) {
                    o->st = 1;
                }
                break;
            case 1:
                if (func_ov002_022088cc(in) != 0) {
                    if (o->b6 != 0) {
                        func_ov146_02299838((unsigned char *) o);
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
                    func_ov146_022997ec((struct UnkStruct_022997ec *) o);
                }
                break;
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}

void func_ov146_02299838(unsigned char *p)
{
    unsigned int v;
    p[0xB2] = 8;
    v = *(unsigned int *) (p + 0xA8) & 0xF;
    if (v != 0) {
        *(unsigned int *) (p + 0xA8) = *(unsigned int *) (p + 0xA8) - v;
    }
}

void func_ov146_022997ec(struct UnkStruct_022997ec *param)
{
    int val;

    if (param->unk_B6 == 0) {
        param->unk_B2 = 1;
        return;
    }
    val = func_ov002_02209eec(&param->unk_15CC);
    if (val < 0x38) {
        val = 0x38;
    }
    if (val > 0xa7) {
        val = 0xa7;
    }
    val = val - (0x38 - (param->unk_A8 & 0xf));
    val = (val >> 4) + 3;
    param->unk_B2 = (unsigned char) val;
}
