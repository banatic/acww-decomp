/* func_02079c00 @ 0x02079c00, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079ca4(signed char *base, int index, int value);

void func_02079c00(signed char *base, int index, int value)
{
    int sum;
    if (func_02079ca4(base, index, value)) {
        sum = base[index] + value;
        if (sum > 127) {
            sum = 127;
        } else if (sum < -128) {
            sum = -128;
        }
        base[index] = (signed char) sum;
    }
}
