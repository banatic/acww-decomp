/* func_ov107_0229c9e4 @ 0x0229c9e4, 0xc4 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb9];
    volatile u8 unk_B9;
} UnkStruct_0229c9e4;

extern void func_0206f9c0(UnkStruct_0229c9e4 *self);
extern int func_ov107_0229d0f0(UnkStruct_0229c9e4 *self, int k);
extern int func_0206fca4(void);
extern void func_ov002_02208d4c(void *p, int a, int b);
extern int func_ov094_022999e4(int id);

void func_ov107_0229c9e4(UnkStruct_0229c9e4 *self)
{
    volatile u16 t;
    unsigned int ok;
    u16 lo;
    u16 hi;
    int id;
    int k;

    func_0206f9c0(self);
    id = func_ov107_0229d0f0(self, self->unk_B9);
    t = id;
    k = func_0206fca4();
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x12b0 && lo <= 0x12e7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 0);
    } else if (lo >= 0x12e8 && lo <= 0x131f) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 2);
    } else if (k == 0x2a) {
        func_ov002_02208d4c((char *) self + 0x2700, 0x10, 3);
    }
    if (func_ov094_022999e4(id) != 0) {
        if (k == 0x2a) {
            func_ov002_02208d4c((char *) self + 0x2700, 1, 1);
        } else {
            func_ov002_02208d4c((char *) self + 0x2700, 0x10, 1);
        }
    }
    func_ov002_02208d4c((char *) self + 0x2700, 2, 4);
}
