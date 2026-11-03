/* barber_machine: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c904 @ 0x0222c904, 0x30 bytes, Thumb
 * func_ov004_0222c8f4 @ 0x0222c8f4, 0x10 bytes, Thumb
 * func_ov004_0222c8c8 @ 0x0222c8c8, 0x2c bytes, Thumb
 */

#include "types.h"

extern int func_020321bc(void *, int, int, int, void *, int, int);
extern int func_02032180(void *);
extern int func_0209d3f8(void *argument0, unsigned char argument1);
extern void *data_ov004_02258224;

int func_ov004_0222c904(char *self)
{
    // DECLS
    // ENDDECLS
    return func_020321bc(self + 0x2d8, 0x2000, 0x4000, 0x2000, self + 0x5c, 0x0, 0x0);
}

int func_ov004_0222c8f4(char *self)
{
    // DECLS
    // ENDDECLS
    return func_02032180(self + 0x2d8);
}

int func_ov004_0222c8c8(void)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_0209d3f8((void *) (*(int *) ((char *) &data_ov004_02258224)), (unsigned char) (0x1));
    if (v2 != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258224) + 0x374) = 0x1;
        return 0x374;
    }
    return v2;
}
