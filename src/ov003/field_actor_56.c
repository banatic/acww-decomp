/* field_actor_56: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02218fac @ 0x02218fac, 0x40 bytes, Thumb
 * func_ov003_02218f94 @ 0x02218f94, 0x16 bytes, Thumb
 * func_ov003_02218f80 @ 0x02218f80, 0x14 bytes, Thumb
 * func_ov003_02218f54 @ 0x02218f54, 0x2c bytes, Thumb
 * func_ov003_02218f18 @ 0x02218f18, 0x3c bytes, Thumb
 * func_ov003_02218f0c @ 0x02218f0c, 0xa bytes, Thumb
 */

#include "types.h"

typedef struct {
    int pad_00[3];
} UnkStruct_02218fac;

typedef struct {
    int pad_00[4];
} UnkStruct_02218fac_2;

struct UnkStruct_02218f94 {
    unsigned char pad_00[12];
    unsigned short unk_0C;
};

struct UnkStruct_02218f0c {
    int a;
    int b;
};

extern unsigned int func_0200e92c(UnkStruct_02218fac *);
extern void func_0200e90c(UnkStruct_02218fac *, int, int, int);
extern void func_ov003_02218fec(UnkStruct_02218fac_2 *, int);
extern int func_0200e894(int, UnkStruct_02218fac *);
extern int func_0200e91c(UnkStruct_02218fac *);
extern void func_020109a0(int, int b, int c, unsigned short d);
extern void func_02010f5c(int argument0);
extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_0200c2c8(unsigned int *p);
extern int func_0200f554(unsigned int *p);
extern void func_02010d64(unsigned int *p);
extern unsigned int data_020ccf94;

int func_ov003_02218fac(int a, int b, int c, int d)
{
    UnkStruct_02218fac l1;
    UnkStruct_02218fac_2 l2;
    int result;

    func_0200e92c(&l1);
    func_0200e90c(&l1, 17, c, d);
    func_ov003_02218fec(&l2, b);
    result = func_0200e894(a, &l1);
    func_0200e91c(&l1);
    return result;
}

void func_ov003_02218f94(int a, struct UnkStruct_02218f94 *b, int previous)
{
    func_020109a0(a, 0x9a, b->unk_0C, 0);
}

void func_ov003_02218f80(int a, int b)
{
    func_ov003_02218fac(a, 3, 5, b);
}

void func_ov003_02218f54(void *arg)
{
    void *p = arg;
    func_02010f5c((int) arg);
    if (func_02056f94((char *) p + 0x2d0) != 0) {
        func_020109fc(p, 0, 3, 0);
    }
}

void func_ov003_02218f18(unsigned int *arg0)
{
    func_ov003_02218f54((void *) arg0);
    if (func_02073908(data_020ccf94, arg0[0x200])) {
        func_0200c2c8(arg0);
    } else {
        func_0200f554(arg0);
    }
    func_02010d64(arg0);
}

void func_ov003_02218f0c(u8 *d, struct UnkStruct_02218f0c *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
