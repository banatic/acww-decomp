/* func_0201ab70 @ 0x0201ab70, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201ab70(char *ptr, int value)
{
    int abs_value;
    short max;

    if (value < 0) {
        abs_value = -value;
    } else {
        abs_value = value;
    }
    max = *(short *) (ptr + 0x20);
    if (abs_value > max) {
        if (value >= 0) {
            value = max;
        } else {
            value = (short) (-max);
        }
    }
    return value;
}
