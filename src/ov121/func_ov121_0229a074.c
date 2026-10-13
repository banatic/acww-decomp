/* func_ov121_0229a074 @ 0x0229a074, 0x3e bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

int func_ov121_0229a074(char *self, unsigned int lo, unsigned int hi)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        if (val == hi) {
            func_ov121_02299a4c(self, 0x40);
            *(unsigned char *) (self + 0xb1) = lo;
        } else {
            *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) + 1;
        }
        return 1;
    }
    return 0;
}
