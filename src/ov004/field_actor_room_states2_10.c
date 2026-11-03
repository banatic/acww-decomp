/* field_actor_room_states2_10: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222af6c @ 0x0222af6c, 0x4e bytes, Thumb
 * func_ov004_0222af58 @ 0x0222af58, 0x14 bytes, Thumb
 * func_ov004_0222af48 @ 0x0222af48, 0x10 bytes, Thumb
 * func_ov004_0222af30 @ 0x0222af30, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct {
    double pad_00;
    char data[4];
} CType;

typedef char DType[16];

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov004_0222afbc(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020779b8(char *p, int b, int c);
extern void func_02077978(void *, int, int);

int func_ov004_0222af6c(void *p0, int p1, int p2, int p3, unsigned char p4, int p5, short p6)
{
    int a;
    CType c;
    DType d;
    int result;

    func_0200e92c(&c);
    func_0200e90c(&c, 0xf, p5, p6);
    a = p4;
    func_ov004_0222afbc(&d, p1, p2, p3, a);
    result = func_0200e894(p0, &c);
    func_0200e91c(&c);
    return result;
}

void func_ov004_0222af58(void *p, int a, int b, short c, unsigned char d)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
    *(short *) ((char *) p + 8) = c;
    *((unsigned char *) p + 0xa) = d;
}

void func_ov004_0222af48(char *self, u8 a, int b, int c)
{
    *self = a;
    func_020779b8(self + 1, b, c);
}

void func_ov004_0222af30(char *self, char *a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (a1) = *(u8 *) (self);
    func_02077978(self + 0x1, a2, a3);
}
