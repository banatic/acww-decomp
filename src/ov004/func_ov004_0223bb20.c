/* func_ov004_0223bb20 @ 0x0223bb20, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd58(void *tbl, unsigned int i);
extern int func_ov004_0220ccf8(void *self, int idx);
extern void func_ov004_0220e578(u16 *dst, void *p);
extern int func_ov004_0220fde0(void *self);
extern u16 func_0204bc50(int x, int y);

int func_ov004_0223bb20(unsigned int idx, u16 *pb, u16 *pc)
{
    u16 tmp;
    void *o;
    if (pb != 0) {
        *pb = 0xfff1;
    }
    if (pc != 0) {
        *pc = 0xfff1;
    }
    o = (void *) func_ov004_0223cd58(func_ov004_0223ce84(), idx);
    if (o != 0) {
        func_ov004_0220ccf8(o, 5);
        if (pb != 0) {
            func_ov004_0220e578(&tmp, o);
            *pb = tmp;
        }
        if (pc != 0) {
            *pc = func_0204bc50(func_ov004_0220fde0(o), 0);
        }
        return 1;
    }
    return 0;
}
