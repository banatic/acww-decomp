/* house_visitor_5: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02275e54 @ 0x02275e54, 0x24 bytes, Thumb
 * func_ov068_02275d98 @ 0x02275d98, 0xbc bytes, Thumb
 * func_ov068_02275d74 @ 0x02275d74, 0x24 bytes, Thumb
 */

#include "types.h"

extern void func_0201d140(void *p, int q);
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
extern void func_0201ce68(void *p, int q);

void func_ov068_02275e54(unsigned char *p, int q)
{
    if (*(unsigned char *) (*(int *) (p + 0x1a4) + 0xa5a) == 0) {
        func_0201d140(p, q);
    }
}

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

void func_ov068_02275d74(unsigned char *p, int q)
{
    if (*(unsigned char *) (*(int *) (p + 0x1a4) + 0xa5a) == 0) {
        func_0201ce68(p, q);
    }
}
