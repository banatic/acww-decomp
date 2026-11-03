/* chest: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02216cf8 @ 0x02216cf8, 0x24 bytes, Thumb
 * func_ov004_02216cf4 @ 0x02216cf4, 0x4 bytes, Thumb
 * func_ov004_02216cd0 @ 0x02216cd0, 0x24 bytes, Thumb
 * func_ov004_02216c8c @ 0x02216c8c, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02216cf8;

struct UnkStruct_02216cf8_2;

struct UnkStruct_02216cf8 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_02216cf8_2 {
    char pad_00[300];
    struct UnkStruct_02216cf8 *b;
};

struct UnkStruct_02216c8c {
    u8 pad_00[4];
};

extern int func_ov004_02217124(struct UnkStruct_02216cf8_2 *, int);
extern int func_ov004_02217230(struct UnkStruct_02216c8c *self);
extern int func_ov004_0222c00c(int *p);
extern int func_02052738(struct UnkStruct_02216c8c *self, int a, int b, int c);

void func_ov004_02216cf8(struct UnkStruct_02216cf8_2 *self)
{
    struct UnkStruct_02216cf8 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_02217124(self, 10);
        }
    }
}

int func_ov004_02216cf4(void *callbackObject)
{
    return 1;
}

void func_ov004_02216cd0(void *self)
{
    void *p = *(void **) ((char *) self + 0x12c);
    if (p != 0 && *(void **) ((char *) p + 4) == 0) {
        func_ov004_02217124((struct UnkStruct_02216cf8_2 *) self, 0xb);
    }
}

int func_ov004_02216c8c(struct UnkStruct_02216c8c *self)
{
    int v;

    v = func_ov004_02217230(self);
    if (v != -1) {
        if (func_ov004_0222c00c(&v)) {
            return func_02052738(self, 3, 0xff, 1);
        }
        return 0;
    }
    return func_02052738(self, 3, 0xff, 1);
}
