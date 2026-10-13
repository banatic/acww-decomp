/* func_0206e854 @ 0x0206e854, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u32 lo, hi;
};

struct UnkStruct_0206e854 {
    struct Pair data;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
};

extern u32 func_020e98b4(u32);
extern void func_02050974(void *);
extern void func_020647ec(struct Pair, u32, u32, u32);
extern int data_021c8188;

void func_0206e854(struct UnkStruct_0206e854 *self)
{
    u32 prod;

    prod = self->unk_08 * self->unk_0C;
    if (self->unk_10 == 0) {
        self->unk_10 = func_020e98b4(prod);
    }
    func_02050974(&data_021c8188);
    func_020647ec(self->data, self->unk_10, prod, 0);
}
