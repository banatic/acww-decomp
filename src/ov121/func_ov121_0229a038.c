/* func_ov121_0229a038 @ 0x0229a038, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_02299a4c(unsigned short *object, unsigned short mask);

int func_ov121_0229a038(char *self, unsigned int lo, unsigned int hi)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        if (val == lo) {
            *(unsigned char *) (self + 0xb1) = hi;
            func_ov121_02299a4c((unsigned short *) self, 0x20);
        } else {
            *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) - 1;
        }
        return 1;
    }
    return 0;
}
