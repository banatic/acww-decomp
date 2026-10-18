/* __sinit_ov032_02260020 @ 0x02260020, 0x1fc bytes, Thumb, module ov032
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;

extern u8 data_ov004_02256914;
extern u8 data_ov032_0226028c[2];
extern Vec data_ov032_022602e4;
extern int data_ov032_0226032c, data_ov032_02260348, data_ov032_02260364, data_ov032_02260380, data_ov032_0226039c,
    data_ov032_022603b8, data_ov032_022603d4;
extern char data_ov032_022602cc, data_ov032_022602f0, data_ov032_02260308, data_ov032_02260320, data_ov032_022602c0,
    data_ov032_022602d8, data_ov032_022602fc, data_ov032_02260314;

extern void func_020012dc(void *object);
extern void func_020b649c(void *object);
extern void func_020b6468(void *self, int id, const Vec *v, unsigned int flags, int a, int b, int c, int d, int e);
extern void __register_global_object(void *obj, void (*dtor)(void *), void *node);

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov032_02260020(void)
{
    Vec t1;
    Vec t2;
    Vec t3;
    Vec t4;
    Vec t5;
    Vec t6;
    Vec t7;

    data_ov032_0226028c[1] = data_ov004_02256914;
    data_ov032_022602e4.x = 0x10000;
    data_ov032_022602e4.y = 0;
    data_ov032_022602e4.z = 0x1d000;
    __register_global_object(&data_ov032_022602e4, func_020012dc, &data_ov032_022602cc);

    t1.x = 0;
    t1.y = 0;
    t1.z = 0;
    func_020b6468(&data_ov032_0226032c, 0x3e, &t1, 0x800000, 0, 2, 2, 0, 4);
    __register_global_object(&data_ov032_0226032c, func_020b649c, &data_ov032_022602f0);

    t2.x = 0xf000;
    t2.y = 0;
    t2.z = 0x1d000;
    func_020b6468(&data_ov032_02260348, 0x7, &t2, 0x10c00000, 16384, 2, 2, (int) 0xffffc000, 1);
    __register_global_object(&data_ov032_02260348, func_020b649c, &data_ov032_02260308);

    t3.x = 0xf000;
    t3.y = 0;
    t3.z = 0x1d000;
    func_020b6468(&data_ov032_02260364, 0x5, &t3, 0x10c00000, 16384, 2, 2, (int) 0xffffc000, 1);
    __register_global_object(&data_ov032_02260364, func_020b649c, &data_ov032_02260320);

    t4.x = 0x17000;
    t4.y = 0;
    t4.z = 0x1a000;
    func_020b6468(&data_ov032_02260380, 0x4, &t4, 0x23800000, (int) 0xffffc000, 2, 2, (int) 0xffffc000, 3);
    __register_global_object(&data_ov032_02260380, func_020b649c, &data_ov032_022602c0);

    t5.x = 0x9000;
    t5.y = 0;
    t5.z = 0x1a000;
    func_020b6468(&data_ov032_0226039c, 0x3, &t5, 0x23800000, 16384, 2, 2, 16384, 3);
    __register_global_object(&data_ov032_0226039c, func_020b649c, &data_ov032_022602d8);

    t6.x = data_ov032_022602e4.x;
    t6.y = data_ov032_022602e4.y;
    t6.z = data_ov032_022602e4.z;
    func_020b6468(&data_ov032_022603b8, 0x2, &t6, 0x23800000, (int) 0xffff8000, 2, 2, (int) 0xffff8000, 3);
    __register_global_object(&data_ov032_022603b8, func_020b649c, &data_ov032_022602fc);

    t7.x = 0;
    t7.y = 0;
    t7.z = 0;
    func_020b6468(&data_ov032_022603d4, 0x3f, &t7, 0x800000, 0, 2, 2, 0, 0);
    __register_global_object(&data_ov032_022603d4, func_020b649c, &data_ov032_02260314);
}

#pragma section INIT end
