/* func_02044390 @ 0x02044390, 0x198 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02044390;
typedef struct {
    int a;
    int b;
} Pair;

extern int func_0204ba94(unsigned short *);
extern int func_0204ba40(unsigned short *);
extern int func_0204b7a0(unsigned short *);
extern int func_02044540(void);
extern int func_0204b910(unsigned short *);
extern int func_02042f20(void *tbl, void *a0, int kind, Pair *pr, int w, int v, int z0, int z1, int a3, int m1);
extern unsigned char data_021c7c48;

int func_02044390(void *a0, unsigned short *p, UnkStruct_02044390 *ctx, int a3)
{
    int result;
    int i, h, g, f, e, d, c, b, a;
    int kind;
    int n;
    unsigned int v;
    unsigned int ok2;
    unsigned int w;
    Pair pr;

    a = 0;
    result = -1;
    i = 1;
    h = 1;
    g = 1;
    f = 1;
    e = 1;
    d = 1;
    c = 1;
    b = 1;

    v = *p;
    if (v >= 0x26 && v <= 0x2a) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 0x5d && v <= 0x61)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0x2f && v <= 0x56)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!(v >= 0x57 && v <= 0x5b)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!(v >= 0x66 && v <= 0x68)) {
            e = 0;
        }
    }
    if (e == 0) {
        if (v != 0x69) {
            f = 0;
        }
    }
    if (f == 0) {
        if (!(v >= 0x6a && v <= 0x6c)) {
            g = 0;
        }
    }
    if (g == 0) {
        if (v != 0x6d) {
            h = 0;
        }
    }
    if (h == 0) {
        if (!(v >= 0xc8 && v <= 0xcf)) {
            i = 0;
        }
    }
    if (i != 0) {
        if (func_0204ba94(p) == 0 && func_0204ba40(p) == 0) {
            kind = 1;
            n = func_0204b7a0(p) - 1;
            ok2 = 0;
            v = *p;
            if (v >= 0x26 && v <= 0x2a) {
                ok2 = 1;
            }
            if (ok2 != 0 || (v >= 0x57 && v <= 0x5b) || (v >= 0x66 && v <= 0x68) || v == 0x69) {
                w = (unsigned short) (n + 0x27);
            } else {
                w = (unsigned short) (n + 0x5e);
            }
            if (v == 0x67 || v == 0x6b) {
                if (func_02044540() != 0) {
                    kind = 2;
                } else {
                    w = *p;
                }
            } else if ((v >= 0x2f && v <= 0x56) || (v >= 0xc8 && v <= 0xcf)) {
                if (func_0204b910(p) != 0) {
                    w = (unsigned short) (*p + 1);
                } else {
                    w = *p;
                }
            } else if (v >= 0x57 && v <= 0x5b) {
                if (func_0204b910(p) == 0) {
                    w = *p;
                }
            } else if (v == 0x6d) {
                w = v;
            }
            v = *p;
            pr.a = ctx->unk_00;
            pr.b = ctx->unk_04;
            result = func_02042f20(&data_021c7c48, a0, kind, &pr, w, v, 0, 0, a3, -1);
        }
    }
    return result;
}
