/* func_ov004_02246378 @ 0x02246378, 0x178 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern u16 func_0204bc50(int a, int b);
extern void __register_global_object(void *o, void *destructor, void *n);
extern void func_020051b0(void *p);
extern void *func_0204f5e0(void *g, int qx, int qy, int rx, int ry, int k);
extern int func_0204bc90(void *p);
extern int func_0204bd08(void *p);
extern void *func_ov004_0223cd50(void);
extern u16 *func_ov004_0223cc10(void *a, int x, int y, int k);
extern int func_ov004_0220fde0(void *p);
extern int func_ov004_022464f0(u16 *p);
extern void *data_021c80bc;
extern u16 data_ov004_0225ff04;
extern u16 data_ov004_0225ff08;
extern int data_ov004_0225ff10;
extern int data_ov004_0225ff14;
extern int data_ov004_0225ff18;
extern int data_ov004_0225ff24;

u16 *func_ov004_02246378(int x, int y)
{
    // DECLS
    u16 *it;
    u16 *e;
    int qx;
    int qy;
    int t1;
    int ok;
    // ENDDECLS
    u16 buf[6];

    if ((data_ov004_0225ff14 & 1) == 0) {
        data_ov004_0225ff04 = 0xfff1;
        __register_global_object(&data_ov004_0225ff04, ((void *) &func_020051b0), &data_ov004_0225ff24);
        data_ov004_0225ff14 |= 1;
    }
    if (data_021c80bc != 0) {
        qx = x >> 4;
        qy = y >> 4;
        it = (u16 *) func_0204f5e0(data_021c80bc, qx, qy, x - (qx << 4), y - (qy << 4), 0);
        if (it != 0) {
            if (func_0204bcdc(it) != 0) {
                buf[1] = 0xfff1;
                t1 = func_0204bc64(it);
                ok = (t1 == func_0204bc64(&buf[1])) ? 1 : 0;
            } else {
                ok = (*it == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                if (func_0204bc90(it) != 0) {
                    e = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
                    if (e == 0) {
                        return &data_ov004_0225ff04;
                    }
                    if ((data_ov004_0225ff10 & 1) == 0) {
                        data_ov004_0225ff08 = 0xfff1;
                        __register_global_object(&data_ov004_0225ff08, ((void *) &func_020051b0), &data_ov004_0225ff18);
                        data_ov004_0225ff10 |= 1;
                    }
                    data_ov004_0225ff08 = func_0204bc50(func_ov004_0220fde0(e), 0);
                    if (func_ov004_022464f0(&data_ov004_0225ff08) != 0) {
                        return &data_ov004_0225ff08;
                    }
                } else if (func_0204bd08(it) != 0) {
                    if (func_0204bcdc(it) != 0) {
                        buf[2] = 0x1547;
                        t1 = func_0204bc64(it);
                        ok = (t1 == func_0204bc64(&buf[2])) ? 1 : 0;
                    } else {
                        ok = (*it == 0x1547) ? 1 : 0;
                    }
                    if (ok == 0 && func_ov004_022464f0(it) != 0) {
                        return it;
                    }
                }
            }
        }
    }
    return &data_ov004_0225ff04;
}
