/* func_ov003_022306a0 @ 0x022306a0, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230734(void *a, int b, int c, int d, unsigned char e);

void func_ov003_022306a0(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1d:
            func_ov003_02230734(self, 0x3c, 0x46, 6, 1);
            break;
        case 0x1b:
            func_ov003_02230734(self, 0x3c, 0x46, 6, 1);
            break;
        case 0xc:
            func_ov003_02230734(self, 0x3c, 0x50, 8, 2);
            break;
        case 0xd:
            func_ov003_02230734(self, 0x3c, 0x50, 8, 3);
            break;
        case 0x1c:
            func_ov003_02230734(self, 0x3c, 0x46, 8, 1);
            break;
    }
}
