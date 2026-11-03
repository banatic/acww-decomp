/* cafe_props: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222db14 @ 0x0222db14, 0x44 bytes, Thumb
 * func_ov004_0222daf0 @ 0x0222daf0, 0x24 bytes, Thumb
 * func_ov004_0222dad8 @ 0x0222dad8, 0x18 bytes, Thumb
 */

#include "types.h"

extern int func_02054ecc(int);
extern int func_ov004_0222c3c4(int, int);
extern void func_02055060(int, int, unsigned char, int, unsigned short, unsigned short);
extern void *data_ov004_02258310;

void func_ov004_0222db14(int unused, int p1, int p2, int p3, unsigned char p4, int p5, unsigned short p6, unsigned short p7)
{
    if (func_02054ecc(p2) != func_ov004_0222c3c4(p3, p1)) {
        func_02055060(p2, func_ov004_0222c3c4(p3, p1), p4, p5, p6, p7);
    }
}

void func_ov004_0222daf0(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef6) = 0x1;
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef7) = 0x1;
    }
}

void func_ov004_0222dad8(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef8) = 0x1;
    }
}
