/* func_ov118_0229a5bc @ 0x0229a5bc, 0x298 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9a];
    volatile unsigned short unk_9A;
    unsigned char pad_9C[0xac - 0x9c];
    volatile unsigned char st;
    unsigned char pad_AD;
    volatile unsigned char ae;
    volatile unsigned char af;
} UnkStruct_0229a5bc;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov118_0229a460(UnkStruct_0229a5bc *o, int n);
extern int func_ov002_02209f00(void *p);
extern int func_ov002_02209eec(void *p);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a254(void *p);
extern void func_ov118_0229ade0(UnkStruct_0229a5bc *o, int n);
extern int func_ov118_0229b390(UnkStruct_0229a5bc *o);
extern int func_ov002_0220a4d4(void *p);

int func_ov118_0229a5bc(UnkStruct_0229a5bc *o, void *in)
{
    unsigned char st;
    int v;
    unsigned char c;
    unsigned short h;
    int w;
    int x;

    st = o->st;
    if (st <= 7) {
        if (func_ov002_022088bc(in) != 0) {
            v = o->st;
            if (v <= 3) {
                o->ae = func_ov002_02209f00((char *) o + 0x6c0);
                o->af = 0x30;
                func_ov002_0220a2b4((char *) o + 0x6c0);
                return 2;
            } else {
                if (v >= 5) {
                    o->st = 8;
                } else {
                    o->st = 9;
                }
                func_ov002_0220a2b4((char *) o + 0x6c0);
            }
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->st != 0) {
                o->st = o->st - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 7) {
                o->st = o->st + 1;
            }
        }
    } else if (st >= 0xa && st <= 0xf) {
        if (func_ov118_0229a460(o, 8) != 0 && func_ov002_0220889c(in) != 0) {
            o->st = 0x10;
        } else if (func_ov002_022088cc(in) != 0) {
            if (o->st > 0xa) {
                o->st = o->st - 1;
            } else {
                h = o->unk_9A;
                if (h >> 4 > 0) {
                    func_ov118_0229ade0(o, h - 0x10);
                    return 3;
                } else {
                    o->st = 9;
                }
            }
        } else if (func_ov002_022088bc(in) != 0) {
            w = func_ov118_0229b390(o) - 1;
            c = o->st;
            if (c < 0xf) {
                if (c < w + 0xa) {
                    o->st = o->st + 1;
                }
            } else {
                h = o->unk_9A;
                if ((h >> 4) + 5 < w) {
                    func_ov118_0229ade0(o, h + 0x10);
                    return 3;
                }
            }
        } else if (func_ov002_022088ac(in) != 0) {
            o->ae = 0x98;
            o->af = func_ov002_02209eec((char *) o + 0x6c0);
            return 2;
        }
    } else if (st == 0x10) {
        if (func_ov002_022088cc(in) != 0) {
            o->st = 8;
        } else if (func_ov002_022088ac(in) != 0) {
            x = func_ov002_0220a4d4((char *) o + 0x678);
            if (x < 0x50) {
                x = 0x50;
            }
            if (x >= 0xb0) {
                x = 0xaf;
            }
            o->st = ((x - 0x50) >> 4) + 0xa;
        }
    } else if ((unsigned char) (st + 0xf8) <= 1) {
        if (func_ov002_022088cc(in) != 0) {
            o->st = 5;
            func_ov002_0220a254((char *) o + 0x6c0);
        } else if (func_ov002_022088bc(in) != 0) {
            o->st = 0xa;
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->st == 9) {
                o->ae = 0x98;
                o->af = func_ov002_02209eec((char *) o + 0x6c0);
                return 2;
            } else {
                o->st = 9;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st == 8 && func_ov118_0229a460(o, 8) != 0) {
                o->st = 0x10;
            } else {
                o->st = 8;
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}
