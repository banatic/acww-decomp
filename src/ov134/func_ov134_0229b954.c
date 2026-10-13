/* func_ov134_0229b954 @ 0x0229b954, 0xbc bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021fbe94;
extern u8 data_ov134_0229c3f4[];
extern u8 data_ov134_0229c410[];
extern u8 data_ov134_0229c42c[];
extern u32 data_ov134_0229c020[];
extern void func_02002d14(void *data, void *obj, int a, int b, int c, int d);
extern void func_02002c6c(void *data, void *obj, int a, int b, int c, int d);
extern u32 func_02064b2c(u32 val, void *obj, int mask, u32 *out);
extern u64 _s32_div_f(int a, int b);
extern void func_02002a88(u32 addr, int a, int b, int c, int d);
extern void func_020e993c(void *obj, u32 val);
extern void func_02002cd8(void *data, void *obj, int a, int b, int c);
typedef struct {
    u8 pad_00[0xa1];
    u8 b;
} Params;
void func_ov134_0229b954(Params *p)
{
    u32 prev;
    u32 unused;
    u32 addr;
    u32 offset;
    int i;
    u8 byte;
    void *obj;
    long long q;
    u32 hi;
    obj = data_021fbe94;
    func_02002d14(data_ov134_0229c3f4, obj, 8, 4, 4, 10);
    func_02002c6c(data_ov134_0229c410, obj, 8, 0xc0, 0xc0, 0x1df);
    byte = p->b;
    prev = func_02064b2c(data_ov134_0229c020[((unsigned int) byte) >> 2], obj, -4, &unused);
    q = _s32_div_f(byte, 4);
    hi = (u32) (q >> 32);
    addr = prev;
    addr = addr + (hi << 8);
    offset = 0xc0;
    i = 0;
    for (; i < 8; i++) {
        func_02002a88(addr, 8, offset, offset, offset + 7);
        addr += 0x400;
        offset += 0x20 ^ 0;
    }

    func_020e993c(obj, prev);
    func_02002cd8(data_ov134_0229c42c, obj, 8, p->b, 4);
}
