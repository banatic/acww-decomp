/* field_actor_room_states2_8: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222ad48 @ 0x0222ad48, 0x30 bytes, Thumb
 * func_ov004_0222ad28 @ 0x0222ad28, 0x20 bytes, Thumb
 * func_ov004_0222acf0 @ 0x0222acf0, 0x36 bytes, Thumb
 * func_ov004_0222acc4 @ 0x0222acc4, 0x2c bytes, Thumb
 * func_ov004_0222acc0 @ 0x0222acc0, 0x2 bytes, Thumb
 * func_ov004_0222ac9c @ 0x0222ac9c, 0x24 bytes, Thumb
 * func_ov004_0222ac80 @ 0x0222ac80, 0x1a bytes, Thumb
 * func_ov004_0222ac74 @ 0x0222ac74, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_02056f94(void *argument0);
extern int func_ov004_0222bdf0(int argument0, int argument1, int argument2, int argument3);
extern void func_ov004_0222adcc(int);
extern void func_ov004_0222ad78(int);
extern void func_02010d64(int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern Vec3 data_ov004_02247774;
extern void func_020109fc(int a, int b, int c, int d);
extern void func_0203ab78(Vec3 *v);
extern int func_0200faa8(void *, int);
extern void func_0200fb58(void *, int, int);
extern void func_02010f5c(void *self);

int func_ov004_0222ad48(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02056f94(self + 0x2d0);
    if (v1 != 0x0) {
        return func_ov004_0222bdf0((int) (self), (int) (*(u8 *) (self + 0x7de)), (int) (0x6), (int) (-0x1));
    }
    return v1;
}

void func_ov004_0222ad28(int arg)
{
    func_ov004_0222adcc(arg);
    func_ov004_0222ad78(arg);
    func_02010d64(arg);
    func_ov004_0222ad48((char *) arg);
}

int func_ov004_0222acf0(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x12, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_0222acc4(int a, void *message, int previous)
{
    Vec3 v;
    func_020109fc(a, 0x9b, 3, 0);
    v.x = data_ov004_02247774.x;
    v.y = data_ov004_02247774.y;
    v.z = data_ov004_02247774.z;
    func_0203ab78(&v);
}

void func_ov004_0222acc0(void *callbackObject, int event) {}

void func_ov004_0222ac9c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0200faa8(self, 0x400);
    func_0200fb58(self, *(int *) ((char *) ((void **) &data_ov004_02247774)),
                  *(int *) ((char *) ((void **) &data_ov004_02247774) + 0x8));
}

void func_ov004_0222ac80(void *self)
{
    func_02010f5c(self);
    func_ov004_0222ac9c((char *) self);
    func_02010d64((int) self);
}

void func_ov004_0222ac74(unsigned char *dst, const unsigned int *src, unsigned int val)
{
    *dst = (unsigned char) *src;
    *(dst + 1) = (unsigned char) *(src + 1);
    *(unsigned int *) (dst + 4) = val;
}
