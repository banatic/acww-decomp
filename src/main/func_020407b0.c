/* func_020407b0 @ 0x020407b0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int lo, hi;
} Date;
typedef struct {
    u8 b[4];
} Rec;
typedef struct {
    unsigned int unk_00;
    int unk_04;
} UnkStruct_020407b0;

extern void func_0209e29c(Date *, int);

int func_020407b0(UnkStruct_020407b0 *p, int arg, Rec rec, int kind)
{
    Date t;
    int result;
    unsigned int w;
    int a;
    int b;
    u8 hi;
    u8 lo2;

    hi = rec.b[3];
    lo2 = rec.b[2];
    result = 0;
    w = p->unk_00;
    a = (w >> 4) & 0xf;
    b = (w >> 11) & 3;
    switch (b) {
        case 0:
            result = (u8) a;
            break;
        case 1:
            if (a == 0) {
                result = hi;
            } else {
                int n;
                t.lo = result;
                t.hi = result;
                if (kind == 0x48) {
                    n = -4;
                } else {
                    n = p->unk_04;
                }
                t.lo = 0;
                t.hi = 0;
                ((u8 *) &t)[5] = (u8) arg;
                ((u8 *) &t)[4] = hi;
                ((u8 *) &t)[3] = lo2;
                if (n < 0) {
                    n = -n;
                }
                func_0209e29c(&t, n);
                result = ((u8 *) &t)[4];
            }
            switch (kind) {
                case 0xb:
                case 0x29:
                case 0x2a:
                case 0x48:
                    if (result == 1 || result == 8) {
                        result = 2;
                    }
                    break;
            }
            break;
        case 2:
            if (a == 1) {
                result = (u8) ((hi & ~1) + 1);
            } else {
                result = (u8) ((hi + 1) & ~1);
            }
            break;
    }
    return result;
}
