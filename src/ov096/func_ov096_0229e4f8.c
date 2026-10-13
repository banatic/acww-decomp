/* func_ov096_0229e4f8 @ 0x0229e4f8, 0x184 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xac];
    unsigned short ac;
    char pad_AE[0xb0 - 0xae];
    unsigned char b0;
    unsigned char b1;
} UnkStruct_0229e4f8;

extern unsigned short func_ov096_0229e4a4(UnkStruct_0229e4f8 *self, int k);
extern int func_0204c4c0(volatile unsigned short *p);
extern int func_0204c4e8(volatile unsigned short *p);

int func_ov096_0229e4f8(UnkStruct_0229e4f8 *self)
{
    volatile unsigned short t;
    unsigned int ok;
    unsigned short a, b;

    if (self->b1 != 2) {
        return 1;
    }
    if (self->b0 != 0) {
        return 1;
    }

    t = self->ac;
    ok = 0;
    a = t;
    b = t;
    if (b >= 0x11a8 && a <= 0x12a7) {
        ok = 1;
    }
    if (ok != 0) {
        return 2;
    }

    if ((a >= 0x1431 && a <= 0x1470) || (a >= 0x1471 && a <= 0x1491)) {
        unsigned short c, d;
        t = func_ov096_0229e4a4(self, 4);
        c = t;
        d = t;
        if (d != 0xfff1 && c >= 0x13a8 && c <= 0x13c7 && func_0204c4c0(&t) == 0) {
            return 6;
        }
        return 3;
    }

    if (a >= 0x13a8 && a <= 0x13c7) {
        if (func_ov096_0229e4a4(self, 3) != 0xfff1 && func_0204c4c0(&t) == 0) {
            return 0;
        }
        return 4;
    }

    if ((a >= 0x13c8 && a <= 0x1407) || (a >= 0x1408 && a <= 0x1428)) {
        return 4;
    }

    if (func_0204c4e8(&t) != 0) {
        return 5;
    }

    {
        unsigned int ok2;
        unsigned short e, f;
        ok2 = 0;
        e = t;
        f = t;
        if (f >= 0x1518 && e <= 0x151c) {
            ok2 = 1;
        }
        if (ok2 != 0 || (e >= 0x1531 && e <= 0x153a) || (e >= 0x153b && e <= 0x1541)) {
            return 7;
        }
        if (e >= 0x155e && e <= 0x155e) {
            return 8;
        }
    }
    return 1;
}
