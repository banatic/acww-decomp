/* func_ov104_0229d6a4 @ 0x0229d6a4, 0x44 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;

int func_ov104_0229d6a4(void)
{
    int diff1;
    int diff2;

    diff1 = (int) data_021f6c60 - (int) data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 8) {
        return 1;
    }

    diff2 = (int) data_021f6c5c - (int) data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}
