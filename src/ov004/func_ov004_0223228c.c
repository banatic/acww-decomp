/* func_ov004_0223228c @ 0x0223228c, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
} UnkStruct_0223228c;
extern int func_020b65c4(void);
extern void *func_020b6590(void);
extern void *func_020b7d3c(void *, void *, int *, int, int, int, int);

void func_ov004_0223228c(char *self)
{
    int a[3];
    if (func_020b65c4() == 0x22) {
        ((UnkStruct_0223228c *) (self + 0x20))->unk_00 = 1;
    }
    if (((UnkStruct_0223228c *) (self + 0x20))->unk_00 != 0) {
        a[0] = 0x108f6;
        a[1] = 0;
        a[2] = 0x1351e;
        func_020b7d3c(func_020b6590(), self, a, 0xf33, 0x6000, 0x16, 0xff);
    }
}
