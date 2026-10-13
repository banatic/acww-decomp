/* func_020b1444 @ 0x020b1444, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Arr6 {
    u16 v[6];
};

struct Src {
    u16 unk_00;
    struct Arr6 unk_02;
    u16 unk_0E;
    struct Arr6 unk_10;
    s8 unk_1C;
    u8 unk_1D;
};

extern void *func_020984e8(void);
extern void *func_02099870(void *);

void func_020b1444(struct Src *dest)
{
    struct Src *src;

    src = (struct Src *) func_02099870(func_020984e8());

    dest->unk_00 = src->unk_00;
    dest->unk_02 = src->unk_02;
    dest->unk_0E = src->unk_0E;
    dest->unk_10 = src->unk_10;
    dest->unk_1C = src->unk_1C;
    dest->unk_1D = src->unk_1D;
}
