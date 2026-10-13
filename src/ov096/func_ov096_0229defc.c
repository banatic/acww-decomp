/* func_ov096_0229defc @ 0x0229defc, 0x1ac bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204c878(volatile u16 *p);
extern int func_0204c120(int a, int b, int *out);

int func_ov096_0229defc(void *self, u16 *A, int mode, u16 *B, u8 force)
{
    volatile u16 t[3];
    int spare;
    // DECLS
    u16 b;
    int v2;
    int x;
    int v1;
    unsigned int ok1;
    int j;
    u16 s;
    u16 d;
    unsigned int ok2;
    unsigned int okA;
    int rem;
    u16 a;
    int cap;
    int n;
    int y;
    int p;
    u16 c;
    unsigned int okB;
    int m;
    // ENDDECLS

    if (mode == 0 && force == 0) {
        goto go;
    }
    return 1;
go:
    t[0] = *A;
    t[1] = *B;
    ok1 = 0;
    a = t[0];
    b = t[0];
    if (b >= 0x1531 && a <= 0x153a) {
        ok1 = 1;
    }
    if (ok1 == 0) {
        goto other;
    }
    ok2 = 0;
    c = t[1];
    d = t[1];
    if (d >= 0x1531 && c <= 0x153a) {
        ok2 = 1;
    }
    if (ok2 == 0) {
        goto other;
    }

    if (a >= 0x1531 && a <= 0x153a) {
        x = a - 0x1531;
    } else {
        x = -1;
    }
    n = x + 1;
    if (c >= 0x1531 && c <= 0x153a) {
        y = c - 0x1531;
    } else {
        y = -1;
    }
    y = y + 1;
    n = n + y;
    if (n > 10) {
        rem = n - 10;
        n = 10;
    } else {
        rem = 0;
    }
    j = n - 1;
    if ((unsigned int) j < 10) {
        s = (u16) (0x1531 + j);
    } else {
        s = 0x1531;
    }
    *A = s;
    if (rem > 0) {
        j = rem - 1;
        if ((unsigned int) j < 10) {
            s = (u16) (0x1531 + j);
        } else {
            s = 0x1531;
        }
        *B = s;
    } else {
        *B = 0xfff1;
    }
    return 0;

other:
    okA = (a >= 0x1492 && a <= 0x14fd) ? 1 : 0;
    if (okA == 0) {
        goto ret1;
    }
    okB = 0;
    c = t[1];
    d = t[1];
    if (d >= 0x1492 && c <= 0x14fd) {
        okB = 1;
    }
    if (okB != 0) {
        goto proceed;
    }
ret1:
    return 1;
proceed:
    v1 = func_0204c878(&t[0]);
    v2 = func_0204c878(&t[1]);
    t[2] = 0x14fd;
    cap = func_0204c878(&t[2]);
    m = (v1 < 1000) ? 1 : 0;
    p = (v2 < 1000) ? 1 : 0;
    if (m != p) {
        return 2;
    }
    if (v1 == cap || v2 == cap) {
        return 3;
    }
    if (v1 < 1000) {
        v1 = v1 + v2;
        if (v1 > 1000) {
            v2 = v1 - 1000;
            v1 = 1000;
        } else {
            v2 = 0;
        }
    } else {
        v1 = v1 + v2;
        if (v1 <= cap) {
            v2 = 0;
        } else {
            v2 = v1 - cap;
            v1 = cap;
        }
    }
    *A = (u16) func_0204c120(v1, 1, &spare);
    if (v2 == 0) {
        *B = 0xfff1;
    } else {
        *B = (u16) func_0204c120(v2, 1, &spare);
    }
    return 0;
}
