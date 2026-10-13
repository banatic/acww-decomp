/* func_ov121_0229a00c @ 0x0229a00c, 0x2a bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

int func_ov121_0229a00c(char *self, unsigned int lo, unsigned int hi, int r3)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) + (r3 - lo);
        return 1;
    }
    return 0;
}
