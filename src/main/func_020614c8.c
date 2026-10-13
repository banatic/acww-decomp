/* func_020614c8 @ 0x020614c8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020614c8(unsigned short *ptr)
{
    int i = 0;
    do {
        *ptr++ = 0xfff1;
        i++;
    } while (i < 256);
}
