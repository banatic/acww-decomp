/* func_ov142_0229a91c @ 0x0229a91c, 0x38 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a76c(void *a, void *b, int c, int d, int e);

void func_ov142_0229a91c(void *self)
{
    *(short *) ((char *) self + 0xDC) = 0;
    *(short *) ((char *) self + 0xCA) = func_ov142_0229a76c(self, (char *) self + 0x12E8, 0x3984, 0x100, 3);
}
