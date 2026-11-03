/* town_map_2: 2 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229a584 @ 0x0229a584, 0x14c bytes, Thumb
 * func_ov120_0229a4bc @ 0x0229a4bc, 0xc8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xab];
    volatile unsigned char st;
} UnkStruct_0229a584;

struct UnkStruct_0229a4bc {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[7];
    unsigned char unk_AB;
    unsigned char unk_AC;
};

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov120_0229a448(UnkStruct_0229a584 *o, int n);
extern int func_ov120_0229b168(UnkStruct_0229a584 *o);
extern int func_ov002_0220a4d4(void *p);
extern void func_ov120_0229adc4(void *p, unsigned char n);
extern void func_ov120_0229b22c(void *p);
extern void func_ov120_0229b214(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void *func_0208e95c(void *p, int n);
extern void func_ov120_0229a438(void *p, int n);

int func_ov120_0229a584(UnkStruct_0229a584 *o, void *in)
{
    unsigned int st;
    int n;
    int x;
    unsigned char s2;

    st = o->st;
    if (st >= 2 && st <= 7) {
        if (func_ov120_0229a448(o, 8) != 0 && func_ov002_0220889c(in) != 0) {
            o->st = 8;
        } else if (func_ov002_022088cc(in) != 0) {
            if (o->st > 2) {
                o->st = o->st - 1;
            } else {
                o->st = 1;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            n = func_ov120_0229b168(o) - 1;
            s2 = o->st;
            if (s2 < 7 && s2 < n + 2) {
                o->st = o->st + 1;
            }
        }
    } else if (st == 8) {
        if (func_ov002_022088cc(in) != 0) {
            o->st = 0;
        } else if (func_ov002_022088ac(in) != 0) {
            x = func_ov002_0220a4d4((char *) o + 0x674);
            if (x < 0x50) {
                x = 0x50;
            }
            if (x >= 0xb0) {
                x = 0xaf;
            }
            o->st = ((x - 0x50) >> 4) + 2;
        }
    } else if (st <= 1) {
        if (func_ov002_022088bc(in) != 0) {
            o->st = 2;
        } else if (func_ov002_022088ac(in) != 0) {
            o->st = 1;
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st == 0 && func_ov120_0229a448(o, 8) != 0) {
                o->st = 8;
            } else {
                o->st = 0;
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}

int func_ov120_0229a4bc(struct UnkStruct_0229a4bc *s)
{
    unsigned char v;

    if (func_ov120_0229a448((UnkStruct_0229a584 *) s, 0x800) != 0) {
        func_ov120_0229adc4(s, (unsigned char) (s->unk_AC + 1));
        return 0;
    }

    v = s->unk_AB;

    if (v == 8) {
        func_ov002_02208098(s, 6);
        func_0208e95c((char *) s + 0x674, 2);
        func_ov120_0229a438(s, 0x1000);
        return 1;
    } else if (v == 0) {
        if (func_ov120_0229a448((UnkStruct_0229a584 *) s, 1) != 0) {
            func_ov120_0229adc4(s, 0);
            func_ov120_0229b22c(s);
            return 2;
        }
        return 0;
    } else if (v == 1) {
        if (func_ov120_0229a448((UnkStruct_0229a584 *) s, 1) == 0) {
            func_ov120_0229adc4(s, 0);
            func_ov120_0229b214(s);
            return 2;
        }
        return 0;
    } else if (v >= 2 && v <= 7) {
        func_ov120_0229adc4(s, (unsigned char) (s->unk_A3 + v + 0xd));
        return 0;
    }

    return 0;
}
