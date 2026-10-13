/* func_ov003_02230604 @ 0x02230604, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230660(void *a, int b, int c, int d, unsigned char e, unsigned char f);

void func_ov003_02230604(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x15:
            func_ov003_02230660(self, 0xc8, 0x3c, 0x28, 0x14, 1);
            break;
        case 0x16:
            func_ov003_02230660(self, 0xc8, 0x28, 0x2d, 0x1e, 3);
            break;
        case 0x17:
            func_ov003_02230660(self, 0x64, 0x46, 0x32, 0x78, 0x1e);
            break;
    }
}
