/* func_020b16fc @ 0x020b16fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f4b08[2];

int func_020b16fc(int arg0)
{
    unsigned int bitmask;
    unsigned int bits;
    int result;

    if (arg0 >= 0x20) {
        bits = data_021f4b08[1];
        bitmask = 1u << (arg0 - 0x20);
        if ((bits & bitmask) != 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        bits = data_021f4b08[0];
        bitmask = 1u << arg0;
        if ((bits & bitmask) != 0) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}
