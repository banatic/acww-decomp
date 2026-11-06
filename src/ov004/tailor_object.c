/* tailor_object: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222fdb8 @ 0x0222fdb8, 0x24 bytes, Thumb
 * func_ov004_0222fd94 @ 0x0222fd94, 0x24 bytes, Thumb
 * func_ov004_0222fd70 @ 0x0222fd70, 0x24 bytes, Thumb
 * func_ov004_0222fd58 @ 0x0222fd58, 0x18 bytes, Thumb
 * func_ov004_0222fd38 @ 0x0222fd38, 0x20 bytes, Thumb
 */

#include "types.h"

typedef int (*Fn)(void *self, int k);

extern void *data_ov004_02258558;

int func_ov004_0222fdb8(void)
{
    void *p = data_ov004_02258558;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 1);
    }
    return 0;
}

int func_ov004_0222fd94(void)
{
    void *p = data_ov004_02258558;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 3);
    }
    return 0;
}

int func_ov004_0222fd70(void)
{
    char *p = (*(char **) &data_ov004_02258558);
    if (p != 0) {
        int v = *(u8 *) (p + 0x24c);
        if (v == 3 || v == 0) {
            return 1;
        }
    }
    return 0;
}

void func_ov004_0222fd58(int v)
{
    char *p = (*(char **) &data_ov004_02258558);
    if (p != 0) {
        *(int *) (p + 0x334) = v << 12;
    }
}

int func_ov004_0222fd38(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258558) != 0x0) {
        return ((u32) (*(int *) ((char *) *(int *) ((char *) &data_ov004_02258558) + 0x334) << 4) >> 16);
    }
    return 0x0;
}
