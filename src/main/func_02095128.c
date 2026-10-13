/* func_02095128 @ 0x02095128, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02095128(unsigned short value, unsigned short *array, int length)
{
    int found;
    int i;

    found = 0;
    if (length != 0 && array != 0) {
        for (i = 0; i < length; array++, i++) {
            if (value == *array) {
                found = 1;
                break;
            }
        }
    }
    return found;
}
