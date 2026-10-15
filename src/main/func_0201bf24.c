/* func_0201bf24 @ 0x0201bf24, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 func_020b65c4(void);
extern int func_020851a0(u16 *p, int a, void *b, int c, void *d, void *e);
extern int data_020ccf94;
extern u8 func_02073dd4(const u8 *data, int index);
extern int func_0201c0e0(void *self);
extern u16 func_0201c444(void *ptr);
extern void func_020771cc(int a, void *out, int c, int d);

void func_0201bf24(void *self, int param2)
{
    u8 *s = (u8 *) self;
    u8 flag = func_020b65c4();
    int g;

    func_020851a0((u16 *) (s + 0xea), flag, s + 0x5c, *(short *) (s + 0x8e), s + 0x568, s + 0x62d);

    g = data_020ccf94;
    if (func_02073dd4((const u8 *) g, *(int *) ((u8 *) g + 0x64)) == 0) {
        return;
    }
    if (func_0201c0e0(self) == 0) {
        return;
    }

    {
        int nibble = (*(u16 *) (s + 0xea) & 0xf000) >> 12;

        if (nibble == 14) {
            int v = func_0201c444(self) + 0xc;
            func_020771cc(v, &param2, 0, 0);
        } else if (nibble == 13) {
            int v = func_0201c444(self) + 0x20;
            func_020771cc(v, &param2, 0, 0);
        }
    }
}
