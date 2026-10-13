/* func_020997b4 @ 0x020997b4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020997b4(unsigned char *data, int value)
{
    unsigned char *p = data + 0x243d;
    *p = (*p & ~0x38) | ((value & 7) << 3);
}
