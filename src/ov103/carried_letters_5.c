/* carried_letters_5: 2 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229cb1c @ 0x0229cb1c, 0x44 bytes, Thumb
 * func_ov103_0229cb08 @ 0x0229cb08, 0x14 bytes, Thumb
 */

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c30;

int func_ov103_0229cb1c(void *receiver)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 8) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}

int func_ov103_0229cb08(int unused, int param)
{
    if (data_021f6c30 < param) {
        return 0;
    }
    return 1;
}
