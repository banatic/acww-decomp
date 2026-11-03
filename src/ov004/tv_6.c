/* tv_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215ddc @ 0x02215ddc, 0x4 bytes, Thumb
 * func_ov004_02215d80 @ 0x02215d80, 0x5c bytes, Thumb
 * func_ov004_02215d74 @ 0x02215d74, 0xc bytes, Thumb
 * func_ov004_02215d60 @ 0x02215d60, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_02057084(void *argument0, void *argument1, void *argument2, void *argument3, int argument4);
extern int func_020570d4(int argument0, int argument1, int argument2, int argument3, int argument4);
extern int func_ov004_0220e050(char *argument0);
extern int func_ov004_0223b314(void);
extern void *data_ov004_022531d8;
extern void *data_ov004_022531e0;
extern void *data_ov004_022531e8;
extern const u8 data_ov004_02247674[];

int func_ov004_02215ddc(void)
{
    return 1;
}

int func_ov004_02215d80(char *self, int a1)
{
    // DECLS
    int v1;
    int v4;
    // ENDDECLS
    if (a1 != 0x0) {
        v1 = *(int *) (self + 0x594);
        func_02057084((void *) (v1), (void *) (&data_ov004_022531d8), (void *) (func_ov004_0223b314()), (void *) (0x0),
                      (int) (0x0));
    } else {
        v4 = *(int *) (self + 0x594);
        func_020570d4((int) (v4), (int) (&data_ov004_022531d8),
                      (int) (func_ov004_0220e050((char *) ((char *) (self + 0x6cc)))), (int) (&data_ov004_022531e0),
                      (int) (&data_ov004_022531e8));
    }
    return 0x1;
}

void *func_ov004_02215d74(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x864) = 0x1;
    return self;
}

u8 func_ov004_02215d60(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247674[i];
    }
    return 0;
}
