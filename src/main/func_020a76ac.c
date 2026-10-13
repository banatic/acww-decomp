/* func_020a76ac @ 0x020a76ac, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a76ac(unsigned char *out, int a, int b, int c)
{
    *out = (a & 0x07) | (((b << 5) & 0xE0) | (c << 3));
}
