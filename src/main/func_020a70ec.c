/* func_020a70ec @ 0x020a70ec, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 a, b, c;
} UnkStruct_020a70ec;

struct GB {
    u8 pad_00[0x64];
    int lim;
};

extern UnkStruct_020a70ec data_021f4320[];
extern struct GB *data_020ccf94;
extern int func_020a71ec(int);
extern void func_020a7738(UnkStruct_020a70ec *, u8 *, u8 *, u8 *);
extern int func_020a627c(UnkStruct_020a70ec *);

int func_020a70ec(int a, int b, int c, u8 *d)
{
    int lim;
    u8 v0, v1, v2, v3, v4, v5;
    int t;

    lim = data_020ccf94->lim;
    *d = 0;
    if (b == 0) {
        if (a == 0) {
            return a;
        }
    } else if (b == 0) {
        if (a == 0) {
            return a;
        }
    } else if (b == 1) {
        if (a == 1) {
            return a;
        }
    } else if (b == 2) {
        if (a == 2) {
            return a;
        }
    } else if (b == 3) {
        if (a == 3) {
            return a;
        }
    } else if (b == 4) {
        if (a != lim) {
            return a;
        }
    } else if (b == 5) {
        if (a != 0) {
            return a;
        }
    } else if (b == 6) {
        t = func_020a71ec(c);
        if (t < 4) {
            if (t == a) {
                return a;
            }
        } else {
            func_020a7738(&data_021f4320[a], &v0, &v1, &v2);
            if (v0 == c && v1 != 0 && v2 != 0) {
                *d = 1;
            }
        }
    } else if (b == 7) {
        func_020a7738(&data_021f4320[a], &v3, &v4, &v5);
        if (v3 == c) {
            if (v4 == 0 && v5 == 0 && a != lim) {
                return a;
            }
        } else {
            t = func_020a627c(data_021f4320);
            if (t < 4 && t == a && a != lim) {
                return a;
            }
        }
    }
    return 4;
}
