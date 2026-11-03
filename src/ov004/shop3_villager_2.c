/* shop3_villager_2: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02221a30 @ 0x02221a30, 0x34 bytes, Thumb
 * func_ov004_02221a2c @ 0x02221a2c, 0x4 bytes, Thumb
 * func_ov004_022219f4 @ 0x022219f4, 0x38 bytes, Thumb
 * func_ov004_022219c8 @ 0x022219c8, 0x2c bytes, Thumb
 * func_ov004_022219c4 @ 0x022219c4, 0x4 bytes, Thumb
 * func_ov004_022219ac @ 0x022219ac, 0x18 bytes, Thumb
 * func_ov004_02221994 @ 0x02221994, 0x18 bytes, Thumb
 * func_ov004_02221974 @ 0x02221974, 0x20 bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *argument0, int argument1, int argument2, int argument3, int argument4, short argument5,
                         short argument6, int argument7, int argument8, unsigned short argument9, unsigned short argument10);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov004_02221a64(void *, int);
extern void *func_0202decc(void *arg);
extern int data_ov004_02253f44;
extern void *func_0202de4c(void *);
extern void func_020edb3c(void *);

int func_ov004_02221a30(char *param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov004_02221a2c(void)
{
    return 1;
}

int func_ov004_022219f4(u8 *self)
{
    int n;
    int v;

    n = func_02016104(self + 0x89c);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 0);
    return 1;
}

int func_ov004_022219c8(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov004_02221a64(self, 1);
    }
    return 1;
}

int func_ov004_022219c4(void)
{
    return 1;
}

void *func_ov004_022219ac(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253f44;
    return arg;
}

void *func_ov004_02221994(void *arg)
{
    *((void **) arg) = &data_ov004_02253f44;
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_02221974(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02253f44);
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
