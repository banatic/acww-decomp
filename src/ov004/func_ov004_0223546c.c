/* func_ov004_0223546c @ 0x0223546c, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern char *data_ov004_022594d4[];
extern void func_0209d238(void *, void *);
extern void func_0209d0a4(void *);

int func_ov004_0223546c(char *self, int i)
{
    char **e;
    if (i < (int) data_ov004_022593a4 || i >= (int) data_ov004_02255c30) {
        return 0;
    }
    e = &data_ov004_022594d4[i];
    if (*e == 0) {
        return 0;
    }
    *(int *) (*e + 0x15c) = i;
    *(int *) (*e + 0x160) = 1;
    func_0209d238(self + 0x7f8, *e + 0x166);
    func_0209d0a4(*e + 0x168);
    return 1;
}
