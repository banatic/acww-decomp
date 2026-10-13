/* func_020765cc @ 0x020765cc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern u8 data_021e5a2c[];

extern void func_020736bc(void *h, u8 *out, int n);
extern void func_02078448(int *out, volatile u16 *id, u8 *buf);
extern int func_0207cec0(u8 *tbl, int key);
extern void func_02080cd8(int a, volatile u16 *id);

void func_020765cc(void)
{
    volatile u16 id;
    u8 buf[3];
    int out;
    int r;

    id = 0xfff1;
    func_020736bc(data_020ccf94, buf, 3);
    func_02078448(&out, &id, buf);
    r = func_0207cec0(data_021e5a2c, out);
    if (r != 0) {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x11a8 && hi <= 0x12a7) {
            ok = 1;
        }
        if (ok > 0) {
            func_02080cd8(r, &id);
        }
    }
}
