/* func_ov068_02275388 @ 0x02275388, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02275388 {
    char pad_00[0x618];
    int unk_618;
    char pad_61C[0xa58 - 0x61c];
    u8 unk_A58;
    u8 unk_A59;
};

extern void *func_020961a8(int);
extern int func_0201c314(struct UnkStruct_02275388 *, void *);
extern int func_020147fc(int *, int, int, int);

int func_ov068_02275388(struct UnkStruct_02275388 *self)
{
    void *p;
    int m;

    p = func_020961a8(4);
    if (p != 0) {
        m = func_0201c314(self, p);
        if (self->unk_A58 != 0 || self->unk_A59 != 0) {
            func_020147fc(&self->unk_618, 0, m, 1);
        } else {
            func_020147fc(&self->unk_618, 0, m, 0);
        }
        return 1;
    }
    return 0;
}
