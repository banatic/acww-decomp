/* func_020401b8 @ 0x020401b8, 0x2fa bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef union {
    u32 w;
    struct {
        u8 b0, b1, b2, b3;
    } b;
} UnkStruct_020401b8;
typedef union {
    u32 all;
    struct {
        u8 b0, b1, b2, b3;
    } b;
} UnkStruct_020401b8_2;
typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_020401b8_3;
typedef struct {
    int lo, hi;
} Date;

extern UnkStruct_020401b8 func_020404b4(UnkStruct_020401b8_3 *p, int b, UnkStruct_020401b8_2 q);
extern void func_02040548(UnkStruct_020401b8_3 *p, UnkStruct_020401b8 *out, int idx);
extern void func_020405e4(UnkStruct_020401b8_3 *p, u8 *b);
extern u8 func_02040614(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3, int a5);
extern int func_020407b0(UnkStruct_020401b8_3 *p, int arg, UnkStruct_020401b8_2 q, int kind);
extern int func_0209de24(int a, int b);
extern void func_0209e140(Date *, int);
extern void func_0209e29c(Date *, int);

UnkStruct_020401b8 func_020401b8(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3)
{
    int acc;
    int t;
    int s;
    int f;
    unsigned int v;
    UnkStruct_020401b8 d;
    Date dt;
    UnkStruct_020401b8 e;
    int m;
    int mm;
    int w;
    int r;
    int n;

    d.w = 0;
    v = p->unk_00;
    m = (v >> 4) & 0xf;
    t = v >> 8;
    t = t & 7;
    s = v >> 1;
    s = s & 7;
    f = v;
    f = f & 1;
    switch ((v >> 13) & 7) {
        case 3:
            switch (q.b.b3) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 10:
                case 11:
                case 12:
                    d.b.b3 = q.b.b3;
                    break;
                default:
                    d.b.b3 = 1;
                    break;
            }
            d.b.b2 = func_02040614(p, a1, q, d.b.b3, a3);
            d.b.b1 = (u8) p->unk_08;
            break;
        case 4:
            switch (q.b.b3) {
                case 6:
                case 7:
                case 8:
                case 9:
                    d.b.b3 = q.b.b3;
                    break;
                default:
                    d.b.b3 = 6;
                    break;
            }
            d.b.b2 = func_02040614(p, a1, q, d.b.b3, a3);
            d.b.b1 = (u8) p->unk_08;
            break;
        case 0:
            d.b.b3 = (u8) func_020407b0(p, a1, q, a3);
            d.b.b2 = func_02040614(p, a1, q, d.b.b3, a3);
            d.b.b1 = (u8) p->unk_08;
            break;
        case 1:
            func_020405e4(p, (u8 *) &d);
            break;
        case 2:
            func_02040548(p, &d, a3);
            break;
        case 5:
            d.b.b3 = (u8) m;
            w = q.b.b0 - ((q.b.b2 - 1) % 7);
            if (w < 0) {
                w = w + 7;
            }
            mm = q.b.b3;
            if (m != mm) {
                acc = 0;
                if ((unsigned int) m < (unsigned int) mm) {
                    for (; m < mm; m++) {
                        acc = acc + func_0209de24(a1, (u8) m);
                    }
                    acc = acc % 7;
                    w = ((w - acc) + 7) % 7;
                } else {
                    for (; (unsigned int) mm < (unsigned int) m; mm++) {
                        acc = acc + func_0209de24(a1, (u8) mm);
                    }
                    w = (w + acc) % 7;
                }
            }
            if ((unsigned int) w <= (unsigned int) s) {
                r = (s - w) + 1;
            } else {
                r = (s - w) + 8;
            }
            d.b.b2 = (u8) (r + 7 * (t - 1));
            d.b.b1 = (u8) p->unk_08;
            break;
        case 6:
            switch (a3) {
                case 0x3d:
                case 0x3e:
                case 0x3f:
                case 0x40:
                case 0x41:
                case 0x42:
                case 0x43:
                case 0x44:
                case 0x45:
                case 0x60:
                    e = func_020404b4(p, a3, q);
                    d = e;
                    break;
                case 0x61:
                case 0x62:
                    if (f) {
                        if (q.b.b3 == 1) {
                            d.b.b3 = 12;
                            d.b.b2 = 31;
                            d.b.b1 = 6;
                        } else {
                            f = 0;
                            d.b.b3 = 12;
                            d.b.b2 = 31;
                            d.b.b1 = 24;
                        }
                    } else {
                        if (q.b.b3 == 1) {
                            d.b.b3 = 1;
                            d.b.b2 = 1;
                            d.b.b1 = 0;
                        } else {
                            d.b.b3 = 12;
                            d.b.b2 = 31;
                            d.b.b1 = 6;
                        }
                    }
                    break;
            }
            break;
    }
    if (d.w != 0) {
        dt.lo = 0;
        dt.hi = 0;
        dt.lo = 0;
        dt.hi = 0;
        ((u8 *) &dt)[5] = (u8) a1;
        ((u8 *) &dt)[4] = d.b.b3;
        ((u8 *) &dt)[3] = d.b.b2;
        n = func_0209de24(a1, d.b.b3);
        if (d.b.b2 > n) {
            ((u8 *) &dt)[3] = (u8) n;
            func_0209e29c(&dt, d.b.b2 - n);
        }
        if (f) {
            n = p->unk_04;
            if (n < 0) {
                if (n < 0) {
                    n = -n;
                }
                func_0209e140(&dt, n);
            } else {
                func_0209e29c(&dt, n);
            }
        }
        d.b.b3 = ((u8 *) &dt)[4];
        d.b.b2 = ((u8 *) &dt)[3];
    }
    return d;
}
