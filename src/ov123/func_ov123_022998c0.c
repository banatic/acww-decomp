/* func_ov123_022998c0 @ 0x022998c0, 0x70 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229b160(void *param, unsigned char val);
extern unsigned char data_021fbe40[];

int func_ov123_022998c0(unsigned char *param)
{
    unsigned short keys = ((unsigned short *) data_021fbe40)[1];
    unsigned char b;

    if (keys & 0x200) {
        b = param[0xa2];
        if (b > 1) {
            func_ov123_0229b160(param, b - 1);
        } else {
            func_ov123_0229b160(param, 15);
        }
        return 1;
    }
    if (keys & 0x100) {
        b = param[0xa2];
        if (b < 15) {
            func_ov123_0229b160(param, b + 1);
        } else {
            func_ov123_0229b160(param, 1);
        }
        return 1;
    }
    return 0;
}
