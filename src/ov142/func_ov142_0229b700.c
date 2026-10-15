/* func_ov142_0229b700 @ 0x0229b700, 0x104 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;

extern int func_ov002_02208054(void *self, int a);
extern void func_ov142_0229b23c(void *self);
extern int func_ov142_0229a1fc(void *self, int a, int b);
extern int func_ov142_0229a298(void *self, int a);
extern int func_ov142_02299668(void *self, int a);
extern int func_ov142_02299c1c(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_02299928(void *self);
extern void func_ov142_02299918(void *self);
extern void func_ov002_0220a574(void *p);

void func_ov142_0229b700(void *self)
{
    int cond;
    int r6;
    int r4;
    int r1;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov142_0229b23c(self);
        return;
    }

    cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (cond == 0) {
        return;
    }

    r6 = data_021f6c58;
    r4 = data_021f6c54;

    r1 = func_ov142_0229a1fc(self, r6, r4);
    if (r1 != 0x19) {
        func_ov142_0229a298(self, r1);
        return;
    }

    if (func_ov142_02299668(self, 0x100) != 0) {
        return;
    }

    if (func_ov142_02299c1c(self, r6, r4) != 0) {
        func_ov002_02208098((void *) (self), 1);
        return;
    }

    if (r6 < 0xb8 || r6 >= 0xc8) {
        return;
    }

    if (func_ov142_02299668(self, 0x400) == 0) {
        if (r4 >= 0x19 && r4 < 0x29) {
            func_ov142_02299928(self);
            func_ov002_02208098((void *) (self), 3);
            return;
        }
    }

    if (func_ov142_02299668(self, 0x800) == 0) {
        if (r4 >= 0x95 && r4 < 0xa5) {
            func_ov142_02299918(self);
            func_ov002_02208098((void *) (self), 3);
            return;
        }
    }

    if (r4 >= 0x2c && r4 <= 0x86) {
        func_ov002_0220a574((char *) self + 0x14c);
        func_ov002_02208098((void *) (self), 2);
    }
}
