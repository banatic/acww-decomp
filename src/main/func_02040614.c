/* func_02040614 @ 0x02040614, 0x19a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02040614;

typedef union {
    unsigned int all;
    struct {
        u8 b0;
        u8 b1;
        u8 b2;
        u8 b3;
    } b;
} UnkStruct_02040614_2;

extern int func_0209de24(int a, int b);
extern int func_0209de88(int a, int b, int c);

u8 func_02040614(UnkStruct_02040614 *p, int a1, UnkStruct_02040614_2 q, int a3, int a5)
{
    int t;
    int acc;
    int i;
    unsigned int v;
    unsigned int s;
    int r6;
    int x;
    int b3;
    int y;
    int r2;
    int j;
    int w;

    v = p->unk_00;
    t = v >> 8;
    t = t & 7;
    s = (v >> 1) & 7;
    r6 = func_0209de24(a1, a3);
    b3 = q.b.b3;
    x = func_0209de24(a1, b3);
    switch (t) {
        case 0:
            return (u8) p->unk_04;
        case 6: {
            y = func_0209de88((u8) a1, a3, (u8) r6);
            if (y < q.b.b0) {
                return (u8) ((r6 - 7) + (q.b.b0 - y));
            } else {
                return (u8) (r6 - (y - q.b.b0));
            }
        }
        case 7: {
            if (s < q.b.b0) {
                y = (u8) ((*(u8 *) &q.b.b2) + ((s - q.b.b0) + 7));
            } else {
                y = (u8) ((*(u8 *) &q.b.b2) + (s - q.b.b0));
            }
            if (b3 != a3 && y > x) {
                y = y - x;
            }
            return (u8) y;
        }
    }
    w = q.b.b0 - (((*(u8 *) &q.b.b2) - 1) % 7);
    if (w < 0) {
        w = w + 7;
    }
    if (a3 != b3) {
        acc = 0;
        i = a3;
        if (a3 == 1 && b3 == 0xc) {
            i = 0xd;
        }
        if ((unsigned int) i < (unsigned int) b3) {
            b3 = q.b.b3;
            for (; i < b3; i++) {
                acc = acc + func_0209de24(a1, (u8) i);
            }
            acc = acc % 7;
            w = ((w - acc) + 7) % 7;
        } else {
            for (j = b3; j < i; j++) {
                acc = acc + func_0209de24(a1, (u8) j);
            }
            w = (w + acc) % 7;
        }
    }
    if ((unsigned int) w <= s) {
        r2 = (s - w) + 1;
    } else {
        r2 = (s - w) + 8;
    }
    switch (a5) {
        case 9:
        case 0x14:
        case 0x25:
        case 0x26:
        case 0x46:
            if (a3 == 2 || a3 == 4 || a3 == 0xa) {
                t = 4;
            }
            break;
    }
    return (u8) (r2 + 7 * (t - 1));
}
