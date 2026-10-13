/* func_020a1224 @ 0x020a1224, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a1224(char *base)
{
    int i = 3;
    do {
        *(base + i + 0xEF) = 0;
    } while (--i >= 0);
}
