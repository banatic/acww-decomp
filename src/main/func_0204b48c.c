/* func_0204b48c @ 0x0204b48c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b48c(unsigned short *addr, unsigned short low, unsigned short high)
{
    unsigned short value;
    int result;

    result = 0;
    value = *addr;
    if (value >= low && value <= high) {
        result = 1;
    }
    return result;
}
