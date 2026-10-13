/* func_ov121_0229ad68 @ 0x0229ad68, 0x44 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;

int func_ov121_0229ad68(void)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 0x10) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 0x10) {
        return 1;
    }

    return 0;
}
