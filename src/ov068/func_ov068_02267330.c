/* func_ov068_02267330 @ 0x02267330, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02267330 {
    char pad_00[0x618];
    int unk_618;
    char pad_61C[0xa04 - 0x61c];
    u8 unk_A04;
};

extern short data_020c80f0;
extern int func_02014868(int *);
extern int func_0202e174(struct UnkStruct_02267330 *);
extern void *func_02096190(int);
extern int func_0201c2b0(struct UnkStruct_02267330 *, void *);

int func_ov068_02267330(struct UnkStruct_02267330 *self)
{
    void *p;
    int n;

    if (func_02014868(&self->unk_618) != 0 || func_0202e174(self) != 0) {
        return 0;
    }
    if (self->unk_A04 != 0) {
        p = func_02096190(4);
        if (p != 0) {
            n = func_0201c2b0(self, p);
            if (n < 0) {
                n = (short) -n;
            }
            if (n > data_020c80f0) {
                return 0;
            }
        }
    }
    return 1;
}
