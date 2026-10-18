/* __sinit_ov021_02260020 @ 0x02260020, 0x204 bytes, Thumb, module ov021
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;

extern u8 data_ov004_02256914;
extern u8 data_ov021_022602a4[2];
extern Vec data_ov021_02260304;
extern int data_ov021_0226034c, data_ov021_02260368, data_ov021_02260384, data_ov021_022603a0, data_ov021_022603bc,
    data_ov021_022603d8, data_ov021_022603f4;
extern char data_ov021_022602ec, data_ov021_02260310, data_ov021_02260328, data_ov021_02260334, data_ov021_022602e0,
    data_ov021_022602f8, data_ov021_0226031c, data_ov021_02260340;

extern void func_020012dc(void *object);
extern void func_020b649c(void *object);
extern void func_020b6468(void *self, int id, const Vec *v, unsigned int flags, int a, int b, int c, int d, int e);
extern void __register_global_object(void *obj, void (*dtor)(void *), void *node);

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov021_02260020(void)
{
    Vec t1;
    Vec t2;
    Vec t3;
    Vec t4;
    Vec t5;
    Vec t6;
    Vec t7;

    data_ov021_022602a4[1] = data_ov004_02256914;
    data_ov021_02260304.x = 0x10000;
    data_ov021_02260304.y = 0x200;
    data_ov021_02260304.z = 0x1d000;
    __register_global_object(&data_ov021_02260304, func_020012dc, &data_ov021_022602ec);

    t1.x = 0;
    t1.y = 0;
    t1.z = 0;
    func_020b6468(&data_ov021_0226034c, 0x3c, &t1, 0x800000, 0, 2, 2, 0, 4);
    __register_global_object(&data_ov021_0226034c, func_020b649c, &data_ov021_02260310);

    t2.x = 0x1b000;
    t2.y = 0;
    t2.z = 0x1a000;
    func_020b6468(&data_ov021_02260368, 0x21, &t2, 0x23800000, (int) 0xffffc000, 2, 2, (int) 0xffffc000, 2);
    __register_global_object(&data_ov021_02260368, func_020b649c, &data_ov021_02260328);

    t3.x = 0x1b000;
    t3.y = 0;
    t3.z = 0x1e000;
    func_020b6468(&data_ov021_02260384, 0x29, &t3, 0x23800000, (int) 0xffffc000, 2, 2, (int) 0xffffc000, 3);
    __register_global_object(&data_ov021_02260384, func_020b649c, &data_ov021_02260334);

    t4.x = data_ov021_02260304.x;
    t4.y = data_ov021_02260304.y;
    t4.z = data_ov021_02260304.z;
    func_020b6468(&data_ov021_022603a0, 0x22, &t4, 0x23800000, (int) 0xffff8000, 2, 2, (int) 0xffff8000, 1);
    __register_global_object(&data_ov021_022603a0, func_020b649c, &data_ov021_022602e0);

    t5.x = 0x16000;
    t5.y = 0;
    t5.z = 0x1d000;
    func_020b6468(&data_ov021_022603bc, 0x27, &t5, 0x23800000, (int) 0xffff8000, 2, 2, (int) 0xffff8000, 3);
    __register_global_object(&data_ov021_022603bc, func_020b649c, &data_ov021_022602f8);

    t6.x = 0x5000;
    t6.y = 0;
    t6.z = 0x1a000;
    func_020b6468(&data_ov021_022603d8, 0x25, &t6, 0x23800000, 16384, 2, 2, 16384, 3);
    __register_global_object(&data_ov021_022603d8, func_020b649c, &data_ov021_0226031c);

    t7.x = 0x5000;
    t7.y = 0;
    t7.z = 0x1a000;
    func_020b6468(&data_ov021_022603f4, 0x23, &t7, 0x23800000, 16384, 2, 2, 16384, 3);
    __register_global_object(&data_ov021_022603f4, func_020b649c, &data_ov021_02260340);
}

#pragma section INIT end
