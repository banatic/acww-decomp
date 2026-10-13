/* func_0202d5fc @ 0x0202d5fc, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_020644cc(u32 a);
extern void func_02063ccc(u32 *out, u32 a, u32 b);
extern void func_020638d4(u16 *status, u32 *buf, u32 p, int a, int b, int c, void *d);
extern void func_02063884(u16 *out, u32 *buf);
extern void func_02063cc8(void *p);

typedef struct {
    u32 a;
    u32 b;
} Elem;

void func_0202d5fc(u16 *out, Elem *arr, u32 param, u32 param4)
{
    u16 status[2];
    u32 val;
    u32 buf14[2];
    u32 buf1c[2];
    u32 buf24[2];
    u32 buf2c[2];
    u32 idx;

    idx = func_020644cc(param);
    *out = 0xfff1;
    arr += idx;
    val = arr->b;
    func_02063ccc(buf14, arr->a, arr->b);
    buf24[0] = buf14[0];
    buf24[1] = buf14[1];
    func_020638d4(status, buf24, param4, 0, 1, 1, &val);
    *out = status[0];
    func_02063cc8(buf24);
    if (*out == 0xfff1) {
        func_02063ccc(buf1c, arr->a, val);
        buf2c[0] = buf1c[0];
        buf2c[1] = buf1c[1];
        func_02063884(&status[1], buf2c);
        *out = status[1];
        func_02063cc8(buf2c);
        func_02063cc8(buf1c);
    }
    func_02063cc8(buf14);
}
