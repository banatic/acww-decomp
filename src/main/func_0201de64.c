/* func_0201de64 @ 0x0201de64, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_0208150c(u32);
extern u32 func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, u32, int base, int offset, int scale, int multiplier, int selected);
extern u32 func_0207cec0(void *, u32);
extern void func_02015e10(void *, u32, u32);

extern struct {
    u32 a;
    u8 b;
} data_020c8d18;

extern u32 data_021e5a2c;

void func_0201de64(void *self, void *out)
{
    int i;
    u32 v;

    v = *(u32 *) (*(u32 *) ((char *) self + 0x100) + 0x830);

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, func_020036e8((unsigned char *) func_0208150c(v)),
                  data_020c8d18.a, 1, 5, data_020c8d18.b);

    *(u32 *) out = (u32) ((char *) self + 0x104);
    *(u8 *) ((char *) out + 4) = *(u8 *) ((char *) self + 0x122);

    for (i = 0; i < 8; i++) {
        if ((*(u8 *) ((char *) self + 0x194) >> i) & 1) {
            func_02015e10(self, func_0208150c(func_0207cec0(&data_021e5a2c, i)), 0);
            *(u8 *) ((char *) self + 0x194) &= ~(1 << i);
            (*(u32 *) ((char *) self + 0x198))--;
            break;
        }
    }
}
