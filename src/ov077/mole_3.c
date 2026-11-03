/* mole_3: 7 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_02279354 @ 0x02279354, 0x4 bytes, Thumb
 * func_ov077_02279350 @ 0x02279350, 0x4 bytes, Thumb
 * func_ov077_02279318 @ 0x02279318, 0x38 bytes, Thumb
 * func_ov077_022792e4 @ 0x022792e4, 0x34 bytes, Thumb
 * func_ov077_022792e0 @ 0x022792e0, 0x4 bytes, Thumb
 * func_ov077_022792dc @ 0x022792dc, 0x4 bytes, Thumb
 * func_ov077_02279234 @ 0x02279234, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02279234 UnkStruct_02279234;

struct UnkStruct_02279234 {
    u8 unk_00[0x564];
    u8 unk_564[0x71c - 0x564];
    u8 unk_71C[4];
    u8 unk_720[4];
};

extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(int *ptr);
extern void func_ov077_02279358(int *ptr, int val);
extern int func_02019c20(u8 *, int, int, int, int, int);
extern int func_0204f490(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f800(u8 *, u8 *, int, int, int, int);
extern u8 data_020e54a8;
extern void *data_021c80bc;

int func_ov077_02279354(void)
{
    return 1;
}

int func_ov077_02279350(void)
{
    return 1;
}

int func_ov077_02279318(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov077_022792e4(int *self)
{
    int *base;
    int result;

    base = (int *) ((char *) self + 0x618);
    result = func_02014868(base);
    if (result != 0) {
        return 1;
    }

    base = (int *) ((char *) self + 0x618);
    result = func_02014868(base);
    if (result == 0) {
        func_ov077_02279358(self, 5);
    }

    return 1;
}

int func_ov077_022792e0(void)
{
    return 1;
}

int func_ov077_022792dc(void)
{
    return 1;
}

int func_ov077_02279234(UnkStruct_02279234 *self)
{
    u16 h[2];
    int a, b, c, d;
    unsigned int ok;
    void *p;

    func_02019c20(self->unk_564, 1, 0xfd, 1, 0, 0);
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        p = data_021c80bc;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        if (p != 0) {
            h[0] = 0x5014;
            h[1] = 0x501a;
            if (func_0204f490(p, &a, &b, &c, &d, &h[0], &h[1], 1, 0) != 0) {
                func_0204f800(self->unk_71C, self->unk_720, a, b, c, d);
            }
        }
    }
    return 1;
}
