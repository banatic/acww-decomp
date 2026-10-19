/* func_ov068_02275d98 @ 0x02275d98, 0xbc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0201cfe4(u8 *self, int event);
extern int func_ov068_02275c78(u8 *obj, int a);
extern void *func_0208150c(void *p);
extern int func_0200366c(void *a, void *b, int c, void *d);
extern int func_020644cc(int a);
extern int func_02068484(void *a, u8 *b, void *c);
extern void func_0206844c(void *a, u8 *b, int c);
extern void func_0200467c(int a);
extern u8 data_021f43e8;
extern u8 data_ov068_022788f8[];
extern u8 data_ov068_02278200[];

void func_ov068_02275d98(u8 *self, int event)
{
    u8 a;
    u8 b;
    u8 *obj;
    u8 st;
    obj = *(u8 **) (self + 0x1a4);
    st = obj[0xa5a];
    if (st == 0) {
        func_0201cfe4(self, event);
        return;
    }
    if (obj == 0) {
        return;
    }
    if (st == 1) {
        func_ov068_02275c78(obj, 2);
        return;
    }
    if (st == 6 || st == 8) {
        obj[0xa5a] = 7;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_022788f8, 0x28,
                      data_ov068_02278200);
        a = func_020644cc(3);
        func_02068484(*(void **) (*(u8 **) (self + 0x1a4) + 0x8dc), &a, data_ov068_022788f8);
        return;
    }
    if (st == 7) {
        b = data_021f43e8;
        func_0206844c(*(void **) (*(u8 **) (self + 0x1a4) + 0x8dc), &b, 0);
        func_ov068_02275c78(*(u8 **) (self + 0x1a4), 0xa);
        func_0200467c(0x5f);
    }
}
