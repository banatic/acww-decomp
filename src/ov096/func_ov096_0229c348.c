/* func_ov096_0229c348 @ 0x0229c348, 0x7c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229c348 {
    u8 pad_00[0xac];
    u16 unk_AC;
} UnkStruct_0229c348;

extern int func_020984e8(void);
extern u16 *func_020993a8(unsigned int argument0);
extern void func_0206f190(volatile u16 *out, void *a, void *b, void *c);
extern void func_ov096_0229e82c(UnkStruct_0229c348 *self, int a);
extern void func_ov096_0229e6a0(UnkStruct_0229c348 *self);
extern void func_0200467c(int a);

void func_ov096_0229c348(UnkStruct_0229c348 *self)
{
    volatile u16 t[2];
    int ok;
    u16 lo;
    u16 hi;

    t[0] = *func_020993a8((unsigned int) func_020984e8());
    t[1] = self->unk_AC;
    func_0206f190(&t[1], (char *) self + 0x320, (char *) self + 0xe8, (char *) self + 0xc8);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        self->unk_AC = lo;
        func_ov096_0229e82c(self, 1);
    } else {
        func_ov096_0229e6a0(self);
    }
    func_0200467c(0x6b);
}
