/* func_ov119_0229b5a8 @ 0x0229b5a8, 0x220 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    volatile unsigned char st;
    unsigned char pad_A1[0xaf - 0xa1];
    volatile unsigned char af;
} UnkStruct_0229b5a8;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov002_02209eec(void *p);
extern int func_ov002_02209f00(void *p);

int func_ov119_0229b5a8(UnkStruct_0229b5a8 *o, void *in)
{
    unsigned int st;
    int v;
    int n;

    st = o->st;
    if (in == 0) {
        return 0;
    }
    if (st <= 7) {
        if (func_ov002_022088bc(in) != 0) {
            if (o->st + 1 < o->af) {
                o->st = o->st + 1;
            }
        } else if (func_ov002_022088cc(in) != 0) {
            if (o->st != 0) {
                o->st = o->st - 1;
            } else {
                o->st = 0x14;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            v = func_ov002_02209eec((char *) o + 0xda8);
            if (v > 0x94) {
                o->st = 0x16;
            } else {
                v = v - 0x35;
                if (v < 0) {
                    v = 0;
                }
                v = v >> 4;
                if (v >= 6) {
                    v = 5;
                }
                o->st = v + 8;
            }
        }
    } else if (st >= 0xe && st <= 0x15) {
        if (func_ov002_022088ac(in) != 0) {
            if (o->st > 0xe) {
                o->st = o->st - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 0x15) {
                o->st = o->st + 1;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            v = func_ov002_02209f00((char *) o + 0xda8);
            if (o->af != 0 && v < 0x80) {
                o->st = 0;
            } else {
                o->st = 8;
            }
        }
    } else if (st >= 8 && st <= 0xd) {
        if (func_ov002_022088cc(in) != 0) {
            if (o->st > 8) {
                o->st = o->st - 1;
            } else {
                o->st = 0x14;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            if (o->st < 0xd) {
                o->st = o->st + 1;
            } else {
                o->st = 0x16;
            }
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->af != 0) {
                v = func_ov002_02209eec((char *) o + 0xda8) - 0x30;
                if (v < 0) {
                    v = 0;
                }
                v = v >> 4;
                n = o->af;
                if (v >= n) {
                    v = n - 1;
                }
                o->st = v;
            }
        }
    } else if (st == 0x16) {
        if (func_ov002_022088cc(in) != 0) {
            o->st = 0xd;
        }
        if (func_ov002_022088ac(in) != 0) {
            n = o->af;
            if (n != 0) {
                o->st = n - 1;
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}
