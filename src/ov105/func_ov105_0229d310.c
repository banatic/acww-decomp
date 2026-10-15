/* func_ov105_0229d310 @ 0x0229d310, 0x44 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;

int func_ov105_0229d310(void *receiver)
{
    int diff;
    int diff2;

    diff = data_021f6c60 - data_021f6c58;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 8) {
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
