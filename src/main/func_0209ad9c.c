/* func_0209ad9c @ 0x0209ad9c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_0209ad9c(void *base, int index)
{
    void *result = 0;
    if (index >= 0 && index < 2) {
        result = (char *) base + index * 48;
    }
    return result;
}
