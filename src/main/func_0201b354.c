/* func_0201b354 @ 0x0201b354, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201b354(unsigned short *ptr)
{
    int result = 2;
    unsigned short v = *ptr;
    if (v < 100) {
        result = 0;
    } else if (v < 800) {
        result = 1;
    }
    return result;
}
