/* func_0200e86c @ 0x0200e86c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

char *func_0200e86c(char *base, int index)
{
    if (index >= 0 && index < 30 && index < *(int *) (base + 0xc7c)) {
        return base + 0x934 + 28 * index;
    }
    return 0;
}
