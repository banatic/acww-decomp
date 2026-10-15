/* func_02044750 @ 0x02044750, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern void *data_020ccf94;
extern char data_021dc7a8[];

extern int func_02044808(void *);
extern int func_0204cafc(void *);
extern int func_0204c878(void *);
extern int func_0205be38(void);
extern int func_020644cc(int);
extern void func_0204cb2c(void *);

void func_02044750(u16 *out0, u8 *out1, u16 arg2)
{
    if (func_02044808(*(void **) ((char *) data_020ccf94 + 0x68)) == 0x136a) {
        volatile u16 v = 0xfff1;
        v = arg2;
        {
            unsigned int ok = 0;
            char *base;
            u16 a = v;
            u16 b = v;
            if (b >= 0x1492 && a <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                *out0 = 0x26;
                *out1 = 0;
                base = data_021dc7a8;
                if (func_0204cafc(base + 0x17254)) {
                    int x = func_0204c878((void *) &v);
                    int y = func_0205be38();
                    x = x / 1000;
                    y = y / 0x19;
                    x += y;
                    if (x > 0x64) {
                        x = 0x64;
                    }
                    if (func_020644cc(0x64) < x) {
                        *out0 = 0x57;
                        func_0204cb2c(base + 0x17254);
                    }
                }
            }
        }
    }
}
