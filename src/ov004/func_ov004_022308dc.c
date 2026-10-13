/* func_ov004_022308dc @ 0x022308dc, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int m[12];
} Mtx;
extern Mtx *func_ov045_02260630(void);
extern void func_0205510c(void *, int);
extern Mtx data_021fbe48;

void func_ov004_022308dc(char *self)
{
    u8 i;
    char *b;
    int z;
    data_021fbe48 = *func_ov045_02260630();
    *(Mtx *) (self + 0x150) = data_021fbe48;
    *(Mtx *) (self + 0x2f4) = data_021fbe48;
    if (*(u8 *) (self + 0x6d4) != 0) {
        func_0205510c(self + 0xec, 0);
    }
    i = 0;
    b = self + 0x290;
    z = i;
    do {
        if (*(u8 *) (self + i + 0x6b0) != 0) {
            func_0205510c(b + i * 0xb8, z);
        }
        i = (u8) (i + 1);
    } while (i < 3);
}
