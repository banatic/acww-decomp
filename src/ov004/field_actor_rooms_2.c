/* field_actor_rooms_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02226c6c @ 0x02226c6c, 0x12 bytes, Thumb
 * func_ov004_02226c2c @ 0x02226c2c, 0x40 bytes, Thumb
 * func_ov004_02226c08 @ 0x02226c08, 0x24 bytes, Thumb
 * func_ov004_02226c00 @ 0x02226c00, 0x8 bytes, Thumb
 * func_ov004_02226bf8 @ 0x02226bf8, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_02226c6c;

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_02226c2c;

typedef struct {
    int x, y, z;
} UnkStruct_02226c2c_2;

typedef struct {
    int a, b, c;
} Triple;

extern unsigned int func_0200e92c(UnkStruct_02226c2c *t);
extern void func_0200e90c(UnkStruct_02226c2c *t, int x, int y, int z);
extern int func_0200e894(void *self, UnkStruct_02226c2c *t);
extern int func_0200e91c(UnkStruct_02226c2c *t);
extern void func_020779b8(unsigned char *parameter0, int parameter1, int parameter2);
extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);

void func_ov004_02226c6c(int *d, UnkStruct_02226c6c v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}

int func_ov004_02226c2c(void *self, UnkStruct_02226c2c_2 *v, int c, int d)
{
    UnkStruct_02226c2c t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x8b, c, d);
    func_ov004_02226c6c((int *) t.b, *(UnkStruct_02226c6c *) &(*v));
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}

void func_ov004_02226c08(char *self, Triple v, int extent, u8 g, u8 h)
{
    *(int *) (self) = v.a;
    *(int *) (self + 4) = v.b;
    *(int *) (self + 8) = v.c;
    *(int *) (self + 0xc) = 0;
    *(int *) (self + 0x10) = extent;
    *(u8 *) (self + 0x14) = g;
    *(u8 *) (self + 0x15) = h;
}

void func_ov004_02226c00(unsigned char *arg0, int arg1, int arg2)
{
    func_020779b8((unsigned char *) arg0, arg1, arg2);
}

void func_ov004_02226bf8(void *arg0, unsigned int *arg1, int arg2)
{
    func_02077978((void *) arg0, (unsigned int *) arg1, arg2);
}
