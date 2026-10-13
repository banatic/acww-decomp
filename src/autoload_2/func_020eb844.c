/* func_020eb844 @ 0x020eb844, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbf3c;
extern unsigned short data_021fbefc;

unsigned int func_020eb844(void)
{
    unsigned int result;
    unsigned short value;

    value = data_021fbefc;
    if (value < 4) {
        result = 0;
    } else {
        result = data_021fbf3c;
    }
    return result;
}
