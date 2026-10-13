/* func_ov142_0229a7e0 @ 0x0229a7e0, 0x6c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a76c(char *self, void *dst, unsigned long src, unsigned long size, int flag);

void func_ov142_0229a7e0(char *self)
{
    unsigned long total;
    unsigned long ret;

    *(unsigned short *) (self + 0xe0) = 0;

    ret = func_ov142_0229a76c(self, self + 0x1528, 0x3fa4, 0x40, 5);
    total = ret;
    ret = func_ov142_0229a76c(self, self + 0x1528 + total * 2, 0x40a4, 0x20, 5);
    total += ret;
    ret = func_ov142_0229a76c(self, self + 0x1528 + total * 2, 0x4124, 0x40, 5);
    total += ret;

    *(unsigned short *) (self + 0xce) = total;
}
