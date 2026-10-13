/* func_ov114_0229c7d0 @ 0x0229c7d0, 0xc0 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u64 _s32_div_f(int, int);
extern void func_02064328(void *, void *, void *, int, int, int);
extern void func_02002c6c(void *, void *, int, int, int, int);
extern void func_02002cd8(void *, void *, int, int, int);

extern u8 data_ov114_0229db68[];
extern u8 data_ov114_0229db78[];
extern u8 data_ov114_0229db88[];
extern u8 data_ov114_0229db9c[];
extern void *data_021fbe94;
extern void *data_ov114_0229dce0;
extern u8 data_ov114_0229dce8[];

void func_ov114_0229c7d0(void *self)
{
    unsigned char *s = (unsigned char *) self;
    u8 val = s[0x12b8];
    u8 sw;
    u64 res1, res2;
    u32 low;
    u8 rem;
    void *ptr;

    if (val == 0xff) {
        return;
    }

    res1 = _s32_div_f(val, 12);
    low = (u32) res1;
    ptr = data_021fbe94;

    sw = s[0x12b7];
    switch (sw) {
        case 0:
            data_ov114_0229dce0 = data_ov114_0229db68;
            break;
        case 1:
            data_ov114_0229dce0 = data_ov114_0229db78;
            break;
        default:
            return;
    }

    func_02064328(data_ov114_0229dce8, data_ov114_0229db88, data_ov114_0229dce0, low, low, val);
    func_02002c6c(data_ov114_0229dce8, ptr, s[0x12b3], 0x11, 0x11, 0xa0);
    func_02064328(data_ov114_0229dce8, data_ov114_0229db9c, data_ov114_0229dce0, low, low, val);

    res2 = _s32_div_f(val, 12);
    rem = (u8) ((u32) (res2 >> 32));
    func_02002cd8(data_ov114_0229dce8, ptr, s[0x12b3], rem, 5);
}
