/* func_020a5430 @ 0x020a5430, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021dc6c4;
extern volatile u8 data_021c75b8;
extern u8 data_021f42ec;
extern u8 data_021f42e8;
extern u16 data_020e3c80;
extern u8 data_021c75b0;
extern u8 data_021f42e0;

extern void func_02074904(int);
extern void func_020a6c08(void);
extern void func_02046600(void);
extern int func_01ffd41c(void *);
extern void func_02041d14(int, int);
extern int func_020edd74(void *);
extern int func_02041c88(int, int, int);

int func_020a5430(u8 *p)
{
    int t;

    func_02074904(0);
    func_020a6c08();
    func_02046600();
    if (!func_01ffd41c(p)) {
        return 0;
    }
    if (data_021dc6c4 != 0) {
        t = (data_021c75b8 == 2);
        if (t) {
            data_021f42ec = 2;
            data_021f42e8 = 0;
            func_02041d14(2, 0x10);
        }
        return 0;
    }
    if (data_020e3c80 != 0xd8) {
        t = (data_021c75b8 == 2);
        if (t || data_021c75b0 != 0) {
            func_02041d14(data_021f42ec, 0xf);
        }
        return 0;
    }
    if (p[0x13] & 1) {
        if (func_020edd74(p) == 0) {
            p[0x13] &= ~1;
            p[0x13] &= ~4;
        } else {
            return 0;
        }
    }
    if (data_021f42e0 != 0) {
        t = (data_021c75b8 == 0);
        if (t) {
            data_021f42e0--;
            if (data_021f42e0 == 0) {
                if (func_02041c88(data_021f42e8, 0xf, 0) == 0) {
                    data_021f42e0 = 1;
                }
            }
        }
    }
    return 1;
}
