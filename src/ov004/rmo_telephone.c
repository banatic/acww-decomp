/* rmo_telephone: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230d94 @ 0x02230d94, 0x24 bytes, Thumb
 * func_ov004_02230d70 @ 0x02230d70, 0x24 bytes, Thumb
 * func_ov004_02230d30 @ 0x02230d30, 0x40 bytes, Thumb
 * func_ov004_02230ce4 @ 0x02230ce4, 0x4c bytes, Thumb
 * func_ov004_02230c98 @ 0x02230c98, 0x4c bytes, Thumb
 */

#include "types.h"

extern void func_ov004_0223121c(void *argument0, int argument1);
extern void *data_ov004_022588c8;
extern void func_02055060(void *, int, int, int, int, int);
extern int func_ov004_0222c3c4(void *, int);

int func_ov004_02230d94(void)
{
    char *p = (*(char **) &data_ov004_022588c8);
    if (p != 0) {
        if (*(u8 *) (p + 0x63c) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_ov004_02230d70(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_ov004_0223121c((void *) (*(int *) ((char *) &data_ov004_022588c8)), (int) (0xa));
        return 0x1;
    }
    return 0x0;
}

void func_ov004_02230d30(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_02055060((char *) *(int *) ((char *) &data_ov004_022588c8) + 0xec,
                      func_ov004_0222c3c4((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x1a4, 0x0), 0x1, 0x1000, 0x0,
                      0x0);
    }
}

void func_ov004_02230ce4(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_02055060((char *) *(int *) ((char *) &data_ov004_022588c8) + 0xec,
                      func_ov004_0222c3c4((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x1a4, 0x0), 0x3, 0x1000,
                      ((u32) (*(int *) ((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x18c) << 4) >> 16), 0x0);
    }
}

void func_ov004_02230c98(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_02055060((char *) *(int *) ((char *) &data_ov004_022588c8) + 0xec,
                      func_ov004_0222c3c4((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x1a4, 0x0), 0x1, 0x1000,
                      ((u32) (*(int *) ((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x18c) << 4) >> 16), 0x0);
    }
}
