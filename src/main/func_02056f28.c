/* func_02056f28 @ 0x02056f28, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02056f28 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[4];
    u8 unk_14;
} UnkStruct_02056f28;

// The failing paths share one return 0.
int func_02056f28(UnkStruct_02056f28 *a, int b)
{
    int v;
    int lo;
    int hi;
    int flag;

    v = b << 12;
    lo = a->unk_08;
    hi = a->unk_0C;
    if (hi == lo) {
        if (lo == b) {
            return 1;
        }
        return 0;
    }
    flag = (a->unk_14 & 2) ? 1 : 0;
    if (flag != 0) {
        if (hi > lo) {
            if (hi <= v) {
                goto ret0;
            }
            if (lo > v) {
                goto ret0;
            }
            return 1;
        }
        if (v >= hi && v < lo) {
            goto ret0;
        }
        return 1;
    }
    if (hi < lo) {
        if (hi >= v) {
            goto ret0;
        }
        if (lo < v) {
            goto ret0;
        }
        return 1;
    }
    if (v <= hi && v > lo) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}
