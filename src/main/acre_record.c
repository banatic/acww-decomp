/* acre_record: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037da8 @ 0x02037da8, 0x64 bytes, Thumb
 * func_02037d9c @ 0x02037d9c, 0xc bytes, Thumb
 * func_02037d80 @ 0x02037d80, 0x1c bytes, Thumb
 * func_02037d64 @ 0x02037d64, 0x1a bytes, Thumb
 * func_02037d48 @ 0x02037d48, 0x1a bytes, Thumb
 * func_02037d2c @ 0x02037d2c, 0x1a bytes, Thumb
 * func_02037d14 @ 0x02037d14, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} Owner;

extern int func_02037e0c(int, int, int, u8);
extern int func_02037bd8(int a);
extern int func_02037c9c(void *obj, int b, int c);
extern int func_02037c78(void *obj, int b, int c);

void func_02037d14(int *r0, int *r1, int r2);

int func_02037da8(int p0, int *p1, int *p2, u16 *p3, u16 *p4, u8 b5)
{
    u16 *p;
    int found;

    p = (u16 *) func_02037e0c(p0, 0, 0, b5);
    found = 0;
    if (p != 0) {
        int i = found;
        while (i < 0x100) {
            u16 hi = *p4;
            unsigned int ok = found;
            u16 cur = *p;
            u16 lo = *p3;
            if (cur >= lo && cur <= hi) {
                ok = 1;
            }
            if (ok != 0) {
                func_02037d14(p1, p2, i);
                found = 1;
                break;
            }
            p++;
            i++;
        }
    }
    return found;
}

int func_02037d9c(int *p)
{
    return func_02037bd8(*p);
}

int func_02037d80(unsigned int param1, unsigned int param2)
{
    unsigned int result;
    unsigned int temp;

    temp = func_02037d9c((int *) param1);
    result = param2 & temp;
    if (param2 == result) {
        return 1;
    } else {
        return 0;
    }
}

int func_02037d64(int a, int b)
{
    int r4;
    r4 = b;
    r4 = r4 & func_02037d9c((int *) a);
    if (r4 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02037d48(Owner *self, int b, int c)
{
    int result;

    result = 0;
    if (self->unk_24 != 0) {
        result = func_02037c9c(self->unk_24, b, c);
    }
    return result;
}

int func_02037d2c(Owner *self, int b, int c)
{
    int result;

    result = 0;
    if (self->unk_24 != 0) {
        result = func_02037c78(self->unk_24, b, c);
    }
    return result;
}

void func_02037d14(int *r0, int *r1, int r2)
{
    int r4;
    int r0_val;
    r4 = r2 & 0xf;
    *r0 = r4;
    r0_val = (r2 >> 4) & 0xf;
    *r1 = r0_val;
}
