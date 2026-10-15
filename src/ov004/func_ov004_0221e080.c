/* func_ov004_0221e080 @ 0x0221e080, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221e080 {
    void *unk_00;
    u32 unk_04;
    u32 unk_08;
};
extern struct UnkStruct_0221e080 *data_021c80bc;
extern int func_02037e0c(void *, int, int, int);
extern int func_0204bc90(int tile);
extern void func_020308e0(int, int);

void func_ov004_0221e080(void *receiver)
{
    struct UnkStruct_0221e080 *q;
    void *base;
    int y;
    int x;
    int zero;
    int tile;

    zero = 0;
    q = data_021c80bc;
    if (q->unk_04 > zero && q->unk_08 > zero && q->unk_00 != 0) {
        base = q->unk_00;
    } else {
        base = 0;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            if ((tile = func_02037e0c(base, x, y, zero)) != 0 && func_0204bc90(tile) != 0) {
                func_020308e0(x, y);
            }
        }
    }
}
