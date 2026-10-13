/* func_ov142_0229a8e8 @ 0x0229a8e8, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a76c(void *a, void *b, int c, int d, int e);

void func_ov142_0229a8e8(char *self)
{
    *(unsigned short *) (self + 0xde) = 0;
    *(unsigned short *) (self + 0xcc) = (unsigned short) func_ov142_0229a76c(self, self + 0x14e8, 0x3e24, 0x20, 4);
}
